#ifndef STUSCREEN_H
#define STUSCREEN_H

#include <QWidget>
#include "stumodifypassself.h"
#include "stuinfoshowself.h"
#include <QPainter>
#include "selectgradeself.h"
#include "globle.h"
#include <QString>
namespace Ui {
class StuScreen;
}

class StuScreen : public QWidget
{
    Q_OBJECT

public:
    explicit StuScreen(QWidget *parent = 0);
    ~StuScreen();
    void initScreen();
    void paintEvent(QPaintEvent *event);

private slots:

    void on_pushButton_modifyPass_clicked();

    void on_pushButton_selectInfo_clicked();

    void on_pushButton_selectGrade_clicked();

    void on_pushButton_back_clicked();
signals:
    void backToLoginScreen();
private:
    Ui::StuScreen *ui;
    StuModifyPassSelf * stumodipass;
    StuInfoShowSelf * stuinfoshowself;
    SelectGradeSelf * selectgradeself;
};

#endif // STUSCREEN_H
