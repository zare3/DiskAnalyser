
#include "fileinfo.h"

#include <QFileSystemModel>
#include <QString>
#include <QDir>
#include <QFile>
#include <QMap>
#include <QFileInfo>

FileInfo :: FileInfo ()
{
    // initializes all variables
    file = new QFileSystemModel;
    permissions = "";
    file_permissions = 0;
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
    // gets directory's size
    return (file->size(file->index(filepath)));
}

QString FileInfo :: getPermissions(const QString & filepath)
{
    // recieves directory's permissions as binary
    file_permissions = file->permissions(file->index(filepath));

    // resets the permissions string message to save new permissions
    permissions  = "";

    // decode the permissions' binary into its equivalent read/write/execute permissions for owner/user/group/others
    permissions = (file_permissions & 0x4000) ? (permissions + "Read Owner\n") : (permissions);
    permissions = (file_permissions & 0x2000) ? (permissions + "Write Owner\n") : (permissions);
    permissions = (file_permissions & 0x1000) ? (permissions + "Execute Owner\n") : (permissions);
    permissions = (file_permissions & 0x0400) ? (permissions + "Read User\n") : (permissions);
    permissions = (file_permissions & 0x0200) ? (permissions + "Write User\n") : (permissions);
    permissions = (file_permissions & 0x0100) ? (permissions + "Execute User\n") : (permissions);
    permissions = (file_permissions & 0x0040) ? (permissions + "Read Group\n") : (permissions);
    permissions = (file_permissions & 0x0020) ? (permissions + "Write Group\n") : (permissions);
    permissions = (file_permissions & 0x0010) ? (permissions + "Execute Group\n") : (permissions);
    permissions = (file_permissions & 0x0004) ? (permissions + "Read Other\n") : (permissions);
    permissions = (file_permissions & 0x0002) ? (permissions + "Write Other\n") : (permissions);
    permissions = (file_permissions & 0x0001) ? (permissions + "Execute Other\n") : (permissions);

    // the returned message is a string with all permisison statuses
    return permissions;
}


/*
QString FileInfo ::getOwner(const QString & filepath)
{
    QFileInfo file_info = file->fileInfo(file->index(filepath));
    return file_info.owner();
}
*/

void FileInfo :: getOwners(const QString& filepath)
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
        QFileInfoList dList = dir.entryInfoList(QDir::Files | QDir::Dirs |  QDir::NoDotAndDotDot | QDir::NoSymLinks) ;

        // for each entry in the list of directories, search for the files' owners (recursion)
        for(int i = 0; i < dList.size(); i++)
            getOwners(dList[i].absoluteFilePath());

        //IndexedOwners.insert(index, owners);
    }
}

void FileInfo :: getGroups(const QString& filepath)
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
            getGroups(dList[i].absoluteFilePath());

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


/*
QString FileInfo ::displayGroups(QString filepath)
{
    QFileInfo file_info = file->fileInfo(file->index(filepath));
    return (file_info.group() + QString::number(file_info.groupId()));

}
*/
