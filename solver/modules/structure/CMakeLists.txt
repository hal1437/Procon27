
# ライブラリ追加
file(GLOB STRUCTURE_SOURCES src/*.cpp include/structure/*.h include/structure/*.hpp)
add_library(structure ${STRUCTURE_SOURCES})

# インクルードディレクトリ追加
target_include_directories(structure PUBLIC include)
target_include_directories(structure PRIVATE include/structure)

# ライブラリをリンク
target_link_libraries(structure util)

# OpenCVが発見できればOpenCVもリンク
if(OpenCV_FOUND)
  target_link_libraries(structure ${OpenCV_LIBS})
endif()

# ArrayFireが発見できればArrayFireもリンク
if(ArrayFire_FOUND)
  target_link_libraries(structure ${ArrayFire_LIBRARIES})
endif()



