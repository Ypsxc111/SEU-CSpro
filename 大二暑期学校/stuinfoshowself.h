#ifndef STUINFOSHOWSELF_H
#define STUINFOSHOWSELF_H

#include <QWidget>
#include <QPainter>
#include <QString>
#include "globle.h"
namespace Ui {
class StuInfoShowSelf;
}

class StuInfoShowSelf : public QWidget
{
    Q_OBJECT

public:
    explicit StuInfoShowSelf(QWidget *parent = 0);
    ~StuInfoShowSelf();
    void iniScreen();
    void paintEvent(QPaintEvent *event);
    void getInformation();
private slots:
    void on_pushButton_back_clicked();
signals:
    void backToStuScreen();
private:
    Ui::StuInfoShowSelf *ui;
    QString ssex;
    QString sage;
    QString splace;
    QString smajor;
    QString sname;

};

#endif // STUINFOSHOWSELF_H
