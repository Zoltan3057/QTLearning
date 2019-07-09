#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QCloseEvent>
#include <QMessageBox>
#include <QDir>
#include <QFileInfoList>
#include <QDebug>
#include <QLabel>
#include <QGraphicsScene>
#include <QPushButton>
#include <QTranslator>
#include <QThread>
#include <QThreadPool>
#include <QMutex>

// The QLibrary class loads shared libraries at runtime.
#include <QLibrary>

// The QPluginLoader class loads a plugin at run-time.
// QPluginLoader provides access to a Qt plugin. A Qt plugin is stored in a shared library (a DLL)
// and offers these benefits over shared libraries accessed using QLibrary:
#include <QPluginLoader>

// The QFileDialog class provides a dialog that allow users to select files or directories.
// The QFileDialog class enables a user to traverse the file system in order to select one or many files or a directory.
#include <QFileDialog>

// The QGraphicsProxyWidget class provides a proxy layer for embedding a QWidget in a QGraphicsScene.
#include <QGraphicsProxyWidget>

// The QRunnable class is an interface for representing a task or piece of code that needs to be executed, represented by your reimplementation of the run() function.
#include <QRunnable>

// The QWaitCondition class provides a condition variable for synchronizing threads.
#include <QWaitCondition>

// OpenCV Inteface (customed)
#include "cvplugininterface.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event);
    void changeEvent(QEvent *event);

private slots:
    void onPluginActionTriggered(bool);
    void onLanguageActionTriggered(bool);
    void onThemeActionTriggered(bool);
    void onCurrentPluginUpdateNeeded();
    void onCurrentPluginErrorMessage(QString msg);
    void onCurrentPluginInfoMessage(QString msg);

    void on_actionAboutQt_triggered();

    void on_actionExit_triggered();

    void on_actionOpenImage_triggered();

    void on_viewOriginalCheck_toggled(bool checked);

    void on_actionSaveImage_triggered();

    void on_action_Camera_triggered();

private:
    Ui::MainWindow *ui;

    void loadSettings();
    void saveSettings();

    QString currentThemeFile;
    QString currentLanguageFile;
    QString currentPluginFile;

    /**
     * @brief   Load all plugins and populate the menus
     */
    void populatePluginsMenu();
    void populateLanguagesMenu();
    void populateThemesMenu();

    QPointer<QPluginLoader> currentPlugin;
    QPointer<QWidget> currentPluginGui;
    QGraphicsScene scene;
    // The QTranslator class provides internationalization support for text output.
    QTranslator translator;
    QGraphicsPixmapItem originalPixmap, processedPixmap;
    cv::Mat originalMat, processedMat;
    QImage originalImage, processedImage;

};

#endif // MAINWINDOW_H
