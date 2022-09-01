#include "modifyadmpass.h"
#include "ui_modifyadmpass.h"
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQuery>
ModifyAdmPass::ModifyAdmPass(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModifyAdmPass)
{
    ui->setupUi(this);
    initScreen();
}

ModifyAdmPass::~ModifyAdmPass()
{
    delete ui;
}

void ModifyAdmPass::initScreen()
{
    setWindowIcon(QIcon(":/imag/icon.jpg"));
    setWindowTitle("修改管理员密码");
    setFixedSize(500,333);
}

void ModifyAdmPass::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,500,333,QPixmap(":/imag/background4.jpg"));
}

void ModifyAdmPass::modifyPassword(QString getOldPass, QString newPass)
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
        query.exec("select adpass from admintable where adid='"+userLogId+"'");
        query.next();
        QString oldP=query.value(0).toString();
        qDebug()<<"获取到的密码是："<<oldP;
        if(oldP==getOldPass)
        {
            query.exec("update admintable set adpass ='"+ newPass +"' where adid='"+ userLogId +"'");
            query.next();
            QMessageBox::information(this,"提示","密码修改成功！");
        }
        else QMessageBox::critical(this,"警告","初始密码输入错误！\n请重新输入！");
    }
    else qDebug()<<"数据库打开失败，修改失败！";
}

void ModifyAdmPass::on_pushButton_back_clicked()
{
    emit this->backToAdminScreen();
}

void ModifyAdmPass::on_pushButton_submit_clicked()
{
    QString oldPass=removeSpace(ui->lineEdit_oldPass->text());
    QString newPass=removeSpace(ui->lineEdit_newPass->text());
    QString againPass=removeSpace(ui->lineEdit_againPass->text());
    if(newPass != againPass)
    {
        QMessageBox::information(this,"注意","两次密码输入不同，请重新输入！");
    }
    else
    {
        modifyPassword(oldPass,newPass);
    }
}
