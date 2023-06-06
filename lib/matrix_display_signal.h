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
    void data_ready(QVector<double> data);
};

#endif /* MATRIX_DISPLAY_SIGNAL_H */