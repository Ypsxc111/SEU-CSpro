#ifndef MODIFYSTUINFO_H
#define MODIFYSTUINFO_H

#include <QWidget>
#include "globle.h"
#include <QPainter>
#include <QString>
namespace Ui {
class ModifyStuInfo;
}

class ModifyStuInfo : public QWidget
{
    Q_OBJECT

public:
    explicit ModifyStuInfo(QWidget *parent = 0);
    ~ModifyStuInfo();
    void initScreen();
    void paintEvent(QPaintEvent *event);
    void getInfoAndShow();
    void setInformation();
signals:
    void backToAdminScreen();
private slots:
    void on_pushButton_back_clicked();



    void on_comboBox_province_currentIndexChanged(int index);

    void on_comboBox_province_activated(int index);

    void on_comboBox_city_activated(const QString &arg1);

    void on_comboBox_college_currentIndexChanged(int index);

    void on_pushButton_select_clicked();

    void on_comboBox_county_activated(int index);

    void on_pushButton_clicked();

    void on_comboBox_major_activated(int index);

    void on_comboBox_class_activated(int index);

private:
    Ui::ModifyStuInfo *ui;
    QString sid;
    QString sname;
    QString ssex;
    QString splace;
    QString smajor;
    QString sage;

};

#endif // MODIFYSTUINFO_H
