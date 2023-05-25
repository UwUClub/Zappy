execute_process(
    COMMAND ping patatoserv.ddns.net -c 1 -q
    RESULT_VARIABLE NO_CONNECTION
)

if (NO_CONNECTION EQUAL 0)
    add_subdirectory(gui)
endif()

add_subdirectory(server)