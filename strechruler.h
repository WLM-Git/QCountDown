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
    void UpdateRuleHeight(float ratio);
    void setRulerReset();
private:
    RulerHeader* m_rulerHeader;
    QPointF m_originalPosition;
    float m_currentPosY;
    float m_currentPosX;

signals:
    void rulerStrechMoveSignal(float);
    void rulerStrechDoneSignal(float);

private slots:
    void OnRulerHeadMove(float positY);
    void OnRulerHeadMoveDone();
};

#endif // STRECHRULER_H
