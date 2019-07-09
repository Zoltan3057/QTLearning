#include "mainwindow.h"
#include "ui_mainwindow.h"

// The QWidget class is the base class of all user interface objects.
// The QMainWindow class provides a main application window.
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setAcceptDrops(true);

    /**
      QGraphicsView Settings
      QGraphicsView visualizes the contents of a QGraphicsScene
      in a scrollable viewport. To create a scene with geometrical
      items, see QGraphicsScene's documentation.
    */
    ui->graphicsView->setAcceptDrops(false);

    // Sets the current scene to scene. If scene is already being viewed, this function does nothing.
    ui->graphicsView->setScene(&scene);

    // This property holds whether the view allows scene interaction.
    ui->graphicsView->setInteractive(true);

    // This property holds the behavior for dragging the mouse over the scene while the left mouse button is pressed.
    // A rubber band will appear. Dragging the mouse will set the rubber band geometry,
    // and all items covered by the rubber band are selected. This mode is disabled for non-interactive views.
    ui->graphicsView->setDragMode(QGraphicsView::RubberBandDrag);

    // This property holds the behavior for selecting items with a rubber band selection rectangle.
    ui->graphicsView->setRubberBandSelectionMode(Qt::IntersectsItemBoundingRect);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// The QDragEnterEvent class provides an event which is
// sent to a widget when a drag and drop action enters it.
void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    // The QStringList class provides a list of strings. QStringList inherits from QList<QString>.
    QStringList acceptedFileTypes;
    acceptedFileTypes.append("jpg");
    acceptedFileTypes.append("png");
    acceptedFileTypes.append("bmp");

    // QDropEvent::mimeData()
    // Returns the data that was dropped on the widget and its associated MIME type information.
    // Returns true if the object can return a list of urls; otherwise returns false. URLs correspond to the MIME type text/uri-list.
    if (event->mimeData()->hasUrls() &&
            event->mimeData()->urls().count() == 1)
    {
        // The QFileInfo class provides system-independent file information.
        // toLocalFile(): Returns the path of this URL formatted as a local file path. The path returned will use
        // forward slashes, even if it was originally created from one with backslashes.
        QFileInfo file(event->mimeData()->urls().at(0).toLocalFile());
        if(acceptedFileTypes.contains(file.suffix().toLower()))
        {
            // Sets the drop action to be the proposed action.
            event->acceptProposedAction();
        }
    }
}

/**
The QDropEvent class provides an event which is sent
when a drag and drop action is completed.

    pos(): Returns the position where the drop was made.
*/

void MainWindow::dropEvent(QDropEvent *event)
{
    /**
    The QPoint class defines a point in the plane
    using integer precision.
    QPoint p;

    p.setX(p.x() + 1);
    p += QPoint(1, 0);
    p.rx()++;
    */

    // mapFromParent(): Translates the parent widget coordinate pos to widget coordinates.
    QPoint viewPos = ui->graphicsView->mapFromParent(event->pos());

    // Returns the viewport coordinate point mapped to scene coordinates.
    QPointF sceneDropPos = ui->graphicsView->mapToScene(viewPos);

    QFileInfo file(event
                   ->mimeData()
                   ->urls()
                   .at(0)
                   .toLocalFile());

    // The QPixmap class is an off-screen image representation that can be used as a paint device.
    QPixmap pixmap;
    if(pixmap.load(file.absoluteFilePath()))
    {
        // The QGraphicsPixmapItem class provides a pixmap item that you can add to a QGraphicsScene.
        QGraphicsPixmapItem *item = new QGraphicsPixmapItem(pixmap);

        item->setPos(sceneDropPos);
        item->setFlag(QGraphicsItem::ItemIsSelectable);
        item->setFlag(QGraphicsItem::ItemIsMovable);
        // Sets the mouse buttons that this item accepts mouse events for.
        item->setAcceptedMouseButtons(Qt::LeftButton);
        // item->setGraphicsEffect(new QCustomGraphicsEffect(this));

        // qDebug() << scene.items().count()
        // scene.clear();
        // Returns the viewport coordinate point mapped to scene coordinates.
        scene.addItem(item);

        // Creates and adds a line item to the scene, and returns the item pointer.
        // The geometry of the line is defined by line, and its pen is initialized to pen.
        // A pen has a style(), width(), brush(), capStyle() and joinStyle().
        // enum Qt::BrushStyle
        // scene.addLine(-200, 200, 200, 200, QPen(QBrush(Qt::SolidPattern),5.0));
        // scene.addEllipse; addRect; addPolygon;

        // ui->graphicsView->resetTransform();
    }
    else
    {
        QMessageBox::critical(this,
                              tr("Error"),
                              tr("The image file cannot be read!"));
    }
}
