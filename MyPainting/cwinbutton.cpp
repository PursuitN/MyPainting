#include "cwinbutton.h"
#include <QDebug>

CWinButton::CWinButton(QWidget *pParent):QPushButton(pParent)
{
    m_nClickTimes =0;
    connect(&m_cTimer,SIGNAL(timeout()),this,SLOT(slotTimerTimeOut()));
    connect(this,SIGNAL(clicked(bool)),this,SLOT(clicked()));
}

void CWinButton::slotTimerTimeOut()
{
    qDebug()<<"CWinButton::slotTimerTimeOut"<<endl;
    m_cTimer.stop();
    if(1==m_nClickTimes){
        qDebug()<<"click event"<<endl;
        //TODO Click respond.
    }else if(2==m_nClickTimes){
        qDebug()<<"double click event"<<endl;
        //TODO Double click respond.
    }
    m_nClickTimes=0;
}

void CWinButton::clicked()
{
    //qDebug()<<"CWinButton::clicked"<<endl;
    m_nClickTimes++;
    m_cTimer.start(200);
}
