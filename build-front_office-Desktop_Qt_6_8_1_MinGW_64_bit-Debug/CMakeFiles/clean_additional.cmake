# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\front_office_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\front_office_autogen.dir\\ParseCache.txt"
  "front_office_autogen"
  )
endif()
