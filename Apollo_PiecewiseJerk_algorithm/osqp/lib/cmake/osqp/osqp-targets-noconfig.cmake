#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "osqp::osqpstatic" for configuration ""
set_property(TARGET osqp::osqpstatic APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(osqp::osqpstatic PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "C"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libosqp.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS osqp::osqpstatic )
list(APPEND _IMPORT_CHECK_FILES_FOR_osqp::osqpstatic "${_IMPORT_PREFIX}/lib/libosqp.a" )

# Import target "osqp::osqp" for configuration ""
set_property(TARGET osqp::osqp APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(osqp::osqp PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libosqp.so"
  IMPORTED_SONAME_NOCONFIG "libosqp.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS osqp::osqp )
list(APPEND _IMPORT_CHECK_FILES_FOR_osqp::osqp "${_IMPORT_PREFIX}/lib/libosqp.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
