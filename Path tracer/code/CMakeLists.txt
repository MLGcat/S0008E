PROJECT(code)
FILE(GLOB code_headers *.h)
FILE(GLOB code_sources *.cpp)

SET(files_code ${code_headers} ${code_sources})
SOURCE_GROUP("code" FILES ${files_code})

ADD_EXECUTABLE(code ${files_code})
TARGET_LINK_LIBRARIES(code core render)
ADD_DEPENDENCIES(code core render)
