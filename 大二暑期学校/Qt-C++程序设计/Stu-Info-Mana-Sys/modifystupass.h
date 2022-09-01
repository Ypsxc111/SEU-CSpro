#ifndef MODIFYSTUPASS_H
#define MODIFYSTUPASS_H

#include <QWidget>
#include "globle.h"
#include <QPainter>
#include <QString>
namespace Ui {
class ModifyStuPass;
}

class ModifyStuPass : public QWidget
{
    Q_OBJECT

public:
    explicit ModifyStuPass(QWidget *parent = 0);
    ~ModifyStuPass();
    void initScreen();
    void paintEvent(QPaintEvent *event);
    void modifyStuPassword(QString stuid,QString getPassword);
private:
    Ui::ModifyStuPass *ui;

signals:
    void backToadminScreen();
private slots:
    void on_pushButton_back_clicked();
    void on_pushButton_submit_clicked();
    void on_lineEdit_stuid_editingFinished();
};

#endif // MODIFYSTUPASS_H
