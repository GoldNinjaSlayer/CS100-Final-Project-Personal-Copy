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



# Add source to this project's executable.
add_executable (CheckersEngine
        "CheckersEngine/Src/Collision.cpp"
        "CheckersEngine/Src/Collision.h"
        "CheckersEngine/Src/Game.cpp"
        "CheckersEngine/Src/Game.h"
        "CheckersEngine/Src/State.h"
        "CheckersEngine/Src/State.cpp"
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
        "CheckersEngine/Src/ECS/ECS.cpp"
        "CheckersEngine/Src/ECS/KeyboardController.h"
        "CheckersEngine/Src/ECS/SpriteComponent.h"
        "CheckersEngine/Src/ECS/TileComponent.h"
        "CheckersEngine/Src/ECS/MouseController.h"
        "CheckersEngine/Src/ECS/TransformComponent.h"
        "CheckersEngine/Src/ECS/ButtonComponent.h"
        "CheckersEngine/Src/ECS/CheckerLocker.h"
        "CheckersEngine/Src/ECS/CheckerLocker.cpp"
        "CheckersEngine/Src/GameLogic/Board.cpp"
        "CheckersEngine/Src/GameLogic/Board.h"
        "CheckersEngine/Src/GameLogic/Checker.cpp"
        "CheckersEngine/Src/GameLogic/Checker.h"
        "CheckersEngine/Src/GameLogic/Player.cpp"
        "CheckersEngine/Src/GameLogic/Player.h"
        "CheckersEngine/Src/GameLogic/GameLogic.cpp"
        "CheckersEngine/Src/GameLogic/GameLogic.h"
        "CheckersEngine/Src/ECS/CheckerLinker.h"
        "CheckersEngine/Src/ECS/TileLinker.h"
        "UnitTests.cpp")
        "CheckersEngine/Src/ECS/TileLinker.h" 
        "CheckersEngine/Src/ECS/LogicComponent.h" 
        "CheckersEngine/Src/ECS/LogicComponent.cpp")

target_link_libraries(CheckersEngine SDL2::SDL2 SDL2::SDL2main SDL2_image::SDL2_image)
target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/SDL2/lib/x64/SDL2.dll
        ${CMAKE_SOURCE_DIR}/SDL2_image/lib/x64/SDL2_image.dll)

# Set the asset source directory and build directory
set(ASSET_SOURCE_DIR "${CMAKE_SOURCE_DIR}/CheckersEngine/assets")
set(ASSET_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/assets")



# Copy the assets from the source directory to the build directory using a custom command
add_custom_command(
    TARGET ${PROJECT_NAME} PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${ASSET_SOURCE_DIR} ${ASSET_BUILD_DIR}
)



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
