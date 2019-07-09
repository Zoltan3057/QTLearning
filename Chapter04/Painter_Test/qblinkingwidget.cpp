/***********************************************************************
 *
 * Mario Anotated on   : 2019-07-09
 * Filename      : qblinkingwidget.cpp
 * Function      : user defined QWidget, QPainter, QBrush
 *
 * 创建一个继承QWidget的新类
 * 重写它的paintEvent函数
 * 用QPainter类在控件上完成绘制操作
 * 向窗口添加QWidget（控件）
 * 将其提升到新创建的控件 promote to
 *
 ************************************************************************/
#include "qblinkingwidget.h"

QBlinkingWidget::QBlinkingWidget(QWidget *parent) : QWidget(parent)
{
    blink  = false;
    connect(&blinkTimer,
            SIGNAL(timeout()),
            this,
            SLOT(onBlink()));
    blinkTimer.start(500);
}

void QBlinkingWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    if(blink)
        painter.fillRect(this->rect(),
                         QBrush(Qt::red));
    else
        painter.fillRect(this->rect(),
                         QBrush(Qt::white));
}

void QBlinkingWidget::onBlink()
{
    blink = !blink;
    this->update();
}
