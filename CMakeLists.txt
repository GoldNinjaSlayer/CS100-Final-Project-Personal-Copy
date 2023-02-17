# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("CheckersEngine")

# CMakeList.txt : CMake project for CheckersEngine, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

list(APPEND CMAKE_PREFIX_PATH "../SDL2/cmake")
list(APPEND CMAKE_PREFIX_PATH "../SDL2_image/cmake")

include_directories(
        ${CMAKE_SOURCE_DIR}/SDL2/include/
        ${CMAKE_SOURCE_DIR}/SDL2_image/include/
)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

file(COPY "${CMAKE_SOURCE_DIR}/CheckersEngine/assets" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")



# Add source to this project's executable.
add_executable (CheckersEngine
        "CheckersEngine/Src/Collision.cpp"
        "CheckersEngine/Src/Collision.h"
        "CheckersEngine/Src/Game.cpp"
        "CheckersEngine/Src/Game.h"
        "CheckersEngine/Src/GameObject.cpp"
        "CheckersEngine/Src/GameObject.h"
        "CheckersEngine/Src/main.cpp"
        "CheckersEngine/Src/Map.cpp"
        "CheckersEngine/Src/Map.h"
        "CheckersEngine/Src/TextureManager.cpp"
        "CheckersEngine/Src/TextureManager.h"
        "CheckersEngine/Src/Vector2D.cpp"
        "CheckersEngine/Src/Vector2D.h"
        "CheckersEngine/Src/ECS/ColliderComponent.h"
        "CheckersEngine/Src/ECS/Components.h"
        "CheckersEngine/Src/ECS/ECS.h"
        "CheckersEngine/Src/ECS/KeyboardController.h"
        "CheckersEngine/Src/ECS/SpriteComponent.h"
        "CheckersEngine/Src/ECS/TileComponent.h"
        "CheckersEngine/Src/ECS/TransformComponent.h")
target_link_libraries(CheckersEngine SDL2::SDL2 SDL2::SDL2main SDL2_image::SDL2_image)
target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/SDL2/lib/x64/SDL2.dll
        ${CMAKE_SOURCE_DIR}/SDL2_image/lib/x64/SDL2_image.dll)


if (WIN32)
    add_custom_command(
            TARGET CheckersEngine POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:SDL2::SDL2>" "$<TARGET_FILE_DIR:CheckersEngine>"
            VERBATIM
    )
    add_custom_command(
            TARGET CheckersEngine POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:SDL2_image::SDL2_image>" "$<TARGET_FILE_DIR:CheckersEngine>"
            VERBATIM
    )

endif()



if (CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET CheckersEngine PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
