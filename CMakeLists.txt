cmake_minimum_required(VERSION 3.16)
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)
project(JogoSimao)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
)
FetchContent_MakeAvailable(SFML)

file(GLOB_RECURSE SOURCES "Source/*.cpp")

add_executable(meu_jogo ${SOURCES})

target_include_directories(meu_jogo PRIVATE
    ${CMAKE_SOURCE_DIR}
)

target_link_libraries(meu_jogo PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
    SFML::Audio
)
