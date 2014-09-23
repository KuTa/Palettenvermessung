#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vtkRenderWindow.h>
#include <pcl/visualization/cloud_viewer.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->updateButton->setDisabled(true);
    this->setWindowTitle("PCL viewer");
    qvtkWidget = new QVTKWidget;
    ui->verticalLayout->addWidget(qvtkWidget);
    //qvtkWidget = vtkRenderer::New();
    cloud.reset (new PointCloudT);
    grabberThread = new QThread();
    grabber = new Grabber();
    grabber->moveToThread(grabberThread);
    grabberThread->start();
    //connect(grabber,SIGNAL(started()),grabberThread, SLOT(start) )
    grabber->initCamera();
    connect(ui->startButton, SIGNAL(released()), this, SLOT(startButtonPressed()) );
    connect(ui->updateButton, SIGNAL(released()), this, SLOT(updateButtonPressed()) );


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startButtonPressed()
{
    viewer.reset (new pcl::visualization::PCLVisualizer ("viewer", false) );
    qvtkWidget->SetRenderWindow (viewer->getRenderWindow ());
    viewer->setupInteractor (qvtkWidget->GetInteractor(), qvtkWidget->GetRenderWindow());
    qvtkWidget->update();
    cloud = grabber->getCloud();
    viewer->addPointCloud(cloud, "cloud");
    ui->startButton->setDisabled(true);
    ui->updateButton->setEnabled(true);
}

void MainWindow::updateButtonPressed()
{

    cloud = grabber->getCloud();
    viewer->updatePointCloud(cloud, "cloud");
    qvtkWidget->update ();
}
