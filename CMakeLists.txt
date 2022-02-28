cmake_minimum_required(VERSION 3.10)

# Game Boilerplate Generator
project(gbgen VERSION 1.0)

configure_file(${PROJECT_SOURCE_DIR}/config/config.h.in ${PROJECT_SOURCE_DIR}/include/config.h)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS On)

add_executable(
	${PROJECT_NAME} 
	${PROJECT_SOURCE_DIR}/src/main.cpp
	${PROJECT_SOURCE_DIR}/src/workspace.cpp
	${PROJECT_SOURCE_DIR}/src/cmakelists.cpp
	${PROJECT_SOURCE_DIR}/src/keymanager.cpp
	${PROJECT_SOURCE_DIR}/src/game.cpp
	${PROJECT_SOURCE_DIR}/src/projectnameclass.cpp
	${PROJECT_SOURCE_DIR}/src/mainfile.cpp
	${PROJECT_SOURCE_DIR}/src/configfile.cpp
)

target_include_directories(
	${PROJECT_NAME}
	PUBLIC ${PROJECT_SOURCE_DIR}/include	
)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
