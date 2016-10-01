
message(STATUS "Added the following executables:")

add_executable(hello hello.cpp)
target_link_libraries(hello util)
message(STATUS "  hello")

add_executable(graph graph.cpp)
target_link_libraries(graph structure)
target_link_libraries(graph util)
target_link_libraries(graph ${OpenCV_LIBS})
message(STATUS "  graph")

add_executable(opencv_test opencv_test.cpp)
target_link_libraries(opencv_test structure)
target_link_libraries(opencv_test ${OpenCV_LIBS})
message(STATUS "  opencv_test")

add_executable(capture_test capture_test.cpp)
target_link_libraries(capture_test ${OpenCV_LIBS})
target_link_libraries(capture_test util)
message(STATUS "  capture_test")

if(TBB_FOUND)
  add_executable(TBB_test TBB_test.cpp)
  target_link_libraries(TBB_test ${TBB_LIBRARIES})
  message(STATUS "  TBB_test")
endif()

if(ArrayFire_FOUND)
  add_executable(ArrayFire_test ArrayFireTest.cpp)
  target_link_libraries(ArrayFire_test ${ArrayFire_LIBRARIES})
  message(STATUS "  ArrayFire_test")
endif()

add_executable(matrix matrix.cpp)
target_link_libraries(matrix structure)
target_link_libraries(matrix ${OpenCV_LIBS})
message(STATUS "  matrix")

add_executable(sequence SequenceSearch.cpp)
target_link_libraries(sequence structure)
target_link_libraries(sequence search)
target_link_libraries(sequence ${OpenCV_LIBS})
message(STATUS "  sequence")

add_executable(limited LimitedSearch.cpp)
target_link_libraries(limited structure)
target_link_libraries(limited search)
target_link_libraries(limited ${OpenCV_LIBS})
if(TBB_FOUND)
  target_link_libraries(limited ${TBB_LIBRARIES})
endif()
message(STATUS "  limited")

