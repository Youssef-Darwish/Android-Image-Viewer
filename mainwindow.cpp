#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "jni.h"
QString selectedFileName;


#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void JNICALL
Java_com_amin_QtAndroidGallery_QtAndroidGallery_fileSelected(JNIEnv */*env*/,
                                                             jobject /*obj*/,
                                                             jstring results)
{
    selectedFileName = QAndroidJniObject(results).toString();
}

#ifdef __cplusplus
}
#endif



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionopen_triggered()
{
    selectedFileName = "#";
    QAndroidJniObject::callStaticMethod<void>("com/amin/QtAndroidGallery/QtAndroidGallery",
                                              "openAnImage",
                                              "()V");
    while(selectedFileName == "#")
        qApp->processEvents();

    if(QFile(selectedFileName).exists())
    {
        QImage img(selectedFileName);
        image = img.copy();
        default_image = image.copy(0,0,image.size().width(),image.size().height());
            this->load_image();
            //
    }

}
void MainWindow::load_image() {
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(image));
    QGraphicsScene *scene = new QGraphicsScene();
    item->scale();
    scene->addItem(item);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
}

void MainWindow::select_area() {
    // qDebug() <<ui->graphicsView->get_selected() << "\n";
    ui->graphicsView->select();
}

void MainWindow::on_actionReset_triggered()
{
    ui->graphicsView->unselect();
    image = default_image.copy(0,0,default_image.size().width(),default_image.size().height());
    this->load_image();

    ui->rotateSlider->setVisible(false);
    ui->rotateSlider->setValue(0);
    ui->angleSpinBox->setVisible(false);
}

void MainWindow::on_actionZoom_In_triggered()
{

    ui->graphicsView->unselect();
    ui->graphicsView->scale(2,2);   //zoom in

}

void MainWindow::on_actionZoom_Out_triggered()
{

    ui->graphicsView->unselect();
    ui->graphicsView->scale(.5,.5); //zoom out
}

void MainWindow::on_actionabout_triggered()
{
    QMessageBox::about(this, tr("About Image Viewer"),
               tr("<p>The <b>Image Viewer</b> is an image editor written in Qt C++ that "
               "enables the user to view and modify images in different formats .</p>"));
}

void MainWindow::on_actionrotate_triggered()
{

    ui->graphicsView->unselect();
    ui->rotateSlider->setVisible(!ui->rotateSlider->isVisible());
    ui->angleSpinBox->setVisible(!ui->angleSpinBox->isVisible());
}

void MainWindow::on_rotateSlider_valueChanged(int value)
{

    ui->graphicsView->unselect();
    ui->angleSpinBox->setValue(value);
    QMatrix rm;
    rm.rotate(value);
    QPixmap pixmap = QPixmap::fromImage(image);
    pixmap = pixmap.transformed(rm, Qt::SmoothTransformation).copy();
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(pixmap);
    QGraphicsScene *scene = new QGraphicsScene();
    scene->addItem(item);
    ui->graphicsView->setScene(scene);
}


