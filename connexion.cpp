#include "connexion.h"
#include <QtPrintSupport/QPrinter>
Connexion::Connexion()
{

}
bool Connexion::createConnexion()
{
     bool test=false;
    db=QSqlDatabase::addDatabase("QODBC");
   // bool test=false;

    db.setDatabaseName("test");
    db.setUserName("ghofrane");
    db.setPassword("esprit");
    if(db.open())
        test=true;
        return test;

}
void Connexion::closeConnexion(){db.close();
}
