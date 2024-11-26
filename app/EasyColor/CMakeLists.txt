include_directories(${CMAKE_SOURCE_DIR}/lib)

get_filename_component(TARGET_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

set(SOURCES 
    main.cpp
    colorwidget.cpp
    mainwindow.cpp
    EasyColor.rc
    ${DIR_RESOURCES}/easy_apps.qrc
)

add_executable(${TARGET_NAME} ${SOURCES})

target_link_libraries(${TARGET_NAME} PUBLIC 
    Qt6::Core 
    Qt6::Widgets
    propertybrowser
    flowlayout
    qtcpp
    easywidget
)


