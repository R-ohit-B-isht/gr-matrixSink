/* -*- c++ -*- */
/*
 * Copyright 2023 gr-matrixSink author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_MATRIXSINK_MATRIX_SINK_IMPL_H
#define INCLUDED_MATRIXSINK_MATRIX_SINK_IMPL_H

#include "matrix_display_signal.h"
#include "matrix_display.h"

#include <gnuradio/matrixSink/matrix_sink.h>
#include <qapplication.h>
#include <QObject>
#include <vector>
namespace gr {
namespace matrixSink {

class matrix_sink_impl : public matrix_sink //, public QObject
{
    //Q_OBJECT
private:
    // Nothing to declare in this block.
    unsigned int d_vlen;
    std::string d_name;
    std::vector<double> d_data;
    char d_zero = 0;
    int d_argc = 1;
    char* d_argv = &d_zero;
    matrix_display* d_display;
    matrix_display_signal* d_signal;

public:
    matrix_sink_impl(const std::string& name,
                     unsigned int num_cols,
                     unsigned int vlen,
                     double x_start,
                     double x_end,
                     double y_start,
                     double y_end,
                     double z_max,
                     double z_min,
                     const std::string& x_axis_label,
                     const std::string& y_axis_label,
                     const std::string& z_axis_label,
                     QWidget* parent = nullptr
                     );
    ~matrix_sink_impl();

    void exec_()override;
    QApplication* d_qApplication;
    QWidget* qwidget() override;

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);

// signals:
//     void data_ready(std::vector<double> data);
};

} // namespace matrixSink
} // namespace gr

#endif /* INCLUDED_MATRIXSINK_MATRIX_SINK_IMPL_H */
