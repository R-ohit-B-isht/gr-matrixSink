/* -*- c++ -*- */
/*
 * Copyright 2023 gr-matrixSink author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "matrix_sink_impl.h"
#include <gnuradio/io_signature.h>
#include <QDebug>
namespace gr {
namespace matrixSink {

using input_type = float;
matrix_sink::sptr matrix_sink::make(const std::string& name,
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
                     QWidget* parent)
{
    return gnuradio::make_block_sptr<matrix_sink_impl>(
     name,
     num_cols,
     vlen, 
     x_start, 
     x_end, 
     y_start, 
     y_end, 
     z_max, 
     z_min, 
     x_axis_label, 
     y_axis_label, 
     z_axis_label, 
     parent);
}


/*
 * The private constructor
 */
matrix_sink_impl::matrix_sink_impl(const std::string& name,
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
                     QWidget* parent)
    : gr::sync_block("matrix_sink",
                     gr::io_signature::make(
                         1, 1, sizeof(input_type)* vlen),
                     gr::io_signature::make(0, 0, 0)),
                     d_vlen(vlen),
                     d_name(name)
{
    if (qApp != nullptr) {
        d_qApplication = qApp;
    } else {
        d_qApplication = new QApplication(d_argc, &d_argv);
    }
    d_display = new matrix_display(name,
     num_cols,
     vlen, 
     x_start, 
     x_end, 
     y_start, 
     y_end, 
     z_max, 
     z_min, 
     x_axis_label, 
     y_axis_label, 
     z_axis_label, 
     parent);
     
}

/*
 * Our virtual destructor.
 */
matrix_sink_impl::~matrix_sink_impl() {delete d_argv;}

void matrix_sink_impl::exec_() {d_qApplication->exec();}

QWidget* matrix_sink_impl::qwidget() {return (QWidget*)d_display;}

int matrix_sink_impl::work(int noutput_items,
                           gr_vector_const_void_star& input_items,
                           gr_vector_void_star& output_items)
{
    auto in = static_cast<const input_type*>(input_items[0]);
    //log the input size
    

    // Do <+signal processing+>

        std::vector<double> data(in , in + d_vlen);
        d_display->set_data(data);


    
    // Tell runtime system how many output items we produced.
    return noutput_items;
}

} /* namespace matrixSink */
} /* namespace gr */



