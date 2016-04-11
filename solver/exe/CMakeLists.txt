
message(STATUS "Added the following executables:")

add_executable(hello hello.cpp)
message(STATUS "  hello")

add_executable(graph graph.cpp)
target_link_libraries(graph structure)
message(STATUS "  graph")



