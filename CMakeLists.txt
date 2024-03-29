cmake_minimum_required(VERSION 3.16)

project(fractal)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK REQUIRED gtk4)
pkg_check_modules(GD REQUIRED gdlib)

include_directories(${GD_INCLUDE_DIR})
include_directories(${GTK_INCLUDE_DIRS})
link_directories(${GD_LIBRARY_DIRS})
link_directories(${GTK_LIBRARY_DIRS})
add_definitions(${GTK_CFLAGS_OTHER})

if (NOT WIN32)
set(MATH "m")
else ()
add_definitions(-DYY_NO_UNISTD_H -D_USE_MATH_DEFINES)
endif ()

set(source lsystem.c lsystem_iter.c lines_normilize.c lines_save_png.c lines_save_txt.c)

flex_target(lsystem_scanner lsystem_scanner.l ${CMAKE_CURRENT_BINARY_DIR}/lsystem_scanner.c
	COMPILE_FLAGS "--header-file=${CMAKE_CURRENT_BINARY_DIR}/lsystem_scanner.h"
	DEFINES_FILE "${CMAKE_CURRENT_BINARY_DIR}/lsystem_scanner.h")
flex_target(turtle_scanner turtle_scanner.l ${CMAKE_CURRENT_BINARY_DIR}/turtle_scanner.c
	COMPILE_FLAGS "--header-file=${CMAKE_CURRENT_BINARY_DIR}/turtle_scanner.h"
	DEFINES_FILE "${CMAKE_CURRENT_BINARY_DIR}/turtle_scanner.h")
bison_target(lsystem_parser lsystem_parser.y ${CMAKE_CURRENT_BINARY_DIR}/lsystem_parser.c COMPILE_FLAGS "-Wcounterexamples")

add_flex_bison_dependency(lsystem_scanner lsystem_parser)
set(source ${source}
	${BISON_lsystem_parser_OUTPUTS}
	${FLEX_lsystem_scanner_OUTPUTS}
	${FLEX_turtle_scanner_OUTPUTS}
	)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_library(fractal ${source})

add_executable(lsystem main.c)
target_link_libraries(lsystem fractal ${GD_LIBRARIES} ${MATH})

add_executable(lsystem_gui main_gui.c)
target_link_libraries(lsystem_gui fractal ${GD_LIBRARIES} ${GTK_LIBRARIES} ${MATH})
