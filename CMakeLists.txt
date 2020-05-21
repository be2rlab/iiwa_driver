cmake_minimum_required(VERSION 3.12)
project(iiwa_driver VERSION 0.0.1)

add_definitions(-std=c++17)

# Add FRI client SDK as a library
# TODO: compile it here!
set(FRI_CLIENT_SDK_PATH "${CMAKE_HOME_DIRECTORY}/fri-client-sdk")
add_library(fri-client-lib STATIC IMPORTED)
set_property(TARGET fri-client-lib 
    PROPERTY IMPORTED_LOCATION ${FRI_CLIENT_SDK_PATH}/lib/libFRIClient.a)
include_directories(${FRI_CLIENT_SDK_PATH}/include)


add_executable(${PROJECT_NAME} src/main.cpp)
add_dependencies(${PROJECT_NAME} fri-client-lib)
target_link_libraries(${PROJECT_NAME} fri-client-lib)




