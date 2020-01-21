#include "allfigure.h"

//#include<iostream>
//using namespace std;


int AllFigure::totalnum=0;

AllFigure::AllFigure(){ 
    /* .默认构造函数. */
    id=totalnum;
    totalnum++;
    figureColor=Qt::black;
}


void AllFigure::DrawFigure(QPainter &painter,int whecmd){
    //do nothing 理论上不会被调用
    qDebug()<<"virtualDrawFigure"<<endl;

}


int AllFigure::getNumber(){
    return totalnum;
}

void AllFigure::translate(int xc, int yc){
    int PointNum=infoPoint.size();
    for(int i=0;i<PointNum;i++){
        infoPoint[i].setX(infoPoint[i].x()+xc);
        infoPoint[i].setY(infoPoint[i].y()+yc);
    }
}

void AllFigure::rotate(int angle, double xc, double yc){
    double radian = qDegreesToRadians(double(angle-180));
    int PointNum=infoPoint.size();
    for(int i=0;i<PointNum;i++){
        double x=infoPoint[i].x();
        double y=infoPoint[i].y();
        infoPoint[i].setX(xc+(x-xc)*qCos(radian)-(y-yc)*qSin(radian)+0.5);
        infoPoint[i].setY(yc+(x-xc)*qSin(radian)+(y-yc)*qCos(radian)+0.5);
    }
}

void AllFigure::rotater(double radian, double xc, double yc){
    int PointNum=infoPoint.size();
    for(int i=0;i<PointNum;i++){
        double x=infoPoint[i].x();
        double y=infoPoint[i].y();
        infoPoint[i].setX(xc+(x-xc)*qCos(radian)-(y-yc)*qSin(radian)+0.5);
        infoPoint[i].setY(yc+(x-xc)*qSin(radian)+(y-yc)*qCos(radian)+0.5);
    }
}

void AllFigure::scale(double multi,double xc,double yc){
    int PointNum=infoPoint.size();
    for(int i=0;i<PointNum;i++){
        double x=infoPoint[i].x();
        double y=infoPoint[i].y();
        x=x*multi+xc*(1-multi);
        y=y*multi+yc*(1-multi);
        infoPoint[i].setX(x+0.5);
        infoPoint[i].setY(y+0.5);
    }
}


int ComputeOutCode(double xmin,double xmax,double ymin,double ymax,double x, double y){
    int code;
    code = 0;               // initialised as being 0 of clip window
    if (x < xmin)           // to the left of clip window
        code |= 1;
    else if (x > xmax)      // to the right of clip window
        code |= 2;
    if (y < ymin)           // below the clip window
        code |= 4;
    else if (y > ymax)      // above the clip window
        code |= 8;
    return code;
}

void AllFigure::clip(double xw1, double yw1, double xw2, double yw2, int alg){

    if(xw1>xw2)qSwap(xw1,xw2);
    if(yw1>yw2)qSwap(yw1,yw2);

    // Cohen-Sutherland算法
    if(alg==0){
        //qDebug()<<"Cohen-Sutherland"<<endl;
        double x1 = infoPoint[0].x();
        double y1 = infoPoint[0].y();
        double x2 = infoPoint[1].x();
        double y2 = infoPoint[1].y();

        int c1 = ComputeOutCode(xw1,xw2,yw1,yw2,x1, y1);
        int c2 = ComputeOutCode(xw1,xw2,yw1,yw2,x2, y2);
        bool saveall = false;

        while (true) {
            if (!(c1 | c2)) { //相或为0，接受并且退出循环
                saveall = true;
                break;
            }
            else if (c1 & c2) { // 相与为1，拒绝且退出循环
                infoPoint.clear();
                id=-1;
                saveall = false;
                break;
            }
            else {
                double x, y;

                //找出在界外的点
                int outcodeOut = c1 ? c1 : c2;

                // 找出和边界相交的点
                // 使用点斜式 y = y1 + slope * (x - x1), x = x1 + (1 / slope) * (y - y1)
                if (outcodeOut & 8) {           // point is above the clip rectangle
                  x = x1 + (x2 - x1) * (yw2 - y1) / (y2 - y1);
                  y = yw2;
                }
                else if (outcodeOut & 4) { // point is below the clip rectangle
                  x = x1 + (x2 - x1) * (yw1 - y1) / (y2 - y1);
                  y = yw1;
                }
                else if (outcodeOut & 2) {  // point is to the right of clip rectangle
                  y = y1 + (y2 - y1) * (xw2 - x1) / (x2 - x1);
                  x = xw2;
                }
                else if (outcodeOut & 1) {   // point is to the left of clip rectangle
                  y = y1 + (y2 - y1) * (xw1 - x1) / (x2 - x1);
                  x = xw1;
                }

                if (outcodeOut == c1) {
                  x1 = x;
                  y1 = y;
                  c1 = ComputeOutCode(xw1,xw2,yw1,yw2,x1, y1);
                }
                else {
                  x2 = x;
                  y2 = y;
                  c2 = ComputeOutCode(xw1,xw2,yw1,yw2,x2, y2);
                }
            }
        }
        if(saveall){
            QPoint newp1(x1+0.5,y1+0.5);
            infoPoint[0]=newp1;
            QPoint newp2(x2+0.5, y2+0.5);
            infoPoint[1]=newp2;
        }
    }

    // Liang-Barsky算法
    else if(alg==1){
        //qDebug()<<"Liang-Barsky"<<endl;
        //窗口
        double xmin = min(xw1,xw2);
        double ymin = min(yw1,yw2);
        double xmax = max(xw1,xw2);
        double ymax = max(yw1,yw2);

        //直线端点
        double x1 = infoPoint[0].x();
        double y1 = infoPoint[0].y();
        double x2 = infoPoint[1].x();
        double y2 = infoPoint[1].y();

        double dx = x2-x1;  //△x
        double dy = y2-y1;  //△y
        double p[4] = {-dx,dx,-dy,dy};
        double q[4] = {x1-xmin,xmax-x1,y1-ymin,ymax-y1};
        double u1 = 0;
        double u2 = 1;

        for(int i=0;i<4;i++){
             //p=0且q＜0时，线段被裁掉
            if(fabs(p[i])<1e-6){
                if(q[i]<0){
                   infoPoint.clear();
                   break;
                }
            }
            else{
                double r = q[i]/p[i];
                if(p[i]<0){
                    u1 = r>u1?r:u1; //u1取0和各个r值之中的最大值
                }else{
                    u2 = r<u2?r:u2; //u2取1和各个r值之中的最小值
                }

                //如果u1>u2，则线段完全落在裁剪窗口之外，应当被舍弃
                if(u1>u2){
                    id=-1;
                    infoPoint.clear();
                }
            }
            QPoint newp1(x1+int(u1*dx+0.5), y1+int(u1*dy+0.5));
            infoPoint[0]=newp1;
            QPoint newp2(x1+int(u2*dx+0.5), y1+int(u2*dy+0.5));
            infoPoint[1]=newp2;
        }
    }
}

void AllFigure::setColor(QColor color){
    figureColor=color;
}

void AllFigure::setId(int i){
    id=i;
}

void AllFigure::setAlgorithm(int type){
    algorithm=type;
}

int AllFigure::getId(){
    return id;
}
