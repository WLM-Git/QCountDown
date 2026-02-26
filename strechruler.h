#ifndef STRECHRULER_H
#define STRECHRULER_H

#include <QWidget>
#include "rulerheader.h"

class StrechRuler : public QWidget
{
    Q_OBJECT
public:
    explicit StrechRuler(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent* event) override;
private:
    RulerHeader* m_rulerHeader;
    QPointF m_originalPosition;
    float m_currentPosY;
    float m_currentPosX;

signals:

private slots:
    void OnRulerHeadMove(float positY);
    void OnRulerHeadMoveDone(float positY);
};

#endif // STRECHRULER_H
