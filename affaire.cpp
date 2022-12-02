#include "affaire.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QMessageBox>
Affaire::Affaire()
{
   id=0; nom=""; type=""; etat=""; jour=0; mois=0; annees=0;
}

Affaire::Affaire(int id,QString nom,QString type,QString etat,int jour,int mois,int annees)
{this->id=id; this->nom=nom; this->etat=etat; this->type=type; this->jour=jour; this->mois=mois; this->annees=annees;}
int Affaire::getid(){return id;}
QString Affaire::getnom(){return nom;}
QString Affaire::getetat(){return etat;}
QString Affaire::getype(){return type;}
int Affaire:: getjour(){return jour;}
int Affaire:: getmois(){return mois;}
int Affaire:: getannees(){return annees;};
void Affaire::setid(int id){this->id=id;}
void Affaire::setnom(QString nom){this->nom=nom;}
void Affaire::setetat(QString etat){this->etat=etat;}
void Affaire::settype(QString type){this->type=type;}
void Affaire::setjour(int jour){this->jour=jour;}
void Affaire:: setmois(int mois){this->mois=mois;}
void Affaire::setannees(int annees){this->annees=annees;}
bool Affaire::ajouter()
{
    QString id_string=QString::number(id);
    QString jour_string=QString::number(jour);
    QString mois_string=QString::number(mois);
    QString annees_string=QString::number(annees);
    QSqlQuery query;
         query.prepare("INSERT INTO affaire (id, nom, etat, type, jour, mois, annees)"
                       "values(:id, :nom, :etat, :type, :jour, :mois, :annees)");
         query.bindValue(":id", id_string);
         query.bindValue(":nom", nom);
         query.bindValue(":etat", etat);
         query.bindValue(":type", type);
         query.bindValue(":jour", jour_string);
         query.bindValue(":mois", mois_string);
         query.bindValue(":annees", annees_string);
         return query.exec();
}

bool Affaire::supprimer(long id)
{

    QSqlQuery query;
    QMessageBox msgbox;
    QString res=QString::number(id);
    if(query.exec("select * from affaire where id='"+res+"'"))
     { int count=0;
         while(query.next())
             count++;
         if(count!=0)
         {
    query.prepare("delete from affaire where id=:id ");
    query.bindValue(":id", res);
         }
         else
             QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                                      QObject::tr("L'identifiant n'existe pas\n"
                                                  "Click cancel to exit."),
                                      QMessageBox::Cancel);
    }
    return query.exec();
}
QSqlQueryModel* Affaire::afficher()
{
   QSqlQueryModel* model=new QSqlQueryModel();

     model->setQuery("SELECT*  FROM affaire");
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("Etat"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("Type"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("jour"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("mois"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("annees"));

    return model;
}

bool Affaire::update()
{
    QSqlQuery query;
    QString id_string=QString::number(id);
    QString jour_string=QString::number(jour);
    QString mois_string=QString::number(mois);
    QString annees_string=QString::number(annees);
    query.prepare("update affaire set id=:id, nom=:nom, etat=:etat, type=:type, jour=:jour, mois=:mois, annees=:annees where id=:id");
    query.bindValue(":id", id_string);
    query.bindValue(":nom", nom);
    query.bindValue(":etat", etat);
    query.bindValue(":type", type);
    query.bindValue(":jour", jour_string);
    query.bindValue(":mois", mois_string);
    query.bindValue(":annees", annees_string);


    return query.exec();


}

QSqlQueryModel * Affaire::rechercheid(QString valeur)
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT* FROM affaire where id='"+valeur+"'");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("etat"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("type"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("jour"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("mois"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("annees"));

    return model;

}

QSqlQueryModel * Affaire::recherchernom(QString valeur)
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT* FROM affaire where nom='"+valeur+"'");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("etat"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("type"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("jour"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("mois"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("annees"));

    return model;

}

QSqlQueryModel * Affaire::triid()
    {
     QSqlQueryModel * model= new QSqlQueryModel();
     model->setQuery("select * from affaire order by id");
     return model;
    }

QSqlQueryModel * Affaire::trietat()
    {
     QSqlQueryModel * model= new QSqlQueryModel();
     model->setQuery("select * from affaire order by etat");
     return model;
    }

QSqlQueryModel * Affaire::trietype()
    {
     QSqlQueryModel * model= new QSqlQueryModel();
     model->setQuery("select * from affaire order by type");
     return model;
    }

int Affaire::statistique(QString departement)
{
    QSqlQuery query;
    query.prepare("select count(*) from affaire where type=:type ");
    query.bindValue(":type",departement);
    query.exec();

    int count =-1;

            while(query.next())
                    {
                        count = query.value(0).toInt() ;
                        return count;

                    }

    return count;

}


