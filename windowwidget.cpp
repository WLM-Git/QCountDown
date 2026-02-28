#include "windowwidget.h"
#include <QScreen>
#include <QPainter>

#define TOOLBUTTON_WIDTH 75
#define TOOLBUTTON_HEIGHT 75

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

    m_pCountDownTimer = new QTimer(this);
    m_bTimerPlaying = false;
    connect(m_pCountDownTimer,&QTimer::timeout,this,&WindowWidget::OnCountDownProcess);
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

    connect(m_pStrechRuler,&StrechRuler::rulerStrechDoneSignal,this,&WindowWidget::OnRulerStrechDone);
    connect(m_pStrechRuler,&StrechRuler::rulerStrechMoveSignal,m_pDialClock,&DialClock::UpDateDialClockTime);

    QFont labelFont;
    labelFont.setFamily("PingFang TC");
    labelFont.setWeight(QFont::Light);
    labelFont.setPixelSize(35);


    m_pTimeLabel = new QLabel(this);
    m_pTimeLabel->setGeometry(138,525,160,60);
    m_pTimeLabel->setFont(labelFont);
    m_pTimeLabel->setStyleSheet("background:transparent;color:#d16b5d");
    m_pTimeLabel->setAlignment(Qt::AlignCenter);
    m_pTimeLabel->setText("00:00");

    m_pPlayButton = new QPushButton(this);
    m_pPlayButton->setGeometry(111,630,TOOLBUTTON_WIDTH,TOOLBUTTON_HEIGHT);
    m_pPlayButton->setIcon(QIcon(":/pic/ImageResources/play.png"));
    m_pPlayButton->setIconSize(QSize(TOOLBUTTON_WIDTH,TOOLBUTTON_HEIGHT));
    m_pPlayButton->setAutoFillBackground(true);
    m_pPlayButton->setFlat(true);
    m_pPlayButton->setStyleSheet(
        "QPushButton,QPushButton::hover,QPushButton::pressed"
        "{background: transparent;"
        "border:none"
        "}"
    );

    connect(m_pPlayButton,&QPushButton::clicked,this,&WindowWidget::OnPlayButtonClicked);

    m_pResetButton = new QPushButton(this);
    m_pResetButton->setGeometry(251,630,TOOLBUTTON_WIDTH,TOOLBUTTON_HEIGHT);
    m_pResetButton->setIcon(QIcon(":/pic/ImageResources/reset.png"));
    m_pResetButton->setIconSize(QSize(TOOLBUTTON_WIDTH,TOOLBUTTON_HEIGHT));
    m_pResetButton->setAutoFillBackground(true);
    m_pResetButton->setFlat(true);
    m_pResetButton->setStyleSheet(
        "QPushButton,QPushButton::hover,QPushButton::pressed"
        "{background: transparent;"
        "border:none"
        "}"
    );

    connect(m_pResetButton,&QPushButton::clicked,this,&WindowWidget::OnResetButtonClicked);
}

QString WindowWidget::caculateFormatTimeWithSeconds(int second)
{
    int TMinutes = second / 60;
    int TSeconds = second % 60;

    //将TMinutes、TSeconds转化为QString类型
    QString strMinutes;
    QString strSeconds;

    //如果数字个位数的话，在前补0
    if(TMinutes >= 0 && TMinutes < 10)
        strMinutes = QString("0%1").arg(TMinutes);
    else
        strMinutes = QString("%1").arg(TMinutes);

    if(TSeconds >= 0 && TSeconds < 10)
        strSeconds = QString("0%1").arg(TSeconds);
    else
        strSeconds = QString("%1").arg(TSeconds);

    QString formatTime = QString("%1:%2").arg(strMinutes, strSeconds);

    return formatTime;
}

void WindowWidget::OnPlayButtonClicked()
{
    if(m_bTimerPlaying)
    {
        m_bTimerPlaying = false;
        if(m_pCountDownTimer->isActive())
            m_pCountDownTimer->stop();
        m_pPlayButton->setIcon(QIcon(":/pic/ImageResources/play.png"));
    }
    else
    {
        m_bTimerPlaying = true;
        m_pCountDownTimer->start(1000);
        m_pPlayButton->setIcon(QIcon(":/pic/ImageResources/pause.png"));
    }
}

void WindowWidget::OnResetButtonClicked()
{
    m_nRulerSettedSeconds = 0;
    m_bTimerPlaying = false;
    if(m_pCountDownTimer->isActive())
        m_pCountDownTimer->stop();
    m_pPlayButton->setIcon(QIcon(":/pic/ImageResources/pause.png"));
    m_pTimeLabel->setText("00:00");
    m_pStrechRuler->setRulerReset();
    m_pDialClock->UpDateDialClockTime(0);

}

void WindowWidget::OnRulerStrechDone(float ratio)
{
    int seconds = 3600 * ratio;
    m_nRulerSettedSeconds = seconds;
    QString formatTime = caculateFormatTimeWithSeconds(seconds);
    m_pTimeLabel->setText(formatTime);
    m_pCountDownTimer->start(1000);
    m_bTimerPlaying = true;
    m_pDialClock->UpDateDialClockTime(ratio);
    m_pPlayButton->setIcon(QIcon(":/pic/ImageResources/pause.png"));
}

//定时器处理逻辑
void WindowWidget::OnCountDownProcess()
{
    if(m_nRulerSettedSeconds <= 0)
    {
        //停止定时器。
        m_bTimerPlaying = false;
        if(m_pCountDownTimer->isActive())
            m_pCountDownTimer->stop();
        m_pPlayButton->setIcon(QIcon(":/pic/ImageResources/pause.png"));
        m_pTimeLabel->setText("00:00");
    }
    else
    {
        //将其展示到m_pTimeLabel上
        QString formatTime = caculateFormatTimeWithSeconds(m_nRulerSettedSeconds);
        m_pTimeLabel->setText(formatTime);

        //更新伸缩条的高度
        float currentRatio =m_nRulerSettedSeconds / 3600.0;
        m_pStrechRuler->UpdateRuleHeight(currentRatio);
        m_nRulerSettedSeconds--;

        //更新表盘上的内容
        m_pDialClock->UpDateDialClockTime(currentRatio);
    }
}
