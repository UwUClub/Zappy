include(cmake/CPM.cmake)

# Done as a function so that updates to variables like
# CMAKE_CXX_FLAGS don't propagate out to other
# targets
function(myproject_setup_dependencies)

  # For each dependency, see if it's
  # already been provided to us by a parent project
  find_package(OGRE QUIET)

  if(NOT TARGET Catch2::Catch2WithMain)
    cpmaddpackage("gh:catchorg/Catch2@3.3.2")
  endif()

  if (NOT OGRE_FOUND)
    message(STATUS "OGRE not found, downloading and building it")
    execute_process(
            COMMAND sh ${CMAKE_CURRENT_SOURCE_DIR}/install_ogre.sh
    )
  else ()
    message(STATUS "OGRE found, using it")
  endif()

endfunction()
