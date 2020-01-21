#ifndef POLYGON_H
#define POLYGON_H

#include<QVector>
#include<QRectF>
#include<QMessageBox>
#include<QImage>
#include<QCursor>
#include<QtGlobal>
#include<QtMath>
#include<QPoint>
#include<QDebug>
#include<QPainter>
#include"allfigure.h"


class Polygon:public AllFigure{

    /* 这是画多边形
     * 每次点一个点，然后两点之间成线，拖着成线
     * 4边形实际存了5个点，最后俩个点一样
     * 最后按鼠标的右键，自动画出最后一条线
     */

public:
    Polygon();
    void DrawFigure(QPainter &painter,int whecmd) override;
    void DrawPolygonLineDDA(QPainter &painter,QPoint begin,QPoint end);    //点点画线，和直线一样
    void DrawPolygonLineBresenham(QPainter &painter,QPoint begin,QPoint end);    //点点画线，和直线一样
    //int getPoint();                                               //获得当前点的个数

private:
    //int pointNum;                                                 //记录多边形的点的个数

};

#endif // POLYGON_H
