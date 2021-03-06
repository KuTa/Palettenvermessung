#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Qt
#include <QMainWindow>
#include <QVTKWidget.h>
#include <QThread>
#include <QImage>

// PCL
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/visualization/pcl_visualizer.h>

//#include <vtkRenderWindow.h>

#include "grabber.h"

typedef pcl::PointXYZRGBA PointT;
typedef pcl::PointCloud<PointT> PointCloudT;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QVTKWidget *qvtkWidget;
    Grabber *grabber;
public slots:
    void startButtonPressed();
    void updateButtonPressed();
    void setnumber(float frame);
    void drawSomething();
    void view_1();
    void view_2();
    void view_3();


private:
    Ui::MainWindow *ui;
    QThread *grabberThread;
    QThread *frameThread;
    QImage rgbImage;
    std::vector<int> indices;
    QImage image;
    void updateCamera();

protected:
    boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer;
    PointCloudT::Ptr cloud;

};

#endif // MAINWINDOW_H
