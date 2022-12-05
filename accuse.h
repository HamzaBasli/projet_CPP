#ifndef ACCUSE_H
#define ACCUSE_H
#include <QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QtPrintSupport/QPrinter>
class Accuse
{
public:
    Accuse ();
    Accuse (QString,QString,QString,QString,QString,QString);
    QString getidentifiant();
    QString getcin();
    QString getnom();
    QString getprenom();
    QString getavocat();
    QString gettype_de_crime();
    void setidentifiant(QString);
    void setcin(QString);
    void setnom(QString);
    void setprenom(QString);
    void setavocat(QString);
    void settype_de_crime(QString);
    bool ajouter();
    bool modifier();
   QSqlQueryModel*  afficher();
   bool supprimer(QString);
    QSqlQueryModel* tri_identifiant();
    //QSqlQueryModel* geo();
private:
    QString identifiant;
    QString cin;
    QString nom;
    QString prenom ;
    QString avocat ;
    QString type_de_crime ;
   // QString remarque;
   // int stat;

};

#endif // ACCUSE_H
