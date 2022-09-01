#ifndef ALLSTUGRADES_H
#define ALLSTUGRADES_H

#include <QWidget>
#include "globle.h"
#include <QPainter>
#include <QSqlQueryModel>
#include "addstugrades.h"
#include <QSortFilterProxyModel>
namespace Ui {
class AllStuGrades;
}

class AllStuGrades : public QWidget
{
    Q_OBJECT

public:
    explicit AllStuGrades(QWidget *parent = 0);
    ~AllStuGrades();
    void initScreen();
    void paintEvent(QPaintEvent *event);
    void studentGradesView();
private slots:
    void on_pushButton_back_clicked();
    void on_comboBox_activated(int index);

    void on_pushButton_asc_clicked();

    void on_pushButton_desc_clicked();

    void on_pushButton_add_clicked();

    void on_pushButton_select_clicked();

signals:
    void backToAdminScreen();
private:
    Ui::AllStuGrades *ui;
    int num = 0;
    QSqlQueryModel * model;
    AddStuGrades * addstugrade;
    QSortFilterProxyModel * proxyModel;
};

#endif // ALLSTUGRADES_H
