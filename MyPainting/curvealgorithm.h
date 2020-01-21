#ifndef CURVEALGORITHM_H
#define CURVEALGORITHM_H

#include<QDialog>
#include<QAbstractButton>
#include<QMessageBox>
#include<QDebug>

namespace Ui {
class CurveAlgorithm;
}

class CurveAlgorithm : public QDialog{
    Q_OBJECT

public:
    explicit CurveAlgorithm(QWidget *parent = nullptr);
    ~CurveAlgorithm();

private:
    Ui::CurveAlgorithm *ui;

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

signals:
    void sendCurveAlgorithm(int algorithm);
};

#endif // CURVEALGORITHM_H
