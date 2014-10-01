#include "grabber.h"
#include <pcl/filters/voxel_grid.h>
#include <chrono>
#include <QMessageBox>

Grabber::Grabber(QObject *parent):
        QObject(parent)
{
    //boost::shared_ptr<const pcl::PointCloud<pcl::PointXYZRGB> > cloudPtr(new pcl::PointCloud<pcl::PointXYZRGB>);
  
}

Grabber::~Grabber()
{
    if(interface != 0)
    {
        interface->stop();
        interface.reset();
    }
    frameThread.detach();
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
   boost::function<void (const boost::shared_ptr<pcl::io::openni2::Image>&)> f = boost::bind (&Grabber::updateImg, this, _1);
   interface->registerCallback(g);
   interface->registerCallback(f);
   interface->start();
   frameThread = std::thread(&Grabber::frames,this);

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

/*void Grabber::calibrate()
{
    //pcl::io::openni2::DepthImage.

}*/


bool Grabber::ready()
{
    bool ready = false;
    if( cloudPtr != boost::shared_ptr<const PointCloudT>() && !cloudPtr->empty()
            )
    {
        ready=true;
        //image = QImage(cloudPtr->width, cloudPtr->height, QImage::Format_RGB32);
    }
    return ready;
}

void Grabber::isRunning()
{
    interface->isRunning();
}
void Grabber::frames() const
{
    const std::chrono::milliseconds dura(500);
    int frame;
    while(true){
        frame = static_cast<int>(interface->getFramesPerSecond());
        emit currentFrames(frame);
        /*if(frame == 30){
             boost::mutex mut2;
             mut2.lock();
             QMessageBox msgBox;
             msgBox.setText("Frames Error");
             msgBox.exec();
             mut2.unlock();
        }*/
        std::this_thread::sleep_for(dura);
    }
}

PointCloudT::Ptr Grabber::getCloud(std::vector<int> &indices)
{

    updatePtr(cloudPtr);
    while(cloudPtr == 0)
    {
        updatePtr(cloudPtr);
    }
    mut.lock();

    PointCloudT::Ptr cloudDataFront(new PointCloudT());
    //*cloudDataFront = *cloudPtr;
    //std::vector<int> indices;
    pcl::removeNaNFromPointCloud(*cloudPtr, *cloudDataFront, indices);
    //for (int it = 0; it < indices.size();it++)
    //std::cout << indices.at(it) << " it: " << it <<std::endl;
    //std::cout << cloudDataFront->size() << std::endl;
    pcl::VoxelGrid<PointT> sor;
    /*sor.setInputCloud (cloudDataFront);
    sor.setLeafSize (0.01f, 0.01f, 0.01f);
    sor.filter (*cloudDataFront);*/
    mut.unlock();
    return cloudDataFront;
}

QImage Grabber::getImage()
{
    updateImg(imgPtr);
    unsigned char *rgb_buffer = new unsigned char[ imgPtr->getWidth() * imgPtr->getHeight() * 3];
    imgPtr->fillRGB(imgPtr->getWidth(), imgPtr->getHeight(), rgb_buffer);
    QImage image = QImage(rgb_buffer, imgPtr->getWidth(), imgPtr->getHeight(), QImage::Format_RGB888);
    //image.data_ptr()
    return image;
}

void Grabber::updatePtr(const boost::shared_ptr<const PointCloudT>& cloud)
{
    mut.lock();
    usleep(50);
    this->cloudPtr = cloud;
    mut.unlock();
}

void Grabber::updateImg(const boost::shared_ptr<const pcl::io::openni2::Image>& img)
{
    mut.lock();
    this->imgPtr = img;
    mut.unlock();
}
