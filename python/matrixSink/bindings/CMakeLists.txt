# Copyright 2020 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

########################################################################
# Check if there is C++ code at all
########################################################################
if(NOT matrixSink_sources)
    MESSAGE(STATUS "No C++ sources... skipping python bindings")
    return()
endif(NOT matrixSink_sources)

########################################################################
# Check for pygccxml
########################################################################
GR_PYTHON_CHECK_MODULE_RAW(
    "pygccxml"
    "import pygccxml"
    PYGCCXML_FOUND
    )

include(GrPybind)

########################################################################
# Python Bindings
########################################################################

list(APPEND matrixSink_python_files
    matrix_sink_python.cc python_bindings.cc)

GR_PYBIND_MAKE_OOT(matrixSink
   ../../..
   gr::matrixSink
   "${matrixSink_python_files}")

# copy bindings extension for use in QA test module
add_custom_command(TARGET matrixSink_python POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:matrixSink_python>
    ${PROJECT_BINARY_DIR}/test_modules/gnuradio/matrixSink/
)

install(TARGETS matrixSink_python DESTINATION ${GR_PYTHON_DIR}/gnuradio/matrixSink COMPONENT pythonapi)
