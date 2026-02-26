#include "windowwidget.h"
#include <QScreen>
#include <QPainter>

WindowWidget::WindowWidget(QWidget *parent)
    : QWidget{parent}
{
    // 1. 设置窗口标志：独立顶层窗口 | 无边框 | 可最小化
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
    //背景透明
    setAttribute(Qt::WA_TranslucentBackground);
    //设置背景图片
    m_bgPixMap.load(":/pic/ImageResources/background.png");

    //获取主屏幕对象
    QScreen* screen = QGuiApplication::primaryScreen();

    //获取屏幕的可用尺寸
    QRect screenGeometry = screen->availableGeometry();

    //计算widget居中
    int startX = (screenGeometry.width() - m_bgPixMap.width())/2;
    int startY = (screenGeometry.height() - m_bgPixMap.height())/2;

    //设置widget居中并设置其尺寸
    setGeometry(startX,startY,m_bgPixMap.width(),m_bgPixMap.height());

    loadFrontWidgets();
}

void WindowWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    painter.drawPixmap(rect(),m_bgPixMap);
}

void WindowWidget::loadFrontWidgets()
{
    m_pDialClock = new DialClock(this);
    m_pStrechRuler = new StrechRuler(this);

}
