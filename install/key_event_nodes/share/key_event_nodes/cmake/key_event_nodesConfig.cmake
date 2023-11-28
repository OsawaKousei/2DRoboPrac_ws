# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_key_event_nodes_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED key_event_nodes_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(key_event_nodes_FOUND FALSE)
  elseif(NOT key_event_nodes_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(key_event_nodes_FOUND FALSE)
  endif()
  return()
endif()
set(_key_event_nodes_CONFIG_INCLUDED TRUE)

# output package information
if(NOT key_event_nodes_FIND_QUIETLY)
  message(STATUS "Found key_event_nodes: 0.0.0 (${key_event_nodes_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'key_event_nodes' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${key_event_nodes_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(key_event_nodes_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "ament_cmake_export_targets-extras.cmake;ament_cmake_export_dependencies-extras.cmake")
foreach(_extra ${_extras})
  include("${key_event_nodes_DIR}/${_extra}")
endforeach()
