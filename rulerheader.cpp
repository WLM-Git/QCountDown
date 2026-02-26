#include "rulerheader.h"
#include <QPainter>
#include <QMouseEvent>

RulerHeader::RulerHeader(QWidget *parent)
    : QWidget{parent}
{
    m_rulerHeader.load(":/pic/ImageResources/ruler_head.png");
    setGeometry(0,0,m_rulerHeader.width(),m_rulerHeader.height());

}

void RulerHeader::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.drawPixmap(rect(),m_rulerHeader);
}

void RulerHeader::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        last_mouse_position = event->globalPosition();
    }
}

void RulerHeader::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    emit rulerHeaderMoveDineSignal(last_mouse_position.x());
}

void RulerHeader::mouseMoveEvent(QMouseEvent *event)
{
    const QPointF position = event->globalPosition() - last_mouse_position;
    emit rulerHeaderMoveSignal(position.y());
}
