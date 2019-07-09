#ifndef QCUSTOMGRAPHICSEFFECT_H
#define QCUSTOMGRAPHICSEFFECT_H

#include <QObject>
#include <QGraphicsEffect>
#include <QPainter>

// Threshhold GraphicsEffect;
/**
 * The QGraphicsEffect class is the base class for all graphics effects.
 * Effects alter the appearance of elements by hooking into the rendering pipeline and operating
 * between the source (e.g., a QGraphicsPixmapItem) and the destination device
 * (e.g., QGraphicsView's viewport). Effects can be disabled by calling setEnabled(false).
 * If effects are disabled, the source is rendered directly.
 *  QGraphicsBlurEffect - blurs the item by a given radius
 *  QGraphicsDropShadowEffect - renders a dropshadow behind the item
 *  QGraphicsColorizeEffect - renders the item in shades of any given color
 *  QGraphicsOpacityEffect - renders the item with an opacity
 */
class QCustomGraphicsEffect : public QGraphicsEffect
{
    Q_OBJECT
public:
    explicit QCustomGraphicsEffect(QObject *parent = nullptr);

protected:
    void draw(QPainter *painter);

signals:

public slots:
};

#endif // QCUSTOMGRAPHICSEFFECT_H
