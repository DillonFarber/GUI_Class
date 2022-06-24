# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\assignment_3_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\assignment_3_autogen.dir\\ParseCache.txt"
  "assignment_3_autogen"
  )
endif()
