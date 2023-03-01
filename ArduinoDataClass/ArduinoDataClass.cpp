#include "ArduinoDataClass.h"

const String INSERT_SP = "ArduinoData.SP_InsertDataPoint";

MySQLConn* _sql;

// public
ArduinoData::ArduinoData(int app_ID, String url, String username, String password, int port) {
  _sql = new MySQLConn(url, username, password, port);
  this->AppID = app_ID;
}

void ArduinoData::testConnect() {
  _sql->testConnect();
}

void ArduinoData::insertDataPoint(int data_point_type_ID, String value) {
  this->insertDataPointInternal(data_point_type_ID, value);
}

void ArduinoData::insertDataPoint(int data_point_type_ID, int value) {
  this->insertDataPointInternal(data_point_type_ID, String(value));
}

void ArduinoData::insertDataPointInternal(int data_point_type_ID, String value) {
  String escaped_value = "\"" + value + "\"";
  String query = "CALL " + INSERT_SP + "(" + this->AppID + ", " + String(data_point_type_ID) + ", " + escaped_value + ");";

  _sql->upsert(query);
}
