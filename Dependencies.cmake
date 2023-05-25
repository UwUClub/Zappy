include(cmake/CPM.cmake)

# Done as a function so that updates to variables like
# CMAKE_CXX_FLAGS don't propagate out to other
# targets
function(myproject_setup_dependencies)

  # For each dependency, see if it's
  # already been provided to us by a parent project

  execute_process(
        COMMAND vulkaninfo
        RESULT_VARIABLE VULKAN_FOUND
        OUTPUT_QUIET
        ERROR_QUIET
  )

  if(NOT TARGET Catch2::Catch2WithMain)
    cpmaddpackage("gh:catchorg/Catch2@3.3.2")
  endif()

  if (NOT TARGET vulkan)
    execute_process(
            COMMAND ./install_vulkan.sh
    )
    find_package(Vulkan REQUIRED)
  endif()

  if (NOT TARGET glh)
    cpmaddpackage(NAME glh
            GITHUB_REPOSITORY g-truc/glm
            GIT_TAG 0.9.9.8
    )
  endif()

  if (NOT VULKAN_FOUND EQUAL 0)
    execute_process(
            COMMAND sh install_vulkan.sh
    )
    find_package(Vulkan REQUIRED)
  endif()

  if (NOT TARGET glfw)
    cpmaddpackage(NAME glfw
            GITHUB_REPOSITORY glfw/glfw
            GIT_TAG 3.3.8
            OPTIONS "GLFW_BUILD_DOCS OFF"
            "GLFW_BUILD_TESTS OFF"
            "GLFW_BUILD_EXAMPLES OFF"
    )
  endif()

endfunction()
