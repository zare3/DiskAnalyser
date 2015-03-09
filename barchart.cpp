#include "barchart.h"

BarChart::BarChart(QWidget* parent) : QWidget(parent)
{
    this->index = 1;
}


void BarChart::paintEvent(QPaintEvent *e)
{
    qDebug () << "WE ARE OUT";
    QWidget::paintEvent(e);
    if (index!=-1)
    {
        qDebug () << "WE ARE IN";
        QPainter painter;
        painter.begin(this);
        Nightcharts PieChart;
        PieChart.setType(Nightcharts::Histogramm);//{Histogramm,Pie,DPie};
        PieChart.setLegendType(Nightcharts::Vertical);//{Round,Vertical}
        PieChart.setCords((this->width()/4)-40,20,this->width()/2,this->height()/2);
        PieChart.addPiece("User_1",Qt::green,20);
        PieChart.addPiece("User_2",Qt::green,40);
        PieChart.addPiece("User_3",Qt::green,40);
        PieChart.draw(&painter);
        PieChart.drawLegend(&painter);
    }
}

void BarChart::setIndex(int index)
{
    this->index = index;
}
