#ifndef BARCHART_H
#define BARCHART_H


#include <QWidget>
#include <QDebug>
#include <QString>
#include <QColor>
#include <QVector>
#include "nightchart.h"

struct Piece
{
    QString name;
    QColor color;
    float percentage;
};

class BarChart : public QWidget
{
public:
    Q_OBJECT
public:
    BarChart(QWidget* );
    virtual void paintEvent (QPaintEvent* );
    void setData(int index, QVector<Piece>*);
 private:
    int index;
    QVector<Piece>* pieces;

};

#endif // BARCHART_H
