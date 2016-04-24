#include "locokit_hw_ros/locokit_hw_interface.h"
#include "locokit_hw_interface.cpp"

bool g_quit = false;

void quitRequested(int sig) {
  g_quit = true;
}



int main( int argc, char** argv ){

  //Initialize ROS
  ros::init(argc, argv, "locokit_hw_interface");

  //Add custom signal handlers
  signal(SIGTERM, quitRequested);

  //Construct the wam structure
  ros::NodeHandle locokit_nh("locokit");

  LocokitHW locokit_robot(locokit_nh);
  locokit_robot.configure();
  locokit_robot.start();

  //ROS callback call
  ros::AsyncSpinner spinner(1);
  spinner.start();

  //Time variables
  struct timespec ts = {0,0};

  if(clock_gettime(CLOCK_REALTIME, &ts) != 0) {
    ROS_FATAL("Failed to poll realtime clock!");
  }

  ros::Time
    last(ts.tv_sec, ts.tv_nsec),
    now(ts.tv_sec, ts.tv_nsec);
  ros::Duration period(1.0);

  //Loop until initialization is completed
  bool a_correr = false;
  while(!g_quit && !a_correr) {
    if(!locokit_robot.configure()) {
      ROS_ERROR("Could not configure Locokit!");
    } else if(!locokit_robot.start()) {
      ROS_ERROR("Could not start Locokit!");
    } else {
      ros::Duration(1.0).sleep();

      if(!locokit_robot.read()) {
        ROS_ERROR("Could not read from Locokit!");
      } else {
        a_correr = true;
      }
    }
    period.sleep();
  }

  // Construct the controller manager
  ros::NodeHandle nh;
  //controller_manager::ControllerManager manager(&locokit_robot, nh);


  //Main loop
  while(!g_quit) {
    //Read the state from the robot
    if(!locokit_robot.read()) {
      g_quit=true;
      break;
    }

    //Update the controllers
    //manager.update(now, period);

    //Send the command to the robot
    locokit_robot.write();
  }

  spinner.stop();
  //ros::shutdown();
  //TODO: clean up when finished


  return 0;
}
