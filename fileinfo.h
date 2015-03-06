#ifndef FILEINFO
#define FILEINFO

#include <QFileSystemModel>
#include <QString>
#include <QDir>
#include <QFile>

class FileInfo
{
public:

    //public member functions
    FileInfo ();                                        // contructor

    void getInfo (const QString&);                      // gets directory credentials
    QString displayInfo();                              // prepares output of info
    QString displayPermissions();                       // prepares output of permissions

private:

    // private variables
    QFileSystemModel *file;                             // used to access file credentials

    QString filename;                                   // file/folder name
    QString path;                                       // file/folder directory
    QString type;                                       // type of directory
    QString permissions;                                // interpreted permissions

    qint64 size;                                        // file size

    QFile::Permissions file_permissions;                // obtained permissions from library function

};
#endif // FILEINFO

