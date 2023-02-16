# CMakeList.txt : CMake project for CheckersEngine, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

list(APPEND CMAKE_PREFIX_PATH "../SDL2/cmake")
list(APPEND CMAKE_PREFIX_PATH "../SDL2_image/cmake")



find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

file(COPY "${CMAKE_SOURCE_DIR}/CheckersEngine/assets" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")



# Add source to this project's executable.
add_executable (CheckersEngine   "Src/Collision.cpp" "Src/Collision.h" "Src/Game.cpp" "Src/Game.h" "Src/GameObject.cpp" "Src/GameObject.h" "Src/main.cpp" "Src/Map.cpp" "Src/Map.h" "Src/TextureManager.cpp" "Src/TextureManager.h" "Src/Vector2D.cpp" "Src/Vector2D.h" "Src/ECS/ColliderComponent.h" "Src/ECS/Components.h" "Src/ECS/ECS.h" "Src/ECS/KeyboardController.h" "Src/ECS/SpriteComponent.h" "Src/ECS/TileComponent.h" "Src/ECS/TransformComponent.h" "../SDL2_image/include/SDL_image.h")
target_link_libraries(CheckersEngine SDL2::SDL2 SDL2::SDL2main SDL2_image::SDL2_image)

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
