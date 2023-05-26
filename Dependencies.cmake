include(cmake/CPM.cmake)

# Done as a function so that updates to variables like
# CMAKE_CXX_FLAGS don't propagate out to other
# targets
function(myproject_setup_dependencies)

  # For each dependency, see if it's
  # already been provided to us by a parent project

  find_package(Vulkan QUIET)

  if(NOT TARGET Catch2::Catch2WithMain)
    cpmaddpackage("gh:catchorg/Catch2@3.3.2")
  endif()

  message(STATUS "Vulkan_FOUND: ${Vulkan_FOUND}")

  if (NOT Vulkan_FOUND)
    execute_process(
            COMMAND sh ${CMAKE_CURRENT_SOURCE_DIR}/install_vulkan.sh
    )
  endif()

  if (NOT TARGET glm)
    cpmaddpackage(NAME glm
            GITHUB_REPOSITORY g-truc/glm
            GIT_TAG 0.9.9.8
    )
  endif()

  if (NOT TARGET glfw)
    CPMAddPackage(
      NAME glfw
      GITHUB_REPOSITORY glfw/glfw
      GIT_TAG 3.3.8
      OPTIONS
        "GLFW_BUILD_TESTS Off"
        "GLFW_BUILD_EXAMPLES Off"
        "GLFW_BUILD_DOCS Off"
        "GLFW_INSTALL Off"
        "GLFW_USE_HYBRID_HPG On"
    )
  endif()

endfunction()
