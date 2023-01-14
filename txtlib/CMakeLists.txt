# set the name
project(txtlib)

# add a header only library
add_library(${PROJECT_NAME} INTERFACE)

# add the include directories
target_include_directories(${PROJECT_NAME} INTERFACE 
    ${CMAKE_SOURCE_DIR}/deps/Txt_Includes
    ${PROJECT_SOURCE_DIR}/include
)

# add the pthread option (required by the txt libraries)
target_link_options(${PROJECT_NAME} INTERFACE
    -pthread
)

# add the directories containing the txt libraries and their dependencies
target_link_directories(${PROJECT_NAME} INTERFACE
    ${CMAKE_SOURCE_DIR}/deps/Txt_Libs/
    ${CMAKE_SOURCE_DIR}/deps/Txt_Libs_deps/
)

# add the txt libraries
target_link_libraries(${PROJECT_NAME} INTERFACE
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
    dl
)