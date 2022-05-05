## local variable for managing the game target ##
set(GAME ${PROJECT_NAME})

## glob is useful but not reliant in compilation so just use it for headers ##
file(GLOB_RECURSE HEADER_LIST
        LIST_DIRECTORIES FALSE
        CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/*.h
        ${CMAKE_SOURCE_DIR}/include/*.hpp
        ${CMAKE_SOURCE_DIR}/include/*.h)

list(APPEND HEADER_FOLDER ${CMAKE_CURRENT_SOURCE_DIR})

## source files get listed here ##
set(GAME_SOURCES
        main.cpp
        ASGEGame.cpp
        classes/gameobject/Buttons.cpp
        classes/gameobject/GameObject.cpp
        classes/gameobject/QuantomObject.cpp
        classes/gameobject/QuantomObject.h
        classes/gameobject/objects/Projectile.cpp
        classes/gameobject/objects/Projectile.hpp
        classes/gameobject/player/Player.cpp
        classes/utility/BoundingBox.cpp
        classes/utility/Tiles.cpp
        classes/utility/SpriteComponent.cpp
        classes/utility/Vector2.cpp 
        classes/utility/Interpolation.cpp
        classes/utility/Interpolation.h
        classes/utility/Vector2.cpp
        classes/States/MainGameState.cpp
        classes/States/MainGameState.h
        classes/States/State.cpp
        classes/States/State.h
        classes/States/TitleState.cpp
        classes/States/TitleState.h
        classes/States/HospitalState.cpp
        classes/States/HospitalState.h
        classes/States/InterrogationState.cpp
        classes/States/InterrogationState.h
        classes/gameplay/Interrogation.cpp
        classes/gameplay/InterrogationQuestion.cpp classes/States/PauseState.cpp classes/States/PauseState.h classes/States/GameWon.cpp classes/States/GameWon.h classes/States/GameOver.cpp classes/States/GameOver.h)

## the ASGE Game, which spawns the Game window ##
add_executable(${GAME} ${HEADER_LIST} ${GAME_SOURCES})

## configure the target. Dependency targets go in the LIBS variable i.e. soloud ##
list(APPEND LIBS "soloud" "magic_enum::magic_enum" "tmxlite")
target_include_directories(${GAME} PRIVATE ${HEADER_FOLDER})
configure_target(${GAME} "${HEADER_FOLDER}" "${HEADER_LIST}" "${LIBS}")
add_asge_dependency(${GAME})

## icon support, because why not ##
if (WIN32)
    set(ICON ${CMAKE_CURRENT_SOURCE_DIR}/resources/game.rc)
elseif (APPLE)
    set(ICON ${CMAKE_CURRENT_SOURCE_DIR}/resources/game.icns)
    set_source_files_properties(
            ${CMAKE_CURRENT_SOURCE_DIR}/resources/game.icns PROPERTIES
            MAXOSX_PACKAGE_LOCATION "resources")
endif ()

## game data ##
add_gamedata(${GAME} ${CMAKE_CURRENT_SOURCE_DIR}/data)
add_dependencies(${GAME} ${GAME}-GD)