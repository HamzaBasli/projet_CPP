#ifndef PROJET_H
#define PROJET_H
#include<QString>
#include<QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include<QDebug>
class projet
{
public:
    projet();
    projet(int,QString,QString,QDate,QDate);
int getid();
QString getnom_projet();
QString getlocalisation();
QSqlQuery query;
QDate getDate_deb();
QDate getDate_fin();
 void setid(int);
 void setnom_projet(QString);
 void setlocalisation(QString);
 void setDate_deb(QDate);
void setDate_fin(QDate);

 bool ajouter();
 QSqlQueryModel* afficher();
 bool supprimer(int);
 bool modifier(int,QString,QString,QDate,QDate);
// QSqlQueryModel* Find_Employe();
    // QSqlQueryModel* recherche_employe(QString search);
private:
 int id_projet;
 QString nom_projet;
 QString localisation;
 QDate date_deb;
 QDate date_fin;

};

#endif // PROJET_H
