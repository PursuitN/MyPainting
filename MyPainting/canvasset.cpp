#include "canvasset.h"
#include "ui_canvasset.h"


CanvasSet::CanvasSet(QWidget *parent) :QDialog(parent),ui(new Ui::CanvasSet){
    ui->setupUi(this);

    ui->canvasWidth->setEchoMode(QLineEdit::Normal);        //设置填写信息
    ui->canvasWidth->setPlaceholderText("width");

    ui->canvasHeight->setEchoMode(QLineEdit::Normal);
    ui->canvasHeight->setPlaceholderText("height");

    Width=0;
    Height=0;

    this->setWindowTitle("Set New Canvas");     //设置窗口的名字
    this->setWindowIcon(QIcon(":/images/imgs/setCanvasBackground.PNG"));     //设置新画布的图标

}

CanvasSet::~CanvasSet()
{
    delete ui;
}


void CanvasSet::on_buttonBox_clicked(QAbstractButton *button){
    Width=(ui->canvasWidth->text()).toInt();
    Height=(ui->canvasHeight->text()).toInt();
    if(Width>=100&&Width<=1000&&Height>=100&&Height<=1000){
        emit sendCanvasInfo(Width,Height);      //发射函数，传递画布的宽高信息
    }
    else{
        QString myTitle = QStringLiteral("错误提示");
        QString myInfo = QStringLiteral("Width/Height不在规定范围内");
        QMessageBox::information(this,myTitle,myInfo,QStringLiteral("确定"));
    }

}
