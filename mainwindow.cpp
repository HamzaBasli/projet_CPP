#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "affaire.h"
#include <QMessageBox>
#include <QIntValidator>
#include <iostream>
#include "connection.h"
#include <QString>
#include <QPainter>
#include <QPrinter>
#include <QPdfWriter>
#include <QFileDialog>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChartView>
#include <QTcharts>
#include <QChartView>
#include <QPieSeries>
#include <QPieSlice>
#include "fichierexel.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->le_id_2->setValidator(new QIntValidator(0,9999999,this));
    ui->lineEdit_jour->setValidator(new QIntValidator(0,99,this));
    ui->lineEdit_mois->setValidator(new QIntValidator(0,99,this));
    ui->lineEdit_annees->setValidator(new QIntValidator(0,9999,this));
    ui->tab_affaires->setModel(A.afficher());

    int ret=Ar.connect_arduino(); // lancer la connexion à arduino
          switch(ret){
          case(0):qDebug()<< "arduino is available and connected to : "<< Ar.getarduino_port_name();
              break;
          case(1):qDebug() << "arduino is available but not connected to :" <<Ar.getarduino_port_name();
             break;
          case(-1):qDebug() << "arduino is not available";
          }
           QObject::connect(Ar.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_supprimer_clicked()
{
    Affaire A1; A1.setid(ui->le_id_supp_2->text().toInt());
    bool test=A1.supprimer(A1.getid());
    QMessageBox msgbox;
    if(test)
    {
        msgbox.setText("Suppression avec succes.");
        ui->tab_affaires->setModel(A.afficher());
    }
    else
        msgbox.setText("Echec de suppression.");
        msgbox.exec();
}

void MainWindow::on_pushbutton_clicked()
{
    int id=ui->le_id_2->text().toInt();
    QString nom=ui->le_nom_2->text();
    QString etat=ui->le_etat_2->text();
    QString type=ui->le_type_3->text();
    int jour=ui->lineEdit_jour->text().toInt();
    int mois=ui->lineEdit_mois->text().toInt();
    int annees=ui->lineEdit_annees->text().toInt();
    Affaire A(id,nom,type,etat,jour,mois,annees);
    bool test=A.ajouter();
    if(test)
        {
          ui->tab_affaires->setModel(A.afficher());

           QMessageBox::information(nullptr, QObject::tr("OK"),
                                    QObject::tr("Ajout effectué\n"
                                                "Click cancel to exit."),
                                    QMessageBox::Cancel);
        }
        else
            QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                                     QObject::tr("Ajout non effectué\n"
                                                 "Click cancel to exit."),
                                     QMessageBox::Cancel);
}

void MainWindow::on_pushButton_update_clicked()
{
    int id=ui->le_id_2->text().toInt();
    QString nom=ui->le_nom_2->text();
    QString etat=ui->le_etat_2->text();
    QString type=ui->le_type_3->text();
    int jour=ui->lineEdit_jour->text().toInt();
    int mois=ui->lineEdit_mois->text().toInt();
    int annees=ui->lineEdit_annees->text().toInt();
    Affaire A(id,nom,type,etat,jour,mois,annees);
    bool test=A.update();
    if(test)
        {
         ui->tab_affaires->setModel(A.afficher());

           QMessageBox::information(nullptr, QObject::tr("OK"),
                                    QObject::tr("mise a jour effectuée\n"
                                                "Click cancel to exit."),
                                    QMessageBox::Cancel);
        }
        else
            QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                                     QObject::tr("mise a jour non effectuée\n"
                                                 "Click cancel to exit."),
                                     QMessageBox::Cancel);


}

void MainWindow::on_pushButton_clicked()
{
    Affaire A;
    QString valeur=ui->lineEdit_recherche->text();
    QString Atype=ui->comboBox_2->currentText();
    if(Atype=="ID")
        ui->tab_affaires->setModel(A.rechercheid(valeur));
    else
        if(Atype=="Nom")
            ui->tab_affaires->setModel(A.recherchernom(valeur));
}





void MainWindow::on_pushButton_trie_clicked()
{
    Affaire A;
    QString Atype=ui->comboBox->currentText();
    if(Atype=="ID")

        ui->tab_affaires->setModel(A.triid());

    else
        if(Atype=="Etat")

            ui->tab_affaires->setModel(A.trietat());

        else
            if(Atype=="Type")

                ui->tab_affaires->setModel(A.trietype());

}

int MainWindow::createPDF()
{
    QPrinter printer;
         QString id=ui->le_id_2->text();
         QString nom=ui->le_nom_2->text();
         QString etat=ui->le_etat_2->text();
         QString type=ui->le_type_3->text();
         QString jour=ui->lineEdit_jour->text();
         QString mois=ui->lineEdit_mois->text();
         QString annees=ui->lineEdit_annees->text();
          printer.setOutputFormat(QPrinter::PdfFormat);
          printer.setOutputFileName("fishier_affaires.pdf");
          QPainter painter;
          QImage image(":/image/tribunal.jpg");
          if (! painter.begin(&printer)) { // failed to open file
              qWarning("failed to open file, is it writable?");
              return 1;
          }
          painter.drawImage(-40,-40,image);
          painter.drawText(10, 10, "identifiant");
          painter.drawText(100, 10,id);
          painter.drawText(10, 30, "nom");
          painter.drawText(100, 30,nom);
          painter.drawText(10, 50,"etat");
          painter.drawText(100, 50,etat);
          painter.drawText(10, 70,"type");
          painter.drawText(150, 70,type);
          painter.drawText(10,90,"jour");
          painter.drawText(100, 90,jour);
          painter.drawText(10, 110,"mois");
          painter.drawText(100, 110,mois);
          painter.drawText(10, 130,"annees");
          painter.drawText(100, 130,annees);

          if (! printer.newPage()) {
              qWarning("failed in flushing page to disk, disk full?");
              return 1;
          }
          int question = QMessageBox::question(this, "voulez vous afficher le fichier PDF", "PDF Enregistré:Voulez vous l'Afficher?", QMessageBox::Yes |  QMessageBox::No);
                                          if (question == QMessageBox::Yes)
                                          {
                                              QDesktopServices::openUrl(QUrl::fromLocalFile("fishier_affaires.pdf"));

                                              painter.end();
                                          }
          painter.end();
}

void Affaire::calendrier(QTextCharFormat f,QCalendarWidget * w)
{
    QDate date;
    QSqlQuery query("SELECT jour,mois,annees FROM affaire");
    while (query.next())
    {
        date.setDate(query.value(2).toInt(),query.value(1).toInt(),query.value(0).toInt());
        w->setDateTextFormat(date,f);
    }
}



void MainWindow::on_export_fichier_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                    tr("Excel Files (*.xls)"));
    if (fileName.isEmpty())
        return;

    fichierExel obj(fileName, "mydata", ui->tab_affaires);

    //colums to export
    obj.addField(0, "entier", "char(20)");
    obj.addField(1, "reel", "char(20)");
    obj.addField(2, "combobox", "char(20)");
    obj.addField(3, "lineedit", "char(20)");
    obj.addField(4, "textedit", "char(20)");
    obj.addField(5, "dateedit", "char(20)");
    obj.addField(5, "timeedit", "char(20)");


    int retVal = obj.export2Excel();
    if( retVal > 0)
    {
        QMessageBox::information(this, tr("Done"),
                                 QString(tr("%1 records exported!")).arg(retVal)
                                 );
    }
}

void Affaire::stat()
{
    int id=0; QString nom=""; QString type=""; QString etat=""; int jour=0; int mois=0; int annees=0;

     Affaire A(id,nom,type,etat,jour,mois,annees);




       QPieSeries *series = new QPieSeries();
       series->setHoleSize(0.35);

       QPieSlice *slice = series->append("administratif", A.statistique("administratif"));

       slice->setExploded();
       slice->setLabelVisible();
       series->append("penale", A.statistique("penale"));
       series->append("civile", A.statistique("civile"));

       QChart *chart = new QChart();
       chart->addSeries(series);
       chart->setAnimationOptions(QChart::SeriesAnimations);
       chart->setTitle("statistiques par departement");
       chart->setTheme(QChart::ChartThemeBlueIcy);


       QChartView *chartview = new QChartView(chart);
       chartview->setRenderHint(QPainter::Antialiasing);

       chartview->setParent(ui->horizontalFrame);
}
