file(GLOB EXERCISES_SOURCES "src/*")
add_library(Exercises STATIC ${EXERCISES_SOURCES})
target_include_directories(Exercises PUBLIC inc)
target_link_libraries(Exercises PUBLIC Date)