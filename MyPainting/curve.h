#ifndef CURVE_H
#define CURVE_H

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


class Curve:public AllFigure{

    /* 这是画曲线
     * 存各个点
     */

public:
    Curve();
    void DrawFigure(QPainter &painter,int whecmd) override;
    void DrawCurveBezier(QPainter &painter);                                        //用Bezier画出曲线
    void CurveBezier(QPainter &painter,vector<QPointF> p);
    void CurveBezier2(QPainter &painter,vector<QPointF> p);
    void DrawCurveBspline(QPainter &painter);                                        //用Bezier画出曲线
    void CurveBspline(QPainter &painter,vector<QPoint> p);
};

#endif // CURVE_H
