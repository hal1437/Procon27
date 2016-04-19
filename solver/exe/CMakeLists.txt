
message(STATUS "Added the following executables:")

add_executable(hello hello.cpp)
message(STATUS "  hello")

add_executable(graph graph.cpp)
target_link_libraries(graph structure)
message(STATUS "  graph")

add_executable(opencv_test opencv_test.cpp)
target_link_libraries(opencv_test ${OpenCV_LIBS})
target_link_libraries(opencv_test structure)
message(STATUS "  opencv_test")

add_executable(capture_test capture_test.cpp)
target_link_libraries(capture_test ${OpenCV_LIBS})
message(STATUS "  capture_test")




