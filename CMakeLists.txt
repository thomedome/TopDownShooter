cmake_minimum_required(VERSION 3.28)

project(TopDownShooter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.2
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM
)

FetchContent_MakeAvailable(SFML)

add_executable(TopDownShooter
        src/main.cpp
        src/classes/Entity.cpp
        src/classes/Entity.h
        src/classes/Player.cpp
        src/classes/Player.h
        src/classes/enums.h
        src/classes/Weapon.cpp
        src/classes/Weapon.h
        src/classes/GameHandler.cpp
        src/classes/GameHandler.h
        src/classes/Bullet.cpp
        src/classes/Bullet.h
        src/classes/common.h
        src/classes/ProjectileManager.cpp
        src/classes/ProjectileManager.h
        src/classes/Enemy.cpp
        src/classes/Enemy.h
        src/classes/Button.cpp
        src/classes/Button.h
)

add_custom_command(
        TARGET TopDownShooter POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:TopDownShooter>/assets"
)

target_link_libraries(TopDownShooter PRIVATE SFML::Graphics)