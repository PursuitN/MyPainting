#ifndef CIRCLE_H
#define CIRCLE_H

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


class Circle:public AllFigure{

    /* 这是画正圆
     * 一个是圆心，一个是拉出的半径
     * 分别存放在infoPoint的0和1的位置上
     */

public:
    Circle();
    void DrawFigure(QPainter &painter,int whecmd) override;
    void DrawCircleCenter(QPainter &painter,QPoint begin,QPoint end);
    void DrawCircleBresenham(QPainter &painter,QPoint begin,QPoint end);
};

#endif // CIRCLE_H
