#include "logscreen.h"
#include "ui_logscreen.h"
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QFileInfo>
LogScreen::LogScreen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LogScreen)
{
    ui->setupUi(this);

    iniScene();
    createdatebase();



}

LogScreen::~LogScreen()
{
    delete ui;
}

void LogScreen::iniScene()
{
    setFixedSize(500,312);
    setWindowTitle("登陆界面");
    setWindowIcon(QIcon(":/imag/icon.jpg"));
//    ui->lineEdit_id->setText("000001");
//    ui->lineEdit_password->setText("12345678");
    ui->label_4->setStyleSheet("border :1px ;background-color: rgba(0,0,0,0);color:#ff6600");
    ui->label_4->setFont(QFont("Timers",28,QFont::Bold));
}


void LogScreen::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,500,312,QPixmap(":/imag/backgroundLog.jpg"));
}

void LogScreen::createdatebase()
{

    //判断是否存在
    QString dbName="custom2.db";
    QFileInfo info(dbName);
    bool isExits=info.exists();
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName(dbHostName);
    db.setDatabaseName(dbName);
    db.setUserName(dbusername);
    db.setPassword(dbpassword);
    bool isOpen=db.open();
    if(isOpen)
    {
        if(!isExits)
        {
            QSqlQuery query(db);
            bool ok1=query.exec("CREATE TABLE admintable ( adid nchar ( 5 ) PRIMARY KEY NOT NULL, adpass nchar ( 20 ) NOT NULL );");
            bool ok2=query.exec("INSERT INTO admintable ( adid, adpass ) VALUES ( '00001', '12345678' ),( '00002', '12345678' );");
            bool ok3=query.exec("CREATE TABLE studentpasstable ( stid char ( 6 ) PRIMARY KEY NOT NULL, spass nchar ( 20 ) NOT NULL );");
            bool ok4=query.exec("INSERT INTO studentpasstable ( stid, spass )"
                    "VALUES"
                        "( '000001', '12345678' ),"
                        "( '000102', '000000' ), "
                        "( '000011', '99999' ); ");
            bool ok5=query.exec("CREATE TABLE stutable ("
                        "stid char ( 6 ) PRIMARY KEY NOT NULL,"
                        "sname char ( 5 ) NOT NULL,"
                       " ssex nchar ( 1 ),"
                        "sage tinyint,"
                        "splace nchar ( 50 ),"
                       "smajor nchar ( 50 ) "
                   ");");
            bool ok6=query.exec("INSERT INTO stutable ( stid, sname, ssex, sage, splace, smajor )"
                    "VALUES"
                        "( '000001', '张三', '男', '20', '四川省成都市郫都区', '计算机与软件工程学院计算机科学与技术2班' ),"
                        "( '000102', '李四', '男', '19', '上海市浦东新区', '管理学院会计学2班' ),"
                       "( '000011', '李娜', '女', '20', '北京市朝阳区', '理学院信息与计算科学1班' );");
            bool ok7=query.exec("CREATE TABLE gradetable ("
                        "stid nchar ( 6 ) NOT NULL,"
                        "grademath numeric ( 4, 1 ) NOT NULL,"
                        "gradeen numeric ( 4, 1 ) NOT NULL,"
                       "gradec numeric ( 4, 1 )"
                    ");");
             bool ok8=query.exec("INSERT INTO gradetable ( stid, grademath, gradeen, gradec )"
                    "VALUES"
                        "( '000001', '84', '86', '72' ),"
                        "( '000011', '15', '45', '100' ),"
                        "( '000102', '30.5', '74', '99' )");

           if(ok1&&ok2&&ok3&&ok4&&ok5&&ok6&&ok7&&ok8)
               qDebug()<<"创建表成功";
           else qDebug()<<"创建表失败";
       }
       else qDebug()<<"表已存在";
    }
}

bool LogScreen::checkpassword(bool flag_pos, QString getId, QString getPass)
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
        if(flag_pos)
        {
            query.exec("select adpass from admintable where adid='"+getId+"'");
        }
        else
        {
            query.exec("select spass from studentpasstable where stid='"+getId+"'");
        }
        query.next();
        QString str=query.value(0).toString();
        str=removeSpace(str);
        qDebug()<<"获取到的密码是："<<str;
        if(str==getPass)
        {
            qDebug()<<"密码正确";
            return true;
        }
        else
        {
            qDebug()<<"密码错误";
            return false;
        }
    }
}

void LogScreen::on_pushButton_log_clicked()
{
    QString getId=removeSpace(ui->lineEdit_id->text());
    QString getPass=removeSpace(ui->lineEdit_password->text());
    bool flag_pos;//管理员为1，学生为0

    if(ui->radioButton->isChecked())
        flag_pos=1;
    else flag_pos=0;
    if(checkpassword(flag_pos,getId,getPass) && getId != "")
    {
        userLogId=getId;

        qDebug()<<"userLogId1:"<<userLogId;
        this->hide();
        if(flag_pos==1)
        {
            AdminScreen * adminscreen=new AdminScreen;
            adminscreen->show();
            connect(adminscreen,&AdminScreen::backToLoginScreen,[=](){
                this->show();
                adminscreen->hide();
            });

        }
        else
        {
            StuScreen * stuscreen=new StuScreen;
            stuscreen->show();
            connect(stuscreen,&StuScreen::backToLoginScreen,[=](){
                this->show();
                stuscreen->hide();
            });

        }
    }
    else
    {
        QMessageBox::information(this,"提示","登陆失败,可能的原因:\n  1.账号错误\n  2.密码错误\n若忘记密码，请及时联系学校管理员修改");
    }

}

void LogScreen::on_pushButton_clear_clicked()
{
    ui->lineEdit_id->setText("");
    ui->lineEdit_password->setText("");
}
