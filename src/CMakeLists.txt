configure_file(config/config.h.in include/config.h)

add_executable(gbgen
	ArgsParser.cpp
	writeHelp.cpp
	ProjectListFiles.cpp
	ProjectBuilder.cpp
	main.cpp

	utils/StringTrim.cpp
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

	KeyManager.cpp
	MouseManager.cpp
	Config.cpp
	Time.cpp
	Cronometer.cpp
	Random.cpp
	SceneManager.cpp
	Game.cpp
	ProjectClass.cpp
	MainFile.cpp
	TextureManager.cpp

	workspace.cpp
	Task.cpp
)

target_include_directories(gbgen PRIVATE include include/generators)

target_link_libraries(gbgen ${CMAKE_THREAD_LIBS_INIT} STM::SimpleTaskManager)

# set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# install(TARGETS ${PROJECT_NAME} DESTINATION bin)
