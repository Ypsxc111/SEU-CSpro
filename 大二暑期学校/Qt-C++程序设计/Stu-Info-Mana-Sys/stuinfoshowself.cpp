#include "stuinfoshowself.h"
#include "ui_stuinfoshowself.h"
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQuery>
StuInfoShowSelf::StuInfoShowSelf(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StuInfoShowSelf)
{
    ui->setupUi(this);
    iniScreen();
    getInformation();
    qDebug()<<"学生账号为："<<userLogId;
    ui->lineEdit_age->setText(sage);
    ui->lineEdit_id->setText(userLogId);
    ui->lineEdit_major->setText(smajor);
    ui->lineEdit_place->setText(splace);
    ui->lineEdit_sex->setText(ssex);
    ui->lineEdit_name->setText(sname);
}

StuInfoShowSelf::~StuInfoShowSelf()
{
    delete ui;
}

void StuInfoShowSelf::iniScreen()
{
    setWindowTitle("个人信息展示");
    setWindowIcon(QIcon(":/imag/icon.jpg"));
    setFixedSize(500,333);
}

void StuInfoShowSelf::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,500,333,QPixmap(":/imag/background2.jpg"));
}

void StuInfoShowSelf::getInformation()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName(dbHostName);       //选择本地主机
    db.setDatabaseName("custom2.db");                            //设置数据源名称
    db.setUserName(dbusername);                         //登录用户
    db.setPassword(dbpassword);                         //密码
    bool isOpen=db.open();
    if(isOpen)
    {
        QSqlQuery query(db);
        query.exec("select sname,ssex,sage,splace,smajor from stutable where stid='"+userLogId+"'");
        query.next();
        sname=removeSpace(query.value(0).toString());
        ssex=removeSpace(query.value(1).toString());
        sage=removeSpace(query.value(2).toString());
        splace=removeSpace(query.value(3).toString());
        smajor=removeSpace(query.value(4).toString());
    }
    else qDebug()<<"打开失败，读取失败";
}

void StuInfoShowSelf::on_pushButton_back_clicked()
{
    emit this->backToStuScreen();
}
