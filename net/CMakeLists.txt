find_package(Boost 1.70.0 CONFIG REQUIRED)

fcppt_utils_load_source_files(net/files.txt ALDA_NET_FILES)

if(WIN32)
  set(ASIO_LIBS ws2_32 mswsock)
elseif(UNIX)
  set(ASIO_LIBS pthread)

  set(ASIO_OPTIONS -pthread)
endif()

add_alda_library(
  alda_net
  HAS_IMPL_DIR
  COMPILE_DEFINITIONS
  BOOST_ALL_NO_LIB
  BOOST_ASIO_HAS_STD_INVOKE_RESULT
  COMPILE_FLAGS
  ${ASIO_OPTIONS}
  INTERFACE_LINK_LIBS
  fcppt_boost_interface
  fcppt_core_interface
  fcppt_log_interface
  LINK_LIBS
  ${alda_TARGET}
  fcppt_boost_interface
  ${fcppt_core_TARGET}
  ${fcppt_log_TARGET}
  ${ASIO_LIBS}
  SYSTEM_INCLUDE_DIRS
  ${Boost_INCLUDE_DIRS})
