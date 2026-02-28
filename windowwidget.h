#ifndef WindowWidget_H
#define WindowWidget_H

#include <QWidget>
#include "dialclock.h"
#include <QPushButton>
#include "strechruler.h"
#include <QTimer>
#include <QLabel>

class WindowWidget : public QWidget
{
    Q_OBJECT
public:
    explicit WindowWidget(QWidget *parent = nullptr);
private:
    void paintEvent(QPaintEvent* event) override;
    void loadFrontWidgets();
    QString caculateFormatTimeWithSeconds(int);
    void OnPlayButtonClicked();
    void OnResetButtonClicked();
private:
    QPixmap m_bgPixMap;
    DialClock* m_pDialClock;
    StrechRuler* m_pStrechRuler;
    QPushButton* m_pResetButton;
    QPushButton* m_pPlayButton;
    QTimer* m_pCountDownTimer;
    QLabel* m_pTimeLabel;
    bool m_bTimerPlaying;
    int m_nRulerSettedSeconds;
signals:
private slots:
    void OnRulerStrechDone(float);
    void OnCountDownProcess();
};

#endif // WindowWidget_H
