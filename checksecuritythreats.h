#ifndef CHECKSECURITYTHREATS_H
#define CHECKSECURITYTHREATS_H

#include <QDialog>
#include <QStandardItemModel>

namespace Ui {
class CheckSecurityThreats;
}

class CheckSecurityThreats : public QDialog
{
    Q_OBJECT

public:
    explicit CheckSecurityThreats(QWidget *parent = 0);
    ~CheckSecurityThreats();

private:
    Ui::CheckSecurityThreats *ui;
    QStandardItemModel *model;
};

#endif // CHECKSECURITYTHREATS_H
