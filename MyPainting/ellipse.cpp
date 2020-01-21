#include "ellipse.h"


Ellipse::Ellipse(){

}


void Ellipse::DrawFigure(QPainter &painter,int whecmd){

    if(infoPoint.empty()){
        return;
    }

    /* 因为椭圆只有一种算法，alg没用 */

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

    DrawEllipse(&painter,p1,p2);
    /* p1是圆心 p2是椭圆的右下角，是一个矩形那种感觉*/

}



void DrawEllipsePoints(QPainter *painter,int xCenter, int yCenter, int x, int y){
     painter->drawPoint(xCenter + x, yCenter + y);
     painter->drawPoint(xCenter - x, yCenter + y);
     painter->drawPoint(xCenter + x, yCenter - y);
     painter->drawPoint(xCenter - x, yCenter - y);
}

void Ellipse::DrawEllipse(QPainter *painter, QPoint &begin, QPoint &end){

    double x_b=begin.x();          //椭圆中心点
    double y_b=begin.y();
    double rx=abs(end.x()-x_b);    //椭圆长短轴
    double ry=abs(end.y()-y_b);

    double rx_2=rx*rx;
    double ry_2=ry*ry;

    double x=0;
    double y=ry;
    DrawEllipsePoints(painter,x_b,y_b,x,y);                 //画第一个点

    double p=ry_2- rx_2*ry + rx_2/4;                        //决策点
    while (ry_2*x <= rx_2*y){

        // 切线斜率k<=1的区域

        if (p < 0){
            p += 2*ry_2*x +3*ry_2;
        }
        else{
            p += 2*ry_2*x - 2*rx_2*y + 2*rx_2+ 3*ry_2;
            y--;
        }
        x++;
        DrawEllipsePoints(painter,x_b, y_b, x, y);
    }

    p= ry_2*(x+1/2)*(x+1/2)+rx_2*(y-1)*(y-1)-rx_2*ry_2;     //决策点
    while (y >= 0){

        // 切线斜率k>1的区域，使用区域1中最后点(x0,y0)来计算区域2中参数初值

        if (p<= 0){
            p+= 2*ry_2*x - 2*rx_2*y + 2*ry_2 + 3*rx_2;
            x++;
        }
        else{
            p+= 3*rx_2 - 2*rx_2*y;
        }
        y--;
        DrawEllipsePoints(painter,x_b, y_b, x, y);
    }

}
