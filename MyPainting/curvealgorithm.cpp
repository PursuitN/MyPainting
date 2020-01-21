#include "curvealgorithm.h"
#include "ui_curvealgorithm.h"

CurveAlgorithm::CurveAlgorithm(QWidget *parent) :QDialog(parent),
    ui(new Ui::CurveAlgorithm){
    ui->setupUi(this);
    this->setWindowTitle("Set Curve Algorithm");     //设置窗口的名字
    this->setWindowIcon(QIcon(":/images/imgs/setCanvasBackground.PNG"));
}

CurveAlgorithm::~CurveAlgorithm(){
    delete ui;
}

void CurveAlgorithm::on_buttonBox_clicked(QAbstractButton *button){
    bool bezier=ui->Bezier->isChecked();
    bool bspline=ui->Bspline->isChecked();
    if( (bezier==false&&bspline==false)||(bezier==true&&bspline==true) ){
        QString myTitle = QStringLiteral("错误提示");
        QString myInfo = QStringLiteral("请选择有且仅有一个算法选项！");
        QMessageBox::information(this,myTitle,myInfo,QStringLiteral("确定"));
    }
    else{
        if(bezier==true){
            emit sendCurveAlgorithm(0);
        }
        else{
            emit sendCurveAlgorithm(1);
        }
    }
}
