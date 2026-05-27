file(GLOB FILE_MANAGER_SOURCES "src/*")
add_library(FileManager STATIC ${FILE_MANAGER_SOURCES})
target_include_directories(FileManager PUBLIC inc)