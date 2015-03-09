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
    void setData(int index, double percentage_1, double percentage_2,QString percentage_1_name, QString percentage_2_name  );
 private:
    int index;
    double percentage_1;
    double percentage_2;
    QString percentage_1_name;
    QString percentage_2_name;
};

#endif // PIECHART_H
