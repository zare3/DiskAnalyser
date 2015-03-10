#ifndef INTERACTIVECHART_H
#define INTERACTIVECHART_H
#include <QtWebKitWidgets/QWebView>
#include <QWidget>

class InteractiveChart : public QWidget
{
    Q_OBJECT
    QWebView* chart;
public:
    explicit InteractiveChart(QWidget *parent = 0);
    QWebView* GetChart();
signals:

public slots:

};

#endif // INTERACTIVECHART_H
