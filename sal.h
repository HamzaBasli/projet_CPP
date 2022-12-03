#ifndef SAL_H
#define SAL_H
#include <QString>
#include <QSqlQueryModel>


class sal
{
public:
    sal();
    sal(int,QString,QString,QString);
      sal(int,float);
    int getnum();
    QString getemplacement();
    QString getcapacite();
    QString getetat();
    void setnum(int);
    void setcapacite(QString);
    void setemplacement(QString);
    void setetat(QString);
    bool ajouter();
    bool modifier();
   // bool modifier1(float);
    QSqlQueryModel* afficher();
    bool supprimer(int);
    QSqlQueryModel* recherche(QString);
    QSqlQueryModel* trinum();
    QSqlQueryModel* tricap();

private:

    int num;
    QString emplacement,capacite,etat;
   // float temperature;

};


#endif // SAL_H

