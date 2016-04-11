
# ライブラリ追加
file(GLOB UTIL_SOURCES src/*.cpp include/slide/*.hpp)
add_library(util ${STRUCTURE_SOURCES})

# インクルードディレクトリ追加
target_include_directories(util PUBLIC include)
target_include_directories(util PRIVATE include/util)

# ライブラリをリンク
# target_link_libraries(structure util)

