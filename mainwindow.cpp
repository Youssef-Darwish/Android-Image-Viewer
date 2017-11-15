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
    mode = NO_MODE;
    ui->setupUi(this);
    QWidget::connect (ui->graphicsView, SIGNAL(area_selected()),
                       this, SLOT(select_area()));
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
        image.reset();
        QImage img(selectedFileName);
        image.setQImage(img.copy());
        image.setQImage(image.getQImage()->copy(0,0,image.getQImage()->size().width(),image.getQImage()->size().height()));
        this->load_image();
    }

}

void MainWindow::load_image() {
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(*image.getQImage()));
    QGraphicsScene *scene = new QGraphicsScene();
    image.setOrignal(image.getQImage()->copy());
    item->scale();
    scene->addItem(item);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
}

void MainWindow::select_area() {
    ui->graphicsView->select();
}

void MainWindow::on_actionReset_triggered()
{
    ui->graphicsView->unselect();
    image.setQImage(image.getOrignal()->copy(0,0,image.getOrignal()->size().width(),image.getOrignal()->size().height()));
    this->load_image();

    ui->rotateSlider->setVisible(false);
    ui->rotateSlider->setValue(0);
    ui->angleSpinBox->setVisible(false);
}

void MainWindow::on_actionZoom_In_triggered()
{
    mode = ZOOM_IN;
   double scale_ = 2;
   if (image.getCropArea().width() > 5 && image.getCropArea().height() > 5) {
       QPointF tempP = ui->graphicsView->mapToScene(ui->graphicsView->get_selected()->x(),
                                              ui->graphicsView->get_selected()->y());
       ui->graphicsView->fitInView(tempP.x(),
                                   tempP.y(),
                                   ui->graphicsView->get_selected()->width(),
                                   ui->graphicsView->get_selected()->height(),
                                   Qt::KeepAspectRatio);

//        ui->graphicsView->setSceneRect(tempP.x(),
//                                       tempP.y(),
//                                       ui->graphicsView->get_selected()->width(),
//                                       ui->graphicsView->get_selected()->height());

       ui->graphicsView->centerOn(ui->graphicsView->mapToScene(ui->graphicsView->get_selected()->center()));

       ui->graphicsView->unselect();
   } else {
       ui->graphicsView->scale(scale_ , scale_);
   }
}

void MainWindow::on_actionZoom_Out_triggered()
{
    mode = ZOOM_OUT;
    double scale_  = 0.5;
    if (image.getCropArea().width() > 5 && image.getCropArea().height() > 5) {
        ui->graphicsView->centerOn(ui->graphicsView->get_selected()->center());
        ui->graphicsView->unselect();
        scale_ = 0.7;
    }

    ui->graphicsView->scale(scale_, scale_);
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
    mode = ROTATE;
    ui->graphicsView->unselect();
    ui->angleSpinBox->setValue(value);

    image.setRotationAngle(value);
    updatePixmap();
}



void MainWindow::on_actioncrop_triggered()
{
    mode = CROP;
    QRect *area = ui->graphicsView->get_selected();
    if(!area || (area->width() <10 && area->height()<10))
        return;
//       qDebug() << area->x() << " "<<area->y();

       QPointF temp =  ui->graphicsView->mapToScene( *(new QPoint(area->x(),area->y())) );
       QPointF temp2 =  ui->graphicsView->mapToScene( *(new QPoint(area->x()+area->width()
                                                                  ,area->y()+area->height())) );
//       qDebug() << temp << " "<<temp2;
       area->setX( temp.x());
       area->setY( temp.y());
       area->setWidth(temp2.x()-temp.x());
       area->setHeight(temp2.y()-temp.y());

       image.setCropArea(*area);
       updatePixmap();

       ui->rotateSlider->setVisible(false);
       ui->angleSpinBox->setVisible(false);
       ui->graphicsView->unselect();
   }

void MainWindow::on_actionsave_triggered()
{
    QBuffer buffer;
    buffer.open(QIODevice::WriteOnly);
    image.getPixMap()->save(&buffer, "PNG");
    buffer.close();

    QString path = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    path.append("/Image");
    path.append(QTime::currentTime().toString());
    path.append(".png");

    QFile file( path  );
    if( file.open( QIODevice::WriteOnly ) )
    {
        file.write( buffer.buffer() );
//        qDebug()<<"saved";

        file.close();
    }
    if( file.error() != QFileDevice::NoError ){}
//        qDebug()<<"fatal";
//    qDebug()<<"saved";
}


void MainWindow::updatePixmap() {
//    delete ui->graphicsView->scene()->items().at(0);
//    delete ui->graphicsView->scene();

    QMatrix rm;
    rm.rotate(image.getRotationAngle());

    pixmap = QPixmap::fromImage(*image.getQImage());

    pixmap = pixmap.transformed(rm, Qt::SmoothTransformation);
    if (image.getCropArea().width() > 5 && image.getCropArea().height() > 5 && mode == CROP) {
            pixmap = pixmap.copy(image.getCropArea().x(),
                                 image.getCropArea().y(),
                                 image.getCropArea().width(),
                                 image.getCropArea().height());
    }

    image.setPixMap(pixmap);

//    qDebug() << mode << "\n";
    if (mode == CROP) {
        image.setQImage(pixmap.toImage().copy());
    }

    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(pixmap);
    QGraphicsScene *scene = new QGraphicsScene();
    item->scale();
    scene->addItem(item);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
}



