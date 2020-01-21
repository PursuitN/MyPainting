#include "clipalgorithm.h"
#include "ui_clipalgorithm.h"

ClipAlgorithm::ClipAlgorithm(QWidget *parent) :QDialog(parent),
    ui(new Ui::ClipAlgorithm){
    ui->setupUi(this);

    this->setWindowTitle("Set Clip Algorithm");     //设置窗口的名字
    this->setWindowIcon(QIcon(":/images/imgs/setCanvasBackground.PNG"));
}

ClipAlgorithm::~ClipAlgorithm(){
    delete ui;
}

void ClipAlgorithm::on_buttonBox_clicked(QAbstractButton *button){
    bool cohenSutherland=ui->CohenSutherland->isChecked();
    bool liangBarsky=ui->LiangBarsky->isChecked();
    if( (cohenSutherland==false&&liangBarsky==false)||(cohenSutherland==true&&liangBarsky==true) ){
        QString myTitle = QStringLiteral("错误提示");
        QString myInfo = QStringLiteral("请选择有且仅有一个算法选项！");
        QMessageBox::information(this,myTitle,myInfo,QStringLiteral("确定"));
    }
    else{
        if(cohenSutherland==true){
            emit sendClipAlgorithm(0);
        }
        else{
            emit sendClipAlgorithm(1);
        }
    }
}
