cmake_minimum_required(VERSION 3.23)
project(ChronoCheckers)

set(CMAKE_CXX_STANDARD 14)

include_directories(
        ${CMAKE_SOURCE_DIR}/SDL2/include/
        ${CMAKE_SOURCE_DIR}/SDL2_image-2.0.1/include/
)


add_executable(ChronoCheckers
        Src/Collision.cpp
        Src/Game.cpp
        Src/GameObject.cpp
        Src/main.cpp
        Src/Map.cpp
        Src/TextureManager.cpp
        Src/Vector2D.cpp

        Src/ECS/ColliderComponent.h
        Src/ECS/Components.h
        Src/ECS/ECS.h
        Src/ECS/KeyboardController.h
        Src/ECS/SpriteComponent.h
        Src/ECS/TileComponent.h
        Src/ECS/TransformComponent.h
        )
