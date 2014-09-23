#ifndef GRABBER_H
#define GRABBER_H


#include <pcl/io/openni2_grabber.h>
#include <pcl/common/transforms.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/filters/passthrough.h>

#include <QObject>

typedef pcl::PointXYZRGBA PointT;
typedef pcl::PointCloud<PointT> PointCloudT;

class Grabber : public QObject
{
    Q_OBJECT
/* 
  public functions
*/
public:
  explicit Grabber(QObject *parent = 0);
  //~Grabber();
  bool initCamera();
  bool ready();
  PointCloudT::Ptr  getCloud();

private:
  /*
   * private funtions
   * 
   */
  void updatePtr(const boost::shared_ptr<const PointCloudT>& cloud);
  /*
   * private variables
   * 
   */
  boost::shared_ptr<pcl::Grabber> interface;
  boost::mutex mut;
  boost::shared_ptr<const PointCloudT> cloudPtr;
};
#endif // GRABBER_H
