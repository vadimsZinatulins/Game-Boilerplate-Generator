# Create an executable named 'gbgen'
add_executable(gbgen)

# Add main source files
target_sources(
    gbgen
        PRIVATE 
            ProjectBuilder.cpp 
            workspace.cpp
            main.cpp
)

# Add utility source files
target_sources(
    gbgen
        PRIVATE 
            utils/StringTrim.cpp
            utils/replaceAll.cpp
            utils/ArgsParser.cpp
)

# Add math-related source files
target_sources(
    gbgen
        PRIVATE
            math/MathExtensionBuilder.cpp
)

# Tell the compiler where to find header files
target_include_directories(gbgen PRIVATE "${PROJECT_SOURCE_DIR}/include")

# Link against the SimpleTaskManager library
target_link_libraries(gbgen STM::SimpleTaskManager)

# Set installation paths based on GNU standards and platform
include(GNUInstallDirs)

# Install the executable
install(
    TARGETS ${PROJECT_NAME}
    RUNTIME
        DESTINATION ${CMAKE_INSTALL_BINDIR}
        COMPONENT runtime
)
