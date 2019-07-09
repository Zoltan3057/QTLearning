#ifndef CVPLUGININTERFACE_H
#define CVPLUGININTERFACE_H

#include <QObject>
#include <QString>
#include "opencv2/opencv.hpp"

class CvPluginInterface
{
public:
    virtual ~CvPluginInterface() {}
    virtual QString description() = 0;
    virtual void processImage(const cv::Mat &inputImage, cv::Mat &outputImage) = 0;
};

/**
 * This macro associates the given Identifier (a string literal)
 * to the interface class called ClassName. The Identifier must be unique.
 *
 * This macro is normally used right after the class definition for ClassName,
 * in a header file. See the Plug & Paint example for details.
 */

#define CVPLUGININTERFACE_IID "com.amin.cvplugininterface"
Q_DECLARE_INTERFACE(CvPluginInterface, CVPLUGININTERFACE_IID)

#endif // CVPLUGININTERFACE_H
