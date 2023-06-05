// # ifdef MATRIX_DISPLAY_H
// # define MATRIX_DISPLAY_H

#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <qwt_plot.h>
#include <qwt_plot_spectrogram.h>
#include <qwt_matrix_raster_data.h>
#include <qwt_color_map.h>
#include <qwt_scale_widget.h>
#include <qwt_interval.h>
#include <vector>
#include <QVector>


class matrix_display : public QWidget
{
    Q_OBJECT
public:
    explicit matrix_display(const std::string& name,
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
                     QWidget* parent = nullptr);

    // ~matrix_display();
public slots:
    void set_data(QVector<double> data);


private:

QwtPlotSpectrogram* d_spectrogram;
QwtPlot* d_plot;
QwtLinearColorMap* d_colorMap;
QwtMatrixRasterData* d_data;
QHBoxLayout* d_hLayout;
QwtScaleWidget* d_x_axis;
QwtScaleWidget* d_y_axis;
QwtScaleWidget* d_z_axis;
unsigned int d_vlen;
unsigned int d_num_cols;
double d_x_start;
double d_x_end;
double d_y_start;
double d_y_end;
double d_z_max;
double d_z_min;
QList<double> d_contour_levels;

};

// #endif // MATRIX_DISPLAY_H




