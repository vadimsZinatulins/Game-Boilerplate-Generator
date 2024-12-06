add_executable(gbgen)

# Core sources
target_sources(
	gbgen
		PRIVATE 
			ArgsParser.cpp 
			writeHelp.cpp 
			ProjectBuilder.cpp 
			workspace.cpp
			main.cpp
)

# Utility sources
target_sources(
	gbgen
		PRIVATE 
			utils/StringTrim.cpp
			utils/replaceAll.cpp
)

# Math sources
target_sources(
	gbgen
		PRIVATE
			math/MathExtensionBuilder.cpp
)

target_include_directories(gbgen PRIVATE "${PROJECT_SOURCE_DIR}/include")

target_link_libraries(gbgen STM::SimpleTaskManager)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
