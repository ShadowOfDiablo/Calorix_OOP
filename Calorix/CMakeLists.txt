cmake_minimum_required(VERSION 3.16)

project(Calorix)

add_subdirectory(Date)
add_subdirectory(Exercises)
add_subdirectory(FileManager)
add_subdirectory(FitnessGoal)
add_subdirectory(Food)
add_subdirectory(UsersLogic)

add_executable(calorix Calorix.cpp)

target_link_libraries(calorix PRIVATE Date Exercises FileManager FitnessGoal Food UsersLogic)
