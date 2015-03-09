#include "ExtTreeModel.h"
#include <QDebug>

ExtTreeModel::ExtTreeModel(QObject* parent, StatisticsThread* ptr) : QAbstractItemModel(parent){
    Stat = ptr;
    root = new Item();
}
ExtTreeModel::~ExtTreeModel(){
    if(root) delete root;
}

QModelIndex ExtTreeModel::index(int row, int column, const QModelIndex &parent) const{
    if(!hasIndex(row, column, parent)) return QModelIndex();
    
    Item* ptr;
    if(!parent.isValid()) ptr = root;
    else ptr = static_cast<Item*>(parent.internalPointer());
    
    if(row < ptr->Child.size()) return createIndex(row, column, ptr->Child[row]);
    else return QModelIndex();
}
QModelIndex ExtTreeModel::parent(const QModelIndex &idx) const{
    if(!idx.isValid()) return QModelIndex();
    Item* ptr = static_cast<Item*>(idx.internalPointer())->Parent;
    if(ptr) return createIndex(root->Child.indexOf(ptr), 0, ptr);
    else return QModelIndex();
}
int ExtTreeModel::rowCount(const QModelIndex &parent) const{
    if(parent.column() > 0) 
        return 0;
    Item* ptr;
    if(!parent.isValid())
        return root->Child.size();
    else
        ptr = static_cast<Item*>(parent.internalPointer());
    return ptr->Child.size();
}
int ExtTreeModel::columnCount(const QModelIndex &parent) const{
    return 3;
}
QVariant ExtTreeModel::data(const QModelIndex & index, int role) const{
    if(!index.isValid())
        return QVariant();
    if(role != Qt::DisplayRole)
        return QVariant();
    return static_cast<Item*>(index.internalPointer())->data(index.column());
}
Qt::ItemFlags ExtTreeModel::flags(const QModelIndex &index) const{
    if (!index.isValid()) return 0;
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

void ExtTreeModel::SetDir(const QModelIndex& dir){
    while(!Stat->isReady());
    const StatisticsThread::ExtStat* const data = Stat->getExt(dir);
    delete root;
    root = new Item();
    root->push("Document", 0);
    root->push("Audio", 0);
    root->push("Archive", 0);
    root->push("Others", 0);
    for(QMap<QString, quint64>::const_iterator it = data->nExt.begin(); it != data->nExt.end(); it++){
        if(it.key() == "doc" || it.key() == "docx" || it.key() == "ods")
            root->Child[0]->push(it.key(), it.value());
        else if(it.key() == "mp3" || it.key() == "wav" || it.key() == "ogg")
            root->Child[1]->push(it.key(), it.value());
        else if(it.key() == "zip" || it.key() == "tar" || it.key() == "rar")
            root->Child[2]->push(it.key(), it.value());
        else
            root->Child[3]->push(it.key(), it.value());
    }
    //root->Child[0]->push("doc", 100);
    //root->Child[0]->push("docx", 1000);
    
    //root->Child[1]->push("mp3", 1040);
    //root->Child[1]->push("wav", 1080);
    //root->Child[1]->push("ogg", 10);
    
    //root->Child[2]->push("zip", 50);
    //root->Child[2]->push("rar", 90);
    //root->Child[2]->push("tar", 500);
    
    //root->Child[3]->push("meeh", 1);
    //root->Child[3]->push("unkown", 5);
    //root->Child[3]->push("a5r str", 4);
}

Item::Item(Item* p, QString _str, int _sz){
    str = _str;
    sz = _sz;
    Parent = p;
    if(p != 0){
        p->sz += _sz;
    }
}
Item::~Item(){
    for(int i = 0; i < Child.size(); i++) delete Child[i];
}
void Item::push(QString _str, int _sz){
    Child.push_back(new Item(this, _str, _sz));
}
QVariant Item::data(int idx){
    switch(idx){
    case 0:
    case 1:
        return QVariant(str);
    case 2:
        return QVariant(sz);
    default:
    return QVariant();
    }
}
