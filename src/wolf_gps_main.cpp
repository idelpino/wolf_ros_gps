//
// Created by ptirindelli on 8/02/16.
//

#include "wolf_gps_node.h"


int main(int argc, char **argv)
{
    std::cout << "\n=========== WOLF GPS MAIN ===========\n\n";

    //init ros
    ros::init(argc, argv, "wolf_gps_node");

    /*
     * Parameters, to be optimized
     */
    StateBlock* sensor_p = new StateBlock(Eigen::Vector3s::Zero()); //gps sensor position
    sensor_p->fix(); // TODO only for now, to simplify things
    StateBlock* sensor_o = new StateBlock(Eigen::Vector4s::Zero(), ST_QUATERNION);   //gps sensor orientation
    sensor_o->fix(); //orientation is fixed, because antenna omnidirectional, so is not going to be optimized
    StateBlock* sensor_bias = new StateBlock(Eigen::Vector1s::Zero());    //gps sensor bias

    StateBlock* init_vehicle_p = new StateBlock(Eigen::Vector3s(4789000, 177000, 4195000));    //vehicle initial position
    StateBlock* init_vehicle_o = new StateBlock(Eigen::Vector1s::Zero());// vehicle initial orientation

    SensorGPS* gps_sensor_ptr = new SensorGPS(sensor_p, sensor_o, sensor_bias, init_vehicle_p, init_vehicle_o);

    Eigen::Vector3s prior = Eigen::Vector3s(10, 10, 90*M_PI/180);

    // init wolf odom sensor
    WolfScalar odom_std[2];
    odom_std[0] = 0.2; // odometry_translational_std
    odom_std[1] = 0.2; // odometry_rotational_std
    SensorOdom2D* odom_sensor_ptr_ = new SensorOdom2D(new StateBlock(Eigen::Vector2s::Zero()), new StateBlock(Eigen::Vector1s::Zero()), odom_std[0], odom_std[1]);//both arguments initialized on top



    // Trilateration node
    WolfGPSNode wgNode();

    ros::spin();

    return 0;
}