/***********************************************************************
 *
 * Mario Anotated on   : 2019-07-09
 * Filename      : mainwindow.cpp
 * Function      : using QPixmap;
 *                 Define dragEnterEvent; dropEvent; resizeEvent
 *
 ************************************************************************/
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setAcceptDrops(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * QDragEnterEvent:
 * The QDragEnterEvent class provides an event which is sent to a widget
 * when a drag and drop action enters it.
 * A widget must accept this event in order to receive the drag move events
 * that are sent while the drag and drop action is in progress. The drag enter event is
 * always immediately followed by a drag move event.
 * QDragEnterEvent inherits most of its functionality from QDragMoveEvent,
 * which in turn inherits most of its functionality from QDropEvent.
 */
void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    QStringList acceptedFileTypes;
    acceptedFileTypes.append("jpg");
    acceptedFileTypes.append("png");
    acceptedFileTypes.append("bmp");

    // mimeData: Returns the data that was dropped on the widget
    //           and its associated MIME type information.
    // hasUrls:  Returns true if the object can return a list of urls;
    if (event->mimeData()->hasUrls() && event->mimeData()->urls().count() == 1)
    {
        QFileInfo file(event->mimeData()->urls().at(0).toLocalFile());
        if(acceptedFileTypes.contains(file.suffix().toLower()))
        {
            event->acceptProposedAction();
        }
    }
}

void MainWindow::dropEvent(QDropEvent *event)
{

    QFileInfo file(event->mimeData()->urls().at(0).toLocalFile());

    /**
     * Loads a pixmap from the file with the given fileName.
     * Returns true if the pixmap was successfully loaded; otherwise invalidates the pixmap and returns false.
     *
     * The loader attempts to read the pixmap using the specified format.
     * If the format is not specified (which is the default), the loader probes the file for a header to guess the file format.
     *
     * The file name can either refer to an actual file on disk or to one of the application's embedded resources.
     * See the Resource System overview for details on how to embed pixmaps and other resource files in the application's executable.
     * If the data needs to be modified to fit in a lower-resolution result (e.g. converting from 32-bit to 8-bit),
     * use the flags to control the conversion.
     */
    if(pixmap.load(file.absoluteFilePath()))
    {
        ui->label->setPixmap(pixmap.scaled(ui->label->size(),
                                           Qt::KeepAspectRatio,
                                           Qt::SmoothTransformation));
    }
    else
    {
        QMessageBox::critical(this,
                              tr("Error"),
                              tr("The image file cannot be read!"));
    }
}

/**
 * The QResizeEvent class contains event parameters for resize events.
 * Resize events are sent to widgets that have been resized.
 */
void MainWindow::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    if(!pixmap.isNull())
    {
        ui->label->setPixmap(pixmap.scaled(ui->label->width()-5,
                                           ui->label->height()-5,
                                           Qt::KeepAspectRatio,
                                           Qt::SmoothTransformation));
    }
}
