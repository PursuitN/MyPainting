#include "mainwindow.h"
#include "ui_mainwindow.h"




MainWindow::MainWindow(QWidget *parent,cmdcontrol *ctrl) : QMainWindow(parent),ui(new Ui::MainWindow){
    ui->setupUi(this);

    this->setWindowTitle("myPainting");     //整个应用程序的名字
    this->setWindowIcon(QIcon(":/images/imgs/myPainting.PNG"));     //整个应用程序的图标

    initMdiArea();

    WindowIndex=0;

    if(ctrl!=nullptr){

        //表明是命令行
        vector<string> cmds=ctrl->getPacket();
        int cmdsize=cmds.size();

        for(int i=0;i<cmdsize;i++){
            vector<string> wordPacket=ctrl->cmdtheOne(cmds[i]);

            //resetCanvas width height
            if(wordPacket[0]=="resetCanvas"){
                //qDebug()<<"resetCanvas"<<endl;
                int width= stoi(wordPacket[1]);
                int height=stoi(wordPacket[2]);
                if(allCanvans.size()!=0){
                    allCanvans.clear();
                }
                NewCanvas(width,height);
            }

            //saveCanvas name
            else if(wordPacket[0]=="saveCanvas"){
                //qDebug()<<"saveCanvas"<<endl;
                QString path=QString::fromStdString(ctrl->getSavepath());
                QString name=QString::fromStdString(wordPacket[1]);
                allCanvans[0]->canvasSaveCmd(path,name);

            }

            //setColor R G B
            else if(wordPacket[0]=="setColor"){
                //qDebug()<<"setColor"<<endl;
                int r=stoi(wordPacket[1]);
                int g=stoi(wordPacket[2]);
                int b=stoi(wordPacket[3]);
                QColor thecolor(r,g,b);
                allCanvans[0]->setColor(thecolor);
            }

            //drawLine id x1 y1 x2 y2 algorithm
            else if(wordPacket[0]=="drawLine"){
                //qDebug()<<"drawLine"<<endl;
                Canvas *ca=allCanvans[0];
                ca->drawCmd(wordPacket);

            }

            //drawPolygon id n algorithm x1 y1 x2 y2 … xn yn
            else if(wordPacket[0]=="drawPolygon"){
                //qDebug()<<"drawPolygon"<<endl;
                vector<string> wordPacket2=ctrl->cmdtheOne(cmds[i+1]);
                for(int i=0;i<wordPacket2.size();i++){
                    wordPacket.push_back(wordPacket2[i]);
                }
                i=i+1;
                Canvas *ca=allCanvans[0];
                ca->drawCmd(wordPacket);
            }

            //drawEllipse id x y rx ry
            else if(wordPacket[0]=="drawEllipse"){
                //qDebug()<<"drawEllipse"<<endl;
                Canvas *ca=allCanvans[0];
                ca->drawCmd(wordPacket);
            }

            //drawCurve id n algorithm x1 y1 x2 y2 … xn yn
            else if(wordPacket[0]=="drawCurve"){
                //qDebug()<<"drawCurve"<<endl;
                vector<string> wordPacket2=ctrl->cmdtheOne(cmds[i+1]);
                for(int i=0;i<wordPacket2.size();i++){
                    wordPacket.push_back(wordPacket2[i]);
                }
                i=i+1;
                Canvas *ca=allCanvans[0];
                ca->drawCmd(wordPacket);
            }

            //translate id dx dy - rotate id x y r - scale id x y s - clip id x1 y1 x2 y2 algorithm
            else{
                Canvas *ca=allCanvans[0];
                allCanvans.clear();
                ca->changeCmd(wordPacket);
            }
        }
    }
}

MainWindow::~MainWindow(){
    delete ui;
}



void MainWindow::initMdiArea(){

    /* MDI QMdiArea 多文档区域
     * https://www.cnblogs.com/azbane/p/8656427.html
     */

    //setCentralWidget(ui->mdiArea);
    ui->mdiArea->setViewMode(QMdiArea::TabbedView);     //页切换模式 tab模式
    ui->mdiArea->setTabPosition(QTabWidget::North);     //放置tabBar的位置
    ui->mdiArea->setTabShape(QTabWidget::Rounded);      //tab的形状，Rounded圆角型；Triangular三角形,Triangular
    ui->mdiArea->setTabsClosable(true);                 //每个tab上放置红叉关闭某一个tab ，false:没有叉；true:有叉
    ui->mdiArea->setTabsMovable(true);                  //多个tab可鼠标拖动摆放顺序
}

unsigned int MainWindow::findWindow(){
    unsigned int index=allWindow.find(ui->mdiArea->activeSubWindow()).value();
    return index;
}



void MainWindow::on_HelpVersion_triggered(){

    /* 此模块为点击 “帮助/版本信息”内容 */

    QString myTitle = QStringLiteral("版本信息");
    QString myInfo = QStringLiteral("2019年计算机图形学大作业\n"
                                    "MyPainting\n"
                                    "作者：171860029 张雨");
    QMessageBox::information(this,myTitle,myInfo,QStringLiteral("确定"));

}

void MainWindow::on_NewCanvas_triggered(){

    /* 点击新建画布，构建一个新画布 */

    CanvasSet * canvasSet=new CanvasSet;        //设置画布大小UI弹出
    canvasSet->setModal(true);
    canvasSet->show();
    //一旦受到sendCanvasInfo(int,int)信号，传递信号给函数NewCanvas(int,int)，新建画布
    connect(canvasSet,SIGNAL(sendCanvasInfo(int,int)),this,SLOT(NewCanvas(int,int)));

}

void MainWindow::NewCanvas(int wi,int he){


    width=wi;
    height=he;

    /* 点击新建画布，构建一个新画布 */

    Canvas *theCanvas = new Canvas(this,width,height);              //新建一张画布
    allCanvans.push_back(theCanvas);                                //将新建的画布放入画布容器

    QMdiSubWindow *w = ui->mdiArea->addSubWindow(theCanvas);        //将这张画布加入子窗口
    allWindow.insert(w,WindowIndex);                                //窗口和窗口序号加入Qmap中
    WindowIndex++;
    ui->mdiArea->setActiveSubWindow(w);

    w->setWindowTitle(QStringLiteral("画布"));                       //设置每个画布上面的名字
    w->show();

}

void MainWindow::on_SaveCanvas_triggered(){
    unsigned int windowIndex=findWindow();
    allCanvans[windowIndex]->canvasSave();
}

void MainWindow::on_CleanCanvas_triggered(){
    unsigned int windowIndex=findWindow();
    allCanvans[windowIndex]->canvasClean();
}


void MainWindow::on_LinePaint_triggered(){
    LineAlgorithm *lineAlg=new LineAlgorithm;
    lineAlg->setModal(true);
    lineAlg->show();
    connect(lineAlg,SIGNAL(sendLineAlgorithm(int)),this,SLOT(NewLine(int)));
}

void MainWindow::NewLine(int algorithm){

    unsigned int windowIndex=findWindow();

    allCanvans[windowIndex]->setMode(0);
    allCanvans[windowIndex]->setFigure(1);
    allCanvans[windowIndex]->setAlgorithm(algorithm);
    //qDebug()<<windowIndex<<endl;
    //qDebug()<<"LineTriggered4"<<endl;
}


void MainWindow::on_CirclePaint_triggered(){
    unsigned int windowIndex=findWindow();
    allCanvans[windowIndex]->setFigure(2);
    allCanvans[windowIndex]->setMode(0);
}

void MainWindow::on_EllipsePaint_triggered(){
    unsigned int windowIndex=findWindow();
    allCanvans[windowIndex]->setFigure(3);
    allCanvans[windowIndex]->setMode(0);
}

void MainWindow::on_PolygonPaint_triggered(){
//    unsigned int windowIndex=findWindow();
//    allCanvans[windowIndex]->setFigure(4);
//    allCanvans[windowIndex]->setMode(0);
    PolygonAlgorithm *polygonAlg=new PolygonAlgorithm;
    polygonAlg->setModal(true);
    polygonAlg->show();
    connect(polygonAlg,SIGNAL(sendPolygonAlgorithm(int)),this,SLOT(NewPolygon(int)));
}

void MainWindow::NewPolygon(int algorithm){
    unsigned int windowIndex=findWindow();

    allCanvans[windowIndex]->setMode(0);
    allCanvans[windowIndex]->setFigure(4);
    allCanvans[windowIndex]->setAlgorithm(algorithm);
}

void MainWindow::on_CurvePaint_triggered(){
//    unsigned int windowIndex=findWindow();
//    allCanvans[windowIndex]->setFigure(5);
//    allCanvans[windowIndex]->setMode(0);
        CurveAlgorithm *curveAlg=new CurveAlgorithm;
        curveAlg->setModal(true);
        curveAlg->show();
        connect(curveAlg,SIGNAL(sendCurveAlgorithm(int)),this,SLOT(NewCurve(int)));
        //qDebug()<<"LineTriggered2"<<endl;
}

void MainWindow::NewCurve(int algorithm){
    unsigned int windowIndex=findWindow();
    allCanvans[windowIndex]->setMode(0);
    allCanvans[windowIndex]->setFigure(5);
    allCanvans[windowIndex]->setAlgorithm(algorithm);
}


void MainWindow::on_DeleteFigure_triggered(){
    unsigned int windowIndex=findWindow();
    allCanvans[windowIndex]->setMode(6);
}

void MainWindow::on_ChangePoint_triggered(){
    QString myTitle = QStringLiteral("修改图元");
    QString myInfo = QStringLiteral("修改：通过对控制点的修改进行图元修改\n"
                                    "不支持多边形的修改");
    QMessageBox::information(this,myTitle,myInfo,QStringLiteral("确定"));

    unsigned int windowIndex=findWindow();
    allCanvans[windowIndex]->setMode(7);
}


void MainWindow::on_TranslateFigure_triggered(){


    unsigned int windowIndex=findWindow();
    allCanvans[windowIndex]->setMode(1);
}

void MainWindow::on_RotateFigure_triggered(){
    QString myTitle = QStringLiteral("旋转");
    QString myInfo = QStringLiteral("旋转：对圆/椭圆外所有图元有效\n"
                                    "请注意不要点击圆/椭圆图元");
    QMessageBox::information(this,myTitle,myInfo,QStringLiteral("确定"));

    unsigned int windowIndex=findWindow();
    allCanvans[windowIndex]->setMode(3);
}

void MainWindow::on_ScaleFigure_triggered(){
    unsigned int windowIndex=findWindow();
    allCanvans[windowIndex]->setMode(4);
}

void MainWindow::on_ClipFigure_triggered(){

//    unsigned int windowIndex=findWindow();
//    allCanvans[windowIndex]->setMode(5);
    ClipAlgorithm *clipAlg=new ClipAlgorithm;
    clipAlg->setModal(true);
    clipAlg->show();
    connect(clipAlg,SIGNAL(sendClipAlgorithm(int)),this,SLOT(NewClip(int)));
}

void MainWindow::NewClip(int algorithm){
    unsigned int windowIndex=findWindow();
    allCanvans[windowIndex]->setMode(5);
    allCanvans[windowIndex]->setAlgorithm(algorithm);
}


void MainWindow::on_SelectColor_triggered(){
    QColor color = QColorDialog::getColor(Qt::black, this);
    unsigned int windowIndex=findWindow();
    allCanvans[windowIndex]->setColor(color);

}

void MainWindow::on_NewCanvas2_triggered(){
    on_NewCanvas_triggered();
}

void MainWindow::on_SaveCanvas2_triggered(){
    on_SaveCanvas_triggered();
}

void MainWindow::on_CleanCanvas2_triggered(){
    on_CleanCanvas_triggered();
}

void MainWindow::on_LinePaint2_triggered(){
    on_LinePaint_triggered();
}

void MainWindow::on_CirclePaint2_triggered(){
    on_CirclePaint_triggered();
}

void MainWindow::on_EllipsePaint2_triggered(){
    on_EllipsePaint_triggered();
}

void MainWindow::on_PolygonPaint2_triggered(){
    on_PolygonPaint_triggered();
}

void MainWindow::on_CurvePaint2_triggered(){
    on_CurvePaint_triggered();
}

void MainWindow::on_TranslateFigure2_triggered(){
    on_TranslateFigure_triggered();
}

void MainWindow::on_RotateFigure2_triggered(){
    on_RotateFigure_triggered();
}

void MainWindow::on_ScaleFigure2_triggered(){
    on_ScaleFigure_triggered();
}

void MainWindow::on_ClipFigure2_triggered(){
    on_ClipFigure_triggered();
}

void MainWindow::on_SelectColor2_triggered(){
    on_SelectColor_triggered();
}

void MainWindow::on_DeleteFigure2_triggered(){
    on_DeleteFigure_triggered();
}

void MainWindow::on_ChangePoint2_triggered(){
    on_ChangePoint_triggered();
}
