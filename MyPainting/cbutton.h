#ifndef CBUTTON_H
#define CBUTTON_H
#include <QPushButton>
#include <QTimer>

class CButton : public QPushButton
{
    Q_OBJECT
public:
    explicit CButton(QWidget *pParent);

private:
    void mousePressEvent(QMouseEvent *e);
    void mouseDoubleClickEvent(QMouseEvent *event);

private slots:
    void slotTimerTimeOut();
    void mouseClicked();

private:
    QTimer m_cTimer;
};

#endif // CBUTTON_H
