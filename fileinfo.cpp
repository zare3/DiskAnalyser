#include "fileinfo.h"

#include <QFileSystemModel>
#include <QString>
#include <QDir>
#include <QFile>
#include <QMap>
#include <QFileInfo>

FileInfo :: FileInfo (QFileSystemModel* file)
{
    // initializes all variables
    this->file = file;
    permissions = "";
    file_permissions = 0;
    permissionsGrid.resize(4);
    for (int i=0; i<4; i++)
        permissionsGrid[i].resize(3);
}

QString FileInfo :: getName(const QString & filepath)
{
    // gets directory's name
    return (file->fileName(file->index(filepath)));
}

QString FileInfo :: getType(const QString & filepath)
{
    // gets directory's type
    return (file ->type(file->index(filepath)));
}

qint64 FileInfo :: getSize(const QString & filepath)
{
    QDir dir(filepath);
    qint64 sum = 0;
    // find info about the file
    QFileInfo file_info = file->fileInfo(file->index(filepath));

    // if the path is that of a file, get its size
    if (file_info.isFile())
    {
        return (file->size(file->index(filepath)));
    }
    else
    {
        // if the path is that of a folder, get the size of the content files
        // get a list of the directories inside the current directory
        QFileInfoList dList = dir.entryInfoList(QDir::Files | QDir::Dirs |  QDir::NoDotAndDotDot | QDir::NoSymLinks) ;

        // for each entry in the list of directories, search for the files' size (recursion)
        for(int i = 0; i < dList.size(); i++)
            sum += getSize(dList[i].absoluteFilePath());
        return sum;
    }
}

QVector<QVector<bool> >  FileInfo :: getPermissions(const QString & filepath)
{
    // recieves directory's permissions as binary
    file_permissions = file->permissions(file->index(filepath));

    permissionsGrid[ownerRow][readCol] = (file_permissions & 0x4000) ? 1 : 0;
    permissionsGrid[ownerRow][writeCol] = (file_permissions & 0x2000) ? 1: 0;
    permissionsGrid[ownerRow][execCol] = (file_permissions & 0x1000) ? 1: 0;
    permissionsGrid[userRow][readCol] = (file_permissions & 0x0400) ? 1: 0;
    permissionsGrid[userRow][writeCol] = (file_permissions & 0x0200) ? 1: 0;
    permissionsGrid[userRow][execCol] = (file_permissions & 0x0100) ? 1: 0;
    permissionsGrid[groupRow][readCol] = (file_permissions & 0x0040) ? 1: 0;
    permissionsGrid[groupRow][writeCol] = (file_permissions & 0x0020) ? 1: 0;
    permissionsGrid[groupRow][execCol] = (file_permissions & 0x0010) ? 1: 0;
    permissionsGrid[otherRow][readCol] = (file_permissions & 0x0004) ? 1: 0;
    permissionsGrid[otherRow][writeCol] = (file_permissions & 0x0002) ? 1: 0;
    permissionsGrid[otherRow][execCol] = (file_permissions & 0x0001) ? 1: 0;

    return permissionsGrid;
}

/*
QString FileInfo ::getOwner(const QString & filepath)
{
    QFileInfo file_info = file->fileInfo(file->index(filepath));
    return file_info.owner();
}
*/

void FileInfo :: calcOwners(const QString& filepath)
{
    uint id;                                        // owner ID
    QDir dir(filepath);                             // QDir pointing to the 'filepath' directory
    statistics st;                                  // used to save name and number of files of owner

    // save file index
    index = file->index(filepath);

    // find info about the file
    QFileInfo file_info = file->fileInfo(file->index(filepath));

    // if the path is that of a file, find its owner
    if(file_info.isFile())
    {
        // find the owner of the file
        id = file_info.ownerId();

        // search for the owner in the map
        QMap <uint, statistics> ::iterator i = owners.find(id);

        // if found, update file_count of that file
        if (i != owners.end() && i.key() == id  )
            (i.value()).file_count = (i.value()).file_count + 1;

        // if not found, and new node in list for the owner
        else
        {
            st.name = file_info.owner();                // get owner name
            st.file_count = 1;                          // set count with 1 (current file)
            owners.insert(id, st);                      // insert these data in the map
        }

    }

    // else if the directory is not a file
    else
    {
        // get a list of the directories inside the current directory
        QFileInfoList dList = dir.entryInfoList(QDir::Files | QDir::Dirs | QDir::Hidden |  QDir::NoDotAndDotDot | QDir::NoSymLinks) ;

        // for each entry in the list of directories, search for the files' owners (recursion)
        for(int i = 0; i < dList.size(); i++)
            calcOwners(dList[i].absoluteFilePath());

        //IndexedOwners.insert(index, owners);
    }
}


void FileInfo :: calcGroups(const QString& filepath)
{
    uint id;                                        // group ID
    QDir dir(filepath);                             // QDir pointing to the 'filepath' directory
    statistics st;                                  // used to save name and number of files of group

    // save file index
    index = file->index(filepath);

    // find info about the file
    QFileInfo file_info = file->fileInfo(file->index(filepath));

    // if the path is that of a file, find its group
    if(file_info.isFile())
    {
        // find the group of the file
        id = file_info.groupId();

        // search for the group in the map
        QMap <uint, statistics> ::iterator i = groups.find(id);

        // if found, update file_count of that file
        if (i != groups.end() && i.key() == id  )
            (i.value()).file_count = (i.value()).file_count + 1;

        // if not found, and new node in list for the group
        else
        {
            st.name = file_info.group();                // get group name
            st.file_count = 1;                          // set count with 1 (current file)
            groups.insert(id, st);                      // insert these data in the map
        }

    }

    // else if the directory is not a file
    else
    {
        // get a list of the directories inside the current directory
        QFileInfoList dList = dir.entryInfoList(QDir::Files | QDir::Dirs |  QDir::NoDotAndDotDot | QDir::NoSymLinks) ;

        // for each entry in the list of directories, search for the files' owners (recursion)
        for(int i = 0; i < dList.size(); i++)
            calcGroups(dList[i].absoluteFilePath());

        //IndexedGroups.insert(index, groups);
    }

}

/*
QString FileInfo ::displayInfo()
{
    // this function returns the string message for display of info
    return ("Name: " + filename + "\n" +
            "Path: " + path + "\n" +
            "Size: " + QString::number(size) + " bytes\n" +
            "Type: " + type + "\n"
            );
}
*/

QString FileInfo ::displayPermissions()
{
    // this function returns the string message for display of permissions
    return ("Permissions: \n" + permissions + "\n");
}

QString FileInfo ::displayOwners()
{
    QString message = "";
    QMap <uint, statistics> :: iterator i  = owners.begin();

    for(i = owners.begin() ; i != owners.end();  i++)
        message += "Owner Name:" + (i.value()).name + "\nNumber of owned files: " + QString ::number((i.value()).file_count) + "\n";

    owners.clear();

    return message;// + displayGroups();
}

/*
QString FileInfo :: displayIndexedOwners ()
{
    QString message = "";
    QMap <QModelIndex, QMap<uint, statistics> > :: iterator i  = IndexedOwners.begin();

    for(i = IndexedOwners.begin() ; i != IndexedOwners.end();  i++)
        message += "Owner Name:" + ((i.value()).value()).name + "\nNumber of owned files: " + QString ::number((i.value()).file_count) + "\n";

    IndexedOwners.clear();

    return message;
}
*/


QString FileInfo ::displayGroups()
{
    QString message = "";
    QMap <uint, statistics> :: iterator i  = groups.begin();

    for(i = groups.begin() ; i != groups.end();  i++)
        message += "Group Name:" + (i.value()).name + "\nNumber of owned files: " + QString ::number((i.value()).file_count) + "\n";

    groups.clear();

    return message;
}

QVector<UserOwner>* FileInfo::getOwners()
{
    QVector<UserOwner>* userOwners = new QVector<UserOwner>();
    QMap <uint, statistics> :: iterator i  = owners.begin();

    for(i = owners.begin() ; i != owners.end();  i++)
    {
        UserOwner t;
        t.ownerName = (i.value()).name;
        t.numOwnedFiles = QString ::number(i.value().file_count);
        userOwners->push_back(t);
    }

    owners.clear();

    return userOwners;
}

QVector<GroupOwner>* FileInfo::getGroups()
{

    QVector<GroupOwner>* groupsOwners = new QVector<GroupOwner>();
    QMap <uint, statistics> :: iterator i  = groups.begin();

    for(i = groups.begin() ; i != groups.end();  i++)

    {
        GroupOwner t;
        t.groupName = (i.value()).name;
        t.numOwnedFiles = QString ::number(i.value().file_count);
        groupsOwners->push_back(t);

   }
    groups.clear();

    return groupsOwners;


}


/*
QString FileInfo ::displayGroups(QString filepath)
{
    QFileInfo file_info = file->fileInfo(file->index(filepath));
    return (file_info.group() + QString::number(file_info.groupId()));

}
*/
