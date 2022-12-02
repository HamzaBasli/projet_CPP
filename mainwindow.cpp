#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "avocat.h"
#include <QMessageBox>
#include <QIntValidator>
#include<QPainter>
#include<QPdfWriter>
#include <QtCharts/QChartView>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
QT_CHARTS_USE_NAMESPACE
#include <QTextStream>
#include <QPieSeries>
#include<QChart>
#include<QPieSlice>
#include<QVBoxLayout>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
      ui->le_id->setValidator(  new QIntValidator(0,9999999 , this));
      ui->tab_avocat->setModel(A.afficher() );


}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_ajouter_clicked()
{
    int id=ui->le_id->text().toInt() ;
    int cin=ui->le_cin->text().toInt() ;
    int nbrcas=ui->le_nbrcas->text().toInt() ;
    QString nom=ui->le_nom->text();
    QString prenom=ui->le_prenom->text();
    QString typecas=ui->le_typecas->text();
    Avocat A(id,cin,nbrcas,nom,prenom,typecas);


bool test=A.ajouter();
QMessageBox msgBox ;
   if (test)
    {


       msgBox.setText(("Ajout avec succes"));
           ui->tab_avocat->setModel(A.afficher());
           }
           else
            msgBox.setText(("Echec d'ajout"));
msgBox.exec();

   }


void MainWindow::on_pb_supp_clicked()
{

    Avocat A1; A1.setid(ui->le_id_supp->text().toInt());
       bool test=A1.supprimer(A1.getid());
       QMessageBox msgBox;
       if(test)
       {
           msgBox.setText("Supprimer avec succes .");
           ui->tab_avocat->setModel(A.afficher());

       }
       else
           msgBox.setText("Echec de suppression ");
       msgBox.exec();
}

void MainWindow::on_pb_trier_clicked()
{
    Avocat A;
                 ui->tab_avocat->setModel(A.tri_identifiant());
                QMessageBox::information(nullptr, QObject::tr("Ok"),
                     QObject::tr("tri effectué.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);
                    ui->tab_avocat->setModel(A.tri_identifiant());

}


void MainWindow::on_le_rechercher_textChanged()
{
    QString rech=ui-> le_rechercher ->text();
        ui->tab_avocat->setModel(A .Recherche(rech));

}



void MainWindow::on_le_pdf_clicked()
{

    QString id=ui->le_id->text();
       QString cin=ui->le_cin->text();
        QString nom=ui->le_nom->text();
        QString prenom=ui->le_prenom->text();
        QString nbrcas=ui->le_nbrcas->text();
        QString typecas=ui->le_typecas->text();
        QPdfWriter pdf("C:/Users/eyabe/OneDrive/Bureau/Atelier_Connexion/pdf.pdf");
        QPainter painter(&pdf);
        painter.setPen(Qt::red);
      painter.drawText(4000,400,"avocat ce N:"+id+"");
        painter.setPen(Qt::black);
        painter.drawText(4000,400,"avocat ce N:"+cin+"");
        painter.drawText(3000,1500,"nom:"+nom+"");
        painter.drawText(2000,1000,"prenom:"+prenom+"");
        painter.drawText(2000,1000,"nbrcas:"+nbrcas+"");
        painter.drawText(8000,5000,"typecas:"+typecas+"");

        painter.end();




}

void MainWindow::on_le_statique_clicked()
{
             QPieSeries * series1 = new QPieSeries();

             series1->append("typecas",300);

             series1->append("cin",100);

             series1->append("id",50);

             QChart * chart1=new QChart();

             chart1->addSeries(series1);

             chart1->setTitle("statistique");

             QChartView * chartView1=new QChartView(chart1);

             chartView1->setRenderHints(QPainter::Antialiasing);
             QVBoxLayout *layout1 = new QVBoxLayout(ui->le_widget);
             layout1->addWidget(chartView1);

}
