find_package(Vulkan QUIET)
find_package(glfw3 QUIET)
find_package(glm QUIET)

if (NO_CONNECTION EQUAL 0)
    add_subdirectory(gui)
elseif (Vulkan_FOUND AND glfw3_FOUND EQUAL 1 AND glm_FOUND EQUAL 1)
    message(STATUS "GUI: ON")
    add_subdirectory(gui)
else()
    message(STATUS "GUI: OFF")
    execute_process(
            COMMAND touch zappy_gui
    )
endif()

add_subdirectory(server)