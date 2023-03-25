cmake_minimum_required(VERSION 3.0.0)
project(oz_project C)

include(CTest)
enable_testing()

add_executable(oz_project asembler.c binaryMaker.c FileListFuncs.c helpers.c
macroDecoder.c MacroListFuncs.c outputMaker.c SymbolListFuncs.c)

set_property(TARGET oz_project PROPERTY C_STANDARD 90)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
