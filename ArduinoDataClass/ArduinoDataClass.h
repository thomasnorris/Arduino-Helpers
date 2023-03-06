#ifndef ARD_DATA_CLASS_H_
#define ARD_DATA_CLASS_H_

#include <Arduino.h>
#include "../MySQLConnectorClass/MySQLConnectorClass.h"

class ArduinoDataClient {
  public:
    ArduinoDataClient(int app_ID, String url, String username, String password, int port = 3306);
    // insert
    void insertDataPoint(int data_point_type_ID, String value);
    void insertDataPoint(int data_point_type_ID, int value);
    // update
    void updateDataPoint(int data_point_type_ID, String value);
    void updateDataPoint(int data_point_type_ID, int value);
    // get
    String getSumToday(int data_point_type_ID);
    String getSumThisWeek(int data_point_type_ID);
    String getLast(int data_point_type_ID);
  private:
    void upsertInternal(String proc, int data_point_type_ID, String value);
    String getSumInternal(String proc, int data_point_type_ID);
    int AppID;
};

#endif