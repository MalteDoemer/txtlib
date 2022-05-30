# set the name
project(txtlib)

# add a header only library
add_library(${PROJECT_NAME} INTERFACE)

# add include directories
target_include_directories(${PROJECT_NAME} INTERFACE 
    ${CMAKE_SOURCE_DIR}/deps/Txt_Includes
    ${PROJECT_SOURCE_DIR}/include
)