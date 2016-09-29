
# サブディレクトリの追加
add_subdirectory(util)
add_subdirectory(structure)
# add_subdirectory(search)
add_subdirectory(capture)

# Qt5導入時はUIもビルドする
if(Qt5Widgets_FOUND)
# 	add_subdirectory(ui)
endif()
