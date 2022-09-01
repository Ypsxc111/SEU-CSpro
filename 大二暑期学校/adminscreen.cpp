#include "adminscreen.h"
#include "ui_adminscreen.h"

AdminScreen::AdminScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminScreen)
{
    ui->setupUi(this);
    iniScene();
    allStudentInfo=new AllStuInfo;
    addstuInfo = new AddStudent;
    modistupassword=new ModifyStuPass;
    modiadminpass=new ModifyAdmPass;
    //addstudentgrade=new AddStuGrades;
    allstugradeshow=new AllStuGrades;
    modistuinfo=new ModifyStuInfo;
    connect(allStudentInfo,&AllStuInfo::backToAdminScreen,[=](){
        allStudentInfo->hide();
        this->show();
    });
    connect(addstuInfo,&AddStudent::backToAdminScreen,[=](){
        addstuInfo->hide();
        this->show();
    });
    connect(modistupassword,&ModifyStuPass::backToadminScreen,[=](){
        modistupassword->hide();
        this->show();
    });
    connect(modiadminpass,&ModifyAdmPass::backToAdminScreen,[=](){
        modiadminpass->hide();
        this->show();
    });
//    connect(addstudentgrade,&AddStuGrades::backToAdminScreen,[=](){
//        addstudentgrade->hide();
//        this->show();
//    });
    connect(allstugradeshow,&AllStuGrades::backToAdminScreen,[=](){
        allstugradeshow->hide();
        this->show();
    });
    connect(modistuinfo,&ModifyStuInfo::backToAdminScreen,[=](){
        modistuinfo->hide();
        this->show();
    });
}

AdminScreen::~AdminScreen()
{
    delete ui;
}

void AdminScreen::iniScene()
{
    setWindowIcon(QIcon(":/imag/icon.jpg"));
    setWindowTitle("管理员操作界面");
    setFixedSize(500,333);
}

void AdminScreen::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,500,333,QPixmap(":/imag/background4.jpg"));
}

void AdminScreen::on_pushButton_infoShow_clicked()
{
    this->hide();
    allStudentInfo->show();

}

void AdminScreen::on_pushButton_addInfo_clicked()
{
    this->hide();
    addstuInfo->show();
}

void AdminScreen::on_pushButton_modiAdPass_clicked()
{
    this->hide();
    modiadminpass->show();
}

void AdminScreen::on_pushButton_modiStuP_clicked()
{
    this->hide();
    modistupassword->show();
}

void AdminScreen::on_pushButton_addGrade_clicked()
{
    emit this->backToLoginScreen();

    //addstudentgrade->show();
}

void AdminScreen::on_pushButton_gradeShow_clicked()
{
    this->hide();
    allstugradeshow->show();
}

void AdminScreen::on_pushButton_modyInfo_clicked()
{
    this->hide();
    modistuinfo->show();
}
