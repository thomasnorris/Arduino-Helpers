#include "ArduinoDataClass.h"

const String INSERT_SP = "ArduinoData.SP_InsertDataPoint";
const String UPDATE_SP = "ArduinoData.SP_UpdateDataPoint";

MySQLConn* _sql;

// public
ArduinoData::ArduinoData(int app_ID, String url, String username, String password, int port) {
  _sql = new MySQLConn(url, username, password, port);
  this->AppID = app_ID;
}

void ArduinoData::insertDataPoint(int data_point_type_ID, String value) {
  this->upsertInternal(INSERT_SP, data_point_type_ID, value);
}

void ArduinoData::insertDataPoint(int data_point_type_ID, int value) {
  this->upsertInternal(INSERT_SP, data_point_type_ID, String(value));
}

void ArduinoData::updateDataPoint(int data_point_type_ID, String value) {
  this->upsertInternal(UPDATE_SP, data_point_type_ID, value);
}

void ArduinoData::updateDataPoint(int data_point_type_ID, int value) {
  this->upsertInternal(UPDATE_SP, data_point_type_ID, String(value));
}

// private
// either update or insert procs, both take the same params
void ArduinoData::upsertInternal(String proc, int data_point_type_ID, String value) {
  String escaped_value = "\"" + value + "\"";
  String query = "CALL " + proc + "(" + this->AppID + ", " + String(data_point_type_ID) + ", " + escaped_value + ");";

  _sql->upsert(query);
}
