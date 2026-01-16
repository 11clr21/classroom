#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include "idatabase.h"
#include <QTimer>
#include <QFileDialog>
#include <QTextStream>
#include <QFile>
#include <QDateTime>
#include <QDate>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 1. 【初始化组件】设置一个很大的可选范围
    ui->dateTimeEdit->setDisplayFormat("yyyy-MM-dd");
    ui->dateTimeEdit->setCalendarPopup(true); // 弹出日历选择器
    ui->dateTimeEdit->setDateRange(QDate(2000, 1, 1), QDate(2100, 12, 31));

    // 2. 预加载数据库中所有的日期
    fetchAvailableDates();

    // --- 初始化班级列表 ---
    classTableModel = new QSqlTableModel(this);
    classTableModel->setTable("class_room"); // 设置要操作的表名

    // 【可选】设置表头显示的中文名称，默认会显示数据库里的英文字段名
    classTableModel->setHeaderData(1, Qt::Horizontal, "班级名称");
    classTableModel->setHeaderData(2, Qt::Horizontal, "教室号");
    classTableModel->setHeaderData(3, Qt::Horizontal, "校区");

    // 执行查询（相当于 SELECT * FROM class_room）
    classTableModel->select();

    // 把模型设置给 TableView 组件
    ui->classList->setModel(classTableModel);

    // 【美化】让表格列宽自适应内容，或者平均分布
    ui->classList->resizeColumnsToContents();
    ui->classList->setSelectionBehavior(QAbstractItemView::SelectRows);

    m_scrollTimer = new QTimer(this);
    connect(m_scrollTimer, &QTimer::timeout, this, &MainWindow::updateScrollingNotice);

    // 设置滚动速度，200毫秒刷新一次，数字越小滚动越快
    m_scrollTimer->start(1000);
}

// 查询且缓存用户选中的日期
void MainWindow::fetchAvailableDates()
{
    QSqlDatabase db = IDatabase::getInstance().getDatabase();
    if (!db.isOpen()) return;

    QSqlQuery query(db);
    query.exec("SELECT DISTINCT course_date FROM course_info");

    if (query.lastError().isValid()) {
        qDebug() << "SQL worng:" << query.lastError().text();
    } else {
        qDebug() << "SQL success and find" << query.size() << "records";
    }

    availableDates.clear();

    while (query.next()) {
        QString dateStr = query.value("course_date").toString();
        QDate d = QDate::fromString(dateStr, "yyyy-MM-dd");

        // 确保日期转换成然后添加
        if (d.isValid()) {
            availableDates.append(d);
        }
    }

    // 开始自动锁定有课的第一天
    if (!availableDates.isEmpty()) {
        ui->dateTimeEdit->setDate(availableDates.first());
    } else {
        qDebug() << "no course";
    }
}

// 核心拦截函数：当用户修改日期时触发查询和显示
void MainWindow::on_dateTimeEdit_dateChanged(const QDate &date)
{
    // 检查这个日期是否在我们的“可用列表”里
    if (availableDates.contains(date)) {
        qDebug() << "choose date:" << date.toString("yyyy-MM-dd");

        // 1. 更新成员变量，保存当前选中的日期
        currentSelectedDate = date;

        // 2. 【核心逻辑】直接查询
        QSqlDatabase db = IDatabase::getInstance().getDatabase();
        if (db.isOpen()) {
            QSqlQuery query(db);

            QString dateStr = date.toString("yyyy-MM-dd");

            QString sql = QString("SELECT notice_title FROM notice_info WHERE publish_time = '%1'").arg(dateStr);

            qDebug() << "拼接后的 SQL:" << sql; // 调试用

            // 直接执行
            if (query.exec(sql)) {
                if (query.next()) {
                    // 【修改点】获取的时候也要用 'notice_title'
                    QString titleContent = query.value("notice_title").toString();
                    qDebug() << "the notice is:" << titleContent;

                    // 显示到 Label 上
                    m_originalNotice = titleContent;
                    ui->notice_label->setText(m_originalNotice);

                } else {
                    qDebug() << "this day not have notice";
                    ui->notice_label->setText("暂无公告");
                }
            } else {
                qDebug() << "find notice error:" << query.lastError().text();
            }
        }

        // 当日期改变时，根据之前的选择刷新课程信息
        // 检查用户之前是否选择了教室
        if (!currentRoomNumber.isEmpty()) {
            queryRoomCourseInfo(); // 调用教室查询
        }
        // 如果没有选择教室，再检查是否选择了班级
        else if (!currentClassName.isEmpty()) {
            queryClassCourseInfo(); // 调用班级查询
        }
        // 如果两者都为空，说明用户只是改变了日期，没有选择具体对象，可以不做任何操作
        else {
            qDebug() << "日期已更改，但未选择具体的教室或班级，不执行课程查询。";
            ui->course_text->clear(); // 可以选择清空显示区域
            ui->next_course_text->clear();
        }

    } else {
        // 无效日期处理
        qDebug() << "Invalid date, auto rollback.";
        ui->dateTimeEdit->blockSignals(true);
        if (!availableDates.isEmpty()) {
            ui->dateTimeEdit->setDate(availableDates.first());
        }
        ui->dateTimeEdit->blockSignals(false);
    }
}

void MainWindow::on_classList_clicked(const QModelIndex &index)
{
    int row = index.row();

    // 获取教室号 (第3列，索引是2)
    QString roomNumber = classTableModel->data(classTableModel->index(row, 2)).toString();
    currentRoomNumber = roomNumber;

    // 获取班级名称 (第2列，索引是1)
    QString className = classTableModel->data(classTableModel->index(row, 1)).toString();
    currentClassName = className; // 保存班级名称

    qDebug() << "你点击了班级，教室号:" << currentRoomNumber;
    qDebug() << "你点击的班级名称:" << currentClassName;
    qDebug() << "当前选中的日期:" << currentSelectedDate;

    queryRoomCourseInfo();
    queryClassCourseInfo();
}

// 查询指定教室在指定日期的课程
void MainWindow::queryRoomCourseInfo() {
    // 检查日期和教室号是否有效
    if (!currentSelectedDate.isValid() || currentRoomNumber.isEmpty()) {
        ui->course_text->setText("请先选择日期和教室");
        qDebug() << "无效的日期或教室号";
        return;
    }

    QSqlDatabase db = IDatabase::getInstance().getDatabase();
    if (!db.isOpen()) {
        ui->course_text->setText("数据库连接失败");
        return;
    }

    QSqlQuery query(db);
    QString dateStr = currentSelectedDate.toString("yyyy-MM-dd");

    // 使用 JOIN 连接两个表，连接条件是 course_room = room_number
    QString sql = QString(
                      "SELECT ci.course_name, ci.course_room, ci.start_time, ci.end_time, ci.teacher_name, cr.class_name "
                      "FROM course_info AS ci "
                      "INNER JOIN class_room AS cr ON ci.course_room = cr.room_number "
                      "WHERE ci.course_date = '%1' AND ci.course_room = '%2' "
                      "ORDER BY ci.start_time ASC"
                      ).arg(dateStr).arg(currentRoomNumber);

    qDebug() << "查询教室课程的 SQL:" << sql;

    if (query.exec(sql)) {
        ui->course_text->clear();
        QString displayText;
        bool hasCourse = false;

        while (query.next()) {
            hasCourse = true;
            QString courseName = query.value("course_name").toString();
            QString courseRoom = query.value("course_room").toString();
            QString startTime = query.value("start_time").toString();
            QString endTime = query.value("end_time").toString();
            QString teacherName = query.value("teacher_name").toString();
            QString className = query.value("class_name").toString(); // 从 class_room 表获取

            displayText += QString("时间: %1 - %2\n").arg(startTime).arg(endTime);
            displayText += QString("课程: %1\n").arg(courseName);
            displayText += QString("教师: %1\n").arg(teacherName);
            displayText += QString("班级: %1\n").arg(className);
            displayText += QString("教室: %1\n").arg(courseRoom);
            displayText += "------------------\n";
        }

        if (hasCourse) {
            ui->course_text->setText(displayText);
        } else {
            ui->course_text->setText(QString("%1 教室在 %2 没有安排课程")
                                         .arg(currentRoomNumber).arg(dateStr));
        }

    } else {
        qDebug() << "查询教室课程失败:" << query.lastError().text();
        ui->course_text->setText("查询数据库出错");
    }
}

// 查询指定班级在指定日期的课程
void MainWindow::queryClassCourseInfo() {
    // 检查日期和班级名称是否有效
    if (!currentSelectedDate.isValid() || currentClassName.isEmpty()) {
        ui->next_course_text->setPlainText("请先选择日期和班级");

        qDebug() << "无效的日期或班级名称";
        return;
    }


    QSqlDatabase db = IDatabase::getInstance().getDatabase();
    if (!db.isOpen()) {
        ui->next_course_text->setPlainText("数据库连接失败");
        return;
    }


    QSqlQuery query(db);
    QString dateStr = currentSelectedDate.toString("yyyy-MM-dd");

    // 连接条件改为 class_id = id
    // 确保 course_info 表中确实存在 class_id 字段，且与 class_room 的 id 对应
    QString sql1 = QString(
                       "SELECT ci.course_name, ci.course_room, ci.start_time, ci.end_time, ci.teacher_name, cr.class_name "
                       "FROM course_info AS ci "
                       "INNER JOIN class_room AS cr ON ci.class_id = cr.id "
                       "WHERE ci.course_date = '%1' AND cr.class_name = '%2' "
                       "ORDER BY ci.start_time ASC"
                       ).arg(dateStr).arg(currentClassName);

    qDebug() << "查询班级课程的 SQL:" << sql1;

    if (query.exec(sql1)) {
        qDebug() << "查询执行成功";

        ui->next_course_text->clear();
        QString displayText;
        bool hasCourse = false;

        while (query.next()) {
            hasCourse = true;
            QString courseName = query.value("course_name").toString();
            QString courseRoom = query.value("course_room").toString();
            QString startTime = query.value("start_time").toString();
            QString endTime = query.value("end_time").toString();
            QString teacherName = query.value("teacher_name").toString();
            QString className = query.value("class_name").toString(); // 从 class_room 表获取

            displayText += QString("时间: %1 - %2\n").arg(startTime).arg(endTime);
            displayText += QString("课程: %1\n").arg(courseName);
            displayText += QString("教师: %1\n").arg(teacherName);
            displayText += QString("班级: %1\n").arg(className);
            displayText += QString("教室: %1\n").arg(courseRoom);
            displayText += "------------------\n";
        }

        if (hasCourse) {
            qDebug() << "查询到课程，显示内容";
            ui->next_course_text->setPlainText(displayText);
        } else {
            qDebug() << "查询到课程，但没有课程";
            ui->next_course_text->setPlainText(QString("%1 班级在 %2 没有安排课程")
                                                   .arg(currentClassName).arg(dateStr));
        }

    } else {
        qDebug() << "查询班级课程失败:" << query.lastError().text();
        ui->next_course_text->setPlainText("查询数据库出错");
    }
}

void MainWindow::on_findclassNumber_clicked()
{
    // 1. 获取用户在 classnumber_text 输入框中的内容
    QString inputRoom = ui->classnumber_text->text().trimmed();

    // 2. 如果输入为空，则清除筛选条件，显示所有数据
    if (inputRoom.isEmpty()) {
        classTableModel->setFilter("");
        classTableModel->select();
        qDebug() << "输入为空，已重置显示所有班级";
        return;
    }

    // 3. 设置 SQL 过滤条件
    QString filter = QString("room_number = '%1'").arg(inputRoom);

    // 4. 应用筛选到模型
    classTableModel->setFilter(filter);

    // 5. 执行查询并刷新界面
    if (classTableModel->select()) {
        qDebug() << "筛选成功，找到" << classTableModel->rowCount() << "条记录";
    } else {
        qDebug() << "筛选失败:" << classTableModel->lastError().text();
    }
}

void MainWindow::on_findclassName_clicked()
{
    // 1. 获取用户在 classnumber_text 输入框中的内容
    QString inputRoom = ui->classname_text->text().trimmed();

    // 2. 如果输入为空，则清除筛选条件，显示所有数据
    if (inputRoom.isEmpty()) {
        classTableModel->setFilter("");
        classTableModel->select();
        qDebug() << "输入为空，已重置显示所有班级";
        return;
    }

    // 3. 设置 SQL 过滤条件
    QString filter = QString("class_name = '%1'").arg(inputRoom);

    // 4. 应用筛选到模型
    classTableModel->setFilter(filter);

    // 5. 执行查询并刷新界面
    if (classTableModel->select()) {
        qDebug() << "筛选成功，找到" << classTableModel->rowCount() << "条记录";
    } else {
        qDebug() << "筛选失败:" << classTableModel->lastError().text();
    }
}

void MainWindow::updateScrollingNotice()
{
    QString currentText = ui->notice_label->text();

    // 1. 如果文本为空，或者文本已经是占位符，就不滚动
    if (currentText.isEmpty() || currentText.contains("暂无公告")) {
        return;
    }

    // 2. 执行“跑马灯”操作：
    // 取出第一个字符，拼接到字符串末尾，实现向左移动的效果
    // 例如 "ABC" -> "BCA" -> "CAB" -> "ABC"
    QChar firstChar = currentText.at(0);
    currentText = currentText.mid(1) + firstChar;

    // 3. 更新 Label 显示
    ui->notice_label->setText(currentText);
}

// 【修改版】刷新按钮点击事件：包含时间显示和全数据刷新
void MainWindow::on_updata_clicked()
{
    // --- 功能 1：显示刷新时的当前时间 ---
    QDateTime currentTime = QDateTime::currentDateTime();
    ui->newtime->setText(currentTime.toString("yyyy-MM-dd hh:mm:ss"));

    qDebug() << "begin update the data……";

    // --- 功能 2：刷新班级列表 ---
    if (classTableModel->select()) {
        qDebug() << "班级列表刷新成功，当前共有" << classTableModel->rowCount() << "个班级";
        ui->classList->resizeColumnsToContents();
    } else {
        qDebug() << "班级列表刷新失败:" << classTableModel->lastError().text();
    }

    // --- 功能 3：刷新可用日期 ---
    fetchAvailableDates();

    // --- 功能 4：根据当前状态刷新详情 ---
    if (currentSelectedDate.isValid()) {
        QSqlDatabase db = IDatabase::getInstance().getDatabase();
        if (db.isOpen()) {
            QSqlQuery query(db);
            QString dateStr = currentSelectedDate.toString("yyyy-MM-dd");

            // 刷新公告
            QString noticeSql = QString("SELECT notice_title FROM notice_info WHERE publish_time = '%1'").arg(dateStr);
            if (query.exec(noticeSql)) {
                if (query.next()) {
                    ui->notice_label->setText(query.value("notice_title").toString());
                } else {
                    ui->notice_label->setText("暂无公告");
                }
            }
        }

        // 刷新教室课程信息
        if (!currentRoomNumber.isEmpty()) {
            queryRoomCourseInfo();
        }
        // 刷新班级课程信息
        else if (!currentClassName.isEmpty()) {
            queryClassCourseInfo();
        }
        else {
            ui->course_text->clear();
            ui->next_course_text->clear();
        }
    } else {
        qDebug() << "当前未选中有效日期，仅刷新列表。";
    }

    qDebug() << "数据刷新完成。";
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 【修改版】保存教室课程信息 (course_text) 到文件
void MainWindow::on_createfile1_clicked()
{
    QString content = ui->course_text->toPlainText();

    if (content.isEmpty()) {
        QMessageBox::warning(this, "提示", "当前没有可保存的教室课程信息！");
        return;
    }

    QString defaultFileName = QString("教室课程表_%1.txt").arg(QDate::currentDate().toString("yyyyMMdd"));
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    "保存课程信息",
                                                    defaultFileName,
                                                    "文本文件 (*.txt);;所有文件 (*)");

    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
        out.setEncoding(QStringConverter::Utf8);
#else
        out.setCodec("UTF-8");
#endif

        out << content;
        file.close();

        QMessageBox::information(this, "成功", "教室课程信息已成功保存！");
    } else {
        QMessageBox::critical(this, "错误", "无法保存文件，请检查权限或路径。\n" + file.errorString());
    }
}

// 【修改版】保存班级课程信息 (next_course_text) 到文件
void MainWindow::on_createfile2_clicked()
{
    QString content = ui->next_course_text->toPlainText();

    if (content.isEmpty()) {
        QMessageBox::warning(this, "提示", "当前没有可保存的班级课程信息！");
        return;
    }

    // 修改默认文件名为 "班级课程表"，方便区分
    QString defaultFileName = QString("班级课程表_%1.txt").arg(QDate::currentDate().toString("yyyyMMdd"));
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    "保存课程信息",
                                                    defaultFileName,
                                                    "文本文件 (*.txt);;所有文件 (*)");

    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
        out.setEncoding(QStringConverter::Utf8);
#else
        out.setCodec("UTF-8");
#endif

        out << content;
        file.close();

        QMessageBox::information(this, "成功", "班级课程信息已成功保存！");
    } else {
        QMessageBox::critical(this, "错误", "无法保存文件，请检查权限或路径。\n" + file.errorString());
    }
}

