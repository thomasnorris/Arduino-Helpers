#ifndef MYSQL_CONN_H_
#define MYSQL_CONN_H_

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#include <WString.h>

class MySQLConn {
    public:
        MySQLConn(String url, String username, String password, int port = 3306);
        void testConnect();
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