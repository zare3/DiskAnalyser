#ifndef FILEINFO
#define FILEINFO

#include <QFileSystemModel>
#include <QString>
#include <QDir>
#include <QFile>
#include <QMap>

class statistics
{
public:
    QString name;
    qint64 file_count;
};

class FileInfo
{
public:

    //public member functions
    FileInfo ();                                        // contructor

    // functions that get attributes
    QString getName(const QString&);                   // gets name of directory indicated by QString path
    QString getType(const QString&);                   // gets type of directory indicated by QString path
    qint64 getSize(const QString&);                    // gets size of directory indicated by QString path
    QString getPermissions(const QString&);            // gets permission states (read/write/execute) for owner/user/group/other
    void getOwners(const QString&);                    // gets list of owners for folder/file and folder children; saved in a map
    void getGroups(const QString& );                   // gets list of groups for folder/file and folder children; saved in a map

    // functions that display (used for testing)
    //QString displayInfo();                              // prepares output of info
    QString displayPermissions();                       // prepares output of permissions
    QString displayOwners();
    QString displayGroups();

    //QString getOwner(const QString&);

private:

    // private variables
    QFileSystemModel *file;                             // used to access file credentials
    QModelIndex index;                                  // file index
    QString permissions;                                // interpreted permissions
    QFile::Permissions file_permissions;                // obtained permissions from library function
    QMap <uint, statistics> owners;                    // contains owner ID, name, and corresponding number of owned files
    QMap <uint, statistics> groups;                    // contains group ID, name, and corresponding number of owned files
    QMap <QModelIndex, QMap<uint,statistics> > IndexedOwners;

};
#endif // FILEINFO

