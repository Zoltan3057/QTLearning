/***********************************************************************
 *
 * Mario Anotated on   : 2019-07-09
 * Filename      : qenhancedgraphicsview.cpp
 * Function      : inherite class QGraphicsView
 *                 QMenu; QAction; QGraphicsItem; QMouseEvent
 *
 ************************************************************************/
#include "qenhancedgraphicsview.h"

QEnhancedGraphicsView::QEnhancedGraphicsView(QWidget *parent)
    : QGraphicsView(parent)
{
}

// The QWheelEvent class contains parameters that describe a wheel event.
void QEnhancedGraphicsView::wheelEvent(QWheelEvent *event)
{
    // Returns the wheel's orientation.
    if (event->orientation() == Qt::Vertical)
    {
        double angleDeltaY = event->angleDelta().y();
        double zoomFactor = qPow(1.0015, angleDeltaY);

        // Scales the current view transformation by (sx, sy).
        scale(zoomFactor, zoomFactor);

        if(angleDeltaY > 0)
        {
            // Scrolls the contents of the viewport to ensure that the scene coordinate pos, is centered in the view.
            this->centerOn(sceneMousePos);
            sceneMousePos = this->mapToScene(event->pos());
        }

        // This function does not cause an immediate repaint;
        // instead it schedules a paint event for processing when Qt returns to the main event loop.
        // This permits Qt to optimize for more speed and less flicker than a call to repaint() does.
        this->viewport()->update();

        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void QEnhancedGraphicsView::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
    {
        // The QMenu class provides a menu widget for use in menu bars, context menus, and other popup menus.
        QMenu menu;

        // The QAction class provides an abstract user interface action that can be inserted into widgets.
        QAction *clearAllAction = menu.addAction("Clear All");
        connect(clearAllAction,
                SIGNAL(triggered(bool)),
                this,
                SLOT(clearAll(bool)));

        QAction *clearSelectedAction = menu.addAction("Clear Selected");
        connect(clearSelectedAction,
                SIGNAL(triggered(bool)),
                this,
                SLOT(clearSelected(bool)));

        QAction *noEffectAction = menu.addAction("No Effect");
        connect(noEffectAction,
                SIGNAL(triggered(bool)),
                this,
                SLOT(noEffect(bool)));

        QAction *blurEffectAction = menu.addAction("Blur Effect");
        connect(blurEffectAction,
                SIGNAL(triggered(bool)),
                this,
                SLOT(blurEffect(bool)));

        QAction *dropShadEffectAction = menu.addAction("Drop Shadow Effect");
        connect(dropShadEffectAction,
                SIGNAL(triggered(bool)),
                this,
                SLOT(dropShadowEffect(bool)));

        QAction *colorizeEffectAction = menu.addAction("Colorize Effect");
        connect(colorizeEffectAction,
                SIGNAL(triggered(bool)),
                this,
                SLOT(colorizeEffect(bool)));

        QAction *customEffectAction = menu.addAction("Custom Effect");
        connect(customEffectAction,
                SIGNAL(triggered(bool)),
                this,
                SLOT(customEffect(bool)));

        menu.exec(event->globalPos());
        event->accept();
    }
    else
    {
        QGraphicsView::mousePressEvent(event);
    }
}

void QEnhancedGraphicsView::clearAll(bool)
{
    scene()->clear();
}

void QEnhancedGraphicsView::clearSelected(bool)
{
    while(scene()->selectedItems().count() > 0)
    {
        delete scene()->selectedItems().at(0);
        // Removes the item at index position i. i must be a valid index position in the list (i.e., 0 <= i < size()).
        scene()->selectedItems().removeAt(0);
    }
}

void QEnhancedGraphicsView::noEffect(bool)
{
    foreach(QGraphicsItem *item, scene()->selectedItems())
    {
        item->setGraphicsEffect(Q_NULLPTR);
    }
}

void QEnhancedGraphicsView::blurEffect(bool)
{
    foreach(QGraphicsItem *item, scene()->selectedItems())
    {
        item->setGraphicsEffect(new QGraphicsBlurEffect(this));
    }
}

void QEnhancedGraphicsView::dropShadowEffect(bool)
{
    foreach(QGraphicsItem *item, scene()->selectedItems())
    {
        item->setGraphicsEffect(new QGraphicsDropShadowEffect(this));
    }
}

void QEnhancedGraphicsView::colorizeEffect(bool)
{
    foreach(QGraphicsItem *item, scene()->selectedItems())
    {
        item->setGraphicsEffect(new QGraphicsColorizeEffect(this));
    }
}

void QEnhancedGraphicsView::customEffect(bool)
{
    foreach(QGraphicsItem *item, scene()->selectedItems())
    {
        item->setGraphicsEffect(new QCustomGraphicsEffect(this));
    }
}
