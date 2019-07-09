/****************************************************************************
** Meta object code from reading C++ file 'template_plugin.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../template_plugin/template_plugin.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/qplugin.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'template_plugin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Template_Plugin_t {
    QByteArrayData data[6];
    char stringdata0[59];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Template_Plugin_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Template_Plugin_t qt_meta_stringdata_Template_Plugin = {
    {
QT_MOC_LITERAL(0, 0, 15), // "Template_Plugin"
QT_MOC_LITERAL(1, 16, 12), // "updateNeeded"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 12), // "errorMessage"
QT_MOC_LITERAL(4, 43, 3), // "msg"
QT_MOC_LITERAL(5, 47, 11) // "infoMessage"

    },
    "Template_Plugin\0updateNeeded\0\0"
    "errorMessage\0msg\0infoMessage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Template_Plugin[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,
       3,    1,   30,    2, 0x06 /* Public */,
       5,    1,   33,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::QString,    4,

       0        // eod
};

void Template_Plugin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Template_Plugin *_t = static_cast<Template_Plugin *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateNeeded(); break;
        case 1: _t->errorMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->infoMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Template_Plugin::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Template_Plugin::updateNeeded)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Template_Plugin::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Template_Plugin::errorMessage)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (Template_Plugin::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Template_Plugin::infoMessage)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject Template_Plugin::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Template_Plugin.data,
      qt_meta_data_Template_Plugin,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Template_Plugin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Template_Plugin::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Template_Plugin.stringdata0))
        return static_cast<void*>(const_cast< Template_Plugin*>(this));
    if (!strcmp(_clname, "CvPluginInterface"))
        return static_cast< CvPluginInterface*>(const_cast< Template_Plugin*>(this));
    if (!strcmp(_clname, "com.computervision.cvplugininterface"))
        return static_cast< CvPluginInterface*>(const_cast< Template_Plugin*>(this));
    return QObject::qt_metacast(_clname);
}

int Template_Plugin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void Template_Plugin::updateNeeded()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void Template_Plugin::errorMessage(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Template_Plugin::infoMessage(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

QT_PLUGIN_METADATA_SECTION const uint qt_section_alignment_dummy = 42;

#ifdef QT_NO_DEBUG

QT_PLUGIN_METADATA_SECTION
static const unsigned char qt_pluginMetaData[] = {
    'Q', 'T', 'M', 'E', 'T', 'A', 'D', 'A', 'T', 'A', ' ', ' ',
    'q',  'b',  'j',  's',  0x01, 0x00, 0x00, 0x00,
    0xb0, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x00, 0x00,
    0x9c, 0x00, 0x00, 0x00, 0x1b, 0x03, 0x00, 0x00,
    0x03, 0x00, 'I',  'I',  'D',  0x00, 0x00, 0x00,
    '$',  0x00, 'c',  'o',  'm',  '.',  'c',  'o', 
    'm',  'p',  'u',  't',  'e',  'r',  'v',  'i', 
    's',  'i',  'o',  'n',  '.',  'c',  'v',  'p', 
    'l',  'u',  'g',  'i',  'n',  'i',  'n',  't', 
    'e',  'r',  'f',  'a',  'c',  'e',  0x00, 0x00,
    0x1b, 0x0a, 0x00, 0x00, 0x09, 0x00, 'c',  'l', 
    'a',  's',  's',  'N',  'a',  'm',  'e',  0x00,
    0x0f, 0x00, 'T',  'e',  'm',  'p',  'l',  'a', 
    't',  'e',  '_',  'P',  'l',  'u',  'g',  'i', 
    'n',  0x00, 0x00, 0x00, 0x1a, 0x00, 0xa1, 0x00,
    0x07, 0x00, 'v',  'e',  'r',  's',  'i',  'o', 
    'n',  0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00,
    0x05, 0x00, 'd',  'e',  'b',  'u',  'g',  0x00,
    0x15, 0x12, 0x00, 0x00, 0x08, 0x00, 'M',  'e', 
    't',  'a',  'D',  'a',  't',  'a',  0x00, 0x00,
    0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00,
    0x80, 0x00, 0x00, 0x00, '@',  0x00, 0x00, 0x00,
    't',  0x00, 0x00, 0x00, 'd',  0x00, 0x00, 0x00
};

#else // QT_NO_DEBUG

QT_PLUGIN_METADATA_SECTION
static const unsigned char qt_pluginMetaData[] = {
    'Q', 'T', 'M', 'E', 'T', 'A', 'D', 'A', 'T', 'A', ' ', ' ',
    'q',  'b',  'j',  's',  0x01, 0x00, 0x00, 0x00,
    0xb0, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x00, 0x00,
    0x9c, 0x00, 0x00, 0x00, 0x1b, 0x03, 0x00, 0x00,
    0x03, 0x00, 'I',  'I',  'D',  0x00, 0x00, 0x00,
    '$',  0x00, 'c',  'o',  'm',  '.',  'c',  'o', 
    'm',  'p',  'u',  't',  'e',  'r',  'v',  'i', 
    's',  'i',  'o',  'n',  '.',  'c',  'v',  'p', 
    'l',  'u',  'g',  'i',  'n',  'i',  'n',  't', 
    'e',  'r',  'f',  'a',  'c',  'e',  0x00, 0x00,
    0x15, 0x0a, 0x00, 0x00, 0x08, 0x00, 'M',  'e', 
    't',  'a',  'D',  'a',  't',  'a',  0x00, 0x00,
    0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x9b, 0x0d, 0x00, 0x00,
    0x09, 0x00, 'c',  'l',  'a',  's',  's',  'N', 
    'a',  'm',  'e',  0x00, 0x0f, 0x00, 'T',  'e', 
    'm',  'p',  'l',  'a',  't',  'e',  '_',  'P', 
    'l',  'u',  'g',  'i',  'n',  0x00, 0x00, 0x00,
    '1',  0x00, 0x00, 0x00, 0x05, 0x00, 'd',  'e', 
    'b',  'u',  'g',  0x00, 0x1a, 0x00, 0xa1, 0x00,
    0x07, 0x00, 'v',  'e',  'r',  's',  'i',  'o', 
    'n',  0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00,
    '@',  0x00, 0x00, 0x00, '\\', 0x00, 0x00, 0x00,
    0x80, 0x00, 0x00, 0x00, 0x8c, 0x00, 0x00, 0x00
};
#endif // QT_NO_DEBUG

QT_MOC_EXPORT_PLUGIN(Template_Plugin, Template_Plugin)

QT_WARNING_POP
QT_END_MOC_NAMESPACE
