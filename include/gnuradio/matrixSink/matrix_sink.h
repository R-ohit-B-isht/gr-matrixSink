/* -*- c++ -*- */
/*
 * Copyright 2023 gr-matrixSink author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_MATRIXSINK_MATRIX_SINK_H
#define INCLUDED_MATRIXSINK_MATRIX_SINK_H

#include <gnuradio/matrixSink/api.h>
#include <gnuradio/sync_block.h>
#include <qapplication.h>
#include <QWidget>

namespace gr {
namespace matrixSink {

/*!
 * \brief <+description of block+>
 * \ingroup matrixSink
 *
 */
class MATRIXSINK_API matrix_sink : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<matrix_sink> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of matrixSink::matrix_sink.
     *
     * To avoid accidental use of raw pointers, matrixSink::matrix_sink's
     * constructor is in a private implementation
     * class. matrixSink::matrix_sink::make is the public interface for
     * creating new instances.
     */
    static sptr make(const std::string& name,
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

    virtual void exec_() = 0;
    virtual QWidget* qwidget() = 0;
};

} // namespace matrixSink
} // namespace gr

#endif /* INCLUDED_MATRIXSINK_MATRIX_SINK_H */
