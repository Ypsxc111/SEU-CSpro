#include "allstugrades.h"
#include "ui_allstugrades.h"
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQuery>

AllStuGrades::AllStuGrades(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AllStuGrades)
{
    ui->setupUi(this);
    model=new QSqlQueryModel;
    addstugrade=new AddStuGrades;
    initScreen();
    studentGradesView();
    connect(addstugrade,&AddStuGrades::backToAdminScreen,[=](){
        addstugrade->hide();
        this->show();
    });
}

AllStuGrades::~AllStuGrades()
{
    delete ui;
}

void AllStuGrades::initScreen()
{
    setWindowTitle("学生成绩展示");
    setWindowIcon(QIcon(":/imag/icon.jpg"));
    setFixedSize(500,333);
    ui->tableView->setStyleSheet("border :1px ;background-color: rgba(0,0,0,0)");
}

void AllStuGrades::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,500,333,QPixmap(":/imag/background4.jpg"));
}

void AllStuGrades::studentGradesView()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName(dbHostName);
    db.setDatabaseName("custom2.db");
    db.setUserName(dbusername);
    db.setPassword(dbpassword);
    bool isOpen=db.open();
    if(isOpen)
    {
        qDebug()<<"database open success!";

        QString cmd="select stutable.stid,sname,grademath,gradeen,gradec,gradec+gradeen+grademath from stutable,gradetable where stutable.stid=gradetable.stid";
        proxyModel=new QSortFilterProxyModel(this);
        model->setQuery(cmd);
        proxyModel->setSourceModel(model);
        proxyModel->setHeaderData(0,Qt::Horizontal,tr("学号"));
        proxyModel->setHeaderData(1,Qt::Horizontal,tr("姓名"));
        proxyModel->setHeaderData(2,Qt::Horizontal,tr("数学"));
        proxyModel->setHeaderData(3,Qt::Horizontal,tr("英语"));
        proxyModel->setHeaderData(4,Qt::Horizontal,tr("C++"));
        proxyModel->setHeaderData(5,Qt::Horizontal,tr("总分"));

        ui->tableView->setModel(proxyModel);
        ui->tableView->show();
        ui->tableView->setColumnWidth(0,80);
        ui->tableView->setColumnWidth(1,60);
        ui->tableView->setColumnWidth(2,50);
        ui->tableView->setColumnWidth(3,50);
        ui->tableView->setColumnWidth(4,50);
        ui->tableView->setColumnWidth(5,50);
    }
}

void AllStuGrades::on_pushButton_back_clicked()
{
    emit this->backToAdminScreen();
}

void AllStuGrades::on_comboBox_activated(int index)
{
    num=index;
    //qDebug()<<num;
}

void AllStuGrades::on_pushButton_asc_clicked()
{
    proxyModel->sort(num,Qt::AscendingOrder);
    qDebug()<<num;
}

void AllStuGrades::on_pushButton_desc_clicked()
{
    proxyModel->sort(num,Qt::DescendingOrder);
    qDebug()<<num;

}

void AllStuGrades::on_pushButton_add_clicked()
{
    this->hide();
    addstugrade->show();
}

void AllStuGrades::on_pushButton_select_clicked()
{

    studentGradesView();
}
