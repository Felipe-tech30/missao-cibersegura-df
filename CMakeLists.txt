cmake_minimum_required(VERSION 3.16)
project(pcdf_missao_cibersegura C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_package(raylib 4.5 QUIET)

if(NOT raylib_FOUND)
    set(RAYLIB_LOCAL "C:/raylib")
    if(EXISTS "${RAYLIB_LOCAL}/raylib/src/raylib.h" AND
       EXISTS "${RAYLIB_LOCAL}/w64devkit/lib/libraylib.a")
        add_library(raylib STATIC IMPORTED)
        set_target_properties(raylib PROPERTIES
            IMPORTED_LOCATION "${RAYLIB_LOCAL}/w64devkit/lib/libraylib.a"
            INTERFACE_INCLUDE_DIRECTORIES "${RAYLIB_LOCAL}/raylib/src"
        )
    else()
        message(FATAL_ERROR "raylib nao encontrada. Instale-a ou ajuste RAYLIB_LOCAL.")
    endif()
endif()

add_executable(pcdf_missao_cibersegura
    src/main.c
    src/jogo.c
    src/mapa.c
    src/personagem.c
    src/ameacas.c
    src/dicas.c
    src/interface.c
    src/salvamento.c
)

target_include_directories(pcdf_missao_cibersegura PRIVATE include)
target_link_libraries(pcdf_missao_cibersegura PRIVATE raylib)

if(WIN32)
    target_link_libraries(pcdf_missao_cibersegura PRIVATE opengl32 gdi32 winmm)
endif()

if(MSVC)
    target_compile_options(pcdf_missao_cibersegura PRIVATE /W4)
else()
    target_compile_options(pcdf_missao_cibersegura PRIVATE -Wall -Wextra -Wpedantic)
endif()
