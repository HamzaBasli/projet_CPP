#include "sal.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <iostream>

sal::sal()
{
num=0; emplacement=" "; capacite= " "; etat=" ";

}
sal:: sal(int num,QString emplacement,QString capacite,QString etat)
{this->num=num; this->emplacement=emplacement; this->capacite=capacite; this->etat=etat;}
 //sal:: sal(int num,float temperature)
//{this->num=num; this->temperature;}
int sal::getnum() {return num;}
QString sal::getemplacement() {return emplacement;}
QString sal::getcapacite() {return capacite;}
QString sal::getetat() {return etat;}

void sal::setnum(int num) {this->num=num;}
void sal::setcapacite(QString capacite) {this->capacite=capacite;}
void sal::setemplacement(QString emplacement){this->emplacement=emplacement;}
void sal::setetat(QString etat) {this->etat=etat;}
bool sal::ajouter()
{
    QSqlQuery query;
    QString num_string=QString::number(num);
        query.prepare("INSERT INTO TABLE1 (num, capacite, emplacement,etat) "
                      "VALUES (:num, :capacite, :emplacement, :etat)");
        query.bindValue(":num", num_string);
        query.bindValue(":capacite", capacite);
        query.bindValue(":emplacement", emplacement);
        query.bindValue(":etat", etat);
        return  query.exec();}
bool sal::modifier()
{
    QSqlQuery query;
       QString res=QString::number(num);

        query.prepare("UPDATE TABLE1 SET  num=:num ,emplacement=:emplacement, capacite=:capacite, etat=:etat  WHERE num=:num");

        query.bindValue(":num",res);
        query.bindValue(":emplacement",emplacement);
        query.bindValue(":capacite",capacite);
        query.bindValue(":etat",etat);


    return query.exec();
}
//bool sal::modifier1(float data )
//{

   //  QString tmp=QString::number(data);

        //  QSqlQuery query;

      //  query.prepare("UPDATE TABLE1 SET temperature=:temperature  WHERE num=1");
      //  query.bindValue(":num",1);
       // query.bindValue(":temperature",tmp);
   // return query.exec();
//}
bool sal::supprimer(int num)
{ QSqlQuery query;
    QString kes=QString::number(num);

        query.prepare("Delete from TABLE1 where num=:num");

        query.bindValue(":num", kes);

        return  query.exec();}
QSqlQueryModel* sal::afficher()
{
   QSqlQueryModel* model=new QSqlQueryModel();
   model->setQuery("SELECT* FROM TABLE1");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("num"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("emplacement"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("capacite"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("etat"));


   return model;
}
QSqlQueryModel * sal ::trinum()
    {
     QSqlQueryModel * model= new QSqlQueryModel();
     model->setQuery("select * from TABLE1 order by num");
     return model;
    }
QSqlQueryModel * sal::recherche(QString valeur)
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT* FROM TABLE1 where num='"+valeur+"'");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("num"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("emplacement"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("capacite"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("etat"));

    return model;

}
QSqlQueryModel* sal::tricap()
{
 QSqlQueryModel * model= new QSqlQueryModel();
 model->setQuery("select * from TABLE1 order by capacite");
 return model;
}





