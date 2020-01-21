#ifndef ALLFIGURE_H
#define ALLFIGURE_H

#include<vector>
#include<QVector>
#include<QRectF>
#include<QMessageBox>
#include<QImage>
#include<QCursor>
#include<QtGlobal>
#include<QtMath>
#include<QDebug>
#include<QPainter>
#include <QColorDialog>

using namespace std;


class AllFigure{

    /* .AllFigure作为所有图形的父类，定义了画图等基础性功能. */

public:  
    AllFigure();
    vector<QPoint> infoPoint;                               //每个图形存在一些关键点，存储这些关键点，第一个可以用来选中
    QPoint drawPoint;                                       //用来存储每个点的控制点，用来移动等
    virtual void DrawFigure(QPainter &painter,int whecmd);  //虚函数

    void setColor(QColor color);                            //设置该图形的颜色
    void setId(int id);                                     //设置图形的id
    void setAlgorithm(int type);                            //0-dda 1-breseham

    int getNumber();                                        //获得当前图形的总数目，没什么用好像==
    int getId();                                            //获取id
    void translate(int xc,int yc);                          //平移，xy两个方向改变的量
    void rotate(int angle,double xc,double yc);                   //旋转，旋转度数（度数），旋转点
    void rotater(double radian,double xc,double yc);                   //旋转，旋转度数(弧度），旋转点
    void scale(double multi,double xc,double yc);                 //缩放，倍数，旋转点
    void clip(double xw1,double yw1,double xw2,double yw2,int alg);     //裁剪，矩形点，算法选择

protected:
    static int totalnum;                                    //总共生成的图形的数目
    int id;                                                 //每个图元都有一个id
    QColor figureColor;                                     //该图形的颜色
    int algorithm;                                          //该图形的算法

};


#endif // ALLFIGURE_H
