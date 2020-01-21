#ifndef POLYGONALGORITHM_H
#define POLYGONALGORITHM_H

#include <QDialog>
#include<QAbstractButton>
#include<QMessageBox>

namespace Ui {
class PolygonAlgorithm;
}

class PolygonAlgorithm : public QDialog{
    Q_OBJECT

public:
    explicit PolygonAlgorithm(QWidget *parent = nullptr);
    ~PolygonAlgorithm();

private:
    Ui::PolygonAlgorithm *ui;

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

signals:
    void sendPolygonAlgorithm(int algorithm);

};

#endif // POLYGONALGORITHM_H
