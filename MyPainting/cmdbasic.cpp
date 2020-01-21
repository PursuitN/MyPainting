#include "cmdbasic.h"


cmdbasic::cmdbasic(){
}


void cmdbasic::resetCanvas(int width, int height){
    CanvasPix =new QPixmap(width,height);       //此QPixmap对象用来准备随时接收绘制的内容,大小为初始的大小
    CanvasPix->fill(Qt::white);                 //填充背景色为白色

    TempPix =new QPixmap(width,height);         //此QPixmap对象用来准备随时接收绘制的内容,大小为初始的大小
    TempPix->fill(Qt::white);

}

void cmdbasic::saveCanvas(QString name,QString path){
    QFile myfile(name);
    CanvasPix->save(&myfile,"PNG");
    //CanvasPix->save(path);
}
