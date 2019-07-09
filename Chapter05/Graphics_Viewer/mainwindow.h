#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPixmap>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QFileInfo>
#include <QMessageBox>
#include <QDebug>

#include "qcustomgraphicseffect.h"

// Autocreated MainWindow Class
// class MainWindow: public Ui_MainWindow {};
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
    /**
     * @brief Read File Path
     * @param event
     */
    void dragEnterEvent(QDragEnterEvent *event);
    /**
     * @brief create QGraphicsPixmapItem On Scene
     * @param event
     */
    void dropEvent(QDropEvent *event);

private:
    Ui::MainWindow *ui;
    QGraphicsScene scene;

};

#endif // MAINWINDOW_H
