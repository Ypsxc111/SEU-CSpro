#include "selectgradeself.h"
#include "ui_selectgradeself.h"
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQuery>
SelectGradeSelf::SelectGradeSelf(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelectGradeSelf)
{
    ui->setupUi(this);
    initScreen();
    getDateAndShow();
}

SelectGradeSelf::~SelectGradeSelf()
{
    delete ui;
}

void SelectGradeSelf::initScreen()
{
    setWindowTitle("个人成绩展示");
    setWindowIcon(QIcon(":/imag/icon.jpg"));
    setFixedSize(500,333);
}

void SelectGradeSelf::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,500,333,QPixmap(":/imag/background2.jpg"));
}

void SelectGradeSelf::getDateAndShow()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName(dbHostName);
    db.setDatabaseName("custom2.db");
    db.setUserName(dbusername);
    db.setPassword(dbpassword);
    bool isOpen=db.open();
    if(isOpen)
    {
        QSqlQuery query(db);
        query.exec("select * from gradetable where stid='"+userLogId+"'");
        query.next();
        math=removeSpace(query.value(1).toString());
        english=removeSpace(query.value(2).toString());
        cplusplus=removeSpace(query.value(3).toString());
        avgGrade=(math.toFloat()+english.toFloat()+cplusplus.toFloat())/3;
    }
    else qDebug()<<"打开数据库失败";
    ui->lineEdit->setText(math);
    ui->lineEdit_2->setText(english);
    ui->lineEdit_3->setText(cplusplus);
    ui->lineEdit_4->setText(convert(avgGrade));
}

QString SelectGradeSelf::convert(float f)
{
        QString str;
        str=QString("%1").arg(f,0,'f',3);

        return str;

}

void SelectGradeSelf::on_pushButton_back_clicked()
{
    emit this->backToStuScreen();
}
