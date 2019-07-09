#ifndef FILTER_PLUGIN_GLOBAL_H
#define FILTER_PLUGIN_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(FILTER_PLUGIN_LIBRARY)
// This macro marks a symbol for shared library export (see Creating Shared Libraries).
#  define FILTER_PLUGINSHARED_EXPORT Q_DECL_EXPORT
#else
#  define FILTER_PLUGINSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // FILTER_PLUGIN_GLOBAL_H
