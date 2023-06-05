#include "matrix_display.h"
#include <vector>

matrix_display::matrix_display(const std::string& name,
                               unsigned int num_cols,
                               unsigned int vlen,
                               bool contour,
                               const std::string& color_map,
                               const std::string& interpolation,
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



    d_plot = new QwtPlot;

    set_color_map(color_map);
    
    set_x_axis_label(x_axis_label);
    set_y_axis_label(y_axis_label);
    set_z_axis_label(z_axis_label);


    d_spectrogram = new QwtPlotSpectrogram;
    d_spectrogram->setDisplayMode( QwtPlotSpectrogram::DisplayMode::ImageMode, true );
    set_contour(contour);
    d_spectrogram->setColorMap( d_colorMap );

    d_data = new QwtMatrixRasterData;
    
    d_data->setInterval( Qt::XAxis, QwtInterval( d_x_start, d_x_end ) );
    d_data->setInterval( Qt::YAxis, QwtInterval( d_y_start, d_y_end ) );
    d_data->setInterval( Qt::ZAxis, QwtInterval( d_z_min, d_z_max ) );
    set_interpolation(interpolation);
    d_spectrogram->attach(d_plot);
    d_plot->repaint();
    d_plot->show();

    d_hLayout = new QHBoxLayout();
    d_hLayout->addWidget(d_plot);
    this->setLayout(d_hLayout);

}

void matrix_display::set_contour(bool contour)
{
    if (contour)
    {
        for ( double level = 0.5; level < 10.0; level += 1.0 )
            d_contour_levels += level;
        d_spectrogram->setContourLevels( d_contour_levels );
        d_spectrogram->setDisplayMode( QwtPlotSpectrogram::DisplayMode::ContourMode, true );
    }
    else
        d_spectrogram->setDisplayMode( QwtPlotSpectrogram::DisplayMode::ImageMode, true );
}

void matrix_display::set_color_map(const std::string& color_map) 
{
    if (color_map == "rgb")
    {
        d_colorMap= new QwtLinearColorMap( Qt::darkCyan, Qt::red ,QwtColorMap::RGB );
        d_colorMap->addColorStop(0.1,Qt::cyan);
        d_colorMap->addColorStop(0.6,Qt::green);
        d_colorMap->addColorStop(0.95,Qt::yellow);
    }
    else if (color_map == "indexed")
    {
        d_colorMap = new QwtLinearColorMap(Qt::blue, Qt::red, QwtColorMap::Indexed);
    }
    else if (color_map == "alpha")
    {
        QwtAlphaColorMap *alpha_map= new QwtAlphaColorMap();
        alpha_map->setColor(Qt::darkBlue);
        d_colorMap= (QwtLinearColorMap*)alpha_map;
    }
}

void matrix_display::set_interpolation(const std::string& interpolation) 
{
    //'BilinearInterpolation','BicubicInterpolation','NearestNeighbour'
    if (interpolation == "BilinearInterpolation")
    {
        d_data->setResampleMode(QwtMatrixRasterData::ResampleMode::BilinearInterpolation );
    }
    else if (interpolation == "BicubicInterpolation")
    {
        d_data->setResampleMode(QwtMatrixRasterData::ResampleMode::BicubicInterpolation );
    }
    else if (interpolation == "NearestNeighbour")
    {
        d_data->setResampleMode(QwtMatrixRasterData::ResampleMode::NearestNeighbour );
    }
}

void matrix_display::set_x_axis_label(const std::string& x_axis_label) 
{
    d_x_axis = d_plot->axisWidget(QwtPlot::xBottom);
    d_x_axis->setTitle(x_axis_label.c_str());
    d_plot->enableAxis(QwtPlot::xBottom, true);
}

void matrix_display::set_y_axis_label(const std::string& y_axis_label) 
{
    d_y_axis = d_plot->axisWidget(QwtPlot::yLeft);
    d_y_axis->setTitle(y_axis_label.c_str());
    d_plot->enableAxis(QwtPlot::yLeft, true);
}

void matrix_display::set_z_axis_label(const std::string& z_axis_label) 
{
    d_z_axis = d_plot->axisWidget(QwtPlot::yRight);
    d_z_axis->setTitle(z_axis_label.c_str());
    d_z_axis->setColorBarEnabled( true );
    d_z_axis->setColorMap( QwtInterval( d_z_min, d_z_max ) , (QwtColorMap*)d_colorMap);
    d_plot->setAxisScale( QwtPlot::yRight, d_z_min, d_z_max );
    d_plot->enableAxis(QwtPlot::yRight, true);
}


void matrix_display::set_data(QVector<double> data)
{

    d_data->setValueMatrix(data, d_num_cols);

    d_spectrogram->setData(d_data);
    d_plot->replot();
    
}
