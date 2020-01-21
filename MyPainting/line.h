#ifndef LINE_H
#define LINE_H

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
#include<QDebug>
#include"allfigure.h"

class Line:public AllFigure{

    /* 这是直线
     * 直线两个端点
     * 分别存放在infoPoint的0和1的位置上
     */

public:
    Line();
    void DrawFigure(QPainter &painter,int whecmd)  override;
    void DrawLineBresenham(QPainter &painter,QPoint begin,QPoint end);
    void DrawLineDDA(QPainter &painter,QPoint begin,QPoint end);
};

#endif // LINE_H
