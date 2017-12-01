#include "mainwindow.h"
#include "xygraphicsview.h"
#include "xygraphicsscene.h"
#include "xycanvasgraphicsitem.h"
#include "xyrectgraphicsitem.h"
#include "xypathgraphicsitem.h"
#include "xyellipsegraphicsitem.h"

#include <QToolBar>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    scene = new XYGraphicsScene(0, 0, 700, 500);
    view = new XYGraphicsView(scene);
    canvas = new XYCanvasGraphicsItem;

    view->scene()->setBackgroundBrush(QPixmap(":/backimage.jpg"));

    setCentralWidget(view);

    initToolBar();
}

MainWindow::~MainWindow()
{

}

void MainWindow::setShape(QAction *act)
{
    if (act)
    {
        scene->setItemMovable(false);
        if (act->text() == "Rect")
        {
            scene->setShape(XYGraphicsScene::RECT);
        }
        else if (act->text() == "Path")
        {
            scene->setShape(XYGraphicsScene::PATH);
        }
        else if (act->text() == "Ellipse")
        {
            scene->setShape(XYGraphicsScene::ELLIPSE);
        }
        else if (act->text() == "Line")
        {
            scene->setShape(XYGraphicsScene::LINE);
        }
        else if (act->text() == "Arrows")
        {
            scene->setShape(XYGraphicsScene::ARROWS);
        }
        else if (act->text() == "Text")
        {
            scene->setShape(XYGraphicsScene::TEXT);
        }
        else if (act->text() == "Cursor")
        {
            scene->setShape(XYGraphicsScene::CURSOR);
            scene->setItemMovable(true);
        }
    }
}

void MainWindow::openPixmap()
{
    lastPixmapPath = QFileDialog::getOpenFileName(this, tr("Open File"),
                                 "",
                                 tr("PNG (*.png);;JPG (*.jpg)"));
    QPixmap pixmap(lastPixmapPath);
    if (!pixmap.isNull())
    {
        if (canvas->scene())
        {
            canvas->scene()->removeItem(canvas);
        }
        canvas->setPixmap(pixmap);
        scene->setSceneRect(pixmap.rect());
        scene->addItem(canvas);
    }
}

void MainWindow::savePixmap()
{
    QString path = lastPixmapPath;
    if (path.isEmpty())
    {
        path = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                      "untitled.png",
                                                      tr("PNG (*.png);;JPG (*.jpg)"));
    }
    if (!path.isEmpty())
    {
        QPixmap pixmap(scene->sceneRect().width(), scene->sceneRect().height());

        QPainter painter(&pixmap);
        scene->render(&painter);
        if (pixmap.save(path, path.mid(path.lastIndexOf(".") + 1).toUpper().toLocal8Bit().data()))
        {
            lastPixmapPath = path;
        }
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (QMessageBox::question(this, QStringLiteral("确认"), QStringLiteral("是否需要保存当前图片？"))
            == QMessageBox::Yes)
    {
        savePixmap();
    }
    QMainWindow::closeEvent(event);
}

void MainWindow::initToolBar()
{
    QToolBar *bar = new QToolBar;
    QActionGroup *shapeGroup = new QActionGroup(this);

    QAction *act = bar->addAction(QIcon(":/open.ico"), QString("Open File"), this, SLOT(openPixmap()));
    act = bar->addAction(QIcon(":/save.ico"), QString("Save File"), this, SLOT(savePixmap()));

    act = bar->addAction(QIcon(":/rect.ico"), QString("Rect"));
    act->setCheckable(true);
    act->setChecked(true);
    scene->setShape(XYGraphicsScene::RECT);
    shapeGroup->addAction(act);
    act = bar->addAction(QIcon(":/ellipse.ico"), QString("Ellipse"));
    act->setCheckable(true);
    shapeGroup->addAction(act);
    act = bar->addAction(QIcon(":/arrows.ico"), QString("Arrows"));
    act->setCheckable(true);
    shapeGroup->addAction(act);
    act = bar->addAction(QIcon(":/line.ico"), QString("Line"));
    act->setCheckable(true);
    shapeGroup->addAction(act);
    act = bar->addAction(QIcon(":/draw.ico"), QString("Path"));
    act->setCheckable(true);
    shapeGroup->addAction(act);
    act = bar->addAction(QIcon(":/text.ico"), QString("Text"));
    act->setCheckable(true);
    shapeGroup->addAction(act);
    act = bar->addAction(QIcon(":/cursor.ico"), QString("Cursor"));
    act->setCheckable(true);
    shapeGroup->addAction(act);

    connect(shapeGroup, SIGNAL(triggered(QAction *)), this, SLOT(setShape(QAction *)));

    addToolBar(bar);
}
