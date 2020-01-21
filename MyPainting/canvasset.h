#ifndef CANVASSET_H
#define CANVASSET_H

#include <QDialog>
#include<QAbstractButton>
#include<QMessageBox>

#include<QObject>


namespace Ui {
class CanvasSet;
}

class CanvasSet : public QDialog{

    /*点击新建画布后，会出现的ui界面*/

    Q_OBJECT


public:
    explicit CanvasSet(QWidget *parent = nullptr);
    ~CanvasSet();

    int Width;                                              //画布的宽高
    int Height;


private slots:

    void on_buttonBox_clicked(QAbstractButton *button);     //点击“OK”后的槽


private:
    Ui::CanvasSet *ui;


signals:
    void sendCanvasInfo(int w,int h);                       //和mainwindow之间进行交流，传递画布宽高信息

};


#endif // CANVASSET_H
