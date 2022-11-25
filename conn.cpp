#include "conn.h"

Conn::Conn()
{

}

bool Conn::createconn()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("mak");
db.setUserName("MAHDI");//inserer nom de l'utilisateur
db.setPassword("esprit18");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}


