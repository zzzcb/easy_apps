get_filename_component(TARGET_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME) 

set(SOURCES 
    flowlayout.cpp
)

add_library(${TARGET_NAME} SHARED
	${SOURCES}
)

target_link_libraries(${TARGET_NAME} PUBLIC 
    Qt6::Core
    Qt6::Widgets
)

set_target_properties(${TARGET_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)
#动态库导出
target_compile_definitions(${TARGET_NAME} PRIVATE BUILDING_DLL)
