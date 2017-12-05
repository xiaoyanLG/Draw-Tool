#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class XYGraphicsView;
class XYGraphicsScene;
class XYCanvasGraphicsItem;
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void setShape(QAction *act);
    void openPixmap(const QString &path = QString());
    void savePixmap();
    void settingPen();

protected:
    void closeEvent(QCloseEvent *event);
    bool eventFilter(QObject *watched, QEvent *event);

private:
    void initToolBar();

private:
    XYGraphicsView *view;
    XYGraphicsScene *scene;
    XYCanvasGraphicsItem *canvas;
    QString          lastPixmapPath;

};

#endif // MAINWINDOW_H
