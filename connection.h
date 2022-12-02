#ifndef CONNECTION_H
#define CONNECTION_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include<QPainter>
#include<QPdfWriter>

class Connection
{
    QSqlDatabase db ;
public:
    Connection();
    bool createconnection();
    void closeconnection();
};

#endif // CONNECTION_H
