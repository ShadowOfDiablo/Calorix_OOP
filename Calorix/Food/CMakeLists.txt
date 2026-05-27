file(GLOB FOOD_SOURCES "src/*")
add_library(Food STATIC ${FOOD_SOURCES})
target_include_directories(Food PUBLIC inc)
target_link_libraries(Food PUBLIC Date)