
# ライブラリ追加
file(SEARCH SEARCH_SOURCES src/*.cpp include/structure/*.h include/structure/*.hpp)
add_library(structure ${SEARCH_SOURCES})

# インクルードディレクトリ追加
target_include_directories(search PUBLIC include)
target_include_directories(search PRIVATE include/structure)

# ライブラリをリンク
target_link_libraries(search util)
target_link_libraries(search structure)

