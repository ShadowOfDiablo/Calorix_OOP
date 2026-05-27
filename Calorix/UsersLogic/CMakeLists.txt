file(GLOB USERS_LOGIC_SOURCES "*/src/*")
add_library(UsersLogic STATIC ${USERS_LOGIC_SOURCES})
target_include_directories(UsersLogic PUBLIC */inc/*)