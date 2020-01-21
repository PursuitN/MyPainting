#include "linealgorithm.h"
#include "ui_linealgorithm.h"

LineAlgorithm::LineAlgorithm(QWidget *parent) :QDialog(parent),ui(new Ui::LineAlgorithm){
    ui->setupUi(this);
    this->setWindowTitle("Set Line Algorithm");     //设置窗口的名字
    this->setWindowIcon(QIcon(":/images/imgs/setCanvasBackground.PNG"));
}

LineAlgorithm::~LineAlgorithm(){
    delete ui;
}


void LineAlgorithm::on_buttonBox_clicked(QAbstractButton *button){
    bool dda=ui->DDA->isChecked();
    bool bres=ui->Bresenham->isChecked();
    if( (dda==false&&bres==false)||(dda==true&&bres==true) ){
        QString myTitle = QStringLiteral("错误提示");
        QString myInfo = QStringLiteral("请选择有且仅有一个算法选项！");
        QMessageBox::information(this,myTitle,myInfo,QStringLiteral("确定"));
    }
    else{
        if(dda==true){
            emit sendLineAlgorithm(0);
        }
        else{
            emit sendLineAlgorithm(1);
        }
    }
}
