#include "ArduinoDataClass.h"

namespace {
  const String INSERT_SP = "ArduinoData.SP_InsertDataPoint";
  const String UPDATE_SP = "ArduinoData.SP_UpdateDataPoint";
  const String GET_SUM_TODAY_SP = "ArduinoData.SP_SumValueOfDataPointsToday";
  const String GET_LAST_DTP_SP = "ArduinoData.SP_GetLastDataPoint";

  MySQLConn* _sql;
}

// public
ArduinoDataClient::ArduinoDataClient(int app_ID, String url, String username, String password, int port) {
  _sql = new MySQLConn(url, username, password, port);
  this->AppID = app_ID;
}

void ArduinoDataClient::insertDataPoint(int data_point_type_ID, String value) {
  this->upsertInternal(INSERT_SP, data_point_type_ID, value);
}

void ArduinoDataClient::insertDataPoint(int data_point_type_ID, int value) {
  this->upsertInternal(INSERT_SP, data_point_type_ID, String(value));
}

void ArduinoDataClient::updateDataPoint(int data_point_type_ID, String value) {
  this->upsertInternal(UPDATE_SP, data_point_type_ID, value);
}

void ArduinoDataClient::updateDataPoint(int data_point_type_ID, int value) {
  this->upsertInternal(UPDATE_SP, data_point_type_ID, String(value));
}

String ArduinoDataClient::getSumToday(int data_point_type_ID) {
  return this->getSumInternal(GET_SUM_TODAY_SP, data_point_type_ID);
}

String ArduinoDataClient::getLast(int data_point_type_ID) {
  String query = "CALL " + GET_LAST_DTP_SP + "(" + this->AppID + ", " + String(data_point_type_ID) + ");";

  return _sql->getSingleValue(query);
}

// private
// either update or insert procs, both take the same params
void ArduinoDataClient::upsertInternal(String proc, int data_point_type_ID, String value) {
  String escaped_value = "\"" + value + "\"";
  String query = "CALL " + proc + "(" + this->AppID + ", " + String(data_point_type_ID) + ", " + escaped_value + ");";

  _sql->upsert(query);
}

// gets the sum of data points for a certain proc
String ArduinoDataClient::getSumInternal(String proc, int data_point_type_ID) {
  String query = "CALL " + proc + "(" + this->AppID + ", " + String(data_point_type_ID) + ");";

  return _sql->getSingleValue(query);
}
