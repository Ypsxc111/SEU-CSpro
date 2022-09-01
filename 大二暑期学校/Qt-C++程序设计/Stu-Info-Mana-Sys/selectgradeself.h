#ifndef SELECTGRADESELF_H
#define SELECTGRADESELF_H

#include <QWidget>
#include "globle.h"
#include "QPainter"
#include <QString>

namespace Ui {
class SelectGradeSelf;
}

class SelectGradeSelf : public QWidget
{
    Q_OBJECT

public:
    explicit SelectGradeSelf(QWidget *parent = 0);
    ~SelectGradeSelf();
    void initScreen();
    void paintEvent(QPaintEvent *event);
    void getDateAndShow();
    QString convert(float f);
private slots:
    void on_pushButton_back_clicked();

private:
    Ui::SelectGradeSelf *ui;
    QString math;
    QString english;
    QString cplusplus;
    float avgGrade;


signals:
    void backToStuScreen();
};

#endif // SELECTGRADESELF_H
