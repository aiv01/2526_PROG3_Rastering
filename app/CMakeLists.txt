file(GLOB_RECURSE APP_SOURCES src/*.cpp)
add_executable(RasterApp ${APP_SOURCES})
target_include_directories(RasterApp PRIVATE include/ libraries/raylib/include/)

if (WIN32)
    target_link_directories(RasterApp PRIVATE libraries/raylib/x64)
    target_link_libraries(RasterApp PRIVATE raylibdll)
    add_custom_command(TARGET RasterApp POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_CURRENT_SOURCE_DIR}/libraries/raylib/x64/raylib.dll
            $<TARGET_FILE_DIR:RasterApp>
    )

elseif (APPLE)
    target_link_directories(RasterApp PRIVATE libraries/raylib/osx)
    target_link_libraries(RasterApp PRIVATE raylib)
    add_custom_command(TARGET RasterApp POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_CURRENT_SOURCE_DIR}/libraries/raylib/osx/libraylib.dylib
            $<TARGET_FILE_DIR:RasterApp>
    )
    # Ensure the executable can find the dylib at runtime
    set_target_properties(RasterApp PROPERTIES
        BUILD_RPATH "@executable_path"
        INSTALL_RPATH "@executable_path"
    )
endif()

add_custom_command(TARGET RasterApp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/resources
        $<TARGET_FILE_DIR:RasterApp>/resources
)
