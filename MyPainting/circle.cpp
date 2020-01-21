#include "circle.h"


Circle::Circle(){

}

void Circle::DrawFigure(QPainter &painter,int whecmd){

    /*是一个继承figure类的函数
     *这里是通过两点画圆
     */
    //qDebug()<<"DrawFigure:Circle"<<endl;

    if(infoPoint.empty()){
        return;
    }

    QPoint p1=infoPoint[0];
    QPoint p2=infoPoint[1];

    //暂时拿第一个点作为标志性点
    if(whecmd==0){
        drawPoint=infoPoint[0];
        QPen pen;
        pen.setColor(Qt::red);
        pen.setWidth(8);
        painter.setPen(pen);
        painter.drawPoint(drawPoint);
    }

    QPen thePen;
    thePen.setColor(figureColor);
    painter.setPen(thePen);

    if(algorithm=0){
        //qDebug()<<"DrawCircleCenter"<<endl;
        DrawCircleCenter(painter,p1,p2);
    }
    else{
        //qDebug()<<"DrawCircleBresenham"<<endl;
        DrawCircleBresenham(painter,p1,p2);
    }
}

void Circle::DrawCircleCenter(QPainter &painter,QPoint begin,QPoint end){

    double tmp=qPow(begin.x()-end.x(),2)+qPow(begin.y()-end.y(),2);
    double radius = qFloor(qSqrt(tmp));        //算出半径
    int dx = begin.x();    //圆心与原点在x轴的偏移
    int dy = begin.y();    //圆心与原点在y轴的偏移

    int x = 0,y= radius;    //第一个点
    double d =1-radius;       //变量d初始值
    double deltax=3;
    double deltay=5-radius-radius;


    while(x<=y){
        //绘制每个1/8个圆
        painter.drawPoint(x+dx,y+dy);
        painter.drawPoint(y+dx,x+dy);
        painter.drawPoint(-x+dx,y+dy);
        painter.drawPoint(y+dx,-x+dy);
        painter.drawPoint(x+dx,-y+dy);
        painter.drawPoint(-y+dx,x+dy);
        painter.drawPoint(-x+dx,-y+dy);
        painter.drawPoint(-y+dx,-x+dy);
        if(d<0){
            //参考自PPT
            d+=deltax;
            deltax+=2;
            deltay+=2;
            x++;
        }
        else{
           d+=deltay;
           deltax+=2;
           deltay+=4;
           x++;
           y--;
        }
    }
}

void Circle::DrawCircleBresenham(QPainter &painter,QPoint begin,QPoint end){

    double radius = qFloor(qSqrt(qPow(begin.x()-end.x(),2)+qPow(begin.y()-end.y(),2)));        //算出半径
    int dx = begin.x();    //圆心与原点在x轴的偏移
    int dy = begin.y();    //圆心与原点在y轴的偏移

    int x = 0,y= radius;    //第一个点
    double p = 3-2*radius;       //变量d初始值

    while(x<=y){
        //绘制每个1/8个圆
        painter.drawPoint(x+dx,y+dy);
        painter.drawPoint(y+dx,x+dy);
        painter.drawPoint(-x+dx,y+dy);
        painter.drawPoint(y+dx,-x+dy);
        painter.drawPoint(x+dx,-y+dy);
        painter.drawPoint(-y+dx,x+dy);
        painter.drawPoint(-x+dx,-y+dy);
        painter.drawPoint(-y+dx,-x+dy);
        if(p<0){
            //参考自PPT
            p=p+4*x+6;
            x++;
        }
        else{
            p=p+4*(x-y)+10;
            x++;
            y--;
        }
    }
}
