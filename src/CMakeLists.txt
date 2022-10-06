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
)

target_include_directories(gbgen PRIVATE "${PROJECT_SOURCE_DIR}/include" "${PROJECT_SOURCE_DIR}/include/generators")

target_link_libraries(gbgen STM::SimpleTaskManager)

install(TARGETS ${PROJECT_NAME} RUNTIME)
