
# ライブラリ追加
file(GLOB SEARCH_SOURCES src/*.cpp include/search/*.h include/search/*.hpp)
add_library(search ${SEARCH_SOURCES})

# インクルードディレクトリ追加
target_include_directories(search PUBLIC include)
target_include_directories(search PRIVATE include/search)

# ライブラリをリンク
target_link_libraries(search util)
target_link_libraries(search structure)

