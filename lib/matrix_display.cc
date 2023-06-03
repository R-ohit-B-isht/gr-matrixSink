#include "matrix_display.h"
#include <vector>

matrix_display::matrix_display(const std::string& name,
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
            :QWidget(parent),
                d_vlen(vlen),
                d_num_cols(num_cols),
                d_x_start(x_start),
                d_x_end(x_end),
                d_y_start(y_start),
                d_y_end(y_end),
                d_z_max(z_max),
                d_z_min(z_min)

                                                    
{

    for ( double level = 0.5; level < 10.0; level += 1.0 )
        d_contour_levels += level;

    d_plot = new QwtPlot;

    d_colorMap= new QwtLinearColorMap( Qt::darkCyan, Qt::red ,QwtColorMap::RGB );
    d_colorMap->addColorStop(0.1,Qt::cyan);
    d_colorMap->addColorStop(0.6,Qt::green);
    d_colorMap->addColorStop(0.95,Qt::yellow);
    
    d_x_axis = d_plot->axisWidget(QwtPlot::xBottom);
    d_x_axis->setTitle(x_axis_label.c_str());
    d_plot->enableAxis(QwtPlot::xBottom, true);

    d_y_axis = d_plot->axisWidget(QwtPlot::yLeft);
    d_y_axis->setTitle(y_axis_label.c_str());
    d_plot->enableAxis(QwtPlot::yLeft, true);

    d_z_axis = d_plot->axisWidget(QwtPlot::yRight);
    d_z_axis->setTitle(z_axis_label.c_str());
    d_z_axis->setColorBarEnabled( true );
    d_z_axis->setColorMap( QwtInterval( d_z_min, d_z_max ) , (QwtColorMap*)d_colorMap);
    d_plot->setAxisScale( QwtPlot::yRight, 0, 10.0 );
    d_plot->enableAxis(QwtPlot::yRight, true);


    d_spectrogram = new QwtPlotSpectrogram;
    d_spectrogram->setDisplayMode( QwtPlotSpectrogram::DisplayMode::ContourMode, true );
    d_spectrogram->setContourLevels( d_contour_levels );
    d_spectrogram->setColorMap( d_colorMap );

    d_spectrogram->attach(d_plot);
    d_plot->repaint();
    d_plot->show();

    d_hLayout = new QHBoxLayout();
    d_hLayout->addWidget(d_plot);
    this->setLayout(d_hLayout);

}

void matrix_display::set_data(std::vector<double> data) {

    QVector<double> qvector_data;
    //convert from std::vector to QVector
    for (unsigned int i = 0; i < d_vlen; i++) {
        qvector_data.push_back(data[i]);
    }

    d_data = new QwtMatrixRasterData;
    d_data->setValueMatrix(qvector_data, d_num_cols);
    d_data->setInterval( Qt::XAxis, QwtInterval( d_x_start, d_x_end ) );
    d_data->setInterval( Qt::YAxis, QwtInterval( d_y_start, d_y_end ) );
    d_data->setInterval( Qt::ZAxis, QwtInterval( d_z_min, d_z_max ) );
    d_spectrogram->setData(d_data);
    d_plot->replot();
    d_plot->repaint();
    d_plot->show();

    update();
}
