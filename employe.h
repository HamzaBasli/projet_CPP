#ifndef EMPLOYE_H
#define EMPLOYE_H

#include <QString>
#include<QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QTableWidget>
class employe
{public:
        employe();
        employe(int ,QString ,int ,int ,QString ,QString );

        QString getnometprenom ();
        int getCIN ();
        QString getposte ();
        int getid();
        int getdat ();
        QString getsexe();
        void setnometprenom(QString);
        void setCIN (int);
        void setposte(QString);
        void setid(int);
        void setdat(int);
        void setsexe(QString);
        bool ajouter();

        QSqlQueryModel *afficher();
        bool supprimer(int);
        bool modifier();
        QSqlQueryModel * trier(QString x);
        QSqlQueryModel * rechercher(QString a);
        int sexeH();
        int sexeF();



private:
        int CIN,id,dat,RPM;
        QString nometprenom,poste,sexe;
        void on_pushButton_readRPM_clicked();
};

#endif // EMPLOYÉ_H
