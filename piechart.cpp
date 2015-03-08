#include "piechart.h"

PieChart::PieChart(QWidget* parent) : QWidget(parent)
{
    this->index = -1;
}


void PieChart::paintEvent(QPaintEvent *e)
{
    qDebug () << "WE ARE OUT";
    QWidget::paintEvent(e);
    if (index!=-1)
    {
        qDebug () << "WE ARE IN";
        QPainter painter;
        painter.begin(this);
        Nightcharts PieChart;
        PieChart.setType(Nightcharts::Dpie);//{Histogramm,Pie,DPie};
        PieChart.setLegendType(Nightcharts::Vertical);//{Round,Vertical}
        PieChart.setCords((this->width()/4)-40,20,this->width()/2,this->height()/2);
        PieChart.addPiece("Contigous",Qt::green,99.8);
        PieChart.addPiece("Non Contigous",Qt::red,0.2);
        PieChart.draw(&painter);
        PieChart.drawLegend(&painter);
    }
}

void PieChart::setIndex(int index)
{
    this->index = index;
}
