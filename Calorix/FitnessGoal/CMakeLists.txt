file(GLOB FITNESS_GOAL_SOURCES "src/*")
add_library(FitnessGoal STATIC ${FITNESS_GOAL_SOURCES})
target_include_directories(FitnessGoal PUBLIC inc)
target_link_libraries(FitnessGoal PUBLIC Date)