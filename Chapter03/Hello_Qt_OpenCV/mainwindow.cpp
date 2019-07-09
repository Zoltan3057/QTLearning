/***********************************************************************
 *
 * Mario Anotated on   : 2019-07-09
 * Filename      : mainwindow.cpp
 * Function      : Using QTranslator, QMenu, QAction,
 *                 Resources.qrc, sytlesheet
 *
 ************************************************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadSettings();

    /**
    * The QTranslator class provides internationalization support for text output.
    * An object of this class contains a set of translations from a source language to a target language.
    * QTranslator provides functions to look up translations in a translation file. Translation files are created using Qt Linguist.
    * The most common use of QTranslator is to:
    *   load a translation file,
    *   install it using QCoreApplication::installTranslator(),
    *   and use it via QObject::tr().
    */

    // TS file: Create by lupdate, extract every tr("") from sources;
    //          File::Open - Open it with language tools
    turkishTranslator = new QTranslator(this);
    turkishTranslator->load(":/translations/translation_tr.qm");

    germanTranslator = new QTranslator(this);
    germanTranslator->load(":/translations/translation_de.qm");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_inputPushButton_pressed()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Input Image"), QDir::currentPath(), tr("Images") + " (*.jpg *.png *.bmp)");
    if(QFile::exists(fileName))
    {
        ui->inputLineEdit->setText(fileName);
    }
}

void MainWindow::on_outputPushButton_pressed()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Select Output Image"), QDir::currentPath(), "*.jpg;;*.png;;*.bmp");
    if(!fileName.isEmpty())
    {
        ui->outputLineEdit->setText(fileName);
        using namespace cv;

        Mat inpImg, outImg;
        inpImg = imread(ui->inputLineEdit->text().toStdString());
        if(ui->medianBlurRadioButton->isChecked())
            cv::medianBlur(inpImg, outImg, 5);
        else if(ui->gaussianBlurRadioButton->isChecked())
            cv::GaussianBlur(inpImg, outImg, Size(5, 5), 1.25);
        imwrite(fileName.toStdString(), outImg);
        if(ui->displayImageCheckBox->isChecked())
            imshow(tr("Output Image").toStdString(), outImg);
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    int result = QMessageBox::warning(this, tr("Exit"), tr("Are you sure you want to close this program?"), QMessageBox::Yes, QMessageBox::No);
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

void MainWindow::loadSettings()
{
    QSettings settings("Packt", "Hello_OpenCV_Qt", this);
    ui->inputLineEdit->setText(settings.value("inputLineEdit", "").toString());
    ui->outputLineEdit->setText(settings.value("outputLineEdit", "").toString());
    ui->medianBlurRadioButton->setChecked(settings.value("medianBlurRadioButton", true).toBool());
    ui->gaussianBlurRadioButton->setChecked(settings.value("gaussianBlurRadioButton", false).toBool());
    ui->displayImageCheckBox->setChecked(settings.value("displayImageCheckBox", false).toBool());
}

void MainWindow::saveSettings()
{
    QSettings settings("Packt", "Hello_OpenCV_Qt", this);
    settings.setValue("inputLineEdit", ui->inputLineEdit->text());
    settings.setValue("outputLineEdit", ui->outputLineEdit->text());
    settings.setValue("medianBlurRadioButton", ui->medianBlurRadioButton->isChecked());
    settings.setValue("gaussianBlurRadioButton", ui->gaussianBlurRadioButton->isChecked());
    settings.setValue("displayImageCheckBox", ui->displayImageCheckBox->isChecked());
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


// Slots for QMenu - language
void MainWindow::on_actionTurkish_triggered()
{
    // A global pointer referring to the unique application object.
    // It is equivalent to QCoreApplication::instance(), but cast as a QApplication pointer,
    // so only valid when the unique application object is a QApplication.
    qApp->installTranslator(turkishTranslator);
}

void MainWindow::on_actionGerman_triggered()
{
    qApp->installTranslator(germanTranslator);
}

void MainWindow::on_actionEnglish_triggered()
{
    qApp->removeTranslator(turkishTranslator);
    qApp->removeTranslator(germanTranslator);
}
