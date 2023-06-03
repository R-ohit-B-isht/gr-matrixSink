#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# Copyright 2023 gr-matrixSink author.
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

from gnuradio import gr, gr_unittest
# from gnuradio import blocks
try:
  from gnuradio.matrixSink import matrix_sink
except ImportError:
    import os
    import sys
    dirname, filename = os.path.split(os.path.abspath(__file__))
    sys.path.append(os.path.join(dirname, "bindings"))
    from gnuradio.matrixSink import matrix_sink

class qa_matrix_sink(gr_unittest.TestCase):

    def setUp(self):
        self.tb = gr.top_block()

    def tearDown(self):
        self.tb = None

    def test_instance(self):
        # FIXME: Test will fail until you pass sensible arguments to the constructor
        instance = matrix_sink()
        # instance = text_msg('TestString','test',80,10,None)
        # b = sip.wrapinstance(instance.qwidget(),Qt.QWidget)

    def test_001_descriptive_test_name(self):
        # set up fg
        self.tb.run()
        # check data


if __name__ == '__main__':
    gr_unittest.run(qa_matrix_sink)
