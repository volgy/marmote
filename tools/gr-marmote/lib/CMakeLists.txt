# Copyright 2011,2012 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.

########################################################################
# Setup library
########################################################################
include(GrPlatform) #define LIB_SUFFIX

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})
list(APPEND marmote_sources
    mac_framer_b_impl.cc
    gmsk_packet_sink_b_impl.cc
    mac_deframer_impl.cc
    traffic_generator_impl.cc
    cdma_packet_source_impl.cc
    cdma_packet_sink_impl.cc
    mseq_lfsr.cc
    pn_spreader_f_impl.cc
    pn_synchronizer_impl.cc
    pn_despreader_impl.cc
    cdma_packet_framer_impl.cc
    pn_spreader_b_impl.cc
    pn_despreader_cc_impl.cc
    pn_synchronizer_cc_impl.cc
    gmsk_packet_framer_b_impl.cc
    pn_matched_filter_impl.cc
    peak_tagger_cc_impl.cc
    binary_slicer_fi_impl.cc )

add_library(gnuradio-marmote SHARED ${marmote_sources})
target_link_libraries(gnuradio-marmote ${Boost_LIBRARIES} ${GNURADIO_RUNTIME_LIBRARIES})
set_target_properties(gnuradio-marmote PROPERTIES DEFINE_SYMBOL "gnuradio_marmote_EXPORTS")

########################################################################
# Install built library files
########################################################################
install(TARGETS gnuradio-marmote
    LIBRARY DESTINATION lib${LIB_SUFFIX} # .so/.dylib file
    ARCHIVE DESTINATION lib${LIB_SUFFIX} # .lib file
    RUNTIME DESTINATION bin              # .dll file
)

########################################################################
# Build and register unit test
########################################################################
include(GrTest)

include_directories(${CPPUNIT_INCLUDE_DIRS})
list(APPEND test_marmote_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/test_marmote.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_marmote.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_traffic_generator.cc
)

add_executable(test-marmote ${test_marmote_sources})

target_link_libraries(
  test-marmote
  ${GNURADIO_CORE_LIBRARIES}
  ${Boost_LIBRARIES}
  ${CPPUNIT_LIBRARIES}
  gnuradio-marmote
)

GR_ADD_TEST(test_marmote test-marmote)
