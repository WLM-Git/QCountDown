#ifndef WindowWidget_H
#define WindowWidget_H

#include <QWidget>
#include "dialclock.h"
#include "strechruler.h"

class WindowWidget : public QWidget
{
    Q_OBJECT
public:
    explicit WindowWidget(QWidget *parent = nullptr);
private:
    void paintEvent(QPaintEvent* event) override;
    void loadFrontWidgets();
private:
    QPixmap m_bgPixMap;
    DialClock* m_pDialClock;
    StrechRuler* m_pStrechRuler;
signals:
};

#endif // WindowWidget_H
