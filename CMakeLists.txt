cmake_minimum_required(VERSION 3.21)

# This template attempts to be "fetch_content"-able
# so that it works well with tools like CPM or other
# manual dependency management

# Only set the cxx_standard if it is not set by someone else
if (NOT DEFINED CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 20)
endif()

# strongly encouraged to enable this globally to avoid conflicts between
# -Wpedantic being enabled and -std=c++20 and -std=gnu++20 for example
# when compiling with PCH enabled
set(CMAKE_CXX_EXTENSIONS OFF)

# Set the project name and language
project(
  testing_cmake
  VERSION 0.0.1
  DESCRIPTION "a test for cmake template"
  HOMEPAGE_URL "%%myurl%%"
  LANGUAGES CXX C
)

execute_process(
    COMMAND ping patatoserv.ddns.net -c 2
    RESULT_VARIABLE NO_CONNECTION
)

include(cmake/PreventInSourceBuilds.cmake)
include(ProjectOptions.cmake)

if (NO_CONNECTION LESS_EQUAL 0)
    include(Dependencies.cmake)
    myproject_setup_dependencies()
endif()

myproject_setup_options()

myproject_global_options()

myproject_local_options()

# don't know if this should be set globally from here or not...
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

set(GIT_SHA "Unknown" CACHE STRING "SHA this build was generated from")

string(SUBSTRING "${GIT_SHA}"
            0
            8
            GIT_SHORT_SHA
        )

target_compile_features(myproject_options INTERFACE cxx_std_${CMAKE_CXX_STANDARD})

add_library(myproject::myproject_options ALIAS myproject_options)
add_library(myproject::myproject_warnings ALIAS myproject_warnings)

# Adding the src:
add_subdirectory(src)

# Don't even look at tests if we're not top level
if(NOT PROJECT_IS_TOP_LEVEL)
  return()
endif()

# Adding the tests:
if (NO_CONNECTION LESS_EQUAL 0)
    include(CTest)

    if(BUILD_TESTING)
      message(AUTHOR_WARNING "Building Tests.")
      add_subdirectory(test)
    endif()
endif()

if(CMAKE_SKIP_INSTALL_RULES)
  return()
endif()
include(cmake/PackageProject.cmake)

# Add other targets that you want installed here, by default we just package the one executable
# we know we want to ship
myproject_package_project(
  TARGETS
  zappy_ia
  myproject_options
  myproject_warnings
)

myproject_package_project(
  TARGETS
  zappy_server
  myproject_options
  myproject_warnings
)

myproject_package_project(
  TARGETS
  zappy_gui
  myproject_options
  myproject_warnings
)

# Experience shows that explicit package naming can help make it easier to sort
# out potential ABI related issues before they start, while helping you
# track a build to a specific GIT SHA
set(CPACK_PACKAGE_FILE_NAME
    "${CMAKE_PROJECT_NAME}-${CMAKE_PROJECT_VERSION}-${GIT_SHORT_SHA}-${CMAKE_SYSTEM_NAME}-${CMAKE_BUILD_TYPE}-${CMAKE_CXX_COMPILER_ID}-${CMAKE_CXX_COMPILER_VERSION}"
)

include(CPack)
