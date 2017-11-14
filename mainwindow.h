#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QSlider>
#include <QSpinBox>
#include <QtGui>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <QGraphicsPixmapItem>
#include <iostream>
#include <QTransform>
#include <QImage>
#include <QScrollArea>

#include <QtWidgets>
#include <QtAndroidExtras>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
     void select_area();

private slots:

    void on_actionopen_triggered();
    void on_actionReset_triggered();
    void on_actionZoom_In_triggered();
    void on_actionZoom_Out_triggered();
    void on_actionabout_triggered();
    void on_actionrotate_triggered();
    void on_rotateSlider_valueChanged(int value);
    void load_image();

    void on_actioncrop_triggered();

    void on_actionsave_triggered();

private:
    Ui::MainWindow *ui;
    QImage image;
    QImage default_image;

};

#endif // MAINWINDOW_H
