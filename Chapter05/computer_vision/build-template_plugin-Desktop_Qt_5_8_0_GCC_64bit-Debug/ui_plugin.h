/********************************************************************************
** Form generated from reading UI file 'plugin.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLUGIN_H
#define UI_PLUGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PluginGui
{
public:
    QGridLayout *gridLayout;
    QLabel *label;

    void setupUi(QWidget *PluginGui)
    {
        if (PluginGui->objectName().isEmpty())
            PluginGui->setObjectName(QStringLiteral("PluginGui"));
        PluginGui->resize(319, 530);
        gridLayout = new QGridLayout(PluginGui);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(PluginGui);
        label->setObjectName(QStringLiteral("label"));
        label->setWordWrap(true);

        gridLayout->addWidget(label, 0, 0, 1, 1);


        retranslateUi(PluginGui);

        QMetaObject::connectSlotsByName(PluginGui);
    } // setupUi

    void retranslateUi(QWidget *PluginGui)
    {
        PluginGui->setWindowTitle(QApplication::translate("PluginGui", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("PluginGui", "<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; font-weight:600;\">This is a template plugin.</span></p><p align=\"center\"><span style=\" font-size:12pt; font-weight:600;\">It can be cloned and used to create new plugins.</span></p></body></html>", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PluginGui: public Ui_PluginGui {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLUGIN_H
