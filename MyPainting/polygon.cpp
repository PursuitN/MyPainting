#include "polygon.h"


Polygon::Polygon(){
    //pointNum=0;
}


void Polygon::DrawFigure(QPainter &painter,int whecmd){

    if(infoPoint.empty()){
        return;
    }

    //暂时拿第一个点作为标志性点
    if(whecmd==0){
        drawPoint=infoPoint[0];
        QPoint p1=infoPoint[0];
        QPen pen;
        pen.setColor(Qt::red);
        pen.setWidth(8);
        painter.setPen(pen);
        painter.drawPoint(drawPoint);
    }
    QPen thePen;
    thePen.setColor(figureColor);
    painter.setPen(thePen);

    int numAlready=infoPoint.size();
    QPoint last=infoPoint[numAlready-1];         //最后一个点
    QPoint lasttwo=infoPoint[numAlready-2];      //倒数第二个点

    //qDebug()<<"DrawPolygonLine"<<endl;

    if(algorithm==0){
        //qDebug()<<"DrawPolygonLineDDA"<<endl;
        if(last==lasttwo){
            // 点击右键了，最后两个点会相同；没点右键，令两个点相同，最后两个点也会相同

            for(int i=0;i<numAlready-2;i++){
                DrawPolygonLineDDA(painter,infoPoint[i],infoPoint[i+1]);
            }
            DrawPolygonLineDDA(painter,infoPoint[0],last);
        }
        else{

            for(int i=0;i<numAlready-1;i++){
                DrawPolygonLineDDA(painter,infoPoint[i],infoPoint[i+1]);
            }
            //DrawPolygonLine(painter,lasttwo,last);
        }
    }
    else{
        //qDebug()<<"DrawPolygonLineBresenham"<<endl;
        if(last==lasttwo){
            // 点击右键了，最后两个点会相同；没点右键，令两个点相同，最后两个点也会相同

            for(int i=0;i<numAlready-2;i++){
                DrawPolygonLineBresenham(painter,infoPoint[i],infoPoint[i+1]);
            }
            DrawPolygonLineBresenham(painter,infoPoint[0],last);
        }
        else{

            for(int i=0;i<numAlready-1;i++){
                DrawPolygonLineBresenham(painter,infoPoint[i],infoPoint[i+1]);
            }
            //DrawPolygonLine(painter,lasttwo,last);
        }
    }
}

void Polygon::DrawPolygonLineDDA(QPainter &painter,QPoint begin,QPoint end){
    //qDebug()<<"DrawPolygonLineDDA"<<endl;
    int x_b=begin.x();
    int y_b=begin.y();
    int x_e=end.x();
    int y_e=end.y();
    double delt_x=(x_e-x_b);
    double delt_y=(y_e-y_b);
    double x=x_b;
    double y=y_b;

    if(abs(delt_x)>abs(delt_y)){
        //斜率小于1
        double m=delt_y/delt_x;
        if(delt_x>0){
            //从左到右
            for(int i=0;i<=abs(delt_x);i++){
                painter.drawPoint((x+0.5),(y+0.5));
                x=x+1;
                y=y+m;
            }
        }
        else{
            //从右向左
            for(int i=0;i<=abs(delt_x);i++){
                painter.drawPoint((x+0.5),(y+0.5));
                x=x-1;
                y=y-m;
            }
        }
    }
    else{
        //斜率大于1
        double m=delt_x/delt_y;
        if(delt_y>0){
            //从下到上
            for(int i=0;i<=abs(delt_y);i++){
                painter.drawPoint((x+0.5),(y+0.5));
                x=x+m;
                y=y+1;
            }
        }
        else{
            //从上向下
            for(int i=0;i<=abs(delt_y);i++){
                painter.drawPoint((x+0.5),(y+0.5));
                x=x-m;
                y=y-1;
            }
        }
    }
}

void Polygon::DrawPolygonLineBresenham(QPainter &painter,QPoint begin,QPoint end){
    //qDebug()<<"DrawPolygonLineBresenham"<<endl;
    int x_b = begin.x();
    int y_b = begin.y();
    int x_e= end.x();
    int y_e= end.y();

    double delt_x=x_e-x_b;
    double delt_y=y_e-y_b;

    if(abs(delt_x)>abs(delt_y)){

        //斜率小于1

        if(x_b>=x_e){
            //将从右向左的改成从左向右
            qSwap(x_b,x_e);
            qSwap(y_b,y_e);
        }
        delt_x=x_e-x_b;
        delt_y=y_e-y_b;

        double x=x_b;
        double y=y_b;

        if(y_b<=y_e){

            //从下到上
            double p=2*delt_y-delt_x;

            for(int i=0;i<=delt_x;i++){
                painter.drawPoint(x,y);
                x++;
                if(p>=0){
                    y++;
                    p=p+2*(delt_y-delt_x);
                }
                else{
                    p=p+2*delt_y;
                }
            }

        }
        else{

            //从上到下

            double p=2*delt_y+delt_x;

            for(int i=0;i<=delt_x;i++){
                painter.drawPoint(x,y);
                x++;
                if(p<=0){
                    y--;
                    p=p+2*(delt_y+delt_x);
                }
                else{
                    p=p+2*delt_y;
                }
            }

        }


    }
    else{

        //斜率大于1

        if(y_b>=y_e){
            //将从上向下的改成从下向上
            qSwap(x_b,x_e);
            qSwap(y_b,y_e);
        }
        delt_x=x_e-x_b;
        delt_y=y_e-y_b;

        double x=x_b;
        double y=y_b;

        if(x_b<=x_e){

            //从左到右
            double p=2*delt_x-delt_y;

            for(int i=0;i<=delt_y;i++){
                painter.drawPoint(x,y);
                y++;
                if(p>=0){
                    x++;
                    p=p+2*(delt_x-delt_y);
                }
                else{
                    p=p+2*delt_x;
                }
            }

        }
        else{

            //从右到左

            double p=2*delt_x+delt_y;

            for(int i=0;i<=delt_y;i++){
                painter.drawPoint(x,y);
                y++;
                if(p<=0){
                    x--;
                    p=p+2*(delt_y+delt_x);
                }
                else{
                    p=p+2*delt_x;
                }
            }
        }
    }
}
