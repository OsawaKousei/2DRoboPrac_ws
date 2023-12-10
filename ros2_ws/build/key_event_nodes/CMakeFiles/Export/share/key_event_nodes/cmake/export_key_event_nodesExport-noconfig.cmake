#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "key_event_nodes::key_hit_event_node" for configuration ""
set_property(TARGET key_event_nodes::key_hit_event_node APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(key_event_nodes::key_hit_event_node PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libkey_hit_event_node.so"
  IMPORTED_SONAME_NOCONFIG "libkey_hit_event_node.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS key_event_nodes::key_hit_event_node )
list(APPEND _IMPORT_CHECK_FILES_FOR_key_event_nodes::key_hit_event_node "${_IMPORT_PREFIX}/lib/libkey_hit_event_node.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
