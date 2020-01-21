#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiSubWindow>

#include<QtDebug>
#include<qmessagebox.h>

#include"canvas.h"
//#include<random>
#include<stdlib.h>
#include<vector>
#include"canvasset.h"
#include"linealgorithm.h"
#include"polygonalgorithm.h"
#include"curvealgorithm.h"
#include"clipalgorithm.h"

#include"cmdcontrol.h"

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow{
    Q_OBJECT


public:
    explicit MainWindow(QWidget *parent = nullptr,cmdcontrol *ctrl=nullptr);
    ~MainWindow();

    void initMdiArea();                                 //初始化子窗口
    unsigned int findWindow();                          //找到当前的窗口


public slots:
    void NewCanvas(int width,int height);               //用于窗体之间传递设置画布大小，新建画布
    void NewLine(int algorithm);                        //用于新画直线，并且传递直线的算法
    void NewPolygon(int algorithm);                     //用于新画多边形，并且传递多边形的算法
    void NewCurve(int algorithm);                       //用于新画曲线，并且传递曲线的算法
    void NewClip(int algorithm);                        //用于新裁剪，并且传递裁剪的算法

private:
    Ui::MainWindow *ui;

    vector<Canvas*> allCanvans;                         //放所有的画布
    unsigned int WindowIndex;                           //窗口序号
    QMap<QMdiSubWindow*,unsigned int> allWindow;        //用来找相应窗口的map

    int width;
    int height;                                         //存当前的width和height

private slots:
    void on_HelpVersion_triggered();                    //点击 “帮助/版本信息”
    void on_NewCanvas_triggered();                      //点击 “新建画布图标"
    void on_SaveCanvas_triggered();                     //点击 “保存画布”
    void on_CleanCanvas_triggered();                    //点击 “清空画布”

    void on_LinePaint_triggered();                      //点击 “画直线”图标
    void on_CirclePaint_triggered();                    //点击 “画圆”图标
    void on_EllipsePaint_triggered();                   //点击 “画椭圆”图标
    void on_PolygonPaint_triggered();                   //点击 “画多边形”图标
    void on_CurvePaint_triggered();                     //点击 “画曲线”图标

    void on_TranslateFigure_triggered();                //点击 “平移曲线”图标
    void on_RotateFigure_triggered();                   //点击 “旋转图元”图标
    void on_ScaleFigure_triggered();                    //点击 “缩放图元”图元
    void on_ClipFigure_triggered();                     //点击 “裁剪线段”图元

    void  on_SelectColor_triggered();                   //点击选择颜色
    void on_DeleteFigure_triggered();                   //点击删除图元图标
    void on_ChangePoint_triggered();                   //点击改变图元，改变选中点

    void on_NewCanvas2_triggered();                     //以下均为在文件中
    void on_SaveCanvas2_triggered();
    void on_CleanCanvas2_triggered();
    void on_LinePaint2_triggered();
    void on_CirclePaint2_triggered();
    void on_EllipsePaint2_triggered();
    void on_PolygonPaint2_triggered();
    void on_CurvePaint2_triggered();
    void on_TranslateFigure2_triggered();
    void on_RotateFigure2_triggered();
    void on_ScaleFigure2_triggered();
    void on_ClipFigure2_triggered();
    void on_SelectColor2_triggered();
    void on_DeleteFigure2_triggered();
    void on_ChangePoint2_triggered();




};


#endif // MAINWINDOW_H
