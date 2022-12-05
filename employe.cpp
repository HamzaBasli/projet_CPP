#include "employe.h"
#include <QtDebug>
#include <QtSql/QSqlQuery>


employe::employe()
{
    CIN=id=dat=0;
    nometprenom=poste=sexe="";
}

employe::employe(int CIN, QString nometprenom, int id, int dat, QString poste, QString sexe)
{
    this->CIN=CIN;
    this->nometprenom=nometprenom;
    this->id=id;
    this->dat=dat;
    this->poste=poste;
    this->sexe=sexe;
}

int employe::getCIN(){return CIN;}
QString employe::getnometprenom(){return nometprenom;}
int employe::getdat(){return dat;}
int employe::getid(){return id;}
QString employe::getposte(){return poste;}
QString employe::getsexe(){return sexe;}
void employe::setid(int id){this->id=id;}
void employe::setCIN(int CIN){this->CIN=CIN;}
void employe::setdat(int dat){this->dat=dat;}
void employe::setnometprenom(QString nometprenom){this->nometprenom=nometprenom;}
void employe::setposte(QString poste){this->poste=poste;}
void employe::setsexe(QString sexe){this->sexe=sexe;}


bool employe::ajouter()
{
QSqlQuery query;
    QString id_string=QString::number(id);
    QString CIN_string=QString::number(CIN);
    QString dat_string=QString::number(dat);
     query.prepare("INSERT INTO employé (CIN, id, dat,nometprenom,sexe,poste) "
                   "VALUES (:CIN, :id, :dat,:nometprenom,:sexe,:poste)");
     query.bindValue(":CIN", CIN_string);
     query.bindValue(":id", id_string);
     query.bindValue(":dat", dat_string);
     query.bindValue(":nometprenom", nometprenom);

     query.bindValue(":sexe", sexe);
     query.bindValue(":poste", poste);

     return query.exec();
}
bool employe::supprimer(int CINs)
{
    QSqlQuery query;
    QString res=QString::number(CINs);
    query.prepare("delete from employé where CIN= :CINs");
    query.bindValue(":CINs",res);
    return query.exec();
}
QSqlQueryModel *employe::afficher()
{
        QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from employé");
    model ->setHeaderData(0,Qt::Horizontal,QObject::tr("CIN"));
    model ->setHeaderData(1,Qt::Horizontal,QObject::tr("ID"));
    model ->setHeaderData(2,Qt::Horizontal,QObject::tr("DAT"));
    model ->setHeaderData(3,Qt::Horizontal,QObject::tr("NOMETPRENOM"));
    model ->setHeaderData(4,Qt::Horizontal,QObject::tr("SEXE"));
    model ->setHeaderData(5,Qt::Horizontal,QObject::tr("POSTE"));
    return model;
}
bool employe::modifier()
{
QSqlQuery query;
 QString string_CIN=QString::number(CIN);
  QString string_id=QString::number(id);
   QString string_dat=QString::number(dat);
query.prepare("UPDATE EMPLOYé SET CIN=:CIN,nometprenom=:nometprenom,id=:id,dat=:dat,poste=:poste,sexe=:sexe where CIN=:CIN");
query.bindValue(":CIN", string_CIN);
query.bindValue(":nometprenom", nometprenom);
query.bindValue(":id", string_id);
query.bindValue(":dat", string_dat);
query.bindValue(":poste", poste);
query.bindValue(":sexe", sexe);
return    query.exec();
}

QSqlQueryModel *employe::trier(QString x)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    qDebug()<<x<<endl;
    if(x=="nometprenom")
        model->setQuery("select cin,nometprenom,id,dat,poste,sexe from employé order by nometprenom");
    else if(x=="CIN")
        model->setQuery("select cin,nometprenom,id,dat,poste,sexe from employé order by CIN");
    else if (x=="id")
        model->setQuery("select cin,nometprenom,id,dat,poste,sexe from employé order by id");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nometprenom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("dat"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("poste"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("sexe"));

        return model;
}
QSqlQueryModel* employe::rechercher(QString a)
{
    QSqlQueryModel * query=new QSqlQueryModel();

    query->setQuery("select * from employé where CIN like '%"+a+"%' ");
    return    query;
}
int employe :: sexeH()
{
    QSqlQuery query;
    query.prepare("select COUNT(*) from employé where sexe='homme'");
    query.exec();
    while(query.next())
    {
       return query.value(0).toInt();
    }
}

int employe :: sexeF()
{
    QSqlQuery query;
    query.prepare("select COUNT(*) from employé where sexe='femme'");
    query.exec();
    while(query.next())
    {
       return query.value(0).toInt();
    }
}


