#ifndef BARCHART_H
#define BARCHART_H


#include <QWidget>
#include <QDebug>
#include "nightchart.h"

class BarChart : public QWidget
{
public:
    Q_OBJECT
public:
    BarChart(QWidget* );
    virtual void paintEvent (QPaintEvent* );
    void setIndex(int index);
 private:
    int index;
};

#endif // BARCHART_H
