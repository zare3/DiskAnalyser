#ifndef PIECHART_H
#define PIECHART_H

#include <QWidget>
#include <QDebug>
#include "nightchart.h"

class PieChart : public QWidget
{
    Q_OBJECT
public:
    PieChart(QWidget* );
    virtual void paintEvent (QPaintEvent* );
    void setIndex(int index);
 private:
    int index;
};

#endif // PIECHART_H
