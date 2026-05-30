file(GLOB FILE_MANAGER_SOURCES "src/*")
add_library(FileManager STATIC ${FILE_MANAGER_SOURCES})
target_include_directories(FileManager PUBLIC inc)
target_link_libraries(FileManager PUBLIC UsersLogic Food Exercises FitnessGoal Date)