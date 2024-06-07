#ifndef DATACOLLECTOR_H_
#define DATACOLLECTOR_H_

#include <ctime>
#include <fstream>
#include <iomanip>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "vector3.h"

class Drone;

/**
 * @class DataCollector
 * @brief Represents a singleton class responsible for collecting and managing
 * related data belonging to drone activities.
 *
 * This class is mainly resposible for collecting and recording various metric
 * data such as speed, mileage, delivery times, and locations for drones. It
 * ensures that only one instance of the class exists throughout the simulation
 * run.
 */
class DataCollector {
 public:
  /**
   * @brief Responsible for retrieving the singleton instance of the
   * DataCollector.
   * @return Responsible for returning the reference to the singleton instance
   * of the DataCollector.
   */
  static DataCollector& getInstance();

  /**
   * @brief Removing the copy constructor operator to prevent copying of the
   * singleton instance.
   */
  DataCollector(const DataCollector&) = delete;

  /**
   * @brief Removing the assignment operator to prevent copying of the singleton
   * instance.
   */
  DataCollector& operator=(const DataCollector&) = delete;

  /**
   * @brief Responsibe for recording the speed of the drone.
   * @param droneId The ID of the drone.
   * @param speed The speed of the drone.
   */
  void recordDroneSpeed(int droneId, double speed);

  /**
   * @brief Responsibe for recording the mileage of the drone.
   * @param droneId The ID of the drone.
   * @param mileage The mileage of the drone.
   */
  void recordDroneMileage(int droneId, double mileage);

  /**
   * @brief Responsible for marking the start of the delivery process for a
   * drone.
   * @param droneId The ID of the drone.
   */
  void startDelivery(int droneId);

  /**
   * @brief Responsible for starting the timer in order to track the delivery
   * time for a drone.
   * @param droneId The ID of the drone.
   */
  void startDeliveryTimer(int droneId);

  /**
   * @brief Responsible for recording the delivery time for a drone.
   * @param droneId The ID of the drone.
   * @param time The time to record the delivery process.
   */
  void recordDeliveryTime(int droneId, double time);

  /**
   * @brief Responsible for retrieving the start time of the delivery process
   * for a drone.
   * @param droneId The ID of the drone.
   * @return Returns the start time of the delivery.
   */
  std::time_t getDeliveryStartTime(int droneId);

  /**
   * @brief Responsible for recording the pickup time for a drone.
   * @param droneId The ID of the drone.
   * @param time The time to record the pickup process.
   */
  void recordPickupTime(int droneId, const std::time_t& time);

  /**
   * @brief Responsible for recording the dropoff time for a drone.
   * @param droneId The ID of the drone.
   * @param time The time to record the dropoff process.
   */
  void recordDropoffTime(int droneId, const std::time_t& time);

  /**
   * @brief Responsible for formatting the recorded time value in a readable
   * format.
   * @param time The time to be formatted.
   * @return Returns the formatted time value as a readable string.
   */
  std::string formatTime(const std::time_t& time);

  /**
   * @brief Responsible for recording the pickup location for a drone.
   * @param droneId The ID of the drone.
   * @param location The location to be recorded.
   */
  void recordPickupLocation(int droneId, const Vector3& location);

  /**
   * @brief Responsible for recording the dropoff location for a drone.
   * @param droneId The ID of the drone.
   * @param location The location to be recorded.
   */
  void recordDropoffLocation(int droneId, const Vector3& location);

  /**
   * @brief Responsible for recording a new drone in the simulation system.
   * @param droneId The ID of the drone.
   */
  void recordDrone(int droneId);

  /**
   * @brief Responsible for recording the spawn location of a robot.
   * @param robotId The ID of the robot.
   * @param location The spawn location of the robot
   */
  void recordRobotSpawnLocation(int robotId, const Vector3& location);

  /**
   * @brief Responsible to write the output collected data to a CSV file.
   */
  void outputDataToCSV();

  /**
   * @brief Responsible for writing more additional data to a second CSV file
   */
  void outputMoreDataToCSV();

 private:
  DataCollector();

  ~DataCollector();

  static DataCollector*
      instance;  // Static instance pointer for the singleton pattern

  /**
   * @struct DroneData
   * @brief A structure responsible for storing various metric data related to a
   * single drone.
   */
  struct DroneData {
    double totalSpeed;
    double totalMileage;
    int numDeliveries;
    double totalDistance;
    double totalTimeTaken;
    std::vector<std::time_t> pickupTimes;
    std::vector<std::time_t> dropoffTimes;
    std::vector<Vector3> pickupLocations;
    std::vector<Vector3> dropoffLocations;
  };

  /**
   * @struct RobotData
   * @brief  A structure responsible for storing various metric data related to
   * a single robot.
   */
  struct RobotData {
    Vector3 spawnLocation;
  };

  std::map<int, DroneData>
      droneDataMap;  // Used for mapping the drone ID to its data value

  std::map<int, std::time_t>
      deliveryStartTimes;  // Used for mapping the drone ID to the start time of
                           // its respective deliveries.

  std::map<int, RobotData>
      robotDataMap;  // Used for mapping the robot ID to its data value

  /**
   * @brief Responsible for writing a line into a CSV file.
   * @param file Reference to the object used for writing data to a file.
   * @param data Vector of strings containing the data to write.
   */
  void writeCSVLine(std::ofstream& file, const std::vector<std::string>& data);
};

#endif  // DATACOLLECTOR_H_
