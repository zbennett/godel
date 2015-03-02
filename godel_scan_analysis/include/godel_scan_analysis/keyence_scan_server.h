#ifndef KEYENCE_SCAN_SERVER_H
#define KEYENCE_SCAN_SERVER_H

#include <string>

// scan type
#include <pcl_ros/point_cloud.h>
#include <pcl/point_types.h>

#include <tf/transform_listener.h>

#include "godel_scan_analysis/scan_roughness_scoring.h"

namespace godel_scan_analysis
{
  /**
   * Defines the ROS interface for a surface-quality-map 
   */
  class ScanServer
  {
  public:
    typedef pcl::PointCloud<pcl::PointXYZRGB> ColorCloud;
    typedef pcl::PointCloud<pcl::PointXYZ> Cloud;

    ScanServer()
      : map_(new ColorCloud)
      , start_time_(ros::Time::now())
      , n_(0)
    {
      ros::NodeHandle nh;
      scan_sub_ = nh.subscribe("profiles", 100, &ScanServer::scanCallback, this);
      cloud_pub_ = nh.advertise<ColorCloud>("color_cloud", 1);
    }

    void scanCallback(const Cloud& cloud)
    {
      // ROS_INFO("Processing scan");
      // ros::Time start = ros::Time::now();
      scorer_.analyze(cloud, *map_);
      // ros::Duration dt = ros::Time::now() - start;
      // ROS_INFO("Took %f seconds", dt.toSec());
      map_->header.frame_id = "sensor_optical_frame";
      cloud_pub_.publish(map_);
      map_->clear();
      n_++;

      if (n_ % 100 == 0)
      {
        double dt = (ros::Time::now() - start_time_).toSec();
        ROS_INFO("Rate: %f", n_ / dt);
      }
    }

    /**
     * Queries the underlying map for a colorized point cloud representing the current surface quality of the system
     * @return Shared-Pointer to const PointCloud<PointXYZRGB>
     */
    ColorCloud::ConstPtr getSurfaceQuality() const;
    
  private:
    RoughnessScorer scorer_; /** Object that scores individual lines */
    ColorCloud::Ptr map_; /** Data structure that contains colorised surface quality results */
    tf::TransformListener tf_listener_; // for looking up transforms between laser scan and arm position
    ros::Subscriber scan_sub_; // for listening to scans
    ros::Publisher cloud_pub_; // for outputting colored clouds of data
    std::string from_frame_; // typically laser_scan_frame
    std::string to_frame_; // typically world_frame
    ros::Time start_time_;
    unsigned n_;
  };

} // end namespace godel_scan_analysis

#endif
