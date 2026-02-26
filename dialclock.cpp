#include "dialclock.h"
#include <QPainter>
#define DIALCLOCK_STARTX 75
#define DIALCLOCK_STARTY 188


DialClock::DialClock(QWidget *parent)
    : QWidget{parent}
{
    m_dial.load(":/pic/ImageResources/dial.png");
    m_needle.load(":/pic/ImageResources/needle.png");

    setGeometry(DIALCLOCK_STARTX,DIALCLOCK_STARTY,m_dial.width(),m_dial.height());
    setStyleSheet("background-color: rgba(0,0,0,0)");

    m_rotateValue = 0.0;
}

void DialClock::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    //设置渲染提示
    //抗锯齿：使得边缘平滑
    painter.setRenderHints(QPainter::Antialiasing,true);
    //平滑像素图变换：使得旋转后的指针边缘依然清晰
    painter.setRenderHints(QPainter::SmoothPixmapTransform,true);
    //绘制表盘背景
    painter.drawPixmap(rect(),m_dial);

    //保持painter状态
    painter.save();

    //设置坐标原点为表盘控件中心(移动垫板到画纸中心，QPainter的旋转只会绕着垫板原点)
    painter.translate(width()/2,height()/2);

    //设置绘制方向旋转（旋转垫板）
    painter.rotate(m_rotateValue);

    //绘制指针（实际上是以垫板作为参考进行绘制，-13，-78也是与垫板原点的相对位置。）
    painter.drawPixmap(-13,-78,m_needle);

    //恢复painter状态
    painter.restore();
}
