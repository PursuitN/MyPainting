#include "curve.h"

Curve::Curve(){

}

void Curve::DrawFigure(QPainter &painter, int whecmd){

    if(infoPoint.empty()){
        return;
    }

    //暂时拿第一个点作为标志性点
    if(whecmd==0){
        //qDebug()<<infoPoint.size()<<endl;
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

    //qDebug()<<algorithm<<endl;
    //没毛病，画其他的会带到
    if(algorithm==0){
        //qDebug()<<"DrawCurveBezier"<<endl;
        DrawCurveBezier(painter);
    }
    else{
        //qDebug()<<"DrawCurveBspline"<<endl;
        DrawCurveBspline(painter);
    }
}


void Curve::DrawCurveBezier(QPainter &painter){
    vector <QPointF> p;
    for(int i=0;i<infoPoint.size();i++){
        QPointF tmp(infoPoint[i].x(),infoPoint[i].y());
        p.push_back(tmp);
    }
     CurveBezier(painter,p);
}

void Curve::CurveBezier(QPainter &painter,vector<QPointF>p){
    // 当然可以选择直接套公式，但是那样计算很慢，下面选择用隐式递归来更快的计算
    int pointsnum=p.size();
    if(pointsnum==1){
        // 仅有一个点，就直接画这个点就好了
        painter.drawPoint(p[0]);
    }
    else if(pointsnum>1){
        // 如果将每个部分这么表示 a * (1 - t)^b * t^c * Pn;
        // 首先杨辉三角形计算 a 的值
        int *a=new int[pointsnum];
        a[0]=1;
        a[1]=1;
        for(int i=3;i<=pointsnum;i++){
            int *t=new int[i-1];
            for(int j=0;j<i-1;j++){
                t[j]=a[j];
            }
            a[0]=1;
            a[i-1]=1;
            for(int j=0;j<i-2;j++){
                a[j+1]=t[j]+t[j+1];
            }
        }
        //然后画出点 prec精度表示画多少个点
        int prec=pointsnum*200;
        for(int i=0;i<prec;i++){
            // 画prec个点
            double u=(double)i/(double)prec;
            double x=0;
            double y=0;
            for(int k=0;k<pointsnum;k++){
                // 每个点是p0+p1+p2按权重来的
                double pre=pow(1-u,pointsnum-k-1) * pow(u,k) * a[k];
                x+= pre* (p[k].x());
                y+= pre* (p[k].y());
            }
            painter.drawPoint(QPoint(x+0.5,y+0.5));
        }
    }
}

void Curve::CurveBezier2(QPainter &painter,vector<QPointF>p){
    // https://blog.csdn.net/syx1065001748/article/details/70313523
    // 这种方法是不断二分，画出足够多的点
    // 这里没用到
    int size=p.size();
    //qDebug()<<size;
    if(size<=1){
        return;
    }
    bool c1=(p[size-1].x()<p[0].x()+1);
    bool c2=(p[size-1].x()>p[0].x()-1);
    bool c3=(p[size-1].y()<p[0].y()+1);
    bool c4=(p[size-1].y()>p[0].y()-1);
    if(c1&&c2&&c3&&c4){
        painter.drawPoint(p[0].x(),p[0].y());
        return;
    }

    vector<QPointF> pnew;
    pnew.push_back(p[0]);
    for(int i=1;i<=size-1;i++){
        for(int j=0;j<=size-1-i;j++){
            p[j].setX((p[j].x()+p[j+1].x())/2);
            p[j].setY((p[j].y()+p[j+1].y())/2);
        }
        pnew.push_back(p[0]);
    }
   CurveBezier(painter,p);
   CurveBezier(painter,pnew);
}

void Curve::DrawCurveBspline(QPainter &painter){
     CurveBspline(painter,infoPoint);
}

double polynomial(int k,int d,double u){
    if(d==1){
        if( u>=(double)(k) && u<=(double)(k+1) ){
            return 1.0;
        }
        else{
            return 0.0;
        }
    }
    else{
        return (u-k)/(d-1)*polynomial(k,d-1,u)+(k+d-u)/(d-1)*polynomial(k+1,d-1,u);
    }
}

void Curve::CurveBspline(QPainter &painter,vector<QPoint> points){
    int degree=4;                   // degree为4，那么次数为d-1即3
    int pointnum=points.size();     // 控制点的数目s
    double u;                        // u和
    double du=0.001;                 // u的变化精度
    // u 范围是 [d-1,n+1]
    for(u=degree-1;u<=pointnum;u=u+du){
        QPointF toDraw(0.0,0.0);    //当前u对应的绘制点
        double bkd;
        for(int k=0;k<pointnum;k++){
            bkd=polynomial(k,degree,u);
            toDraw.setX(toDraw.x()+double(points[k].x())*bkd);
            toDraw.setY(toDraw.y()+double(points[k].y())*bkd);
        }
        painter.drawPoint(toDraw.x()+0.5,toDraw.y()+0.5);
    }
}

/*
void Curve::CurveBspline(QPainter &painter,vector<QPoint> points){

    //computerfgraphcis

    if(points.size()<2)
        return;

    vector<QPoint> ps = points;
    vector<QPoint> result;
    for(double delta = 0;delta<1;delta+=0.01)
    {
        for(int size = points.size()-1;size>0;size--)
        {
            for(int i=0;i<size;i++)
            {
                ps[i] += delta*(ps[i+1]-ps[i]);
            }
        }
        result.push_back(ps[0]);
    }
    for(int i=0;i<result.size()-1;i++)
    {
        painter.drawLine(result[i],result[i+1]);
    }
}
*/
