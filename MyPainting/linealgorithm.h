#ifndef LINEALGORITHM_H
#define LINEALGORITHM_H

#include<QDialog>
#include<QAbstractButton>
#include<QMessageBox>

namespace Ui {
class LineAlgorithm;
}


class LineAlgorithm : public QDialog{
    Q_OBJECT

    /* 点击画直线后，选择画直线的算法是dda还是Bresenham */

public:
    explicit LineAlgorithm(QWidget *parent = nullptr);
    ~LineAlgorithm();

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::LineAlgorithm *ui;


signals:
    void sendLineAlgorithm(int algorithm);


};

#endif // LINEALGORITHM_H
