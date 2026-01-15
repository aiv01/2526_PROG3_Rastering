file(GLOB_RECURSE APP_SOURCES ../app/src/*.cpp)
add_library(RasterAppLib STATIC ${APP_SOURCES})
target_include_directories(RasterAppLib PUBLIC ../app/include/)
target_include_directories(RasterAppLib PRIVATE ../app/libraries/raylib/include/)

file(GLOB_RECURSE TEST_SOURCES src/*.cpp)
add_executable(RasterTest ${TEST_SOURCES})
target_include_directories(RasterTest PRIVATE include/)
target_link_libraries(RasterTest PUBLIC RasterAppLib)

add_custom_command(TARGET RasterTest POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/resources
        $<TARGET_FILE_DIR:RasterTest>/resources
)
