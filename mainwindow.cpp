#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vtkRenderWindow.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/visualization/common/common.h>
#include <Eigen/Eigen>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("PCL viewer");
    qvtkWidget = new QVTKWidget;
    ui->verticalLayout->addWidget(qvtkWidget);
    //qvtkWidget = vtkRenderer::New();
    cloud.reset (new PointCloudT);
    grabberThread = new QThread();
    grabber = new Grabber();
    grabber->moveToThread(grabberThread);
    grabberThread->start();
    grabber->initCamera();
    connect(ui->startButton, SIGNAL(released()), this, SLOT(startButtonPressed()) );
    connect(ui->updateButton, SIGNAL(released()), this, SLOT(updateButtonPressed()) );
    connect(grabber, SIGNAL(currentFrames(int)), ui->framesLabel, SLOT(setNum(int)));
    connect(ui->drawButton, SIGNAL(released()), this, SLOT(drawSomething()));
    connect(ui->viewButton_1, SIGNAL(released()), this, SLOT(view_1()));
    connect(ui->viewButton_2, SIGNAL(released()), this, SLOT(view_2()));
    connect(ui->viewButton_3, SIGNAL(released()), this, SLOT(view_3()));
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(view_2()));
    connect(ui->horizontalSlider_2, SIGNAL(valueChanged(int)), this, SLOT(view_2()));
    connect(ui->horizontalSlider_3, SIGNAL(valueChanged(int)), this, SLOT(view_2()));
    connect(ui->horizontalSlider_4, SIGNAL(valueChanged(int)), this, SLOT(view_2()));
    connect(ui->horizontalSlider_5, SIGNAL(valueChanged(int)), this, SLOT(view_2()));
    connect(ui->horizontalSlider_6, SIGNAL(valueChanged(int)), this, SLOT(view_2()));
    connect(ui->horizontalSlider_7, SIGNAL(valueChanged(int)), this, SLOT(view_2()));
    connect(ui->horizontalSlider_8, SIGNAL(valueChanged(int)), this, SLOT(view_2()));
    connect(ui->horizontalSlider_9, SIGNAL(valueChanged(int)), this, SLOT(view_2()));
    connect(ui->horizontalSlider_10, SIGNAL(valueChanged(int)), this, SLOT(view_2()));
    connect(ui->horizontalSlider_11, SIGNAL(valueChanged(int)), this, SLOT(view_2()));
    connect(ui->horizontalSlider_12, SIGNAL(valueChanged(int)), this, SLOT(view_2()));
    //QString fileName = "res/";
    //QImage Image = QImage(fileName,"PNM");
    //int width = Image.width();
    //ui->label->setPixmap(QPixmap::fromImage(image));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setnumber(float frame)
{
    //std::cout << "set num" << frame << std::endl;
    //ui->framesLabel->show();
}

void MainWindow::startButtonPressed()
{
    viewer.reset (new pcl::visualization::PCLVisualizer ("viewer", false) );

    qvtkWidget->SetRenderWindow (viewer->getRenderWindow ());
    updateCamera();
    viewer->setupInteractor (qvtkWidget->GetInteractor(), qvtkWidget->GetRenderWindow());
    qvtkWidget->update();    
    cloud = grabber->getCloud(indices);
    viewer->addPointCloud(cloud, "cloud");
    image = grabber->getImage();
    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->startButton->setDisabled(true);
    ui->updateButton->setEnabled(true);
    ui->drawButton->setEnabled(true);
    ui->viewButton_1->setEnabled(true);
    ui->viewButton_2->setEnabled(true);
    ui->viewButton_3->setEnabled(true);
}

void MainWindow::updateButtonPressed()
{
    image = grabber->getImage();
    ui->label->setPixmap(QPixmap::fromImage(image));
    cloud = grabber->getCloud(indices);
    viewer->updatePointCloud(cloud, "cloud");
    qvtkWidget->update ();
}
void MainWindow::drawSomething()
{
    const QRgb value = qRgb(255, 0, 0);
    uint x, y;
    double temp_x;
    for(uint i = 0; i < cloud->size(); i++){
        cloud->at(i).r = 255;
        cloud->at(i).g = 0;
        cloud->at(i).b = 0;
        y = floor(static_cast<double>(indices.at(i))/static_cast<double>(image.width()));
        temp_x = indices.at(i) / static_cast<double>( image.width());
        x = image.width() * (temp_x - y);
        image.setPixel(x , y, value);
    }
    ui->label->setPixmap(QPixmap::fromImage(image));
    viewer->updatePointCloud(cloud, "cloud");
    qvtkWidget->update ();
}

void MainWindow::updateCamera()
{
    pcl::visualization::Camera camera;
    Eigen::Matrix3f rgb_intrinsics_matrix;
    //rgb_intrinsics_matrix << 525, 0.0, 319.5, 0.0, 525, 239.5, 0.0, 0.0, 1.0;
    rgb_intrinsics_matrix << 569.92842, 0.0, 640.08552 , 0.0,  571.44089, 480.82575, 0.0, 0.0, 1.0;
    Eigen::Matrix4f mat;
    mat(0,0) = static_cast<float>(ui->horizontalSlider->value())/100;
    mat(0,1) = static_cast<float>(ui->horizontalSlider_2->value())/100;
    mat(0,2) = static_cast<float>(ui->horizontalSlider_3->value())/100;
    mat(0,3) = static_cast<float>(ui->horizontalSlider_4->value())/100;
    mat(1,0) = static_cast<float>(ui->horizontalSlider_5->value())/100;
    mat(1,1) = static_cast<float>(ui->horizontalSlider_6->value())/100;
    mat(1,2) = static_cast<float>(ui->horizontalSlider_7->value())/100;
    mat(1,3) = static_cast<float>(ui->horizontalSlider_8->value())/100;
    mat(2,0) = static_cast<float>(ui->horizontalSlider_9->value())/100;
    mat(2,1) = static_cast<float>(ui->horizontalSlider_10->value())/100;
    mat(2,2) = static_cast<float>(ui->horizontalSlider_11->value())/100;
    mat(2,3) = static_cast<float>(ui->horizontalSlider_12->value())/100;
    mat(3,0) = 0.0;
    mat(3,1) = 0.0;
    mat(3,2) = 0.0;
    mat(3,3) = 1.0;

    //viewer->setCameraPosition(x, y, z, view_x, view_y, view_z, up_x, up_y, up_z, 0 );
    //camera.(mat);

    viewer->setCameraParameters(rgb_intrinsics_matrix, mat);
}

void MainWindow::view_1()
{
    /*Eigen::Affine3f intrinsics;
    intrinsics.Identity();
    Eigen::Affine extrinsics;
    extrinsics.Identity();*/
    viewer->setCameraPosition(1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0 );

}

void MainWindow::view_2()
{
    updateCamera();
    pcl::visualization::Camera camera;
    viewer->getCameraParameters(camera);
    Eigen::Matrix4d mat;
    camera.computeViewMatrix( mat);
    ui->label_11->setNum(mat(0,0));
    ui->label_12->setNum(mat(0,1));
    ui->label_13->setNum(mat(0,2));
    ui->label_14->setNum(mat(0,3));
    ui->label_15->setNum(mat(1,0));
    ui->label_16->setNum(mat(1,1));
    ui->label_17->setNum(mat(1,2));
    ui->label_18->setNum(mat(1,3));
    ui->label_19->setNum(mat(2,0));
    ui->label_20->setNum(mat(2,1));
    ui->label_21->setNum(mat(2,2));
    ui->label_22->setNum(mat(2,3));
    ui->label_23->setNum(mat(3,0));
    ui->label_24->setNum(mat(3,1));
    ui->label_25->setNum(mat(3,2));
    ui->label_26->setNum(mat(3,3));
}

void MainWindow::view_3()
{

}


