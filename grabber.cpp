#include "grabber.h"
#include <pcl/filters/voxel_grid.h>

Grabber::Grabber(QObject *parent):
        QObject(parent)
{
    //boost::shared_ptr<const pcl::PointCloud<pcl::PointXYZRGB> > cloudPtr(new pcl::PointCloud<pcl::PointXYZRGB>);
  
}

/*Grabber::~Grabber()
{
    if(interface != 0)
    {
        interface->stop();
        interface.reset();
    }
}
/*
 * Function to initialize the Camera with OpenNI2Grabber
 * camera is always declared as #1, because a single camera operation is assumed with Raspberry Pi
 * camera is started if possible
 * if not possible IOException with error
 */
bool Grabber::initCamera()
{
 try{
   interface = boost::shared_ptr<pcl::io::OpenNI2Grabber>(new pcl::io::OpenNI2Grabber("#1"));
   boost::function<void (const boost::shared_ptr<const PointCloudT>&)> g =
           boost::bind (&Grabber::updatePtr, this, _1);
   interface->registerCallback(g);
   interface->start();
 }
 catch(pcl::IOException e)
 {
    std::cout << "Sensor initialization error: " << e.what() << std::endl;
    interface.reset();
    return false;
 }
    while(!ready()) usleep(50);
    std::cout << "init complete" << std::endl;
 return true;
}

bool Grabber::ready()
{
    bool ready = false;
    if( cloudPtr != boost::shared_ptr<const PointCloudT>() && !cloudPtr->empty()
            )
        ready=true;
    return ready;
}

PointCloudT::Ptr Grabber::getCloud()
{
    updatePtr(cloudPtr);
    while(cloudPtr == 0)
    {
        updatePtr(cloudPtr);
    }
    mut.lock();

    PointCloudT::Ptr cloudDataFront(new PointCloudT());
    //*cloudDataFront = *cloudPtr;
    std::vector<int> indices;
    pcl::removeNaNFromPointCloud(*cloudPtr, *cloudDataFront, indices);
    pcl::VoxelGrid<PointT> sor;
     sor.setInputCloud (cloudDataFront);
     sor.setLeafSize (0.01f, 0.01f, 0.01f);
     sor.filter (*cloudDataFront);
    mut.unlock();
    return cloudDataFront;
}

void Grabber::updatePtr(const boost::shared_ptr<const PointCloudT>& cloud)
{
    mut.lock();
    usleep(50);
    this->cloudPtr = cloud;
    mut.unlock();
}
