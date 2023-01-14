# set the name
project(txtapp)

# create a executable
add_executable(${PROJECT_NAME})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

# add all the source files
target_sources(${PROJECT_NAME} PRIVATE
    ${PROJECT_SOURCE_DIR}/Main.cpp
)

# add txtlib and all external libraries that are required
target_link_libraries(${PROJECT_NAME} PRIVATE
    txtlib
)