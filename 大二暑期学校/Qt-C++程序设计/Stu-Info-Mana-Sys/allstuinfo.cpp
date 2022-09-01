#include "allstuinfo.h"
#include "ui_allstuinfo.h"
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQuery>

AllStuInfo::AllStuInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AllStuInfo)
{
    ui->setupUi(this);
    initScreen();
    studentInfoView();

}

AllStuInfo::~AllStuInfo()
{
    delete ui;
}

void AllStuInfo::initScreen()
{
    setFixedSize(839,527);
    setWindowIcon(QIcon(":/imag/icon.jpg"));
    setWindowTitle("学生信息展示");
    ui->tableView->setStyleSheet("border :1px ;background-color: rgba(0,0,0,0)");
    ui->widget_btn->setStyleSheet("border:0px;background-color: rgba(0,0,0,50);");
    ui->pushButton_3->setStyleSheet("height:40px;background-color:#A06091");
    ui->pushButton_add->setStyleSheet("height:40px;background-color:#A06091");
    ui->pushButton_add->setVisible(false);//展示界面禁止添加学生信息 不再显示此按钮
    ui->pushButton_asc->setStyleSheet("height:40px;background-color:#A06091");
    ui->pushButton_back->setStyleSheet("height:40px;background-color:#A06091");
    ui->pushButton_cancel->setStyleSheet("height:40px;background-color:#A06091");
    ui->pushButton_cancel->setVisible(false);//展示界面禁止添加学生信息 不再显示此按钮
    ui->pushButton_delete->setStyleSheet("height:40px;background-color:#A06091");
    ui->pushButton_desc->setStyleSheet("height:40px;background-color:#A06091");
}

void AllStuInfo::studentInfoView()
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
        model =new QSqlTableModel(this,db);
        model->setTable("stutable");//表名
        model->setHeaderData(0,Qt::Horizontal,QVariant("学号"));
        model->setHeaderData(1,Qt::Horizontal,QVariant("姓名"));
        model->setHeaderData(2,Qt::Horizontal,QVariant("性别"));
        model->setHeaderData(3,Qt::Horizontal,QVariant("年龄"));
        model->setHeaderData(4,Qt::Horizontal,QVariant("籍贯"));
        model->setHeaderData(5,Qt::Horizontal,QVariant("专业"));
        model->setEditStrategy(QSqlTableModel::OnManualSubmit);
        model->select();
        ui->tableView->setModel(model);
//        ui->tableView->setColumnWidth(0,80);
//        ui->tableView->setColumnWidth(1,80);
//        ui->tableView->setColumnWidth(2,50);
//        ui->tableView->setColumnWidth(3,50);
//        ui->tableView->setColumnWidth(4,200);
//        ui->tableView->setColumnWidth(5,300);
        ui->tableView->resizeColumnsToContents();
        ui->tableView->resizeRowsToContents();


    }

}

void AllStuInfo::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,839,527,QPixmap(":/imag/background5.jpg"));
}


void AllStuInfo::on_pushButton_3_clicked()
{
    model->submitAll();
    model->select();

}

void AllStuInfo::on_pushButton_cancel_clicked()
{
    model->revertAll();
}

void AllStuInfo::on_pushButton_add_clicked()
{
    model->insertRow(model->rowCount());
}

void AllStuInfo::on_pushButton_delete_clicked()
{
    int selectRow=ui->tableView->currentIndex().row();
    if(selectRow >= 0)
    {
        int del=QMessageBox::question(this,"提示","是否要删除此学生信息\n删除后数据无法恢复，请慎重考虑!",QMessageBox::Yes | QMessageBox::No,QMessageBox::Yes);
        if(del==QMessageBox::Yes)
        {
            model->removeRow(selectRow);
            model->submitAll();
        }
        else return;

    }
}

void AllStuInfo::on_pushButton_asc_clicked()
{
    model->sort(0,Qt::AscendingOrder);
}

void AllStuInfo::on_pushButton_desc_clicked()
{
    model->sort(0,Qt::DescendingOrder);
}

void AllStuInfo::on_pushButton_back_clicked()
{
    emit this->backToAdminScreen();
}
