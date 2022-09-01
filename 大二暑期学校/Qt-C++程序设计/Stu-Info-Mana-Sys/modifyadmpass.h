#ifndef MODIFYADMPASS_H
#define MODIFYADMPASS_H

#include <QWidget>
#include "globle.h"
#include <QPAinter>
#include<QString>
namespace Ui {
class ModifyAdmPass;
}

class ModifyAdmPass : public QWidget
{
    Q_OBJECT

public:
    explicit ModifyAdmPass(QWidget *parent = 0);
    ~ModifyAdmPass();
    void initScreen();
    void paintEvent(QPaintEvent *event);
    void modifyPassword(QString getOldPass, QString newPass);
private slots:
    void on_pushButton_back_clicked();

    void on_pushButton_submit_clicked();

signals:
    void backToAdminScreen();
private:
    Ui::ModifyAdmPass *ui;
};

#endif // MODIFYADMPASS_H
