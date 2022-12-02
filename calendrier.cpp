#include "calendrier.h"

#include "calendrier.h"
#include <QFormLayout>
#include "affaire.h"
#include <QMessageBox>

Calendrier::Calendrier(QWidget *parent) :
    QWidget(parent)
{
    butjour = new QPushButton("Planning d'Aujourd'hui");
    butmois = new QPushButton("Planning de ce mois");
    datepers = new QDateEdit();
    datepers->setDisplayFormat("dd:MM:yyyy");
    datepers->setDisabled(true);
    pers = new QRadioButton("Personnalisé :");
    pers->setChecked(false);
    QFormLayout *lay= new QFormLayout();
    lay->addRow(butjour);
    lay->addRow(butmois);
    lay->addRow(pers);
    lay->addRow(("Date RDV :"),datepers);
    butvalider = new QPushButton("Valider");
    butvalider->setDisabled(true);
    lay->addRow(butvalider);
    this->setLayout(lay);
    QObject::connect(pers,SIGNAL(clicked(bool)),this,SLOT(Clickpers()));
    QObject::connect(butjour,SIGNAL(clicked(bool)),this,SLOT(Clickjour()));
    QObject::connect(butmois,SIGNAL(clicked(bool)),this,SLOT(Clickmois()));
    QObject::connect(butvalider,SIGNAL(clicked(bool)),this,SLOT(ClickValider()));
}

void Calendrier::Clickpers()
{
    if(pers->isChecked())
    {
        datepers->setDisabled(false);
        butvalider->setDisabled(false);
    }
    else
    {
        datepers->setDisabled(true);
        butvalider->setDisabled(true);
    }
}

void Calendrier::ClickValider()
{
    if(datepers->date().operator >=(QDate::currentDate()))
    {
        Affaire *gesaffaire = new Affaire("cabinet_med","127.0.0.1","root","");
        QSqlQueryModel *m = new QSqlQueryModel();
        m = gesaffaire->CalendrierPers(datepers->date());
        if(!m->lastError().isValid())
        {
            Affaire *rechres = new Affaire();
            rechres->setModelTableView(m);
            rechres->show();
        }
        else
        {
            QMessageBox *alerte= new QMessageBox() ;
            alerte->setText("Erreur ");
            alerte->show();
        }
    }
}

void Calendrier::Clickjour()
{
    Affaire *gesaffaire = new Affaire("cabinet_med","127.0.0.1","root","");
    QSqlQueryModel *m = new QSqlQueryModel();
    m = gesaffaire->CalendrierAjourdhui();
    if(!m->lastError().isValid())
    {
        Affaire *rechres = new Affaire();
        rechres->setModelTableView(m);
        rechres->show();
    }
    else
    {
        QMessageBox *alerte= new QMessageBox() ;
        alerte->setText("Erreur ");
        alerte->show();
    }
}

void Calendrier::Clickmois()
{
    Affaire *gescabmed = new Affaire("tab_affaire","127.0.0.1","root","");
    QSqlQueryModel *m = new QSqlQueryModel();
    m = gescabmed->CalendrierMois();
    if(!m->lastError().isValid())
    {
        Affaire *rechres = new Affaire();
        rechres->setModelTableView(m);
        rechres->show();
    }
    else
    {
        QMessageBox *alerte= new QMessageBox() ;
        alerte->setText("Erreur ");
        alerte->show();
    }
}

Calendrier::~Calendrier()
{

}
