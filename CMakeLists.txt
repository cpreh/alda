cmake_minimum_required(VERSION 3.27.0)

project(alda)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include(GNUInstallDirs)

find_package(fcppt REQUIRED)

set(FCPPT_UTILS_CLANG_TIDY_WHITELIST "fcppt" "alda")

list(APPEND FCPPT_UTILS_CLANG_TIDY_ADDITIONAL_CHECKS
     "-cppcoreguidelines-avoid-const-or-ref-data-members"
     "-misc-misplaced-const")

include(FcpptCMakeUtils)

include(FcpptSymbol)

fcppt_utils_static_shared()

option(ENABLE_TEST "Build the tests" ON)

option(ENABLE_EXAMPLES "Build the examples" ON)

fcppt_utils_link_target(alda)

if(ENABLE_EXAMPLES)
  add_subdirectory(examples)
endif()

if(ENABLE_TEST)
  find_package(Catch2 REQUIRED)

  fcppt_utils_setup_tests()

  enable_testing()

  add_subdirectory(tests)
endif()

set(ALDA_STATIC_LINK_FLAG ALDA_STATIC_LINK)

include(CMakeParseArguments)

function(add_alda_library_base LIBNAME VARIANT)
  set(OPTION_ARGS HAS_IMPL_DIR)

  set(MULTI_ARGS COMPILE_FLAGS COMPILE_DEFINITIONS INCLUDE_DIRS
                 SYSTEM_INCLUDE_DIRS LINK_LIBS INTERFACE_LINK_LIBS)

  cmake_parse_arguments("" "${OPTION_ARGS}" "" "${MULTI_ARGS}" ${ARGN})

  if(${VARIANT} STREQUAL "STATIC")
    fcppt_utils_static_link_name(${LIBNAME} TARGET_NAME)
  elseif(${VARIANT} STREQUAL "INTERFACE")
    fcppt_utils_interface_link_name(${LIBNAME} TARGET_NAME)
  else()
    set(TARGET_NAME ${LIBNAME})
  endif()

  string(TOUPPER ${LIBNAME} LIBNAME_UPPER)

  fcppt_utils_append_source_dir_and_make_groups("${${LIBNAME_UPPER}_FILES}"
                                                FILES_ABS)

  if(${VARIANT} STREQUAL "INTERFACE")
    add_library(${TARGET_NAME} ${VARIANT})
  else()
    add_library(${TARGET_NAME} ${VARIANT} ${FILES_ABS})
  endif()

  if(NOT ${VARIANT} STREQUAL "INTERFACE")
    set_target_properties(${TARGET_NAME} PROPERTIES FOLDER alda)

    fcppt_utils_set_target_compiler_flags(${TARGET_NAME} ADDITIONAL_FLAGS
                                          ${_COMPILE_FLAGS})
  endif()

  set(PUBLIC_INCLUDES
      "$<BUILD_INTERFACE:${FCPPT_UTILS_PROJECT_BINARY_DIR}/include>"
      "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>" ${_INCLUDE_DIRS})

  if(NOT ${VARIANT} STREQUAL "INTERFACE")
    target_include_directories(${TARGET_NAME} PRIVATE ${PUBLIC_INCLUDES})

    target_include_directories(${TARGET_NAME} SYSTEM
                               PRIVATE ${_SYSTEM_INCLUDE_DIRS})

    if("${_HAS_IMPL_DIR}")
      target_include_directories(
        ${TARGET_NAME}
        PRIVATE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/impl/include>")
    endif()
  endif()

  target_include_directories(
    ${TARGET_NAME} INTERFACE ${PUBLIC_INCLUDES}
                             "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

  target_include_directories(${TARGET_NAME} SYSTEM
                             INTERFACE ${_SYSTEM_INCLUDE_DIRS})

  fcppt_utils_interface_static_link(${TARGET_NAME} ${VARIANT}
                                    "${ALDA_STATIC_LINK_FLAG}")

  if(NOT ${VARIANT} STREQUAL "INTERFACE")
    target_link_libraries(${TARGET_NAME} PRIVATE ${_LINK_LIBS})
  endif()

  target_link_libraries(${TARGET_NAME} INTERFACE ${_INTERFACE_LINK_LIBS})

  if(NOT ${VARIANT} STREQUAL "INTERFACE")
    target_compile_definitions(${TARGET_NAME} PRIVATE ${_COMPILE_DEFINITIONS})
  endif()

  target_compile_definitions(${TARGET_NAME} INTERFACE ${_COMPILE_DEFINITIONS})

  fcppt_utils_export_install_target(${TARGET_NAME})
endfunction()

function(add_alda_library LIBNAME)
  set(OPTION_ARGS HAS_IMPL_DIR)

  set(MULTI_ARGS COMPILE_FLAGS COMPILE_DEFINITIONS INCLUDE_DIRS
                 SYSTEM_INCLUDE_DIRS LINK_LIBS INTERFACE_LINK_LIBS)

  string(TOUPPER ${LIBNAME} LIBNAME_UPPER)

  fcppt_generate_symbol_header(
    STATIC_LINK_FLAG "${ALDA_STATIC_LINK_FLAG}" EXPORTS_NAME "${LIBNAME}"
    SYMBOL_NAME "${LIBNAME_UPPER}_DETAIL")

  add_alda_library_base(${LIBNAME} "INTERFACE" ${ARGN})

  if(ENABLE_SHARED)
    add_alda_library_base(${LIBNAME} "SHARED" ${ARGN})
  endif()

  if(ENABLE_STATIC)
    add_alda_library_base(${LIBNAME} "STATIC" ${ARGN})
  endif()

  install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
          DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
endfunction()

install(DIRECTORY ${FCPPT_UTILS_PROJECT_BINARY_DIR}/include/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

fcppt_utils_load_source_files(files.txt ALDA_FILES)

add_alda_library(
  alda
  INTERFACE_LINK_LIBS
  fcppt_core_interface
  fcppt_log_interface
  LINK_LIBS
  ${fcppt_core_TARGET}
  ${fcppt_log_TARGET})

option(ENABLE_NET "Build the alda_net library" ON)

if(ENABLE_NET)
  add_subdirectory(net)
endif()

fcppt_utils_generate_config(CONFIG_PATH ${FCPPT_UTILS_PROJECT_SOURCE_DIR})
