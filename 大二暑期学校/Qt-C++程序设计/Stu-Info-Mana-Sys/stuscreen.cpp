#include "stuscreen.h"
#include "ui_stuscreen.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQuery>
StuScreen::StuScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StuScreen)
{
    ui->setupUi(this);
    stumodipass=new StuModifyPassSelf;
    stuinfoshowself=new StuInfoShowSelf;
    selectgradeself=new SelectGradeSelf;
    initScreen();
    connect(stumodipass,&StuModifyPassSelf::backToStuScreen,[=](){
        stumodipass->hide();
        this->show();
    });
    connect(stuinfoshowself,&StuInfoShowSelf::backToStuScreen,[=](){
        stuinfoshowself->hide();
        this->show();
    });
    connect(selectgradeself,&SelectGradeSelf::backToStuScreen,[=](){
        selectgradeself->hide();
        this->show();
    });
}

StuScreen::~StuScreen()
{
    delete ui;
}

void StuScreen::initScreen()
{
    //获取姓名
    QString sname;
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName(dbHostName);       //选择本地主机
    db.setDatabaseName("custom2.db");                            //设置数据源名称
    db.setUserName(dbusername);                         //登录用户
    db.setPassword(dbpassword);                         //密码
    bool isOpen=db.open();
    if(isOpen)
    {
        qDebug()<<"打开了数据库";
        QSqlQuery query(db);

        bool ok=query.exec("select sname from stutable where stid='"+userLogId+"'");
        qDebug()<<"OK="<<ok;
        query.next();
        sname=query.value(0).toString();


    }
    else qDebug()<<"查询姓名失败";
    qDebug()<<"学生姓名为："<<sname;
    setWindowTitle("学生界面");
    setFixedSize(500,333);
    ui->lineEdit_welcome->setStyleSheet("border :1px ;background-color: rgba(0,0,0,0);color:#10E0F0");
    ui->lineEdit_welcome->setText("欢迎"+ sname +"同学");
    ui->lineEdit_welcome->setFont(QFont("Timers",28,QFont::Bold));
    setWindowIcon(QIcon(":/imag/icon.jpg"));
    ui->pushButton_modifyPass->setStyleSheet("border :1px ;background-color: rgba(0,0,0,100);color:#F2390E;height:60px");
    ui->pushButton_selectGrade->setStyleSheet("border :1px ;background-color: rgba(0,0,0,100);color:#F2390E;height:60px");
    ui->pushButton_selectInfo->setStyleSheet("border :1px ;background-color: rgba(0,0,0,100);color:#F2390E;height:60px");
    ui->pushButton_back->setStyleSheet("border :1px ;background-color: rgba(0,0,0,100);color:#F2390E;height:60px");
    ui->pushButton_modifyPass->setFont(QFont("微软雅黑",11,QFont::Bold));
    ui->pushButton_selectGrade->setFont(QFont("微软雅黑",11,QFont::Bold));
    ui->pushButton_selectInfo->setFont(QFont("微软雅黑",11,QFont::Bold));
    ui->pushButton_back->setFont(QFont("微软雅黑",11,QFont::Bold));
}
void StuScreen::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,500,333,QPixmap(":/imag/background2.jpg"));
}

void StuScreen::on_pushButton_modifyPass_clicked()
{

    this->hide();
    stumodipass->show();
}

void StuScreen::on_pushButton_selectInfo_clicked()
{
    this->hide();
    stuinfoshowself->show();
}

void StuScreen::on_pushButton_selectGrade_clicked()
{
    this->hide();
    selectgradeself->show();
}


void StuScreen::on_pushButton_back_clicked()
{
    emit this->backToLoginScreen();
}
