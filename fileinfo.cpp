#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "fileinfo.h"

#include <QFileSystemModel>
#include <QString>
#include <QDir>
#include <QTreeView>
#include <QFile>
#include <QTextStream>

FileInfo :: FileInfo ()
{
    // initializes all variables
    file = new QFileSystemModel;
    filename = "";
    path = "";
    type = "";
    permissions = "";
    size = 0;
    file_permissions = 0;

}

void FileInfo ::getInfo(const QString & filepath)
{
    path = filepath;                                    // saves new directory's path

    filename = file->fileName(file->index(path));       // gets directory's name

    type = file ->type(file->index(path));              // obtains directory's type

    size = file->size(file->index(path));               // finds directory's size

    file_permissions = file->permissions(file->index(path));    // recieves directory's permissions as binary

    permissions  = "";                                  // resets the permissions string message to save new permissions

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

}

QString FileInfo ::displayInfo()
{
    // this function returns the string message for display of info
    return ("Name: " + filename + "\n" +
            "Path: " + path + "\n" +
            "Size: " + QString::number(size) + " bytes\n" +
            "Type: " + type + "\n"
            );
}

QString FileInfo ::displayPermissions()
{
    // this function returns the string message for display of permissions
    return ("Permissions: \n" + permissions + "\n");
}
