#ifndef ADMINSCREEN_H
#define ADMINSCREEN_H

#include <QWidget>
#include <QPainter>
#include "allstuinfo.h"
#include "addstudent.h"
#include "modifystupass.h"
#include "modifyadmpass.h"

#include "allstugrades.h"
#include "modifystuinfo.h"
namespace Ui {
class AdminScreen;
}

class AdminScreen : public QWidget
{
    Q_OBJECT

public:
    explicit AdminScreen(QWidget *parent = 0);
    ~AdminScreen();
     void iniScene();
     void paintEvent(QPaintEvent *event);
private slots:
     void on_pushButton_infoShow_clicked();

     void on_pushButton_addInfo_clicked();

     void on_pushButton_modiAdPass_clicked();

     void on_pushButton_modiStuP_clicked();

     void on_pushButton_addGrade_clicked();

     void on_pushButton_gradeShow_clicked();

     void on_pushButton_modyInfo_clicked();
signals:
     void backToLoginScreen();

private:
    Ui::AdminScreen *ui;
    AllStuInfo * allStudentInfo;
    AddStudent * addstuInfo;
    ModifyStuPass * modistupassword;
    ModifyAdmPass * modiadminpass;
    AllStuGrades * allstugradeshow;
    ModifyStuInfo * modistuinfo;
};

#endif // ADMINSCREEN_H
