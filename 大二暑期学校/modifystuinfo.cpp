#include "modifystuinfo.h"
#include "ui_modifystuinfo.h"
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQuery>


ModifyStuInfo::ModifyStuInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModifyStuInfo)
{
    ui->setupUi(this);
    initScreen();

}

ModifyStuInfo::~ModifyStuInfo()
{
    delete ui;
}

void ModifyStuInfo::initScreen()
{
    setWindowIcon(QIcon(":/imag/icon.jpg"));
    setWindowTitle("修改学生信息");
    setFixedSize(500,333);
    ui->comboBox_province->setCurrentText("");
    ui->comboBox_college->setCurrentText("");
    ui->comboBox_class->setCurrentText("");
    ui->lineEdit_showMajor->setText("");
}

void ModifyStuInfo::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,500,333,QPixmap(":/imag/background4.jpg"));
}

void ModifyStuInfo::getInfoAndShow()
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
        query.exec("select count(*) from stutable where stid='"+sid+"'");
        query.next();
        int num=query.value(0).toInt();
        if(!num)
        {
            QMessageBox::information(this,"提示","无此学生.\n请重新输入!");
            return;
        }
        else
        {
            query.exec("select sname,ssex,sage,splace,smajor from stutable where stid='"+sid+"'");
            query.next();
            sname=removeSpace(query.value(0).toString());
            ssex=removeSpace(query.value(1).toString());
            sage=removeSpace(query.value(2).toString());
            splace=removeSpace(query.value(3).toString());
            smajor=removeSpace(query.value(4).toString());
        }

    }

    ui->lineEdit_age->setText(sage);
    ui->lineEdit_name->setText(sname);
    if(ssex=="男")
        ui->radioButton_man->setChecked(true);
    else ui->radioButton_woman->setChecked(true);
    ui->lineEdit_showMajor->setText(smajor);
    ui->lineEdit_showPlace->setText(splace);
}

void ModifyStuInfo::setInformation()
{
    sname=ui->lineEdit_name->text();
    sage=ui->lineEdit_age->text();
    splace=ui->lineEdit_showPlace->text();
    smajor=ui->lineEdit_showMajor->text();
    if(ui->radioButton_man->isChecked())
        ssex="男";
    else ssex="女";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName(dbHostName);
    db.setDatabaseName("custom2.db");
    db.setUserName(dbusername);
    db.setPassword(dbpassword);
    bool isOpen=db.open();
    if(isOpen)
    {
        QSqlQuery query(db);
        query.exec("update stutable set sname='"+sname+"',ssex='"+ssex+"',sage='"+sage+"',"
                "splace='"+splace+"',smajor='"+smajor+"' where stid='"+sid+"'");
        query.next();
        qDebug()<<sname<<sage<<splace<<smajor<<ssex;
        QMessageBox::information(this,"消息","修改成功！");
    }
}

void ModifyStuInfo::on_pushButton_back_clicked()
{
    emit this->backToAdminScreen();
}


void ModifyStuInfo::on_comboBox_province_currentIndexChanged(int index)
{
    switch(ui->comboBox_province->currentIndex())
    {
    case 0:
        ui->comboBox_city->clear();
        ui->comboBox_city->insertItem(0,"滁州市");
        ui->comboBox_city->insertItem(1,"合肥市");
        ui->comboBox_city->insertItem(2,"安庆市");
        ui->comboBox_city->insertItem(3,"芜湖市");
        ui->comboBox_city->insertItem(4,"蚌埠市");

        break;
    case 1:
        ui->comboBox_city->clear();
        ui->comboBox_city->insertItem(0,"朝阳区");
        ui->comboBox_city->insertItem(1,"东城区");
        ui->comboBox_city->insertItem(2,"西城区");
        ui->comboBox_city->insertItem(3,"房山区");
        ui->comboBox_city->insertItem(4,"密云区");
        ui->comboBox_city->insertItem(5,"海淀区");

        break;
    case 2:
        ui->comboBox_city->clear();
        ui->comboBox_city->insertItem(0,"广州市");
        ui->comboBox_city->insertItem(1,"深圳市");
        ui->comboBox_city->insertItem(2,"珠海市");
        ui->comboBox_city->insertItem(3,"汕头市");

        break;
    case 3:
        ui->comboBox_city->clear();
        ui->comboBox_city->insertItem(0,"南宁市");
        ui->comboBox_city->insertItem(1,"柳州市");
        ui->comboBox_city->insertItem(2,"桂林市");

        break;
    case 4:
        ui->comboBox_city->clear();
        ui->comboBox_city->insertItem(0,"南京市");
        ui->comboBox_city->insertItem(1,"无锡市");
        ui->comboBox_city->insertItem(2,"常州市");
        ui->comboBox_city->insertItem(3,"苏州市");

        break;
    case 5:
        ui->comboBox_city->clear();
        ui->comboBox_city->insertItem(0,"黄浦区");
        ui->comboBox_city->insertItem(1,"松江区");
        ui->comboBox_city->insertItem(2,"浦东新区");
        ui->comboBox_city->insertItem(3,"宝山区");
        ui->comboBox_city->insertItem(4,"长宁区");
        ui->comboBox_city->insertItem(5,"静安区");

        break;
    case 6:
        ui->comboBox_city->clear();
        ui->comboBox_city->insertItem(0,"成都市");
        ui->comboBox_city->insertItem(1,"德阳市");
        ui->comboBox_city->insertItem(2,"绵阳市");
        ui->comboBox_city->insertItem(3,"宜宾市");
        ui->comboBox_city->insertItem(4,"乐山市");
        ui->comboBox_city->insertItem(5,"巴中市");
        ui->comboBox_city->insertItem(6,"遂宁市");

        break;
    }
}

void ModifyStuInfo::on_comboBox_province_activated(int index)
{
    QString getcity=ui->comboBox_city->currentText();
    if(getcity=="成都市")
    {
        ui->comboBox_county->clear();
        ui->comboBox_county->insertItem(0,"郫都区");
        ui->comboBox_county->insertItem(1,"青羊区");
        ui->comboBox_county->insertItem(2,"都江堰市");
        ui->comboBox_county->insertItem(3,"双流区");
    }
    else if(getcity=="南宁市")
    {
        ui->comboBox_county->clear();
        ui->comboBox_county->insertItem(0,"兴宁区");
        ui->comboBox_county->insertItem(1,"江南区");
        ui->comboBox_county->insertItem(2,"横县");
    }
    else if(getcity=="南京市")
    {
        ui->comboBox_county->clear();
        ui->comboBox_county->insertItem(0,"江宁区");
        ui->comboBox_county->insertItem(1,"秦淮区");
        ui->comboBox_county->insertItem(2,"玄武区");
        ui->comboBox_county->insertItem(3,"建邺区");
        ui->comboBox_county->insertItem(4,"六合区");
        ui->comboBox_county->insertItem(5,"鼓楼区");
    }
    else if(getcity=="广州市")
    {
        ui->comboBox_county->clear();
        ui->comboBox_county->insertItem(0,"花都区");
        ui->comboBox_county->insertItem(1,"越秀区");
        ui->comboBox_county->insertItem(2,"白云区");
    }
    else if(getcity=="无锡市")
    {
        ui->comboBox_county->clear();
        ui->comboBox_county->insertItem(0,"滨湖区");
        ui->comboBox_county->insertItem(1,"锡山区");
        ui->comboBox_county->insertItem(2,"梁溪区");
        ui->comboBox_county->insertItem(3,"新吴区");
        ui->comboBox_county->insertItem(4,"惠山区");
    }
    else if(getcity=="常州市")
    {
        ui->comboBox_county->clear();
        ui->comboBox_county->insertItem(0,"钟楼区");
        ui->comboBox_county->insertItem(1,"武进区");
        ui->comboBox_county->insertItem(2,"金坛区");
    }
    else if(getcity=="滁州市")
    {
        ui->comboBox_county->clear();
        ui->comboBox_county->insertItem(0,"琅琊区");
        ui->comboBox_county->insertItem(1,"南谯区");
        ui->comboBox_county->insertItem(2,"定远县");
    }
    else if(getcity=="合肥市")
    {
        ui->comboBox_county->clear();
        ui->comboBox_county->insertItem(0,"庐阳区");
        ui->comboBox_county->insertItem(1,"蜀山区");
        ui->comboBox_county->insertItem(2,"包河区");
        ui->comboBox_county->insertItem(3,"瑶海区");
    }
    else if(getcity=="安庆市")
    {
        ui->comboBox_county->clear();
        ui->comboBox_county->insertItem(0,"大观区");
        ui->comboBox_county->insertItem(1,"宜秀区");
        ui->comboBox_county->insertItem(2,"茶岭镇");
        ui->comboBox_county->insertItem(3,"怀宁县");
    }
    else if(getcity=="芜湖")
    {
        ui->comboBox_county->clear();
        ui->comboBox_county->insertItem(0,"湾沚区");
        ui->comboBox_county->insertItem(1,"繁昌区");
        ui->comboBox_county->insertItem(2,"鸠江区");

    }
    else if(getcity=="蚌埠市")
    {
        ui->comboBox_county->clear();
        ui->comboBox_county->insertItem(0,"淮上区");
        ui->comboBox_county->insertItem(1,"龙子湖区");
    }
    else if(getcity=="苏州市")
    {
        ui->comboBox_county->clear();
        ui->comboBox_county->insertItem(0,"吴江区");
        ui->comboBox_county->insertItem(1,"相城区");
        ui->comboBox_county->insertItem(2,"虎丘区");
    }
    else ui->comboBox_county->clear();
    splace=ui->comboBox_province->currentText()+ui->comboBox_city->currentText()+ui->comboBox_county->currentText();
    ui->lineEdit_showPlace->setText(splace);
}

void ModifyStuInfo::on_comboBox_city_activated(const QString &arg1)
{
    if(arg1=="成都市")
    {
        ui->comboBox_county->clear();
        ui->comboBox_county->insertItem(0,"郫都区");
        ui->comboBox_county->insertItem(1,"青羊区");
        ui->comboBox_county->insertItem(2,"都江堰市");
        ui->comboBox_county->insertItem(3,"双流区");
    }
    else if(arg1=="德阳市")
    {
        ui->comboBox_county->clear();
        ui->comboBox_county->insertItem(0,"旌阳区");
        ui->comboBox_county->insertItem(1,"罗江区");
        ui->comboBox_county->insertItem(2,"广汉市");
        ui->comboBox_county->insertItem(3,"中江县");
    }
    else if(arg1=="绵阳市")
    {
        ui->comboBox_county->clear();
        ui->comboBox_county->insertItem(0,"游仙区");
        ui->comboBox_county->insertItem(1,"三台县");
        ui->comboBox_county->insertItem(2,"盐亭县");
        ui->comboBox_county->insertItem(3,"平武县");
    }
    else if(arg1=="宜宾市")
    {
        ui->comboBox_county->clear();
        ui->comboBox_county->insertItem(0,"翠屏区");
        ui->comboBox_county->insertItem(1,"宜宾县");
        ui->comboBox_county->insertItem(2,"南溪区");
    }
    else if(arg1=="乐山市")
    {
        ui->comboBox_county->clear();
        ui->comboBox_county->insertItem(0,"市中区");
        ui->comboBox_county->insertItem(1,"五通桥区");
        ui->comboBox_county->insertItem(2,"峨眉山市");
    }
    else if(arg1=="巴中市")
    {
        ui->comboBox_county->clear();
        ui->comboBox_county->insertItem(0,"巴州区");
        ui->comboBox_county->insertItem(1,"恩阳区");
        ui->comboBox_county->insertItem(2,"平昌县");
    }
    else if(arg1=="遂宁市")
    {
        ui->comboBox_county->clear();
        ui->comboBox_county->insertItem(0,"船山区");
        ui->comboBox_county->insertItem(1,"射洪县");
        ui->comboBox_county->insertItem(2,"大英县");
    }
    else if(arg1=="南宁市")
    {
        ui->comboBox_county->clear();
        ui->comboBox_county->insertItem(0,"兴宁区");
        ui->comboBox_county->insertItem(1,"江南区");
        ui->comboBox_county->insertItem(2,"横县");
    }
    else if(arg1=="柳州市")
    {
        ui->comboBox_county->clear();
        ui->comboBox_county->insertItem(0,"柳州区");
        ui->comboBox_county->insertItem(1,"柳北区");
        ui->comboBox_county->insertItem(2,"柳中区");
    }
    else if(arg1=="桂林市")
    {
        ui->comboBox_county->clear();
        ui->comboBox_county->insertItem(0,"秀峰区");
        ui->comboBox_county->insertItem(1,"叠彩区");
        ui->comboBox_county->insertItem(2,"七星区");
    }
    else if(arg1=="广州市")
    {
        ui->comboBox_county->clear();
        ui->comboBox_county->insertItem(0,"花都区");
        ui->comboBox_county->insertItem(1,"越秀区");
        ui->comboBox_county->insertItem(2,"白云区");
    }
    else if(arg1=="深圳市")
    {
        ui->comboBox_county->clear();
        ui->comboBox_county->insertItem(0,"宝安区");
        ui->comboBox_county->insertItem(1,"罗湖区");
        ui->comboBox_county->insertItem(2,"南山区");
    }
    else if(arg1=="珠海市")
    {
        ui->comboBox_county->clear();
        ui->comboBox_county->insertItem(0,"香洲区");
        ui->comboBox_county->insertItem(1,"斗门区");
    }
    else if(arg1=="汕头市")
    {
        ui->comboBox_county->clear();
        ui->comboBox_county->insertItem(0,"金平区");
        ui->comboBox_county->insertItem(1,"龙湖区");
    }
    else if(arg1=="南京市")
    {
        ui->comboBox_county->clear();
        ui->comboBox_county->insertItem(0,"江宁区");
        ui->comboBox_county->insertItem(1,"秦淮区");
        ui->comboBox_county->insertItem(2,"玄武区");
        ui->comboBox_county->insertItem(3,"建邺区");
        ui->comboBox_county->insertItem(4,"六合区");
        ui->comboBox_county->insertItem(5,"鼓楼区");
    }
    else if(arg1=="无锡市")
    {
        ui->comboBox_county->clear();
        ui->comboBox_county->insertItem(0,"滨湖区");
        ui->comboBox_county->insertItem(1,"锡山区");
        ui->comboBox_county->insertItem(2,"梁溪区");
        ui->comboBox_county->insertItem(3,"新吴区");
        ui->comboBox_county->insertItem(4,"惠山区");
    }
    else if(arg1=="常州市")
    {
        ui->comboBox_county->clear();
        ui->comboBox_county->insertItem(0,"钟楼区");
        ui->comboBox_county->insertItem(1,"武进区");
        ui->comboBox_county->insertItem(2,"金坛区");
    }
    else if(arg1=="滁州市")
    {
        ui->comboBox_county->clear();
        ui->comboBox_county->insertItem(0,"琅琊区");
        ui->comboBox_county->insertItem(1,"南谯区");
        ui->comboBox_county->insertItem(2,"定远县");
    }
    else if(arg1=="合肥市")
    {
        ui->comboBox_county->clear();
        ui->comboBox_county->insertItem(0,"庐阳区");
        ui->comboBox_county->insertItem(1,"蜀山区");
        ui->comboBox_county->insertItem(2,"包河区");
        ui->comboBox_county->insertItem(3,"瑶海区");
    }
    else if(arg1=="安庆市")
    {
        ui->comboBox_county->clear();
        ui->comboBox_county->insertItem(0,"大观区");
        ui->comboBox_county->insertItem(1,"宜秀区");
        ui->comboBox_county->insertItem(2,"茶岭镇");
        ui->comboBox_county->insertItem(3,"怀宁县");
    }
    else if(arg1=="芜湖")
    {
        ui->comboBox_county->clear();
        ui->comboBox_county->insertItem(0,"湾沚区");
        ui->comboBox_county->insertItem(1,"繁昌区");
        ui->comboBox_county->insertItem(2,"鸠江区");

    }
    else if(arg1=="蚌埠市")
    {
        ui->comboBox_county->clear();
        ui->comboBox_county->insertItem(0,"淮上区");
        ui->comboBox_county->insertItem(1,"龙子湖区");
    }
    else if(arg1=="苏州市")
    {
        ui->comboBox_county->clear();
        ui->comboBox_county->insertItem(0,"吴江区");
        ui->comboBox_county->insertItem(1,"相城区");
        ui->comboBox_county->insertItem(2,"虎丘区");
    }
    else
    {
        ui->comboBox_county->clear();
    }
    splace=ui->comboBox_province->currentText()+ui->comboBox_city->currentText()+ui->comboBox_county->currentText();
    ui->lineEdit_showPlace->setText(splace);
}

void ModifyStuInfo::on_comboBox_college_currentIndexChanged(int index)
{
    switch(ui->comboBox_college->currentIndex())
    {
    case 0:
        ui->comboBox_major->clear();
        ui->comboBox_major->insertItem(0,"思想政治教育");
        break;
    case 1:
        ui->comboBox_major->clear();
        ui->comboBox_major->insertItem(0,"会计学");
        ui->comboBox_major->insertItem(1,"人力资源管理");
        ui->comboBox_major->insertItem(2,"物流工程");
        ui->comboBox_major->insertItem(3,"市场营销");
        ui->comboBox_major->insertItem(4,"工商管理");
        ui->comboBox_major->insertItem(5,"资产评估");
        ui->comboBox_major->insertItem(6,"财务管理");
        break;
    case 2:
        ui->comboBox_major->clear();
        ui->comboBox_major->insertItem(0,"计算机科学与技术");
        ui->comboBox_major->insertItem(1,"软件工程");
        ui->comboBox_major->insertItem(2,"物联网工程");
        ui->comboBox_major->insertItem(3,"网络空间安全");
        break;
    case 3:
        ui->comboBox_major->clear();
        ui->comboBox_major->insertItem(0,"信息与计算科学");
        ui->comboBox_major->insertItem(1,"化学");
        ui->comboBox_major->insertItem(2,"应用物理学");
        break;
    case 4:
        ui->comboBox_major->clear();
        ui->comboBox_major->insertItem(0,"英语");
        ui->comboBox_major->insertItem(1,"翻译");
        ui->comboBox_major->insertItem(2,"日语");
        break;

    }
    smajor=ui->comboBox_college->currentText()+ui->comboBox_major->currentText()+ui->comboBox_class->currentText();
    ui->lineEdit_showMajor->setText(smajor);
}

void ModifyStuInfo::on_pushButton_select_clicked()
{
    sid=removeSpace(ui->lineEdit_sid->text());
    if(isProperId(sid))
    {
        getInfoAndShow();
    }
    else QMessageBox::information(this,"警告","输入学生学号错误\n请重新输入！");
}

void ModifyStuInfo::on_comboBox_county_activated(int index)
{
    splace=ui->comboBox_province->currentText()+ui->comboBox_city->currentText()+ui->comboBox_county->currentText();
    ui->lineEdit_showPlace->setText(splace);
}

void ModifyStuInfo::on_pushButton_clicked()
{
    setInformation();

}

void ModifyStuInfo::on_comboBox_major_activated(int index)
{
    smajor=ui->comboBox_college->currentText()+ui->comboBox_major->currentText()+ui->comboBox_class->currentText();
    ui->lineEdit_showMajor->setText(smajor);
}

void ModifyStuInfo::on_comboBox_class_activated(int index)
{
    smajor=ui->comboBox_college->currentText()+ui->comboBox_major->currentText()+ui->comboBox_class->currentText();
    ui->lineEdit_showMajor->setText(smajor);
}
