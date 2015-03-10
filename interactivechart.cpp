#include "interactivechart.h"

InteractiveChart::InteractiveChart(QWidget *parent) :
    QWidget(parent)
{
    chart = new QWebView();
    chart->setUrl(QUrl("qrc:/folder/icons/Sunburst.html"));

}

QWebView* InteractiveChart::GetChart()
{
  return chart;
}
