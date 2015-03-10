#ifndef EXTTREEMODEL_H
#define EXTTREEMODEL_H
#include<QAbstractItemModel>
#include<QList>
#include<QString>
#include"StatisticsThread.h"

class Item;

class ExtTreeModel : public QAbstractItemModel{
    //Q_QBJECT
    
    Item* root;
    StatisticsThread* Stat;
    Item* Classify(QString);
public:
    ExtTreeModel(QObject*, StatisticsThread*);
    ~ExtTreeModel();
    // QAbstractItemModel interface
public:
    QModelIndex index(int, int, const QModelIndex &) const;
    QModelIndex parent(const QModelIndex &) const;
    int rowCount(const QModelIndex &) const;
    int columnCount(const QModelIndex &) const;
    QVariant data(const QModelIndex &, int) const;
    Qt::ItemFlags flags(const QModelIndex &) const;
    void SetDir(const QModelIndex&);
};

class Item{
public:
    Item* Parent;
    QList<Item*> Child;
    QString str;
    quint64 sz;
    
    Item(Item* = 0, QString="", int = 0);
    ~Item();
    void push(QString, int);
    QVariant data(int);
};

#endif // EXTTREEMODEL_H
