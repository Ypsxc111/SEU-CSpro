#include "stumodifypassself.h"
#include "ui_stumodifypassself.h"
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQuery>
StuModifyPassSelf::StuModifyPassSelf(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StuModifyPassSelf)
{
    ui->setupUi(this);
    iniScreen();
}

StuModifyPassSelf::~StuModifyPassSelf()
{
    delete ui;
}

void StuModifyPassSelf::iniScreen()
{
    setWindowTitle("修改密码");
    setWindowIcon(QIcon(":/imag/icon.jpg"));
    setFixedSize(500,333);
}
void StuModifyPassSelf::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,500,333,QPixmap(":/imag/background2.jpg"));
}

void StuModifyPassSelf::modifyPassword(QString getOldPass, QString newPass)
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
        query.exec("select spass from studentpasstable where stid='"+userLogId+"'");
        query.next();
        QString oldP=query.value(0).toString();
        if(oldP==getOldPass)
        {
            query.exec("update studentpasstable set spass ='"+ newPass +"' where stid='"+ userLogId +"'");
            query.next();
            QMessageBox::information(this,"提示","修改密码成功!");
        }

        else QMessageBox::critical(this,"警告","初始密码输入错误！\n请重新输入！\n若忘记密码，请联系学校管理员修改");
    }
    else qDebug()<<"数据库打开失败，修改失败！";
}
void StuModifyPassSelf::on_pushButton_back_clicked()
{
    emit this->backToStuScreen();
}

void StuModifyPassSelf::on_pushButton_modifyPass_clicked()
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
        if(newPass != "")
            modifyPassword(oldPass,newPass);
        else QMessageBox::information(this,"提示","新密码不能为空\n请重新输入");
    }

}

void StuModifyPassSelf::on_lineEdit_newPass_editingFinished()
{
    if(!isProperPassword(removeSpace(ui->lineEdit_newPass->text())))
    {
        QMessageBox::information(this,"提示","新密码位数必须大于6位且小于20位\n请重新输入");
        ui->lineEdit_newPass->setText("");
    }
}
