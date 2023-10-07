# set the name
project(txtnet)

# add a header only library
add_library(${PROJECT_NAME} INTERFACE)

# add the include directories
target_include_directories(${PROJECT_NAME} INTERFACE 
    ${PROJECT_SOURCE_DIR}/include
)

# add the pthread option
target_link_options(${PROJECT_NAME} INTERFACE
    -pthread
)

# add the txt libraries
target_link_libraries(${PROJECT_NAME} INTERFACE
    txtlib
    httplib
    json-rpc-lib
)