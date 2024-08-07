#pragma once

const auto CONFIG_H_IN_TEMPLATE { R"(#pragma once

// Set the major version for the project
#define MAJOR_VERSION @{NAME}_VERSION_MAJOR@
// Set the minor version for the project
#define MINOR_VERSION @{NAME}_VERSION_MINOR@

// Window title
#define SCREEN_TITLE "{NAME}"

// Window width
#define SCREEN_WIDTH 800
// Window height
#define SCREEN_HEIGHT 600

// Maximum frame rate
#define FRAME_CAP 60
)" };

auto CONFIG_H_IN_SDL2_IMAGE_CONTENT_TEMPLATE { R"(
// Initializations for SDL2-image:
//  JPG = 1
//  PNG = 2
//  TIF = 4
//  WEBP = 8
// These can be ORed together (example: 1 | 4)
#define IMAGE_INIT 2
)" };