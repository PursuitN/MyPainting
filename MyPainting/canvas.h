#ifndef CANVAS_H
#define CANVAS_H

#include<QPixmap>
#include<QtWidgets>
#include<QWidget>
#include<QOpenGLWidget>
#include<QOpenGLFunctions>
#include<QPaintEvent>
#include<QResizeEvent>

#include<QMouseEvent>
#include<QPushButton>
#include<QPainter>
#include<QFileDialog>
#include<QPoint>
#include<QtDebug>
#include <QColorDialog>

#include<stdlib.h>
#include<vector>
using namespace std;
#include"allfigure.h"
#include"line.h"
#include"circle.h"
#include"ellipse.h"
#include"polygon.h"
#include"curve.h"


class Canvas:public QOpenGLWidget, protected QOpenGLFunctions{

    /* 用于画布的布置 */

    Q_OBJECT

public:
    Canvas(QWidget *parent= nullptr,int width=100,int height=100);      //这里的width和height用来限制画布的大小
    //~Canvas();
    void paintEvent(QPaintEvent *event) override;                       //每次updata自动调用的函数
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;           //鼠标点击
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;            //鼠标移动
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;         //鼠标释放
    void mouseDoubleClickEvent(QMouseEvent *event)Q_DECL_OVERRIDE;      //鼠标双击

    void setFigure(int setmode);                                        //设置画的图元类型
    void setMode(int setmode);                                          //设置移动图元的类型
    void canvasSave();                                                  //保存画布为文件
    void canvasClean();                                                 //清空画布

    int figurePos(QPoint p);                                            //给出点p，找出p属于哪个图形的关键点
    void pointPos(QPoint p);                                                     //给出图形，找出p属于cur图形的哪个关键点

    void setColor(QColor color);                                        //设置当前画布的颜色
    void setAlgorithm(int alg);                                         //设置当前的算法

    void canvasSaveCmd(QString path,QString name);                      //cmd保存画布
    void drawCmd(vector<string> s);                                     //画出图形1直线，2多边形，3,椭圆，4曲线
    void searchFigure(int id);                                          //给定id寻找相应的图元
    void changeCmd(vector<string> s);                                   //图形变换

protected:
    virtual void initializeGL()Q_DECL_OVERRIDE;                         //以下的三个函数是QGLWidget类的initializeGL()、paintGL()和resizeGL()
    virtual void paintGL() Q_DECL_OVERRIDE;
    virtual void resizeGL(int w, int h) Q_DECL_OVERRIDE;


private:
    QOpenGLFunctions *openFunc;         //为了GL的三个函数
    QPixmap *CanvasPix;                 //画布设置♣
    QPixmap *TempPix;                   //用于缓冲的备用
    vector<AllFigure*> figureBox;       //存储该画布上所有的图元♣

    vector<QPoint> points;              //存点，旋转中心0，原图形中心1
    vector<QPoint> infotmp;             //暂时用来存点的,因为要获取图原来的点，就将全部infopoint暂时存在这里

    AllFigure *curfigure;               //当前在画的图元♣

    int drawFigure;                     //表示当前图元，0表示初始，1表示直线，2表示圆，3表示椭圆，4表示多边形，5表示曲线
    int drawState;                      //表示当前状态，0表示默认，1表示正在拖拉,2表示多边形还没有画完
    int changeState;                    //0表示在画图，1平移,2表示现在啥都没干比如选算法,3旋转,4缩放,5裁剪,6删除,7改变点
    int changeIndex;                    //正在被修改的图形的位置，来自int figurePos(QPoint p);
    QColor curColor;                    //当前的画笔颜色♣

    int algorithm;                      //用于不同的算法，0是默认（DDA），1是（Bresenham）
    int add;                            //0默认；1表示是双击，要清楚因为单击带来的失误

    QPoint *tmpPoint;                    //当前修改的点
};


#endif // CANVAS_H
