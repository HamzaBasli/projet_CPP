#include "accuse.h"
#include <QtDebug>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QtDebug>
#include <QObject>
#include "mainwindow.h"
#include"connexion.h"
#include<QString>

Accuse::Accuse()
{  identifiant=" ";
    cin=" ";
    nom=" " ;
    prenom=" ";
    avocat=" ";
   type_de_crime=" ";
   //remarque="";
}
Accuse::Accuse(QString identifiant ,QString cin ,QString nom ,QString prenom ,QString avocat ,QString type_de_crime)
{   this->identifiant=identifiant ;
    this ->cin=cin ;
    this->nom=nom;
    this->prenom=prenom ;
    this->avocat=avocat ;
    this->type_de_crime=type_de_crime ;}
QString Accuse::getidentifiant(){return identifiant;}
QString Accuse::getcin(){return cin;}
QString Accuse::getnom(){return nom;}
QString Accuse::getprenom(){return prenom;}
QString Accuse::getavocat(){return avocat;}
QString Accuse::gettype_de_crime(){return type_de_crime;}
void Accuse::setidentifiant(QString identifiant){this->identifiant=identifiant;}
void Accuse::setcin(QString cin){this->cin=cin;}
void Accuse::setnom(QString nom){this->nom=nom;}
void Accuse::setprenom(QString prenom){this->prenom=prenom;}
void Accuse::setavocat(QString avocat){this->avocat=avocat;}
void Accuse::settype_de_crime(QString type_de_crime){this->type_de_crime=type_de_crime;}

bool Accuse::ajouter()
{
    QSqlQuery query;
    //QString id_string=QString::number(identifiant);
          query.prepare("INSERT INTO accuse (identifiant,cin,nom,prenom,avocat,type_de_crime ) "
                        "VALUES (:identifiant , :cin , :nom ,:prenom , :avocat ,:type_de_crime )");
          query.bindValue(":identifiant",identifiant);
          query.bindValue(":cin",cin);
          query.bindValue(":nom", nom);
          query.bindValue(":prenom", prenom);
          query.bindValue(":avocat",avocat);
          query.bindValue(":type_de_crime",type_de_crime);

         return query.exec();

}
bool Accuse::modifier()
{
    QSqlQuery query;
   // QString res=QString::number(identifiant);

     query.prepare("UPDATE accuse SET  identifiant=:identifiant, cin=:cin, nom=:nom, prenom=:prenom, avocat=:avocat , type_de_crime=:type_de_crime WHERE identifiant=:identifiant ");

     query.bindValue(":identifiant",identifiant);
     query.bindValue(":cin",cin);
     query.bindValue(":nom",nom);
     query.bindValue(":prenom",prenom);
     query.bindValue(":avocat",avocat);
     query.bindValue(":type_de_crime",type_de_crime);


 return query.exec();
}

bool Accuse::supprimer(QString identifiant)
{
    QSqlQuery query ;
    query.prepare(("Delete from accuse where identifiant=:identifiant"));
    query.bindValue(0,identifiant);
    query.bindValue(1,cin);
    query.bindValue(2,nom);
    query.bindValue(3,prenom);
    query.bindValue(4,avocat);
    query.bindValue(5,type_de_crime);
   // query.bindValue(6,remarque);
    return query.exec();

}
QSqlQueryModel * Accuse::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();

   //  QSqlQueryModel* model=new QSqlQueryModel();
          model->setQuery("SELECT * FROM accuse");
          model->setHeaderData(0, Qt::Horizontal, QObject:: tr("identifiant"));//ajouter header data ajouter le nom de colone du tableau
          model->setHeaderData(1, Qt::Horizontal, QObject:: tr("cin"));
          model->setHeaderData(2, Qt::Horizontal, QObject:: tr("nom"));
          model->setHeaderData(3, Qt::Horizontal, QObject:: tr("prenom"));
          model->setHeaderData(4, Qt::Horizontal, QObject:: tr("avocat"));
          model->setHeaderData(5, Qt::Horizontal, QObject:: tr("type_de_crime"));

    return  model;
}
QSqlQueryModel * Accuse::tri_identifiant()
    {
        QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from ACCUSE order by identifiant");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("identifiant"));
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("cin"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOm"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("avocat"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("type_de_crime"));

   return model;
    }
/*
QSqlQueryModel * Accuse::geo()
{
    QString link="https://www.bing.com/maps?q=Technolgy+Store%2C+09.Rue+Hedi+Khefecha+Ariana+2080%2C+Ariana%2C+Tunis%2C+Tunisiemap&cvid=d31c6d30fe8a434c99d88c90876c1c74&aqs=edge..69i57.2098j0j4&FORM=ANAB01&PC=U531";
    QDesktopServices::openUrl(link);
}*/
