#include "conn.h"

Conn::Conn()
{

}

bool Conn::createconn()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("sourceprojet");
db.setUserName("ALE");//inserer nom de l'utilisateur
db.setPassword("aloulou123");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}


