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


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
     ui->le_num->setValidator (new QIntValidator(0, 9999999, this));
     ui->tab_salle->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
     ui->tab_salle->setModel(S.afficher());
     sal tmp;
     int ret=A.connect_arduino(); // lancer la connexion à arduino
     switch(ret){
     case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
         break;
     case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
        break;
     case(-1):qDebug() << "arduino is not available";
     }
      QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(on_tmp_butt_clicked())); // permet de lancer
      //le slot update_label suite à la reception du signal readyRead (reception des données).
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

    data=A.read_from_arduino();
        QMessageBox msg;

        if(data<="25.0")
        { msg.setText("temperature parfaite");
           }
        else
            msg.setText("ouvrez lzs climatiseurs");
        msg.exec();

}

