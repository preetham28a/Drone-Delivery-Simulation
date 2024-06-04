#include "DataCollector.h"

#include <iomanip>

DataCollector* DataCollector::instance = nullptr;

DataCollector& DataCollector::getInstance() {
  if (instance == nullptr) {
    instance = new DataCollector();
  }
  return *instance;
}

DataCollector::DataCollector() {}

DataCollector::~DataCollector() { outputDataToCSV(); }

void DataCollector::recordDroneSpeed(int droneId, double speed) {
  DroneData& data = droneDataMap[droneId];
  data.totalSpeed += speed;
}

void DataCollector::recordDroneMileage(int droneId, double mileage) {
  if (droneDataMap[droneId].numDeliveries > 0) {
    droneDataMap[droneId].totalMileage += mileage;
    droneDataMap[droneId].totalDistance += mileage;
  }
}

void DataCollector::startDelivery(int droneId) {
  if (droneDataMap.find(droneId) == droneDataMap.end()) {
    droneDataMap[droneId] = {0, 0, 0};
  }

  droneDataMap[droneId].numDeliveries++;
}

void DataCollector::startDeliveryTimer(int droneId) {
  deliveryStartTimes[droneId] = std::time(nullptr);
}

void DataCollector::recordDeliveryTime(int droneId, double time) {
  droneDataMap[droneId].totalTimeTaken += time;
}

std::time_t DataCollector::getDeliveryStartTime(int droneId) {
  return deliveryStartTimes[droneId];
}

void DataCollector::recordPickupTime(int droneId, const std::time_t& time) {
  droneDataMap[droneId].pickupTimes.push_back(time);
}

void DataCollector::recordDropoffTime(int droneId, const std::time_t& time) {
  droneDataMap[droneId].dropoffTimes.push_back(time);
}

std::string DataCollector::formatTime(const std::time_t& time) {
  char buffer[80];
  std::strftime(buffer, sizeof(buffer), "%F %T", std::localtime(&time));
  return std::string(buffer);
}

void DataCollector::recordPickupLocation(int droneId, const Vector3& location) {
  droneDataMap[droneId].pickupLocations.push_back(location);
}

void DataCollector::recordDropoffLocation(int droneId,
                                          const Vector3& location) {
  droneDataMap[droneId].dropoffLocations.push_back(location);
}

void DataCollector::recordDrone(int droneId) {
  if (droneDataMap.find(droneId) == droneDataMap.end()) {
    DroneData data = {0, 0, 0, 0, 0, {}, {}, {}, {}};
    droneDataMap[droneId] = data;
  }
}

void DataCollector::recordRobotSpawnLocation(int robotId,
                                             const Vector3& location) {
  robotDataMap[robotId].spawnLocation = location;
}

void DataCollector::outputMoreDataToCSV() {
  std::ofstream file("more_data.csv");
  file << "Robot ID,  Spawn Location\n";
  for (const auto& entry : robotDataMap) {
    file << entry.first << " " << entry.second.spawnLocation.toString() << "\n";
  }
  file.close();
}

void DataCollector::outputDataToCSV() {
  std::ofstream file("drone_data.csv");

  int maxDeliveries = 0;
  for (const auto& entry : droneDataMap) {
    maxDeliveries = std::max(maxDeliveries, entry.second.numDeliveries);
  }

  std::vector<std::string> headers = {"Serial Number",  "Drone ID",
                                      "Average Speed",  "No. of Deliveries",
                                      "Total Distance", "Total Time Taken"};
  for (int i = 1; i <= maxDeliveries; ++i) {
    headers.push_back("Pickup Time D " + std::to_string(i));
    headers.push_back("Drop off Time D " + std::to_string(i));
    headers.push_back("Pickup Location D " + std::to_string(i));
    headers.push_back("Drop off Location D " + std::to_string(i));
  }
  writeCSVLine(file, headers);

  int serialNumber = 1;
  for (const auto& entry : droneDataMap) {
    const DroneData& droneData = entry.second;
    std::vector<std::string> lineData = {
        std::to_string(serialNumber++),
        std::to_string(entry.first),
        std::to_string(droneData.totalSpeed / droneData.numDeliveries),
        std::to_string(droneData.numDeliveries),
        std::to_string(droneData.totalDistance),
        std::to_string(droneData.totalTimeTaken)};

    for (size_t i = 0; i < droneData.numDeliveries; ++i) {
      lineData.push_back(formatTime(droneData.pickupTimes[i]));
      lineData.push_back(formatTime(droneData.dropoffTimes[i]));
      lineData.push_back(droneData.pickupLocations[i].toString());
      lineData.push_back(droneData.dropoffLocations[i].toString());
    }

    writeCSVLine(file, lineData);
  }

  file.close();
}

void DataCollector::writeCSVLine(std::ofstream& file,
                                 const std::vector<std::string>& data) {
  std::vector<int> columnWidths = {15, 10, 15, 20, 20, 20};

  for (size_t i = 6; i < data.size(); i++) {
    if ((i - 6) % 4 == 0 || (i - 6) % 4 == 1)
      columnWidths.push_back(25);
    else
      columnWidths.push_back(30);
  }

  const char separator = ' ';

  for (size_t i = 0; i < data.size(); ++i) {
    file << std::left << std::setw(columnWidths[i]) << std::setfill(separator)
         << data[i];
    if (i < data.size() - 1) {
      file << "  ";
    }
  }
  file << "\n";
}
