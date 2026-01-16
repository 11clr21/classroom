# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Classroom_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Classroom_autogen.dir\\ParseCache.txt"
  "Classroom_autogen"
  )
endif()
