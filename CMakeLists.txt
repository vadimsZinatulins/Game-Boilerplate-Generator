cmake_minimum_required(VERSION 3.10)

# Game Boilerplate Generator
project(gbgen VERSION 3.1)

configure_file(${PROJECT_SOURCE_DIR}/config/config.h.in ${PROJECT_SOURCE_DIR}/include/config.h)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS On)

find_package(Threads REQUIRED)

add_executable(
	${PROJECT_NAME} 
	${PROJECT_SOURCE_DIR}/src/main.cpp

    ${PROJECT_SOURCE_DIR}/src/utils/StringTrim.cpp
    ${PROJECT_SOURCE_DIR}/src/utils/Conditional.cpp
    ${PROJECT_SOURCE_DIR}/src/utils/ForStatement.cpp
    ${PROJECT_SOURCE_DIR}/src/utils/Function.cpp
    ${PROJECT_SOURCE_DIR}/src/utils/IfStatement.cpp
    ${PROJECT_SOURCE_DIR}/src/utils/Instruction.cpp
    ${PROJECT_SOURCE_DIR}/src/utils/WhileStatement.cpp
    ${PROJECT_SOURCE_DIR}/src/utils/WritableContent.cpp
    ${PROJECT_SOURCE_DIR}/src/utils/Class.cpp
    ${PROJECT_SOURCE_DIR}/src/utils/Namespace.cpp
    ${PROJECT_SOURCE_DIR}/src/utils/File.cpp

	${PROJECT_SOURCE_DIR}/src/CMakeFile.cpp
	${PROJECT_SOURCE_DIR}/src/KeyManager.cpp
	${PROJECT_SOURCE_DIR}/src/MouseManager.cpp
	${PROJECT_SOURCE_DIR}/src/Config.cpp
	${PROJECT_SOURCE_DIR}/src/Time.cpp

	${PROJECT_SOURCE_DIR}/src/workspace.cpp
	${PROJECT_SOURCE_DIR}/src/cmakelists.cpp
	${PROJECT_SOURCE_DIR}/src/keymanager.cpp
	${PROJECT_SOURCE_DIR}/src/mousemanager.cpp
	${PROJECT_SOURCE_DIR}/src/game.cpp
	${PROJECT_SOURCE_DIR}/src/projectnameclass.cpp
	${PROJECT_SOURCE_DIR}/src/mainfile.cpp
	${PROJECT_SOURCE_DIR}/src/configfile.cpp
	${PROJECT_SOURCE_DIR}/src/timeclass.cpp
	${PROJECT_SOURCE_DIR}/src/cronometerclass.cpp
	${PROJECT_SOURCE_DIR}/src/randomclass.cpp
	${PROJECT_SOURCE_DIR}/src/utils.cpp
	${PROJECT_SOURCE_DIR}/src/scenemanager.cpp
	${PROJECT_SOURCE_DIR}/src/mainmenuscene.cpp
	${PROJECT_SOURCE_DIR}/src/Task.cpp
)

target_include_directories(
	${PROJECT_NAME}
	PUBLIC ${PROJECT_SOURCE_DIR}/include	
)

target_link_libraries(
	${PROJECT_NAME}
	${CMAKE_THREAD_LIBS_INIT}
)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
