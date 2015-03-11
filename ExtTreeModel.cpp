#include "ExtTreeModel.h"
#include <QDebug>
#include <QFileSystemModel>

ExtTreeModel::ExtTreeModel(QObject* parent, StatisticsThread* ptr) : QAbstractItemModel(parent){
    Stat = ptr;
    root = new Item();
    root->push("Document", 0);
    root->push("Audio", 0);
    root->push("Image", 0);
    root->push("Archive", 0);
    root->push("Others", 0);
    root->Child[0]->icon = QIcon(QPixmap(":/folder/icons/document.png"));
    root->Child[1]->icon = QIcon(QPixmap(":/folder/icons/music.png"));
    root->Child[2]->icon = QIcon(QPixmap(":/folder/icons/image.png"));
    root->Child[3]->icon = QIcon(QPixmap(":/folder/icons/compressed.png"));
    root->Child[4]->icon = QIcon(QPixmap(":/folder/icons/sadFace.png"));
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
    return 2;
}
QVariant ExtTreeModel::data(const QModelIndex & index, int role) const{
    if(!index.isValid())
        return QVariant();
    if(role == Qt::DecorationRole && index.column()==0)
        return static_cast<Item*>(index.internalPointer())->icon;
    if(role != Qt::DisplayRole)
        return QVariant();
    return static_cast<Item*>(index.internalPointer())->data(index.column());
}
Qt::ItemFlags ExtTreeModel::flags(const QModelIndex &index) const{
    if (!index.isValid()) return 0;
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

Item *ExtTreeModel::Classify(QString ext){
    if(ext == "doc" || ext == "docx" || ext == "ods")
        return root->Child[0];
    else if(ext == "mp3" || ext == "wav" || ext == "ogg")
        return root->Child[1];
    else if(ext == "png")
        return root->Child[2];
    else if(ext == "zip" || ext == "tar" || ext == "rar")
        return root->Child[3];
    else
        return root->Child[4];
}
void ExtTreeModel::SetDir(const QModelIndex& dir){
    QFileInfo fInfo = static_cast<const QFileSystemModel*>(dir.model())->fileInfo(dir);
    const StatisticsThread::ExtStat * const data = Stat->_getExt(dir);
    for(int i = 0; i < root->Child.size(); i++){
        for(int j = 0; j < root->Child[i]->Child.size(); j++)
            delete root->Child[i]->Child[j];
        root->Child[i]->sz = 0;
        root->Child[i]->Child.clear();
    }
    if(data == 0){
        QFileInfo fInfo = static_cast<const QFileSystemModel*>(dir.model())->fileInfo(dir);
        Classify(fInfo.suffix())->push(fInfo.suffix(), 1);
    }
    else
    for(QMap<QString, quint64>::const_iterator it = data->nExt.begin(); it != data->nExt.end(); it++)
        Classify(it.key())->push(it.key(), it.value());
}

Item::Item(Item* p, QString _str, int _sz){
    str = _str;
    sz = _sz;
    Parent = p;
    if(p != 0){
        icon = p->icon;
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
        return QVariant(str);
    case 1:
        return QVariant(sz);
    default:
        return QVariant();
    }
}
