# set the name
project(txtapp)

# create a executable
add_executable(${PROJECT_NAME})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)

# add all the source files
target_sources(${PROJECT_NAME} PRIVATE
    ${PROJECT_SOURCE_DIR}/Main.cpp
)

# add the directories for external libraries
target_link_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/deps/Txt_Libs/
    ${CMAKE_SOURCE_DIR}/deps/Txt_Libs_deps/
)

# add txtlib and all external libraries that are required
target_link_libraries(${PROJECT_NAME} PRIVATE
    txtlib

    ROBOProLib
    KeLibTxt
    MotorIOLib
    TxtControlLib
    SDL
    SDL_gfx
    SDL_ttf
    SDL_image
    ts
    z
    freetype
    png16
    jpeg
    bz2
    asound
    SDLWidgetsLib
)