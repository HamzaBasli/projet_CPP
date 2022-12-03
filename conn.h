#ifndef CONN_H
#define CONN_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class Conn
{
    QSqlDatabase db;
public:
    Conn();
    bool createconn();
};

#endif // CONN_H
