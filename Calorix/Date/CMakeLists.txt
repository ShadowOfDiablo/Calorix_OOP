file(GLOB DATE_SOURCES "src/*")
add_library(Date STATIC ${DATE_SOURCES})
target_include_directories(Date PUBLIC inc)