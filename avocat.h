 #ifndef AVOCAT_H
#define AVOCAT_H

#include<QString>
#include<QSqlQueryModel>
#include<QPainter>
#include<QPdfWriter>





class Avocat
{
public:
    Avocat();
    Avocat(int , int,int,QString,QString,QString);
     int getcin ();
     int getid ();
     int getnbrcas ();
     QString getnom();
     QString getprenom () ;
     QString gettypecas ();
     void setcin (int );
     void setid (int);
     void setnbrcas (int);
     void setnom(QString);
     void setprenom(QString);
     void settypecas (QString);
     bool ajouter();

QSqlQueryModel *afficher();

bool supprimer(int);

QSqlQueryModel* tri_identifiant();

QSqlQueryModel* RechercheR(QString);

 void genererPDFact();

private :
    int cin , id , nbrcas ;
    QString nom , prenom,typecas;
};

#endif // AVOCAT_H
