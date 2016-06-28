
cmake_minimum_required(VERSION 2.8.11 FATAL_ERROR)

project(procon27 CXX)


# in-sourceビルドの禁止
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_DISABLE_SOURCE_CHANGES  ON)

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(FATAL_ERROR "In-sourceビルドは許可されていません.")
endif()

# コンパイラ表示
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER}")

# C++コンパイル設定
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")        # C++14を有効化
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")     # enable all warnings
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-sign-compare") # disable some warnings
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-type-limits")  # disable some warnings
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")     # enable all SSE and AVX

# OpenCVのパッケージ検索
set(CMAKE_PREFIX_PATH /usr/local/opt/qt5)
find_package(OpenCV)
if(OpenCV_FOUND)
  MESSAGE(STATUS "Found 'OpenCV' : ${OpenCV_VERSION}")
  add_definitions(-DFIND_OPENCV)
endif()


# Qt5存在確認
find_package(Qt5Widgets)
if(Qt5Widgets_FOUND)
  message(STATUS "Found 'Qt5 library' : ${Qt5Widgets_VERSION}")
else()
  message(STATUS "Notfound 'Qt5 library'")
endif()

# 出力先を設定
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin CACHE PATH "Output directory for executables")
set(LIBRARY_OUTPUT_PATH    ${CMAKE_BINARY_DIR}/lib CACHE PATH "Output directory for libraries")

# サブディレクトリ追加
add_subdirectory(modules)
add_subdirectory(exe)





