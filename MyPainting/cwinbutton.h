#ifndef CWINBUTTON_H
#define CWINBUTTON_H

#include <QPushButton>
#include <QTimer>

class CWinButton : public QPushButton
{
    Q_OBJECT
public:
    explicit CWinButton(QWidget *pParent=nullptr);

private slots:
    void slotTimerTimeOut();
    void clicked();

private:
    int m_nClickTimes;
    QTimer m_cTimer;
};

#endif // CWINBUTTON_H
