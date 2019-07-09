#include "mainwindow.h"
#include "ui_mainwindow.h"

#define PLUGINS_SUBFOLDER                   "/cvplugins/"
#define LANGUAGES_SUBFOLDER                 "/languages/"
#define THEMES_SUBFOLDER                    "/themes/"
#define FILE_ON_DISK_DYNAMIC_PROPERTY       "absolute_file_path"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    loadSettings(); // First thing's first, load settings

    populatePluginsMenu();
    populateLanguagesMenu();
    populateThemesMenu();

    ui->graphicsView->setScene(&scene);
    scene.addItem(&originalPixmap);
    scene.addItem(&processedPixmap);

    /**
     * This property holds how the viewport should update its contents.
     * QGraphicsView uses this property to decide how to update areas of the scene that have been reexposed or changed.
     * Usually you do not need to modify this property, but there are some cases where doing so can improve rendering performance.
     * See the ViewportUpdateMode documentation for specific details.
     * The default value is MinimalViewportUpdate,
     * where QGraphicsView will update as small an area of the viewport as possible when the contents change.
     */
    // FullViewportUpdate: This is the preferred update mode for viewports that do not support partial updates, such as QGLWidget,
    // and for viewports that need to disable scroll optimization.
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
}

MainWindow::~MainWindow()
{
    delete currentPlugin;
    delete ui;
}

void MainWindow::loadSettings()
{
    // The QSettings class provides persistent platform-independent application settings.
    QSettings settings("Packt", "Computer_Vision", this);
    currentThemeFile = settings.value("currentThemeFile", "").toString();
    currentLanguageFile = settings.value("currentLanguageFile", "").toString();
    currentPluginFile = settings.value("currentPluginFile", "").toString();
}

void MainWindow::saveSettings()
{
    QSettings settings("Packt", "Computer_Vision", this);
    settings.setValue("currentThemeFile", currentThemeFile);
    settings.setValue("currentLanguageFile", currentLanguageFile);
    settings.setValue("currentPluginFile", currentPluginFile);
}

void MainWindow::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
    }
    else
    {
        QMainWindow::changeEvent(event);
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    int result = QMessageBox::warning(this, tr("Exit"), tr("Are you sure you want to exit?"), QMessageBox::Yes, QMessageBox::No);
    if(result == QMessageBox::Yes)
    {
        saveSettings();
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void MainWindow::populatePluginsMenu()
{
    // qApp:    A global pointer referring to the unique application object.
    //          It is equivalent to QCoreApplication::instance(), but cast as a QApplication pointer, so only valid when the unique application object is a QApplication.
    QDir pluginsDir(qApp->applicationDirPath() + PLUGINS_SUBFOLDER);
    // entryInfoList() :    Returns a list of QFileInfo objects for all the files and directories in the directory,
    //                      ordered according to the name and attribute filters previously set with setNameFilters() and setFilter(),
    //                      and sorted according to the flags set with setSorting().
    // QDir::NoDotAndDotDot:Do not list the special entries "." and "..".
    QFileInfoList pluginFiles = pluginsDir.entryInfoList(QDir::NoDotAndDotDot | QDir::Files, QDir::Name);
    foreach(QFileInfo pluginFile, pluginFiles)
    {
        // QLibrary::isLibrary:     Returns true if fileName has a valid suffix for a loadable library;
        //                          otherwise returns false.
        if(QLibrary::isLibrary(pluginFile.absoluteFilePath()))
        {
            // The QPluginLoader class loads a plugin at run-time.
            QPluginLoader pluginLoader(pluginFile.absoluteFilePath(), this);
            if(CvPluginInterface *plugin = dynamic_cast<CvPluginInterface*>(pluginLoader.instance()))
            {
                QAction *pluginAction = ui->menu_Plugins->addAction(plugin->title());
                pluginAction->setProperty(FILE_ON_DISK_DYNAMIC_PROPERTY, pluginFile.absoluteFilePath());
                connect(pluginAction, SIGNAL(triggered(bool)), this, SLOT(onPluginActionTriggered(bool)));
                if(currentPluginFile == pluginFile.absoluteFilePath())
                {
                    pluginAction->trigger();
                }
            }
            else
            {
                QMessageBox::warning(this, tr("Warning"),
                                     QString(tr("Make sure %1 is a correct plugin for this application<br>"
                                                "and it's not in use by some other application!")).arg(pluginFile.fileName()));
            }
        }
        else
        {
            QMessageBox::warning(this, tr("Warning"),
                                 QString(tr("Make sure only plugins exist in %1 folder.<br>"
                                            "%2 is not a plugin."))
                                 .arg(PLUGINS_SUBFOLDER)
                                 .arg(pluginFile.fileName()));
        }
    }

    if(ui->menu_Plugins->actions().count() <= 0)
    {
        QMessageBox::critical(this, tr("No Plugins"), QString(tr("This application cannot work without plugins!"
                                                                 "<br>Make sure that %1 folder exists "
                                                                 "in the same folder as the application<br>and that "
                                                                 "there are some filter plugins inside it")).arg(PLUGINS_SUBFOLDER));
        this->setEnabled(false);
    }
}

void MainWindow::populateLanguagesMenu()
{
    QMenu *languagesMenu = new QMenu(this);
    // Add default (english) language
    QAction *defaultLanguageAction = languagesMenu->addAction("English - US");
    defaultLanguageAction->setProperty(FILE_ON_DISK_DYNAMIC_PROPERTY, "");
    connect(defaultLanguageAction, SIGNAL(triggered(bool)), this, SLOT(onLanguageActionTriggered(bool)));

    // Load all languages and populate the menus
    QDir languagesDir(qApp->applicationDirPath() + LANGUAGES_SUBFOLDER);
    QFileInfoList languageFiles = languagesDir.entryInfoList(QStringList() << "*.qm", QDir::NoDotAndDotDot | QDir::Files, QDir::Name);
    foreach(QFileInfo languageFile, languageFiles)
    {
        QAction *languageAction = languagesMenu->addAction(languageFile.baseName());
        languageAction->setProperty(FILE_ON_DISK_DYNAMIC_PROPERTY, languageFile.absoluteFilePath());
        connect(languageAction, SIGNAL(triggered(bool)), this, SLOT(onLanguageActionTriggered(bool)));

        if(currentLanguageFile == languageFile.absoluteFilePath())
        {
            languageAction->trigger();
        }
    }
    ui->actionLanguage->setMenu(languagesMenu);
}

void MainWindow::populateThemesMenu()
{
    QMenu *themesMenu = new QMenu(this);
    // Add default (native) theme
    QAction *defaultThemeAction = themesMenu->addAction("Default");
    defaultThemeAction->setProperty(FILE_ON_DISK_DYNAMIC_PROPERTY, "");
    connect(defaultThemeAction, SIGNAL(triggered(bool)), this, SLOT(onThemeActionTriggered(bool)));

    // Load all themes and populate the menus
    QDir themesDir(qApp->applicationDirPath() + THEMES_SUBFOLDER);
    QFileInfoList themeFiles = themesDir.entryInfoList(QStringList() << "*.thm", QDir::NoDotAndDotDot | QDir::Files, QDir::Name);
    foreach(QFileInfo themeFile, themeFiles)
    {
        QAction *themeAction = themesMenu->addAction(themeFile.baseName());
        themeAction->setProperty(FILE_ON_DISK_DYNAMIC_PROPERTY, themeFile.absoluteFilePath());
        connect(themeAction, SIGNAL(triggered(bool)), this, SLOT(onThemeActionTriggered(bool)));

        if(currentThemeFile == themeFile.absoluteFilePath())
        {
            themeAction->trigger();
        }
    }
    ui->actionTheme->setMenu(themesMenu);
}

void MainWindow::on_actionAboutQt_triggered()
{
    qApp->aboutQt();
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::onPluginActionTriggered(bool)
{
    // Delete Previous Plugin
    if(!currentPlugin.isNull())
    {
        delete currentPlugin;
        delete currentPluginGui;
    }

    // QObject::sender():
    //      Returns a pointer to the object that sent the signal, if called in a slot activated by a signal;
    //      otherwise it returns 0. The pointer is valid only during the execution of the slot that calls this function from this object's thread context.
    currentPluginFile = QObject::sender()->property(FILE_ON_DISK_DYNAMIC_PROPERTY).toString();

    currentPlugin = new QPluginLoader(currentPluginFile, this);

    // The QWidget class is the base class of all user interface objects.
    currentPluginGui = new QWidget(this);

    ui->pluginLayout->addWidget(currentPluginGui);

    CvPluginInterface *currentPluginInstance = dynamic_cast<CvPluginInterface*>(currentPlugin->instance());

    if(currentPluginInstance)
    {
        // ***************** Add plugin ui to the main pluginLayout *****************
        currentPluginInstance->setupUi(currentPluginGui);

        connect(currentPlugin->instance(), SIGNAL(updateNeeded()), this, SLOT(onCurrentPluginUpdateNeeded()));
        connect(currentPlugin->instance(), SIGNAL(infoMessage(QString)), this, SLOT(onCurrentPluginInfoMessage(QString)));
        connect(currentPlugin->instance(), SIGNAL(errorMessage(QString)), this, SLOT(onCurrentPluginErrorMessage(QString)));
    }
}

void MainWindow::onLanguageActionTriggered(bool)
{
    currentLanguageFile = QObject::sender()->property(FILE_ON_DISK_DYNAMIC_PROPERTY).toString();
    qApp->removeTranslator(&translator);
    if(!currentLanguageFile.isEmpty())
    {
        translator.load(currentLanguageFile);
        qApp->installTranslator(&translator);
        ui->retranslateUi(this);
    }
}

void MainWindow::onThemeActionTriggered(bool)
{
    currentThemeFile = QObject::sender()->property(FILE_ON_DISK_DYNAMIC_PROPERTY).toString();
    QFile themeFile(currentThemeFile);
    if(currentThemeFile.isEmpty())
    {
        qApp->setStyleSheet("");
    }
    else
    {
        themeFile.open(QFile::ReadOnly | QFile::Text);
        QString styleSheet = themeFile.readAll();
        // setStyleSheet
        qApp->setStyleSheet(styleSheet);
        themeFile.close();
    }
}

void MainWindow::on_actionOpenImage_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Input Image"),
                                                    QDir::currentPath(),
                                                    tr("Images") + " (*.jpg *.png *.bmp)");

    using namespace cv;
    originalMat = imread(fileName.toStdString());
    if(!originalMat.empty())
    {
        onCurrentPluginUpdateNeeded();
    }
    else if(!fileName.trimmed().isEmpty())
    {
        QMessageBox::critical(this,
                              tr("Error"),
                              tr("Make sure the image file exists "
                                 "and it is accessible!"));
    }
}

void MainWindow::on_viewOriginalCheck_toggled(bool checked)
{
    originalPixmap.setVisible(checked);
    processedPixmap.setVisible(!checked);
}

void MainWindow::onCurrentPluginUpdateNeeded()
{
    if(!originalMat.empty())
    {
        if(!currentPlugin.isNull())
        {
            CvPluginInterface *currentPluginInstance = dynamic_cast<CvPluginInterface*>(currentPlugin->instance());
            if(currentPluginInstance)
            {
                //cv::TickMeter meter;
                //meter.start();
                currentPluginInstance->processImage(originalMat, processedMat);
                //meter.stop();
                //qDebug() << "The process took " << meter.getTimeMilli() << "milliseconds";
            }
        }
        else
        {
            processedMat = originalMat.clone();
        }

        originalImage = QImage(originalMat.data, originalMat.cols, originalMat.rows, originalMat.step, QImage::Format_RGB888);
        originalPixmap.setPixmap(QPixmap::fromImage(originalImage.rgbSwapped()));

        processedImage = QImage(processedMat.data, processedMat.cols, processedMat.rows, processedMat.step, QImage::Format_RGB888);
        processedPixmap.setPixmap(QPixmap::fromImage(processedImage.rgbSwapped()));
    }
}

void MainWindow::on_actionSaveImage_triggered()
{
    if(!ui->viewOriginalCheck->isChecked() && !processedMat.empty())
    {
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save Image"), QDir::currentPath(), "*.jpg;;*.png;;*.bmp");
        if(!fileName.isEmpty())
        {
            cv::imwrite(fileName.toStdString(), processedMat);
        }
    }
    else if(ui->viewOriginalCheck->isChecked() && !originalMat.empty())
    {
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save Image"), QDir::currentPath(), "*.jpg;;*.png;;*.bmp");
        if(!fileName.isEmpty())
        {
            cv::imwrite(fileName.toStdString(), originalMat);
        }
    }
    else
    {
        QMessageBox::warning(this, tr("Warning"), tr("There is nothing to be saved!"));
    }
}

void MainWindow::onCurrentPluginErrorMessage(QString msg)
{
    qDebug() << "Plugin Error Message : " << msg;
}

void MainWindow::onCurrentPluginInfoMessage(QString msg)
{
    qDebug() << "Plugin Info Message : " << msg;
}

void MainWindow::on_action_Camera_triggered()
{

}
