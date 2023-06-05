#ifndef MATRIX_DISPLAY_SIGNAL_H
#define MATRIX_DISPLAY_SIGNAL_H

#include <QObject>
#include <QVector>

class matrix_display_signal : public QObject
{
    Q_OBJECT

public:
    matrix_display_signal() {}
    ~matrix_display_signal() {}    

signals:
    void dataReady(QVector<double> data);
    
};

#endif /* INCLUDED_MATRIXSINK_MATRIX_SINK_IMPL_H */