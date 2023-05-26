execute_process(
        COMMAND vulkaninfo
        RESULT_VARIABLE VULKAN_FOUND
        OUTPUT_QUIET
        ERROR_QUIET
)

if (VULKAN_FOUND EQUAL 0)
    add_subdirectory(gui)
else()
    execute_process(
            COMMAND touch ../zappy_gui
    )
endif()

add_subdirectory(server)