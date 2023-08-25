add_executable(gbgen)

# Core sources
target_sources(
	gbgen
		PRIVATE 
			ArgsParser.cpp 
			writeHelp.cpp 
			ProjectBuilder.cpp 
			main.cpp
)

# Utility sources
target_sources(
	gbgen
		PRIVATE 
			utils/StringTrim.cpp
			utils/replaceAll.cpp
			utils/Instruction.cpp
			utils/Conditional.cpp
			utils/IfStatement.cpp
			utils/ForStatement.cpp
			utils/WhileStatement.cpp
			utils/SwitchStatement.cpp
			utils/Case.cpp
			utils/Function.cpp
			utils/WritableContent.cpp
			utils/Class.cpp
			utils/Namespace.cpp
			utils/File.cpp
)

# Specific generator sources
target_sources(
	gbgen 
		PRIVATE
			KeyManager.cpp
			MouseManager.cpp
			Random.cpp
			SceneManager.cpp
			Game.cpp
			MainFile.cpp
			TextureManager.cpp
			workspace.cpp
)

target_include_directories(gbgen PRIVATE "${PROJECT_SOURCE_DIR}/include" "${PROJECT_SOURCE_DIR}/include/generators")

target_link_libraries(gbgen STM::SimpleTaskManager)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
