#ifndef ADDSTUDENT_H
#define ADDSTUDENT_H

#include <QWidget>
#include "globle.h"
#include <QPainter>
namespace Ui {
class AddStudent;
}

class AddStudent : public QWidget
{
    Q_OBJECT

public:
    explicit AddStudent(QWidget *parent = 0);
    ~AddStudent();
    void paintEvent(QPaintEvent *event);
    void initScreen();
    void getInformation();
    bool setInformation();
private slots:
    void on_comboBox_province_currentIndexChanged(int index);
    void on_pushButton_2_clicked();
    void on_pushButton_submit_clicked();


    void on_comboBox_college_currentIndexChanged(int index);

    void on_comboBox_city_activated(const QString &arg1);

    void on_comboBox_province_activated(int index);

signals:
   void backToAdminScreen();

private:
    Ui::AddStudent *ui;
    QString sname;
    QString sid;
    QString splace;
    QString smajor;
    QString ssex;
    QString sage;
    QString spass;
};

#endif // ADDSTUDENT_H
