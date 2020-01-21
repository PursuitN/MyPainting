#include "canvas.h"

//#include<iostream>
//using namespace std;


Canvas::Canvas(QWidget *parent,int width,int height) :QOpenGLWidget(parent){

    /* 默认函数，这里是直接准备一个画布
     * https://cloud.tencent.com/developer/ask/133893
     * 下面的~Canvas / initializeGL / resizeGL / paintGL都是来自该网站的源码
     */

    CanvasPix =new QPixmap(width,height);       //此QPixmap对象用来准备随时接收绘制的内容,大小为初始的大小
    CanvasPix->fill(Qt::white);                 //填充背景色为白色

    TempPix =new QPixmap(width,height);         //此QPixmap对象用来准备随时接收绘制的内容,大小为初始的大小
    TempPix->fill(Qt::white);

    setMaximumSize(width,height);               //设置绘制区窗体的min/max尺寸，放大会失真，同时控制画布大小
    setMinimumSize(width,height);

    drawFigure=0;
    drawState=0;
    changeState=0;
    changeIndex=-1;
    algorithm=0;
    add=0;
    curfigure=nullptr;
    tmpPoint=nullptr;

    curColor=Qt::black;
}


void Canvas::initializeGL(){

    /* 系统会自动调用的函数 初始化GL */
    initializeOpenGLFunctions();
    this->openFunc  = QOpenGLContext::currentContext()->functions();
    openFunc->glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    //glClearColor(0.0f, 1.0f, 0.5f, 0.0f); 绿色
    //glClearColor(1.0, 1.0, 1.0, 0); /白色
    //glClearColor(0.0, 0.0, 0.0, 0); 黑色

}

void Canvas::resizeGL(int w, int h){
    //w=100;h=20;
    openFunc->glViewport(0, 0, w, h);
    //cout<<w<<h<<endl;
    //openFunc->glViewport(0, 0, 200, 1000);
}

void Canvas::paintGL(){
    openFunc->glClear(GL_COLOR_BUFFER_BIT);
}



void Canvas::setFigure(int setmode){
    drawFigure=setmode;
}

void Canvas::setMode(int setmode){
    changeState=setmode;
}

void Canvas::setAlgorithm(int alg){
    algorithm=alg;
}

int Canvas::figurePos(QPoint p){
    //qDebug()<<"figurePos1"<<endl;
    int figureNum=figureBox.size();
    for(int i=0;i<figureNum;i++){
        if( abs(figureBox[i]->drawPoint.x()-p.x())<6
                &&abs(figureBox[i]->drawPoint.y()-p.y())<6 ){
            //qDebug()<<"figurePos2"<<endl;
            //qDebug()<<i<<endl;
            curfigure=figureBox[i];
            return i;   //找到了相应的位置返回相应的位置
        }
    }
    return -1;  //没找到位置，返回-1
}

void Canvas::pointPos(QPoint p){
    int figureNum=curfigure->infoPoint.size();
    for(int i=0;i<figureNum;i++){
        if( abs(curfigure->infoPoint[i].x()-p.x())<6
                &&abs(curfigure->infoPoint[i].y()-p.y())<6 ){
            tmpPoint=&curfigure->infoPoint[i];   //找到了相应的位置返回相应的位置
            return;
        }
    }
    tmpPoint=nullptr;
}

void Canvas::setColor(QColor color){
    curColor=color;
}



void Canvas::canvasSave(){
    //弹出对话框，获得存储地址，存储内容
    QString savePath = QFileDialog::getSaveFileName(this,"savePainting","","img (*.bmp)");
    //QString savePath="E:\\CUR\\computergraph\\MyPainting\\cmd\\hh.bmp";
    if(!savePath.isEmpty()){
        CanvasPix->save(savePath,"bmp");
    }
}

void Canvas::canvasSaveCmd(QString path, QString name){
    QString tmp=path+"\\"+name+".bmp";
    qDebug()<<"savepath:"+tmp<<endl;
    CanvasPix->save(tmp,"bmp");
}

void Canvas::canvasClean(){
    curfigure=nullptr;
    points.clear();
    infotmp.clear();

    figureBox.clear();
    CanvasPix->fill(Qt::white);
    TempPix->fill(Qt::white);
    QPainter thePainter(this);
    thePainter.drawPixmap(0,0,*TempPix);
    thePainter.drawPixmap(0,0,*CanvasPix);
}



void Canvas::mousePressEvent(QMouseEvent *event){

    /* 鼠标左键按下事件 */

    if(event->button()==Qt::LeftButton){
        //if(changeState!=1&&changeState!=3&&changeState!=4&&changeState!=5&&changeState!=6&&changeState!=7){
        if(changeState==2){
            // 这样子是为了在按下之后能够画，为了避免自动paintevent
            changeState=0;
        }

        if(changeState==0){

            //qDebug()<<"mousePressEvent"<<endl;

            //不为null，析构掉上一个，=0确保状态是等待绘图的状态，放弃这个了不重要
            /*if(!curfigure){
                if(drawState==0){
                    //curfigure->~AllFigure();
                }
             }*/

            //不同的情况下画出不同的图形

            if(drawFigure==0){
                curfigure=new Line;
                curfigure->setColor(curColor);
                curfigure->setAlgorithm(algorithm);
            }
            else if(drawFigure==1){
                curfigure=new Line;
                curfigure->setColor(curColor);
                curfigure->setAlgorithm(algorithm);
            }
            else if(drawFigure==2){
                curfigure=new Circle;
                curfigure->setColor(curColor);
                curfigure->setAlgorithm(algorithm);
            }
            else if(drawFigure==3){
                curfigure=new class Ellipse;
                curfigure->setColor(curColor);
                curfigure->setAlgorithm(algorithm);
            }
            else if(drawFigure==4){
                if(drawState==0){
                    //还没画完是不能new的
                    curfigure=new class Polygon;
                    curfigure->setColor(curColor);
                    curfigure->setAlgorithm(algorithm);
                }
            }
            else if(drawFigure==5){
                if(drawState==0){
                    //还没画完是不能new的
                    curfigure=new class Curve;
                    curfigure->setColor(curColor);
                    curfigure->setAlgorithm(algorithm);
                }
            }


            //if判断是否为鼠标左键按下，获取按下的位置，然后放入该图形的infoPoint[0][1]等等中
            if(event->button()==Qt::LeftButton){
                //qDebug()<<"mousePressEvent2"<<endl;

                if(drawFigure==1||drawFigure==2||drawFigure==3||
                        ((drawFigure==4||drawFigure==5)&&curfigure->infoPoint.size()==0)){
                    //如果是直线、圆、椭圆，那么就只有两个点,多边形初始也是放入两个点
                    QPoint beginpoint=event->pos();
                    //curfigure-> infoPoint[0]=beginpoint; false
                    curfigure->infoPoint.push_back(beginpoint);
                    curfigure->infoPoint.push_back(beginpoint);
                }
                else if((drawFigure==4||drawFigure==5)&&curfigure->infoPoint.size()!=0){
                    //如果是多边形多个点，并且已经有点放入了，只要增加每次后一个点
                    QPoint beginpoint=event->pos();
                    //int numAlready=curfigure->infoPoint.size();
                    curfigure->infoPoint.push_back(beginpoint);    //前一个提前分配的空间就是这个点替换
                    //curfigure->infoPoint.push_back(beginpoint);     //为下一个点提供空间，若为最后一个，最后一个重复放了两次
                }
            }
        }

        else if(changeState==1){

            //正在被修改的图形,平移
            if(event->button()==Qt::LeftButton){
                //qDebug()<<"mousePressEvent7"<<endl;
                QPoint point=event->pos();
                changeIndex=figurePos(point);
                //qDebug()<<"TranslateEvent"<<endl;
                //qDebug("changeIndex:%d\n",changeIndex);
            }
        }

        else if(changeState==3){
            //旋转图形
            if(points.size()==0){
                //放入旋转中心
                QPoint p=event->pos();
                points.push_back(p);
            }
            else{
                //找到当前的选中图形
                QPoint point=event->pos();
                changeIndex=figurePos(point);
                if(changeIndex!=-1){
                    points.push_back(curfigure->drawPoint); //把原来的中心当做points[1]
                    //infotmp.clear();
                    for(int i=0;i<curfigure->infoPoint.size();i++){
                        infotmp.push_back(curfigure->infoPoint[i]);
                    }
                }
            }
            update();
        }

        else if(changeState==4){
            // 缩放图元
            if(points.size()==0){
                //放入缩放中心
                QPoint p=event->pos();
                points.push_back(p);
            }
            else{
                //找到当前的选中图形
                QPoint point=event->pos();
                changeIndex=figurePos(point);
                if(changeIndex!=-1){
                    points.push_back(curfigure->drawPoint); //把原来的中心当做points[1]
                    //infotmp.clear();
                    for(int i=0;i<curfigure->infoPoint.size();i++){
                        infotmp.push_back(curfigure->infoPoint[i]);
                    }
                }
            }
            update();
        }

        else if(changeState==5){
            if(changeIndex!=-1){
                QPoint p=event->pos();
                points.push_back(p);
            }
            update();
        }

        else if(changeState==6){
            //删除图形
            //找到当前的选中图形
            QPoint point=event->pos();
            changeIndex=figurePos(point);
            update();
        }

        else if(changeState==7){
            //修改点
            //找到当前的选中图形
            if(changeIndex==-1){
                QPoint point=event->pos();
                changeIndex=figurePos(point);
                update();
            }
            else{
                QPoint point=event->pos();
                pointPos(point);
            }
        }
    }

    else if(event->button()==Qt::RightButton){
        if(changeState==6){
            //表示在删除图形，结束
            drawState=0;
            if(changeIndex!=-1){
                curfigure->setId(-1);
                curfigure->infoPoint.clear();
                changeIndex=-1;
            }
            update();
        }

        else if(changeState==7){
            //表示在修改点,结束
           drawState=0;
            if(changeIndex!=-1){
                changeIndex=-1;
                tmpPoint=nullptr;
            }
            update();
        }
    }
}

void Canvas::mouseDoubleClickEvent(QMouseEvent *event){
    //qDebug()<<"mouseDoubleClickEvent"<<endl;

    /* 若是最后一下，那么就让存储的最后两个点一样，用于判断表示结束了
     * 右键按下表示自动补充最后一条线
     * 存入figureBox中
     * 最后存入vector的没有重复的最后两个点
     */
    if(drawFigure==4){
        /*
        drawState=0;
        figureBox.push_back(curfigure);
        int numAlready=curfigure->infoPoint.size();
        QPoint lastSecond=curfigure-> infoPoint[numAlready-1];
        curfigure->infoPoint.push_back(lastSecond);
        changeState=0;
        */
        add=1;
        drawState=0;
        figureBox.push_back(curfigure);
        int numAlready=curfigure->infoPoint.size();
        QPoint lastSecond=curfigure-> infoPoint[numAlready-2];
        curfigure->infoPoint[numAlready-1]=lastSecond;
        changeState=0;
        update();
    }

}


void Canvas::mouseMoveEvent(QMouseEvent *event){

    //qDebug()<<"mouseMoveEvent"<<endl;
    if(event->buttons()&Qt::LeftButton){

        drawState=1;

        if(changeState==0){
            //qDebug()<<"mouseMoveEvent6"<<endl;
            //if(drawFigure==0||drawFigure==1||drawFigure==2||drawFigure==3||drawFigure==4||drawFigure==5){
                //为直线，圆，椭圆，就是两个点之间
                QPoint endpoint=event->pos();
                //curfigure-> infoPoint[1]=endpoint;
                int numAlready=curfigure->infoPoint.size();
                curfigure-> infoPoint[numAlready-1]=endpoint;
                //qDebug()<<"mouseMoveEvent2"<<endl;
                update();  //调用paintEvent函数重新绘制
            //}

            /*else if(drawFigure==4){
                //为多边形就是倒数第二个和当前的点之间画线
                QPoint endpoint=event->pos();
                int numAlready=curfigure->infoPoint.size();
                curfigure-> infoPoint[numAlready-1]=endpoint;
                update();
            }*/
        }

        else if(changeState==1&&changeIndex!=-1){
            //qDebug()<<"mouseMoveEvent8"<<endl;
            QPoint point=event->pos();
            int xc=point.x()-figureBox[changeIndex]->drawPoint.x();
            int yc=point.y()-figureBox[changeIndex]->drawPoint.y();
            figureBox[changeIndex]->translate(xc,yc);
            //qDebug()<<"TranslateMoveEvent"<<endl;
            //qDebug("xc:%d\n",xc);
            //qDebug("yc:%d\n",yc);
            update();
        }

        else if(changeState==3&&changeIndex!=-1){
            //表示正在旋转

            for(int i=0;i<curfigure->infoPoint.size();i++){
                curfigure->infoPoint[i]=infotmp[i];
            }

            //三个关键点
            QPoint p1=points[1]; //原来的圆心
            QPoint p3=event->pos(); //结束的圆心
            QPoint p2=points[0];    //围绕的中心点
            double p12=sqrt( (p2.x()-p1.x())*(p2.x()-p1.x()) + (p2.y()-p1.y())*(p2.y()-p1.y()) );
            double p23=sqrt( (p2.x()-p3.x())*(p2.x()-p3.x()) + (p2.y()-p3.y())*(p2.y()-p3.y()) );
            double p13=sqrt( (p1.x()-p3.x())*(p1.x()-p3.x()) + (p1.y()-p3.y())*(p1.y()-p3.y()) );
            //acos出来的是弧度
            double radian=acos((p12*p12+p23*p23-p13*p13)/(2*p12*p23));
            //判断顺时针还是逆时针
            QPoint begin(p1.x()-p2.x(),p1.y()-p2.y()); //以旋转中心建立坐标系
            QPoint end(p3.x()-p2.x(),p3.y()-p2.y());
            double b=qRadiansToDegrees(fabs(atan((double)begin.y()/(double)begin.x())));
            double e=qRadiansToDegrees(fabs(atan((double)end.y()/(double)end.x())));
            if(begin.x()>=0&&begin.y()>=0){
                b=360-b;
            }
            else if(begin.x()<=0&&begin.y()>=0){
                b=180+b;
            }
            else if(begin.x()<=0&&begin.y()<=0){
                b=180-b;
            }

            if(end.x()>=0&&end.y()>=0){
                e=360-e;
            }
            else if(end.x()<=0&&end.y()>=0){
                e=180+e;
            }
            else if(end.x()<=0&&end.y()<=0){
                e=180-e;
            }
            if((e-b)>0&&(e-b)<180){
                radian=radian*(-1);
            }
            if((e-b)<0&&(b-e)>180){
                radian=radian*(-1);
            }

//            double degree=radian*180/3.141592658;
//            qDebug()<<"hhhh"<<endl;
//            qDebug()<<(p12*p12+p23*p23-p13*p13)/(2*p12*p23)<<endl;
//            qDebug()<<radian<<endl;
//            qDebug()<<radian*180/3.141592658<<endl;
            curfigure->rotater(radian,p2.x(),p2.y());   //将图形旋转

            update();
        }

        else if(changeState==4&&changeIndex!=-1){
            //表示正在缩放

            for(int i=0;i<curfigure->infoPoint.size();i++){
                curfigure->infoPoint[i]=infotmp[i];
            }

            //三个关键点
            QPoint p1=points[1]; //原来的位置
            QPoint p3=event->pos(); //结束的位置
            QPoint p2=points[0];    //围绕的缩放点
            double prelength=(p1.x()-p2.x())*(p1.x()-p2.x());
            double curlength=(p3.x()-p2.x())*(p3.x()-p2.x());
            double multi=sqrt(curlength/prelength);

            curfigure->scale(multi,p2.x(),p2.y());   //将图形旋转

            update();
        }

        else if(changeState==5&&changeIndex!=-1){
            QPoint end=event->pos();
            if(points.size()==1){
                points.push_back(end);
            }
            else{
                points[1]=end;
            }
            update();
        }

        else if(changeState==7&&changeIndex!=-1){
            // 在修改点的位置
            if(tmpPoint!=nullptr){
                 QPoint end=event->pos();
                 *tmpPoint=end;
                 update();
            }
        }
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent *event){

    //qDebug()<<"mouseReleaseEvent"<<endl;


    if(event->button()==Qt::LeftButton){

        if(changeState==0){
            if(drawFigure==1){
                drawState=0;
                QPoint endpoint=event->pos();
                curfigure-> infoPoint[1]=endpoint;
                figureBox.push_back(curfigure);        //在鼠标松开的那一刻，该当前图形放入figureBox中
                update();
                //changeState=2;
            }
            else if(drawFigure==2||drawFigure==3){
                drawState=0;
                QPoint endpoint=event->pos();
                curfigure-> infoPoint[1]=endpoint;
                figureBox.push_back(curfigure);        //在鼠标松开的那一刻，该当前图形放入figureBox中
                update();
                //changeState=2;
            }
            else if(drawFigure==5){
                drawState=2;                //左键放开表示表示还没有画完多边形
                QPoint endpoint=event->pos();
                int numAlready=curfigure->infoPoint.size();
                curfigure-> infoPoint[numAlready-1]=endpoint;
                //changeState=0;
                update();
            }
            else if(drawFigure==4&&drawState!=0){
                drawState=2;                //左键放开表示表示还没有画完多边形
                QPoint endpoint=event->pos();
                int numAlready=curfigure->infoPoint.size();
                curfigure-> infoPoint[numAlready-1]=endpoint;
                //changeState=0;
                update();
            }
            /*
            else if(drawFigure==5){
                drawState=2;                //左键放开表示表示还没有画完曲线
                QPoint endpoint=event->pos();
                curfigure-> infoPoint.push_back(endpoint);
                figureBox.push_back(curfigure);
                //changeState=0;
                update();
            }
            */
        }

        else if(changeState==1&&changeIndex!=-1){\
            drawState=0;
            changeIndex=-1;
//            QPoint point=event->pos();
//            int xc=point.x()-figureBox[changeIndex]->drawPoint.x();
//            int yc=point.y()-figureBox[changeIndex]->drawPoint.y();
//            figureBox[changeIndex]->translate(xc,yc);
            update();
        }

        else if((changeState==3||changeState==4)&&changeIndex!=-1){
            drawState=0;
            changeIndex=-1;
            infotmp.clear();
            points.clear();
            update();
        }

        else if(changeState==5){
            if(changeIndex==-1){
                QPoint point=event->pos();
                changeIndex=figurePos(point);
                infotmp.clear();
                points.clear();
            }
            else if(changeIndex!=-1&&points.size()!=0){
                curfigure->clip(points[0].x(),points[0].y(),points[1].x(),points[1].y(),algorithm);
                drawState=0;
                changeIndex=-1;
                infotmp.clear();
                points.clear();
            }
            update();
        }

    }

    else if(event->button()==Qt::RightButton){
        if(changeState!=7&&changeState!=6){
                if(drawFigure==4){
                    drawState=0;
                    int numAlready=curfigure->infoPoint.size();
                    QPoint lastSecond=curfigure-> infoPoint[numAlready-1];
                    curfigure->infoPoint.push_back(lastSecond);
                    figureBox.push_back(curfigure);
                    changeState=0;
                    update();
                }
                else if(drawFigure==5){
                drawState=0;
                figureBox.push_back(curfigure);
                changeState=0;
                update();
            }
        }
    }

}

void Canvas::paintEvent(QPaintEvent *event){

    /* paintEvent是一个系统自动调用的函数
     * 在很多情况下会被调用，然后在每次update()时会被调用
     * 这里就是绘出相关信息
     */

    QPainter thePainter(this);
    QPen thePen;
    thePainter.setPen(thePen);


    if(changeState==0){
        if(drawFigure==1||drawFigure==2||drawFigure==3||drawFigure==4){
            if(drawState==1){
                //当在拖的过程中，在tempPix上显示，tempPix初始获得CanvasPix
                *TempPix=*CanvasPix;
                QPainter p(TempPix);
                p.setPen(thePen);
                curfigure->DrawFigure(p,0);
                thePainter.drawPixmap(0,0,*TempPix);
            }
            else if(drawState!=1){
                //当前状态不为正在画，那么鼠标已经松开，在CanvasPix上画，并且拷贝到thePainter当前画布上
                if(add==0){
                    QPainter p(CanvasPix);
                    p.setPen(thePen);
                    if(!(curfigure==nullptr)){
                        curfigure->DrawFigure(p,0);
                    }
                    thePainter.drawPixmap(0,0,*CanvasPix);
                    changeState=2;
                }
                else if(add==1){
                    add=0;
                    CanvasPix->fill(Qt::white);
                    QPainter p(CanvasPix);
                    p.setPen(thePen);
                    int figureNum=figureBox.size();
                    for(int i=0;i<figureNum;i++){
                        figureBox[i]->DrawFigure(p,0);
                    }
                    thePainter.drawPixmap(0,0,*CanvasPix);
                    changeState=2;
                }
            }          
        }
        else if(drawFigure==5){
            //曲线
            if(drawState==2||drawState==1){
                // 还没画完
                CanvasPix->fill(Qt::white);
                // 画出所有的图形
                QPainter p(CanvasPix);
                p.setPen(thePen);
                int figureNum=figureBox.size();
                for(int i=0;i<figureNum;i++){
                        figureBox[i]->DrawFigure(p,0);
                }
                if(!(curfigure==nullptr)){
                    curfigure->DrawFigure(p,0);
                }
                // 画出控制点
                QPen pen2;
                pen2.setColor(Qt::red);
                pen2.setWidth(8);
                p.setPen(pen2);
                for(int i=0;i<curfigure->infoPoint.size();i++){
                    p.drawPoint(curfigure->infoPoint[i]);
                }
                // 画出多边形
                QPen pen3;
                pen3.setColor(Qt::blue);
                pen3.setWidth(1);
                p.setPen(pen3);
                for(int i=0;i<curfigure->infoPoint.size()-1;i++){
                    p.drawLine(curfigure->infoPoint[i],curfigure->infoPoint[i+1]);
                }
                thePainter.drawPixmap(0,0,*CanvasPix);
            }
            else if(drawState==0){
                // 画完了
                CanvasPix->fill(Qt::white);
                QPainter p(CanvasPix);
                p.setPen(thePen);
                int figureNum=figureBox.size();
                for(int i=0;i<figureNum;i++){
                        figureBox[i]->DrawFigure(p,0);
                }
                if(!(curfigure==nullptr)){
                    curfigure->DrawFigure(p,0);
                }
                thePainter.drawPixmap(0,0,*CanvasPix);
            }
        }
    }

    else if(changeState==1){

        //先清空
        CanvasPix->fill(Qt::white);
        TempPix->fill(Qt::white);

        //在修改某个图形
        if(drawState==1){
            //qDebug()<<"paintEventdrawStateTemp"<<endl;
            *TempPix=*CanvasPix;
            QPainter p(TempPix);
            p.setPen(thePen);
            int figureNum=figureBox.size();
            for(int i=0;i<figureNum;i++){
                figureBox[i]->DrawFigure(p,0);
            }
            thePainter.drawPixmap(0,0,*TempPix);
        }
        else if(drawState!=1){
            QPainter p(CanvasPix);
            p.setPen(thePen);
            int figureNum=figureBox.size();
            for(int i=0;i<figureNum;i++){
                //figureBox[i].DrawFigure(p);
                //AllFigure *tmp=&figureBox[i];
                //(tmp)->DrawFigure(p);
                //(&figureBox[i])->DrawFigure(p);
                //figureBox[i].DrawFigure(p);
                //AllFigure *tmp;
                //tmp=&figureBox[i];
                //tmp->DrawFigure(p);
                figureBox[i]->DrawFigure(p,0);
            }
            thePainter.drawPixmap(0,0,*CanvasPix);
            //changeState=2;
        }
    }

    else if(changeState==3){
        CanvasPix->fill(Qt::white);
        TempPix->fill(Qt::white);
        //在修改某个图形
        if(drawState==1){
            *TempPix=*CanvasPix;
            QPainter p(TempPix);
            //画出旋转中心
            QPen pen;
            pen.setColor(Qt::green);
            pen.setWidth(8);
            p.setPen(pen);
            p.drawPoint(points[0]);
            //求出这个旋转的半径
            if(changeIndex!=-1){
                pen.setColor(Qt::yellow);
                pen.setWidth(1);
                p.setPen(pen);
                QPoint pc=points[0];
                QPoint pp=points[1];
                double r=sqrt((double)((pc.x()-pp.x())*(pc.x()-pp.x()))+(double)(pc.y()-pp.y())*(pc.y()-pp.y()));
                //画出那个旋转的圆,这里是辅助作图，所以直接调用了
                p.drawEllipse(pc.x()-r,pc.y()-r,r+r,r+r);
                //画出剩余的图形
                p.setPen(thePen);
                int figureNum=figureBox.size();
                for(int i=0;i<figureNum;i++){
                    figureBox[i]->DrawFigure(p,0);
                }
                thePainter.drawPixmap(0,0,*TempPix);
            }
        }
        else if(drawState!=1){
            QPainter p(CanvasPix);
            //画出中心
            if(points.size()!=0){
                QPen pen;
                pen.setColor(Qt::green);
                pen.setWidth(8);
                p.setPen(pen);
                p.drawPoint(points[0]);
            }
            //画出所有的图形
            p.setPen(thePen);
            int figureNum=figureBox.size();
            for(int i=0;i<figureNum;i++){
                figureBox[i]->DrawFigure(p,0);
            }
            thePainter.drawPixmap(0,0,*CanvasPix);
        }
    }

    else if(changeState==4){
        CanvasPix->fill(Qt::white);
        TempPix->fill(Qt::white);
        //在修改某个图形
        if(drawState==1){
            *TempPix=*CanvasPix;
            QPainter p(TempPix);
            //画出旋转中心
            QPen pen;
            pen.setColor(Qt::green);
            pen.setWidth(8);
            p.setPen(pen);
            p.drawPoint(points[0]);
            if(changeIndex!=-1){
                //画出缩放直线
                pen.setColor(Qt::yellow);
                pen.setWidth(1);
                p.setPen(pen);
                p.drawLine(points[0],curfigure->drawPoint);
                //画出剩余的图形
                p.setPen(thePen);
                int figureNum=figureBox.size();
                for(int i=0;i<figureNum;i++){
                    figureBox[i]->DrawFigure(p,0);
                }
                thePainter.drawPixmap(0,0,*TempPix);
            }
        }
        else if(drawState!=1){
            QPainter p(CanvasPix);
            //画出中心
            if(points.size()!=0){
                QPen pen;
                pen.setColor(Qt::green);
                pen.setWidth(8);
                p.setPen(pen);
                p.drawPoint(points[0]);
            }
            //画出所有的图形
            p.setPen(thePen);
            int figureNum=figureBox.size();
            for(int i=0;i<figureNum;i++){
                figureBox[i]->DrawFigure(p,0);
            }
            thePainter.drawPixmap(0,0,*CanvasPix);
        }
    }

    else if(changeState==5){
        CanvasPix->fill(Qt::white);
        TempPix->fill(Qt::white);
        //在修改某个图形
        if(drawState==1){
            *TempPix=*CanvasPix;
            QPainter p(TempPix);
            //画出旋转中心
            QPen pen;
            pen.setColor(Qt::yellow);
            pen.setWidth(1);
            p.setPen(pen);
            if(points.size()!=0){
                int tmp1=abs(points[1].x()-points[0].x());
                int tmp2=abs(points[1].y()-points[0].y());

                int tx=(points[0].x()<points[1].x())?points[0].x():points[1].x();
                int ty=(points[0].y()<points[1].y())?points[0].y():points[1].y();

                p.drawRect(tx,ty,tmp1,tmp2);
            }
            //画出剩余的图形
            p.setPen(thePen);
            int figureNum=figureBox.size();
            for(int i=0;i<figureNum;i++){
                figureBox[i]->DrawFigure(p,0);
            }
            if(changeIndex!=-1){
                QPen pen;
                pen.setColor(Qt::green);
                pen.setWidth(8);
                p.setPen(pen);
                p.drawPoint(curfigure->drawPoint);
            }
            thePainter.drawPixmap(0,0,*TempPix);
        }
        else if(drawState!=1){
            QPainter p(CanvasPix);
            //画出所有的图形
            p.setPen(thePen);
            int figureNum=figureBox.size();
            for(int i=0;i<figureNum;i++){
                figureBox[i]->DrawFigure(p,0);
            }
            if(changeIndex!=-1){
                QPen pen;
                pen.setColor(Qt::green);
                pen.setWidth(8);
                p.setPen(pen);
                p.drawPoint(curfigure->drawPoint);
            }
            thePainter.drawPixmap(0,0,*CanvasPix);
        }
    }

    else if(changeState==6){
        // 删除图形
        CanvasPix->fill(Qt::white);
        TempPix->fill(Qt::white);
        QPainter p(CanvasPix);
        p.setPen(thePen);
        int figureNum=figureBox.size();
        for(int i=0;i<figureNum;i++){
            figureBox[i]->DrawFigure(p,0);
        }

        // 重点标出选中的图形
        if(changeIndex!=-1){
            QPen p1;
            p1.setWidth(8);
            p1.setColor(Qt::green);
            p.setPen(p1);
            p.drawPoint(curfigure->drawPoint);
        }

        thePainter.drawPixmap(0,0,*CanvasPix);
    }

    else if(changeState==7){
        // 修改图形
        CanvasPix->fill(Qt::white);
        TempPix->fill(Qt::white);
        QPainter p(CanvasPix);
        p.setPen(thePen);
        int figureNum=figureBox.size();
        for(int i=0;i<figureNum;i++){
            figureBox[i]->DrawFigure(p,0);
        }

        if(changeIndex!=-1){
            int size=curfigure->infoPoint.size();
            // 若为曲线 画出多边形
            QPen pen3;
            pen3.setColor(Qt::blue);
            pen3.setWidth(1);
            p.setPen(pen3);
            if(curfigure->infoPoint[size-1]!=curfigure->infoPoint[size-2]){
                // 对多边形不处理了
                for(int i=0;i<curfigure->infoPoint.size()-1;i++){
                    p.drawLine(curfigure->infoPoint[i],curfigure->infoPoint[i+1]);
                }
            }
            // 画出选中图形的infopoint
            QPen p1;
            p1.setWidth(8);
            p1.setColor(Qt::green);
            p.setPen(p1);
            for(int i=0;i<size;i++){
                p.drawPoint(curfigure->infoPoint[i]);
            }
        }
        thePainter.drawPixmap(0,0,*CanvasPix);
    }
}



void Canvas::drawCmd(vector<string> s){

    //drawLine id x1 y1 x2 y2 algorithm
    if(s[0]=="drawLine"){
        curfigure=new Line;
        curfigure->setColor(curColor);
        int id=stoi(s[1]);
        curfigure->setId(id);
        QPoint p1(stoi(s[2]),stoi(s[3]));
        QPoint p2(stoi(s[4]),stoi(s[5]));
        curfigure->infoPoint.push_back(p1);
        curfigure->infoPoint.push_back(p2);
        QPainter p(CanvasPix);
        if(s[6]=="DDA"){
            curfigure->setAlgorithm(0);
            curfigure->DrawFigure(p,1);
        }
        else if(s[6]=="Bresenham"){
            curfigure->setAlgorithm(1);
            curfigure->DrawFigure(p,1);
        }
        figureBox.push_back(curfigure);
    }

    //drawPolygon id n algorithm x1 y1 x2 y2 … xn yn
    else if(s[0]=="drawPolygon"){
        curfigure=new class Polygon;
        curfigure->setColor(curColor);
        int id=stoi(s[1]);
        curfigure->setId(id);
        int size=s.size();
        for(int i=4;i<size-1;i=i+2){
            QPoint p1(stoi(s[i]),stoi(s[i+1]));
            curfigure->infoPoint.push_back(p1);
        }
        QPoint p1(stoi(s[size-2]),stoi(s[size-1]));
        curfigure->infoPoint.push_back(p1);
        QPainter p(CanvasPix);
        if(s[3]=="DDA"){
            curfigure->setAlgorithm(0);
            curfigure->DrawFigure(p,1);
        }
        else if(s[3]=="Bresenham"){
            curfigure->setAlgorithm(1);
            curfigure->DrawFigure(p,1);
        }
        figureBox.push_back(curfigure);

    }

    //drawEllipse id x y rx ry
    else if(s[0]=="drawEllipse"){
        curfigure=new class Ellipse;
        curfigure->setColor(curColor);
        int id=stoi(s[1]);
        curfigure->setId(id);
        QPoint p1(stoi(s[2]),stoi(s[3]));
        QPoint p2(stoi(s[2])+stoi(s[4]),stoi(s[3])+stoi(s[5]));
        curfigure->infoPoint.push_back(p1);
        curfigure->infoPoint.push_back(p2);
        QPainter p(CanvasPix);
        curfigure->DrawFigure(p,1);
        figureBox.push_back(curfigure);
    }

    //drawCurve id n algorithm x1 y1 x2 y2 … xn yn
    else if(s[0]=="drawCurve"){
        curfigure=new class Curve;
        curfigure->setColor(curColor);
        int id=stoi(s[1]);
        curfigure->setId(id);
        int size=s.size();
        for(int i=4;i<size-1;i=i+2){
            QPoint p1(stoi(s[i]),stoi(s[i+1]));
            curfigure->infoPoint.push_back(p1);
        }
        QPainter p(CanvasPix);
        if(s[3]=="Bezier"){
            curfigure->setAlgorithm(0);
            curfigure->DrawFigure(p,1);
        }
        else if(s[3]=="B-spline"){
            curfigure->setAlgorithm(1);
            curfigure->DrawFigure(p,1);
        }
        figureBox.push_back(curfigure);
    }
}

void Canvas::searchFigure(int id){
    int size=figureBox.size();
    for(int i=0;i<size;i++){
        if(figureBox[i]->getId()==id){
            curfigure=figureBox[i];
            break;
        }
    }
}

void Canvas::changeCmd(vector<string> s){

    searchFigure(stoi(s[1]));

    //translate id dx dy
    if(s[0]=="translate"){
        CanvasPix->fill(Qt::white);
        int dx=stoi(s[2]);
        int dy=stoi(s[3]);
        curfigure->translate(dx,dy);
        QPainter p(CanvasPix);
        for(int i=0;i<figureBox.size();i++){
            figureBox[i]->DrawFigure(p,1);
        }

    }

    //rotate id x y r
    else if(s[0]=="rotate"){
        CanvasPix->fill(Qt::white);
        int xc=stoi(s[2]);
        int yc=stoi(s[3]);
        int angle=stoi(s[4]);

        curfigure->rotate(angle*(-1),xc,yc);
        QPainter p(CanvasPix);
        for(int i=0;i<figureBox.size();i++){
            figureBox[i]->DrawFigure(p,1);
        }
    }

    //scale id x y s
    else if(s[0]=="scale"){
        CanvasPix->fill(Qt::white);
        int xc=stoi(s[2]);
        int yc=stoi(s[3]);
        double multi=stof(s[4]);

        curfigure->scale(multi,xc,yc);
        QPainter p(CanvasPix);
        for(int i=0;i<figureBox.size();i++){
            figureBox[i]->DrawFigure(p,1);
        }
    }

    //clip id x1 y1 x2 y2 algorithm
    else if(s[0]=="clip"){
        CanvasPix->fill(Qt::white);
        int xw1=stoi(s[2]);
        int yw1=stoi(s[3]);
        int xw2=stoi(s[4]);
        int yw2=stoi(s[5]);
        int alg=0;
        if(s[6]=="Cohen-Sutherland"){
            alg=0;
        }
        else if(s[6]=="Liang-Barsky"){
            alg=1;
        }
        curfigure->clip(xw1,yw1,xw2,yw2,alg);
        QPainter p(CanvasPix);
        for(int i=0;i<figureBox.size();i++){
            figureBox[i]->DrawFigure(p,1);
        }
    }
}
