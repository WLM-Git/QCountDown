#ifndef DIALCLOCK_H
#define DIALCLOCK_H

#include <QWidget>

class DialClock : public QWidget
{
    Q_OBJECT
public:
    explicit DialClock(QWidget *parent = nullptr);
private:
    void paintEvent(QPaintEvent* event) override;
private:
    QPixmap m_dial;
    QPixmap m_needle;
    float m_rotateValue;
signals:
};

#endif // DIALCLOCK_H
