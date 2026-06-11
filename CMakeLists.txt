cmake_minimum_required(VERSION 3.16)
project(JogoSimao)

set(CMAKE_CXX_STANDARD 17)

# Força o CMake a encontrar a sua SFML 3.0 instalada no C:
set(SFML_DIR "C:/SFML-3.0.0/lib/cmake/SFML")
find_package(SFML 3.0 COMPONENTS Graphics Window System Audio REQUIRED)

# Coleta todos os seus arquivos .cpp das subpastas
file(GLOB_RECURSE SOURCES "Source/*.cpp" "Entidades/*.cpp" "Fases/*.cpp")

add_executable(meu_jogo ${SOURCES})

target_include_directories(meu_jogo PRIVATE
    ${CMAKE_SOURCE_DIR}
)

# Linkagem correta com letras maiúsculas da SFML 3
target_link_libraries(meu_jogo PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
    SFML::Audio
)