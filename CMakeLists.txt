cmake_minimum_required(VERSION 3.12)
project(iiwa_driver VERSION 0.0.1)

add_definitions(-std=c++11)

# Add FRI client SDK as a library
# TODO: compile it here!
set(FRI_CLIENT_SDK_PATH "${CMAKE_HOME_DIRECTORY}/extern/fri-client-sdk")
add_library(fri-client-lib STATIC IMPORTED)
set_property(TARGET fri-client-lib 
    PROPERTY IMPORTED_LOCATION ${FRI_CLIENT_SDK_PATH}/lib/libFRIClient.a)
target_compile_definitions(fri-client-lib INTERFACE FRI_CLIENT_SDK_VERSION=1.16)

include_directories(
    include/iiwa-driver
    ${FRI_CLIENT_SDK_PATH}/include
)

add_executable(${PROJECT_NAME} src/main.cpp src/PositionLBRClient.cpp)
add_dependencies(${PROJECT_NAME} fri-client-lib)
target_link_libraries(${PROJECT_NAME} fri-client-lib)

add_executable(lbr_gravity src/lbr_gravity.cpp src/GravityLBRClient.cpp)
add_dependencies(lbr_gravity fri-client-lib)
target_link_libraries(lbr_gravity fri-client-lib)

add_executable(lbr_jelly src/lbr_jelly.cpp src/JellyLBRClient.cpp)
add_dependencies(lbr_jelly fri-client-lib)
target_link_libraries(lbr_jelly fri-client-lib)




