#ifndef STUMODIFYPASSSELF_H
#define STUMODIFYPASSSELF_H

#include <QWidget>
#include <QPainter>
#include <QString>
#include "globle.h"
namespace Ui {
class StuModifyPassSelf;
}

class StuModifyPassSelf : public QWidget
{
    Q_OBJECT

public:
    explicit StuModifyPassSelf(QWidget *parent = 0);
    ~StuModifyPassSelf();
    void iniScreen();
    void paintEvent(QPaintEvent *event);
    void modifyPassword(QString getOldPass, QString newPass);
signals:
    void backToStuScreen();
private slots:
    void on_pushButton_back_clicked();

    void on_pushButton_modifyPass_clicked();

    void on_lineEdit_newPass_editingFinished();

private:
    Ui::StuModifyPassSelf *ui;

};

#endif // STUMODIFYPASSSELF_H
