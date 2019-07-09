#ifndef MEDIAN_FILTER_PLUGIN_H
#define MEDIAN_FILTER_PLUGIN_H

#include "median_filter_plugin_global.h"

#include "cvplugininterface.h"

class MEDIAN_FILTER_PLUGINSHARED_EXPORT Median_filter_plugin: public QObject, public CvPluginInterface
{
    Q_OBJECT

    /**
     * Q_PLUGIN_METADATA:
     * This macro is being used to declare meta data that is part of a plugin that instantiates this object.
     * The macro needs to declare the IID of the interface implemented through the object,
     * and reference a file containing the meta data for the plugin.
     *
     * There should be exactly one occurrence of this macro in the source code for a Qt plugin.
    */
    Q_PLUGIN_METADATA(IID "com.amin.cvplugininterface")

    // Declare the interface
    Q_INTERFACES(CvPluginInterface)

public:
    Median_filter_plugin();
    ~Median_filter_plugin();
    QString description();
    void processImage(const cv::Mat &inputImage, cv::Mat &outputImage);
};

#endif // MEDIAN_FILTER_PLUGIN_H
