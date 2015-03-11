#include "barchart.h"

BarChart::BarChart(QWidget* parent) : QWidget(parent)
{
    this->index = 1;
    this->pieces = new QVector<Piece>();
}


void BarChart::paintEvent(QPaintEvent *e)
{
    //qDebug () << "WE ARE OUT";
    QWidget::paintEvent(e);
    if (index!=-1)
    {
        //qDebug () << "WE ARE IN";
        QPainter painter;
        painter.begin(this);
        Nightcharts PieChart;
        PieChart.setType(Nightcharts::Histogramm);//{Histogramm,Pie,DPie};
        PieChart.setLegendType(Nightcharts::Vertical);//{Round,Vertical}
        PieChart.setCords((this->width()/4)-40,20,this->width()/2,this->height()/2);

        for (int i=0; i<pieces->size(); i++)
        {
            PieChart.addPiece(pieces->at(i).name,pieces->at(i).color,pieces->at(i).percentage);
        }
        PieChart.draw(&painter);
        PieChart.drawLegend(&painter);
    }
}

void BarChart::setData(int index,QVector<Piece>* pieces)
{
    this->index = index;
    this->pieces = pieces;
}
