cmake_minimum_required(VERSION 3.22)
project(VampireHunters LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

file(GLOB_RECURSE FONTES CONFIGURE_DEPENDS
    ${CMAKE_SOURCE_DIR}/*.cpp
)
# Ignora arquivos gerados dentro de build/
list(FILTER FONTES EXCLUDE REGEX "/build/|/cmake-build-[^/]*/")

add_executable(jogo ${FONTES})
# Raiz do projeto como include: #include "Entidades/Personagens/Cacador.hpp"
target_include_directories(jogo PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(jogo PRIVATE SFML::Graphics SFML::Window SFML::System)
target_compile_options(jogo PRIVATE -Wall -Wextra -Wpedantic)
