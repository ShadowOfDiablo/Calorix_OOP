file(GLOB USERS_LOGIC_SOURCES "*/src/*")
add_library(UsersLogic STATIC ${USERS_LOGIC_SOURCES})
target_include_directories(UsersLogic PUBLIC 
Admin/inc
Trainee/inc
User/inc
Calorix/inc
UserProfile/inc
)

target_link_libraries(UsersLogic PUBLIC Date Food Exercises FitnessGoal)