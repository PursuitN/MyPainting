#ifndef ELLIPSE_H
#define ELLIPSE_H

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


class Ellipse:public AllFigure{

    /* 这是画椭圆
     * 一个中心，一个矩形的右下角
     * 分别存放在infoPoint的0和1的位置上
     */

public:
    Ellipse();
    void DrawFigure(QPainter &painter,int whecmd) override;
    void DrawEllipse(QPainter *painter, QPoint &begin, QPoint &end);
};

#endif // ELLIPSE_H
