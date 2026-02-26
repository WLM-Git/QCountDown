#include "strechruler.h"
#include <QPainter>
#define RULERWIDGET_STARTX 351
#define RULERWIDGET_STARTY 100

#define RULERWIDGET_WIDTH 82
#define RULERWIDGET_HEIGH 574

#define RULER_MAX_HEIGHT 486

StrechRuler::StrechRuler(QWidget *parent)
    : QWidget{parent}
{
    setGeometry(RULERWIDGET_STARTX,RULERWIDGET_STARTY,RULERWIDGET_WIDTH,RULERWIDGET_HEIGH);
    m_rulerHeader = new RulerHeader(this);
    connect(m_rulerHeader,&RulerHeader::rulerHeaderMoveSignal,this,&StrechRuler::OnRulerHeadMove);
    connect(m_rulerHeader,&RulerHeader::rulerHeaderMoveDineSignal,this,&StrechRuler::OnRulerHeadMoveDone);
    m_originalPosition = m_rulerHeader->pos();

    m_currentPosX = m_originalPosition.x();
    m_currentPosY = m_originalPosition.y();
}

void StrechRuler::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.save();
    //由于要绘制绿色矩形区域，所以只用画刷即可
    painter.setPen(QPen(QColor(127,159,124),1));
    painter.setBrush(QColor(127,159,124));
    painter.drawRect(15,3,52,m_rulerHeader->pos().y());
    painter.restore();

    //画刻度
    float scale = RULER_MAX_HEIGHT / 60 + 0.1;
    float sScale = scale;
    float lScale = scale * 5;

    //要得到各种刻度的数量才能画出来
    //要知道如何画线段

    //得到矩形的高度
    float currentRulerHeight = m_rulerHeader->pos().y();

    int sScaleCount = currentRulerHeight / sScale + 1;      //短刻度数量
    int lScaleCount = currentRulerHeight / lScale + 1;      //长刻度数量

    painter.setPen(QPen(QColor(255,255,255),1));

    for(int i = 0; i < sScaleCount; i++)
    {
        if(i % 5 != 0)
        {
            painter.drawLine(QPoint(67-5, i * sScale),QPoint(67, i * sScale));
        }
    }

    for(int i = 0; i < lScaleCount; i++)
    {
        painter.drawLine(QPoint(67-10, i * lScale),QPoint(67, i * lScale));
    }
}

//接收相对位置的槽函数
void StrechRuler::OnRulerHeadMove(float positY)
{
    float realPosY = m_currentPosY + positY;
    if(realPosY<=0)
    {
        realPosY = 0;
    }
    else if(realPosY>=RULER_MAX_HEIGHT)
    {
        realPosY = RULER_MAX_HEIGHT;
    }

    m_rulerHeader->move(m_currentPosX,realPosY);

    repaint();
}

void StrechRuler::OnRulerHeadMoveDone(float positY)
{
    Q_UNUSED(positY);
    m_currentPosY = m_rulerHeader->pos().y();
    qDebug()<<m_currentPosY<<Qt::endl;
}
