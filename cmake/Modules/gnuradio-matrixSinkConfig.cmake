find_package(PkgConfig)

PKG_CHECK_MODULES(PC_GR_MATRIXSINK gnuradio-matrixSink)

FIND_PATH(
    GR_MATRIXSINK_INCLUDE_DIRS
    NAMES gnuradio/matrixSink/api.h
    HINTS $ENV{MATRIXSINK_DIR}/include
        ${PC_MATRIXSINK_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    GR_MATRIXSINK_LIBRARIES
    NAMES gnuradio-matrixSink
    HINTS $ENV{MATRIXSINK_DIR}/lib
        ${PC_MATRIXSINK_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
          )

include("${CMAKE_CURRENT_LIST_DIR}/gnuradio-matrixSinkTarget.cmake")

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GR_MATRIXSINK DEFAULT_MSG GR_MATRIXSINK_LIBRARIES GR_MATRIXSINK_INCLUDE_DIRS)
MARK_AS_ADVANCED(GR_MATRIXSINK_LIBRARIES GR_MATRIXSINK_INCLUDE_DIRS)
