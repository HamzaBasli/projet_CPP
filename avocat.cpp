#include "avocat.h"
 #include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include<QPainter>
#include<QPdfWriter>


Avocat::Avocat()
{
cin=0 ; id=0; nbrcas=0; nom=" "; prenom=" "; typecas=" ";
}
 Avocat :: Avocat(int id , int cin,int nbrcas,QString prenom,QString nom,QString typecas )
{ this->id=id ; this->cin=cin ;this->nbrcas=nbrcas;
 this->nom=nom; this->prenom=prenom; this->typecas=typecas; }


 int  Avocat::getcin () {return cin;}

 int Avocat::getid () {return id;}

 int Avocat::getnbrcas () {return nbrcas ;}

 QString Avocat:: getnom() { return nom;}

 QString Avocat:: getprenom () {return prenom ;}

 QString Avocat ::gettypecas (){return typecas ;};



 void Avocat :: setcin (int cin ) {this->cin=cin;}
 void Avocat :: setid (int id) {this->id=id ;}
 void Avocat :: setnbrcas (int nbrcas){this->nbrcas=nbrcas ;}
 void Avocat :: setnom(QString nom) {this->nom=nom ;}
 void Avocat ::setprenom(QString prenom) {this->prenom=prenom ;}
 void Avocat :: settypecas (QString typecas ){this->typecas=typecas ;}



 bool Avocat::ajouter()

 {

     QSqlQuery query;
     QString id_string=QString::number(id);
     QString cin_string=QString::number(cin);
     QString nbrcas_string=QString::number(nbrcas);


           query.prepare("INSERT INTO  AVOCATS (id, nom ,cin, prenom, nbrcas , typecas) "
                         "VALUES (:id, :nom, :cin, :prenom , :nbrcas , :typecas)");
           query.bindValue(0, id_string);
           query.bindValue(1, nom);
           query.bindValue(2, cin_string);
           query.bindValue(3, prenom);
           query.bindValue(4, nbrcas_string);
           query.bindValue(5, typecas);
        return   query.exec();
 }






 bool Avocat::supprimer(int id )
 {
     QSqlQuery query ;
         query.prepare(("Delete from Avocats where id=:id"));
         query.bindValue(0,id);
         query.bindValue(1,nom);
         query.bindValue(2,cin);
         query.bindValue(3,prenom);
         query.bindValue(4,nbrcas);
         query.bindValue(5,typecas);
        // query.bindValue(6,remarque);
         return query.exec();

 }






QSqlQueryModel * Avocat::afficher()
{

    QSqlQueryModel * model=new QSqlQueryModel();

       //  QSqlQueryModel* model=new QSqlQueryModel();
              model->setQuery("SELECT * FROM Avocats");
              model->setHeaderData(0, Qt::Horizontal, QObject:: tr("id"));//ajouter header data ajouter le nom de colone du tableau
              model->setHeaderData(1, Qt::Horizontal, QObject:: tr("nom"));
              model->setHeaderData(2, Qt::Horizontal, QObject:: tr("cin"));
              model->setHeaderData(3, Qt::Horizontal, QObject:: tr("prenom"));
              model->setHeaderData(4, Qt::Horizontal, QObject:: tr("nbrcas"));
              model->setHeaderData(5, Qt::Horizontal, QObject:: tr("typecas"));

        return  model;
}





QSqlQueryModel * Avocat ::tri_identifiant ()
    {
    QSqlQueryModel * model= new QSqlQueryModel();

        model->setQuery("select * from Avocats order by id");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("nom"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("cin"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("nbrcas"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("typecas"));

       return model;
    }






QSqlQueryModel* Avocat ::Recherche (QString recherche)
 {
     QSqlQueryModel * model= new QSqlQueryModel();
     model->setQuery("SELECT * FROM Avocats WHERE id LIKE '"+recherche+"%' OR cin LIKE '"+recherche+"%' OR nom LIKE '"+recherche+"%'");
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("cin"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("prenom"));
     model->setHeaderData(4, Qt::Horizontal, QObject::tr("nbrcas"));
     model->setHeaderData(5, Qt::Horizontal, QObject::tr("typecas"));

return model;
}


