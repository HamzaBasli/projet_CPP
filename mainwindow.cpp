#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sal.h"
#include <QIntValidator>
#include <QMessageBox>
#include <QPainter>
#include <QDesktopServices>
#include <QUrl>
#include <QPdfWriter>
#include<mail.h>
#include<QFileDialog>

#include <QtDebug>
#include <QPainter>

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
#include<QPrinter>
#include <QtCore>
#include <QPrinter>
#include <QPrintDialog>
#include <QPdfWriter>
#include <QPainter>
#include<QTextDocument>
#include <QSettings>
#include <QPrinter>
#include <QTextStream>
#include <QFile>
#include <QDataStream>

#include <QTextStream>
#include <QDataStream>
#include <QFile>
#include "employe.h"

#include <QIntValidator>
#include <QTableWidget>
#include<QMessageBox>
#include<QObject>
#include <QtSql/QSqlQueryModel>
#include <QMessageBox>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>


#include "affaire.h"
#include <QMessageBox>
#include <QIntValidator>
#include <iostream>
#include <QString>
#include <QPainter>
#include <QPrinter>
#include <QPdfWriter>
#include <QFileDialog>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChartView>
#include <QChartView>
#include <QPieSeries>
#include <QPieSlice>







MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
     ui->le_num->setValidator (new QIntValidator(0, 9999999, this));
     ui->tab_salle->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
     ui->tab_salle->setModel(S.afficher());
     sal tmp;
     int ret=AR.connect_arduino(); // lancer la connexion à arduino
     switch(ret){
     case(0):qDebug()<< "arduino is available and connected to : "<< AR.getarduino_port_name();
         break;
     case(1):qDebug() << "arduino is available but not connected to :" <<AR.getarduino_port_name();
        break;
     case(-1):qDebug() << "arduino is not available";
     }
      QObject::connect(AR.getserial(),SIGNAL(readyRead()),this,SLOT(on_tmp_butt_clicked())); // permet de lancer
      //le slot update_label suite à la reception du signal readyRead (reception des données).


      ui->lineEdit_3->setValidator(new QIntValidator(11111111, 99999999,ui->lineEdit_3 ));
      ui->lineEdit_2->setValidator(new QIntValidator(11111111, 99999999, ui->lineEdit_2));
      ui->table_employe->setModel(Etmp.afficher());
      int h=Etmp.sexeH(),f=Etmp.sexeF();
          QPieSeries *series1 = new QPieSeries();
          series1->append("HOMME",h);
          series1->append("FEMME",f);
          QChart *chart1=new QChart();
          chart1 ->addSeries(series1);
          chart1->setTitle("Sexe");
          QChartView *chartview1=new QChartView(chart1);
          chartview1->setParent(ui->horizontalFrame);



          QPieSeries *series2 = new QPieSeries();
             series2->setHoleSize(0.35);

             QPieSlice *slice = series2->append("administratif", A.statistique("administratif"));

             slice->setExploded();
             slice->setLabelVisible();
             series2->append("penale", A.statistique("penale"));
             series2->append("civile", A.statistique("civile"));

             QChart *chart2 = new QChart();
             chart2->addSeries(series2);
             chart2->setAnimationOptions(QChart::SeriesAnimations);
             chart2->setTitle("statistiques par departement");
             chart2->setTheme(QChart::ChartThemeBlueIcy);


             QChartView *chartview2 = new QChartView(chart2);
             chartview2->setRenderHint(QPainter::Antialiasing);

             chartview2->setParent(ui->horizontalFrame_3);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pb_modifier_clicked()
{}




void MainWindow::on_pb_ajouter_clicked()
{
    int num=ui->le_num->text().toInt();
    QString emplacement=ui->le_emplacement->text();
    QString capacite=ui->la_capacite->text();
    QString etat=ui->l_etat->text();
    sal s(num,emplacement,capacite,etat);
    bool test=s.ajouter();
    if (test)
    { ui->tab_salle->setModel(s.afficher());
        QMessageBox::information(nullptr, QObject::tr("ok"),
                               QObject::tr("ajout effectue.\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);

           }
               else
                   QMessageBox::critical(nullptr, QObject::tr("not ok"),
                               QObject::tr("ajout non effectue.\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);


    }




void MainWindow::on_pb_supprimer_clicked()
{
    sal s1; s1.setnum(ui->nsp->text().toInt());
    bool test=s1.supprimer(s1.getnum());
    QMessageBox msg_box;
    if(test)
       { msg_box.setText("suppression avec succes");
        ui->tab_salle->setModel(s1.afficher());}
    else
        msg_box.setText("echec de suppression");
    msg_box.exec();
}



void MainWindow::on_pb_update_clicked()
{
    int num=ui->le_num->text().toInt();
       QString emplacement=ui->le_emplacement->text();
       QString capacite=ui->la_capacite->text();
       QString etat=ui->l_etat->text();

       sal s(num,emplacement,capacite,etat);

       bool test=s.modifier();

       if(test)
       {
          ui->tab_salle->setModel(s.afficher());
           QMessageBox::information(nullptr, QObject::tr("OK"),
                       QObject::tr("Modification effectuée.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);
       }
       else
       {
           QMessageBox::critical(nullptr, QObject::tr("not OK"),
                       QObject::tr("Modification non effectuée.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);
       }

}

void MainWindow::on_rechercher_salle_activated(const QString &arg1)
{


}

void MainWindow::on_tri_salle_activated(const QString &arg1)
{

}

void MainWindow::on_rechercher_salle_currentTextChanged(const QString &arg1)
{

}


void MainWindow::on_rechercher_sal_currentTextChanged(const QString &arg1)
{

}


void MainWindow::on_tri_sal_currentTextChanged(const QString &arg1)
{

}

void MainWindow::on_rech_sal_clicked()
{
    sal s;
              QString valeur=ui->lineEdit_salle->text();
              ui->tab_salle->setModel(s.recherche(valeur));
}

void MainWindow::on_tri_sal_clicked()
{
    sal s;

      ui->tab_salle->setModel(s.trinum());
}

void MainWindow::on_tri_cap_clicked()
{

}

void MainWindow::on_PDF_clicked()
{

    QString strStream;
                   QTextStream out(&strStream);
                   const int rowCount = ui->tab_salle->model()->rowCount();
                   const int columnCount =ui->tab_salle->model()->columnCount();


                   out <<  "<html>\n"
                           "<head>\n"
                           "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                           <<  QString("<title>%1</title>\n").arg("eleve")
                           <<  "</head>\n"
                           "<body bgcolor=#CFC4E1 link=#5000A0>\n"
                               "<h1>Liste des Evenements</h1>"

                               "<table border=1 cellspacing=0 cellpadding=2>\n";

                   // headers
                       out << "<thead><tr bgcolor=#f0f0f0>";
                       for (int column = 0; column < columnCount; column++)
                           if (!ui->tab_salle->isColumnHidden(column))
                               out << QString("<th>%1</th>").arg(ui->tab_salle->model()->headerData(column, Qt::Horizontal).toString());
                       out << "</tr></thead>\n";
                       // data table
                          for (int row = 0; row < rowCount; row++) {
                              out << "<tr>";
                              for (int column = 0; column < columnCount; column++) {
                                  if (!ui->tab_salle->isColumnHidden(column)) {
                                      QString data = ui->tab_salle->model()->data(ui->tab_salle->model()->index(row, column)).toString().simplified();
                                      out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                  }
                              }
                              out << "</tr>\n";
                          }
                          out <<  "</table>\n"
                              "</body>\n"
                              "</html>\n";



           QTextDocument *document = new QTextDocument();
           document->setHtml(strStream);


           //QTextDocument document;
           //document.setHtml(html);
           QPrinter printer(QPrinter::PrinterResolution);
           printer.setOutputFormat(QPrinter::PdfFormat);
           printer.setOutputFileName("salle.pdf");
           document->print(&printer);

}

void MainWindow::on_pushButton_statistique_clicked()
{

    QPieSeries * series1 = new QPieSeries();

             series1->append("salle 1",50);

             series1->append("salle 2",35);

             series1->append("salle 5",40);
             series1->append("salle 4",40);
             series1->append("salle 8",90);

             QChart * chart1=new QChart();

             chart1->addSeries(series1);

             chart1->setTitle("statistique");

             QChartView * chartView1=new QChartView(chart1);

             chartView1->setRenderHints(QPainter::Antialiasing);
             QVBoxLayout *layout1 = new QVBoxLayout(ui->tabWidget);
             layout1->addWidget(chartView1);




}

void MainWindow::on_tmp_butt_clicked()
{

    data=AR.read_from_arduino();
        QMessageBox msg;

        if(data<="25.0")
        { msg.setText("temperature parfaite");
           }
        else
            msg.setText("ouvrez lzs climatiseurs");
        msg.exec();

}
void MainWindow::on_pushButton_ajouter_clicked()
{
    int CIN=ui->lineEdit_2->text().toInt();
    int id=ui->lineEdit_3->text().toInt();
    int date=ui->lineEdit_9->text().toInt();
    QString nometprenom=ui->lineEdit->text();
    QString poste=ui->lineEdit_4->text();
    QString sexe=ui->lineEdit_8->currentText();
    employe E(CIN,nometprenom,id,date,poste,sexe);
    bool test=E.ajouter();
    if (test)
    {
        ui->table_employe->setModel(Etmp.afficher());//refresh
        int h=Etmp.sexeH(),f=Etmp.sexeF();
            QPieSeries *series = new QPieSeries();
            series->append("HOMME",h);
            series->append("FEMME",f);
            QChart *chart=new QChart();
            chart ->addSeries(series);
            chart->setTitle("Sexe");
            QChartView *chartview=new QChartView(chart);
            chartview->setParent(ui->horizontalFrame);
        QMessageBox::information(nullptr,QObject::tr("ok"),
                              QObject::tr("ajout effectué\n"
                                          "click cancel to exit."),QMessageBox::Cancel);
    }
    else QMessageBox::critical(nullptr,QObject::tr("not ok"),
            QObject::tr("ajout non effectué\n"
                        "click cancel to exit."),QMessageBox::Cancel);


}
void MainWindow::on_pushButton_supprimer_clicked()
{
    int CINs=ui->lineEdit_CINs->text().toInt();
    bool test= Etmp.supprimer(CINs);
    if (test)
    {
        ui->table_employe->setModel(Etmp.afficher());//refresh
        int h=Etmp.sexeH(),f=Etmp.sexeF();
            QPieSeries *series = new QPieSeries();
            series->append("HOMME",h);
            series->append("FEMME",f);
            QChart *chart=new QChart();
            chart ->addSeries(series);
            chart->setTitle("Sexe");
            QChartView *chartview=new QChartView(chart);
            chartview->setParent(ui->horizontalFrame);
        QMessageBox::information(nullptr,QObject::tr("ok"),
                                 QObject::tr("suppression effectueé \n"
                                             "click cancel to exit."),QMessageBox::Cancel);
    }
    else QMessageBox::critical(nullptr,QObject::tr("not ok"),
                               QObject::tr("suppersion non effectue.\n"
                                           "click cancel to exit"),QMessageBox::Cancel);

    }
void MainWindow::on_pushbutton_modifier_clicked()
{
    int CIN=ui->lineEdit_CIN2->text().toInt();
    int id=ui->lineEdit_ide->text().toInt();
    int date=ui->lineEdit_date->text().toInt();
    QString nometprenom=ui->lineEdit_np->text();
    QString poste=ui->lineEdit_poste->text();
    QString sexe=ui->lineEdit_sexe->text();
    employe E(CIN,nometprenom,id,date,poste,sexe);
    bool test=E.modifier();
    if (test)
    {
        ui->table_employe->setModel(Etmp.afficher());//refresh
        int h=Etmp.sexeH(),f=Etmp.sexeF();
            QPieSeries *series = new QPieSeries();
            series->append("HOMME",h);
            series->append("FEMME",f);
            QChart *chart=new QChart();
            chart ->addSeries(series);
            chart->setTitle("Sexe");
            QChartView *chartview=new QChartView(chart);
            chartview->setParent(ui->horizontalFrame);
        QMessageBox::information(nullptr,QObject::tr("ok"),
                              QObject::tr("ajout effectué\n"
                                          "click cancel to exit."),QMessageBox::Cancel);
    }
    else QMessageBox::critical(nullptr,QObject::tr("not ok"),
            QObject::tr("ajout non effectué\n"
                        "click cancel to exit."),QMessageBox::Cancel);

    }
void MainWindow::on_pushbutton_actualiser_clicked()
{

QString critere=ui->comboBox->currentText();
if(critere!="")

    ui->table_employe->setModel(Etmp.trier(critere));
else
    ui->table_employe->setModel(Etmp.afficher());
}
void MainWindow::on_pushButton_chercher_clicked()
{

QString critere=ui->lineEdit_5->text();
if(critere!="")
ui->table_employe->setModel(Etmp.rechercher(critere));

else
ui->table_employe->setModel(Etmp.afficher());

}

void MainWindow::on_pb_supprimer_2_clicked()
{
    Affaire A1; A1.setid(ui->le_id_supp_3->text().toInt());
    bool test=A1.supprimer(A1.getid());
    QMessageBox msgbox;
    if(test)
    {
        msgbox.setText("Suppression avec succes.");
        ui->tab_affaires_2->setModel(A.afficher());
    }
    else
        msgbox.setText("Echec de suppression.");
        msgbox.exec();
}

void MainWindow::on_pushbutton_2_clicked()
{
    int id=ui->le_id_4->text().toInt();
    QString nom=ui->le_nom_4->text();
    QString etat=ui->le_etat_4->text();
    QString type=ui->le_type_6->text();
    int jour=ui->lineEdit_jour_2->text().toInt();
    int mois=ui->lineEdit_mois_2->text().toInt();
    int annees=ui->lineEdit_annees_2->text().toInt();
    Affaire A(id,nom,type,etat,jour,mois,annees);
    bool test=A.ajouter();
    if(test)
        {
          ui->tab_affaires_2->setModel(A.afficher());

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

void MainWindow::on_pushButton_update_2_clicked()
{
    int id=ui->le_id_4->text().toInt();
    QString nom=ui->le_nom_4->text();
    QString etat=ui->le_etat_4->text();
    QString type=ui->le_type_6->text();
    int jour=ui->lineEdit_jour_2->text().toInt();
    int mois=ui->lineEdit_mois_2->text().toInt();
    int annees=ui->lineEdit_annees_2->text().toInt();
    Affaire A(id,nom,type,etat,jour,mois,annees);
    bool test=A.update();
    if(test)
        {
         ui->tab_affaires_2->setModel(A.afficher());

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

void MainWindow::on_pushButton_10_clicked()
{
    Affaire A;
    QString valeur=ui->lineEdit_recherche_2->text();
    QString Atype=ui->comboBox_4->currentText();
    if(Atype=="ID")
        ui->tab_affaires_2->setModel(A.rechercheid(valeur));
    else
        if(Atype=="Nom")
            ui->tab_affaires_2->setModel(A.recherchernom(valeur));
}

void MainWindow::on_pushButton_trie_2_clicked()
{
    Affaire A;
    QString Atype=ui->comboBox_5->currentText();
    if(Atype=="ID")

        ui->tab_affaires_2->setModel(A.triid());

    else
        if(Atype=="Etat")

            ui->tab_affaires_2->setModel(A.trietat());

        else
            if(Atype=="Type")

                ui->tab_affaires_2->setModel(A.trietype());
}
int MainWindow::createPDF()
{
    QPrinter printer;

         QString id=ui->le_id_4->text();
         QString nom=ui->le_nom_4->text();
         QString etat=ui->le_etat_4->text();
         QString type=ui->le_type_6->text();
         QString jour=ui->lineEdit_jour_2->text();
         QString mois=ui->lineEdit_mois_2->text();
         QString annees=ui->lineEdit_annees_2->text();
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


/*void MainWindow::on_pb_ajouter_clicked1()
{
    int id=ui->le_id->text().toInt() ;
    int cin=ui->le_cin->text().toInt() ;
    int nbrcas=ui->le_nbrcas->text().toInt() ;
    QString nom=ui->le_nom->text();
    QString prenom=ui->le_prenom->text();
    QString typecas=ui->le_typecas->text();
    Avocat AV(id,cin,nbrcas,nom,prenom,typecas);


bool test=AV.ajouter();
QMessageBox msgBox ;
   if (test)
    {


       msgBox.setText(("Ajout avec succes"));
           ui->tab_avocat->setModel(AV.afficher());
           }
           else
            msgBox.setText(("Echec d'ajout"));
msgBox.exec();
}*/

void MainWindow::on_pb_trier_clicked()
{
    Avocat AV;
                 ui->tab_avocat->setModel(AV.tri_identifiant());
                QMessageBox::information(nullptr, QObject::tr("Ok"),
                     QObject::tr("tri effectué.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);
                    ui->tab_avocat->setModel(AV.tri_identifiant());

}

void MainWindow::on_pb_supp_clicked()
{
    Avocat A1; A1.setid(ui->le_id_supp->text().toInt());
       bool test=A1.supprimer(A1.getid());
       QMessageBox msgBox;
       if(test)
       {
           msgBox.setText("Supprimer avec succes .");
           ui->tab_avocat->setModel(AV.afficher());

       }
       else
           msgBox.setText("Echec de suppression ");
       msgBox.exec();
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

void MainWindow::on_le_rechercher_textChanged()
{
    QString rech=ui-> le_rechercher ->text();
        //ui->tab_avocat->setModel(A.RechercheR(rech));

}


void MainWindow::on_pushButton_8_clicked()
{
     ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_9_clicked()
{
     ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_pushButton_13_clicked()
{
     ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_pushButton_14_clicked()
{
     ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_16_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}
void MainWindow::on_pushButton_17_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}
void MainWindow::on_pushButton_18_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}
void MainWindow::on_pushButton_19_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_pb_ajouter_2_clicked()
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
