#include "qcustomgraphicseffect.h"

QCustomGraphicsEffect::QCustomGraphicsEffect(QObject *parent)
    : QGraphicsEffect(parent)
{

}

void QCustomGraphicsEffect::draw(QPainter *painter)
{
    QImage image;
    image = sourcePixmap().toImage();
    // Returns a copy of the image in the given format.
    image = image.convertToFormat(QImage::Format_Grayscale8);
    // Returns the number of bytes occupied by the image data.
    for(int i=0; i<image.byteCount(); i++)
        image.bits()[i] =
                image.bits()[i] < 100 ? 0 : 255;
    // Pixmap cannot be modified.
    painter->drawPixmap(0,0,QPixmap::fromImage(image));
}
