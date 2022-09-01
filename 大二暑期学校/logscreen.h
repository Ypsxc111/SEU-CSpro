#ifndef LOGSCREEN_H
#define LOGSCREEN_H

#include <QMainWindow>
#include <QPainter>
#include <QString>
#include "globle.h"
#include "adminscreen.h"
#include "stuscreen.h"
namespace Ui {
class LogScreen;
}

class LogScreen : public QMainWindow
{
    Q_OBJECT

public:
    explicit LogScreen(QWidget *parent = 0);
    ~LogScreen();
    void iniScene();
    void paintEvent(QPaintEvent *event);
    void createdatebase();
    bool checkpassword(bool flag_pos,QString getId,QString getPass);
private slots:
    void on_pushButton_log_clicked();
    void on_pushButton_clear_clicked();

private:
    Ui::LogScreen *ui;



};

#endif // LOGSCREEN_H
