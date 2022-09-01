#include "modifystupass.h"
#include "ui_modifystupass.h"
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQuery>
ModifyStuPass::ModifyStuPass(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModifyStuPass)
{
    ui->setupUi(this);
    initScreen();
}

ModifyStuPass::~ModifyStuPass()
{
    delete ui;
}

void ModifyStuPass::initScreen()
{
    setWindowIcon(QIcon(":/imag/icon.jpg"));
    setWindowTitle("修改学生密码");
    setFixedSize(500,333);
}

void ModifyStuPass::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,500,333,QPixmap(":/imag/background4.jpg"));
}

void ModifyStuPass::modifyStuPassword(QString stuid, QString getPassword)
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
        query.exec("update studentpasstable set spass ='"+ getPassword +"' where stid='"+ stuid +"'");
        query.next();
        QMessageBox::information(this,"提示","密码修改成功！");
    }
    else qDebug()<<"打开数据库失败";
}

void ModifyStuPass::on_pushButton_back_clicked()
{
    emit this->backToadminScreen();
}

void ModifyStuPass::on_pushButton_submit_clicked()
{
    QString stuid=ui->lineEdit_stuid->text();
    QString getPassword=ui->lineEdit_newPass->text();
    QString againPass=ui->lineEdit_againPass->text();
    if(getPassword != againPass)
        QMessageBox::critical(this,"提示","两次密码输入不同！\n请重新输入。");
    else modifyStuPassword(stuid,getPassword);
}

void ModifyStuPass::on_lineEdit_stuid_editingFinished()
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
        QString stuid=ui->lineEdit_stuid->text();
        int n;
        query.exec("select count(*) from stutable where stid='"+stuid+"'");
        query.next();
        n=query.value(0).toInt();
        if(n)
        {
            query.exec("select sname from stutable where stid='"+stuid+"'");
            query.next();
            ui->lineEdit_sname->setText(query.value(0).toString());
        }
        else
        {
            QMessageBox::information(this,"提示","无此学生\n请检查学号是否正确\n请重新输入");
            ui->lineEdit_stuid->setText("");
            ui->lineEdit_sname->setText("");
        }
    }
}
