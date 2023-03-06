#include "MySQLConnectorClass.h"

namespace {
  WiFiClient _wifiClient;
  MySQL_Connection _conn((Client *)&_wifiClient);
}

// public
MySQLConn::MySQLConn(String url, String username, String password, int port) {
  this->URL = url;
  this->Username = username;
  this->Password = password;
  this->Port = port;
}

String MySQLConn::getSingleValue(String query) {
  this->connect();

  row_values *row = NULL;
  MySQL_Cursor *cur_mem = new MySQL_Cursor(&_conn);
  String result = "NULL";

  // execute
  cur_mem->execute(query.c_str());

  // get columns, don't do anything with them
  column_names *columns = cur_mem->get_columns();

  // Read the single row
  do {
    row = cur_mem->get_next_row();
    if (row != NULL) {
      result = String(row->values[0]);
    }
  } while (row != NULL);

  // free resources
  delete cur_mem;
  this->close();

  return result;
}

void MySQLConn::upsert(String query) {
  this->connect();

  // send off, no return
  MySQL_Cursor *cur_mem = new MySQL_Cursor(&_conn);
  cur_mem->execute(query.c_str());

  delete cur_mem;
  this->close();
}

// private
bool MySQLConn::connect() {
  IPAddress ip_address;
  WiFi.hostByName(this->URL.c_str(), ip_address);

  return _conn.connect(ip_address, this->Port, const_cast<char*>(this->Username.c_str()), const_cast<char*>(this->Password.c_str()));
}

void MySQLConn::close() {
  _conn.close();
}