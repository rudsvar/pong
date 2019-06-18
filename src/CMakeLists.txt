find_package(Curses REQUIRED)
find_package(Threads REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(Game game.c ball.c util.c)
target_include_directories(Game PRIVATE ${PROJECT_SOURCE_DIR}/include)
add_library(Util util.c)
add_executable(server server.c)
add_executable(client client.c)

target_link_libraries(server Game Util Threads::Threads)
target_link_libraries(client Game Util ${CURSES_LIBRARIES})
