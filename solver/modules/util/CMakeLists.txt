
# ライブラリ追加
file(GLOB UTIL_SOURCES src/*.cpp include/util/*.hpp)
add_library(util ${UTIL_SOURCES})

# インクルードディレクトリ追加
target_include_directories(util PUBLIC include)
target_include_directories(util PRIVATE include/util)

