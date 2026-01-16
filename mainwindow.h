#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qdatetime.h>
#include <qsqltablemodel.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void fetchAvailableDates();

    void queryCourseInfo();    //查询课程信息并显示

    void queryRoomCourseInfo();// 查询教室课程

    void queryClassCourseInfo(); // 查询班级课程




private slots:
    void on_dateTimeEdit_dateChanged(const QDate &date);

    void on_classList_clicked(const QModelIndex &index);

    void on_updata_clicked();

    void on_createfile1_clicked();

    void on_createfile2_clicked();

    void on_findclassNumber_clicked();

    void on_findclassName_clicked();

    void updateScrollingNotice(); // 【新增】滚动公告的槽函数



    void on_notice_label_linkActivated(const QString &link);

private:
    Ui::MainWindow *ui;

    QList<QDate> availableDates;// 定义一个列表变量来存储数据库中存储的日期

    QDate currentSelectedDate;// 定义一个成员变量来存储用户当前选中的日期

    QSqlTableModel *classTableModel; // 专门用来显示 class_room 表的模型

    QString currentRoomNumber;      // 【新增】记住教室号

    QSqlTableModel *courseTableModel; // 【新增】右侧课程模型

    QString currentClassName; // 新增的班级名称变量

    QTimer *m_scrollTimer;   // 定时器

    QString m_originalNotice; // 保存完整的公告文本




};
#endif // MAINWINDOW_H
