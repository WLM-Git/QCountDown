#ifndef RULERHEADER_H
#define RULERHEADER_H
#include "qwidget.h"
#include <QPixmap>
#include <QObject>

class RulerHeader : public QWidget
{
    Q_OBJECT
public:
    explicit RulerHeader(QWidget *parent = nullptr);
private:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

private:
    QPixmap m_rulerHeader;
    QPointF last_mouse_position;

signals:
    void rulerHeaderMoveSignal(float);
    void rulerHeaderMoveDineSignal();
};

#endif // RULERHEADER_H
