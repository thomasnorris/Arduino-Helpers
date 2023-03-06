#ifndef MYSQL_CONN_H_
#define MYSQL_CONN_H_

/* Library Requirements */
// https://github.com/ChuckBell/MySQL_Connector_Arduino
//  - there is a bug in v1.2.0, see this: https://github.com/ChuckBell/MySQL_Connector_Arduino/pull/177/files for a fix
// ESP8266WiFi

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#include <WString.h>
#include "../ExceptionHandlerClass/ExceptionHandlerClass.h"

class MySQLConn {
    public:
        MySQLConn(String url, String username, String password, int port = 3306);
        String getSingleValue(String query);
        void upsert(String query);
    private:
        bool connect();
        void close();
        String URL;
        String Username;
        String Password;
        int Port;
};

#endif