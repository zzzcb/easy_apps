#######################################################################
# Find all necessary and optional easy_apps dependencies
#######################################################################

# qt6
find_package(Qt6 REQUIRED COMPONENTS 
	Core 
	Widgets 
)
qt_standard_project_setup()                 # Qt6标准工程配置（会开启自动MOC和UIC）
set(CMAKE_AUTORCC ON)                       # 开启自动RCC
