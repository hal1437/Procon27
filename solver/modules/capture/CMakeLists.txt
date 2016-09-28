
# ライブラリ追加
file(GLOB STRUCTURE_SOURCES src/*.cpp include/capture/*.h include/capture/*.hpp)
add_library(capture ${CAPTURE_SOURCES})

# インクルードディレクトリ追加
target_include_directories(capture PUBLIC include)
target_include_directories(capture PRIVATE include/capture)

# ライブラリをリンク
target_link_libraries(capture util)
target_link_libraries(capture structure)

# OpenCVが発見できればOpenCVもリンク
if(OpenCV_FOUND)
  target_link_libraries(capture ${OpenCV_LIBS})
endif()



