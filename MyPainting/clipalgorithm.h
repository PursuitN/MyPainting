#ifndef CLIPALGORITHM_H
#define CLIPALGORITHM_H

#include <QDialog>
#include<QAbstractButton>
#include<QMessageBox>

namespace Ui {
class ClipAlgorithm;
}


class ClipAlgorithm : public QDialog{
    Q_OBJECT

public:
    explicit ClipAlgorithm(QWidget *parent = nullptr);
    ~ClipAlgorithm();

private:
    Ui::ClipAlgorithm *ui;

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

signals:
    void sendClipAlgorithm(int algorithm);
};

#endif // CLIPALGORITHM_H
