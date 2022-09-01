#ifndef ADDSTUGRADES_H
#define ADDSTUGRADES_H

#include <QWidget>
#include "globle.h"
#include <QPainter>
#include <QString>
namespace Ui {
class AddStuGrades;
}

class AddStuGrades : public QWidget
{
    Q_OBJECT

public:
    explicit AddStuGrades(QWidget *parent = 0);
    ~AddStuGrades();
    void initScreen();
    void paintEvent(QPaintEvent *event);
    bool checkStuId(QString stid);
    void setGrades();
private slots:
    void on_pushButton_back_clicked();
    void on_lineEdit_stid_editingFinished();

    void on_pushButton_submit_clicked();

signals:
    void backToAdminScreen();
private:
    Ui::AddStuGrades *ui;
    QString stid;
    QString english;
    QString math;
    QString cpp;
};

#endif // ADDSTUGRADES_H
