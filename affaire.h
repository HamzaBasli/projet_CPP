#ifndef AFFAIRE_H
#define AFFAIRE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QCalendarWidget>
#include <QTextCharFormat>

class Affaire
{
public:
    Affaire();
    Affaire(int,QString,QString,QString,int,int,int);
    int getid();
    QString getnom();
    QString getetat();
    QString getype();
    int getjour();
    int getmois();
    int getannees();
    void setid(int);
    void setnom(QString);
    void setetat(QString);
    void settype(QString);
    void setjour(int);
    void setmois(int);
    void setannees(int);
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(long);
    bool update();
    QSqlQueryModel* rechercheid(QString valeur);
    QSqlQueryModel* recherchernom(QString valeur);
    QSqlQueryModel* triid();
    QSqlQueryModel* trietat();
    QSqlQueryModel* trietype();
    void calendrier(QTextCharFormat f,QCalendarWidget * w);
    int statistique(QString departement);
    void stat();



private:
 QString nom,etat,type;
 int id,jour,mois,annees;
};

#endif // AFFAIRE_H
