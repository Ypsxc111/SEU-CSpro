#ifndef ALLSTUINFO_H
#define ALLSTUINFO_H

#include <QWidget>
#include "globle.h"
#include <QSqlTableModel>
#include <QPainter>

namespace Ui {
class AllStuInfo;
}

class AllStuInfo : public QWidget
{
    Q_OBJECT

public:
    explicit AllStuInfo(QWidget *parent = 0);
    ~AllStuInfo();
    void initScreen();
    void studentInfoView();
    void paintEvent(QPaintEvent *event);
private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_cancel_clicked();

    void on_pushButton_add_clicked();


    void on_pushButton_delete_clicked();

    void on_pushButton_asc_clicked();

    void on_pushButton_desc_clicked();

    void on_pushButton_back_clicked();

signals:
    void backToAdminScreen();
private:
    Ui::AllStuInfo *ui;
    QSqlTableModel * model;
};

#endif // ALLSTUINFO_H
