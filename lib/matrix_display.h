#ifndef MATRIX_DISPLAY_H
#define MATRIX_DISPLAY_H

#include <gnuradio/qtgui/form_menus.h>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <qwt_color_map.h>
#include <qwt_interval.h>
#include <qwt_matrix_raster_data.h>
#include <qwt_plot.h>
#include <qwt_plot_spectrogram.h>
#include <qwt_scale_widget.h>
#include <QAction>
#include <QApplication>
#include <QFileDialog>
#include <QMenu>
#include <QMouseEvent>
#include <QPixmap>
#include <QVector>
#include <vector>
class matrix_display : public QWidget
{
    Q_OBJECT

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
    QMenu* d_menu;
    QAction* d_save_act;
    bool d_menu_on;
    bool d_stop_state;
    QAction* d_stop_act;
    QMenu* d_contour_menu;
    QMenu* d_interpolation_menu;

public:
    explicit matrix_display(const std::string& name,
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
                            QWidget* parent = nullptr);
    ~matrix_display();

    void set_contour(bool contour);
    void set_color_map(const std::string& color_map);
    void set_interpolation(const std::string& interpolation);
    void set_x_axis_label(const std::string& x_axis_label);
    void set_y_axis_label(const std::string& y_axis_label);
    void set_z_axis_label(const std::string& z_axis_label);
    void initialize_mouse_actions();

public slots:
    void set_data(QVector<double> data);
    void save_figure();
    void mousePressEvent(QMouseEvent* e);
    void set_stop(bool on);
    void set_stop();
    void contour(bool contour);
    void interpolation(const std::string& interpolation);
};
#endif // MATRIX_DISPLAY_H
