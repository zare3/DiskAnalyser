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
        PieChart.addPiece(this->percentage_1_name,Qt::red,percentage_1);
        PieChart.addPiece(this->percentage_2_name,Qt::green,percentage_2);
        PieChart.draw(&painter);
        PieChart.drawLegend(&painter);
    }
}

void PieChart::setData(int index, double percentage_1, double percentage_2, QString percentage_1_name, QString percentage_2_name)
{
    this->index = index;
    this->percentage_1 = percentage_1;
    this->percentage_2 = percentage_2;
    this->percentage_1_name = percentage_1_name;
    this->percentage_2_name = percentage_2_name;
}
