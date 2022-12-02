#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "accuse.h"
#include <QIntValidator>
#include<QIntValidator>
#include <QMessageBox>
#include"connexion.h"
#include <QPixmap>
#include <QLabel>
#include <QTextStream>
#include <QTextDocument>
#include <QPdfWriter>
#include <QPainter>
#include <QPieSeries>
#include<QChart>
#include<QPieSlice>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tab_accuse->setModel(A.afficher());

}

MainWindow::~MainWindow()
{
    delete ui;

}


//for ajouter


void MainWindow::on_pb_ajouter_clicked()
{
 QString id=ui->le_id->text();
    QString cin=ui->le_cin->text();
    QString nom=ui->le_nom->text();
    QString prenom=ui->le_prenom->text();
    QString avocat=ui->avocat->text();
    QString type_de_crime=ui->type_de_crime->text();


    Accuse A(id,cin,nom,prenom,avocat,type_de_crime);
    bool test=A.ajouter();
    QMessageBox msgBox;
    if(test)
    {
        msgBox.setText(("Ajout avec succes"));
     ui->tab_accuse->setModel(A.afficher());
    }
    else
        msgBox.setText(("Echec d'ajout"));
    msgBox.exec();
}

//for supprimer


void MainWindow::on_pb_supprimer_clicked()
{
    Accuse A1; A1.setidentifiant(ui->le_id->text());
    bool test=A1.supprimer(A1.getidentifiant());
    QMessageBox msgBox;
    if(test)
    {
        msgBox.setText("Supprimer avec succes .");
        ui->tab_accuse->setModel(A.afficher());

    }
    else
        msgBox.setText("Echec de suppression ");
    msgBox.exec();

}
// for modifier
void MainWindow::on_pb_modifier_clicked()
{
QString id=ui->le_id->text();
    QString cin=ui->le_cin->text();
    QString nom=ui->le_nom->text();
    QString prenom=ui->le_prenom->text();
    QString avocat=ui->avocat->text();
    QString type_de_crime=ui->type_de_crime->text();


        Accuse A(id,cin,nom,prenom,avocat,type_de_crime);

        bool test=A.modifier();

        if(test)
        {
           ui->tab_accuse->setModel(A.afficher());
            QMessageBox::information(nullptr, QObject::tr("OK"),
                        QObject::tr("Modification effectuée.\n"
                                    "Click Cancel to exit."), QMessageBox :: Cancel);
        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("not OK"),
                        QObject::tr("Modification non effectuée.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }
}

//for tri

void MainWindow::on_pushButton_tri_clicked()
{

       Accuse A;
             ui->tab_accuse->setModel(A.tri_identifiant());
            QMessageBox::information(nullptr, QObject::tr("Ok"),
                 QObject::tr("tri effectué.\n"
                             "Click Cancel to exit."), QMessageBox::Cancel);
                ui->tab_accuse->setModel(A.tri_identifiant());




}

// for pdf


void MainWindow::on_pdf_clicked()
{
   QString id=ui->le_id->text();
   QString cin=ui->le_cin->text();
    QString nom=ui->le_nom->text();
    QString prenom=ui->le_prenom->text();
    QString avocat=ui->avocat->text();
    QString type_de_crime=ui->type_de_crime->text();
    QPdfWriter pdf("C:/Users/ghofrane/Documents/Gestion_Accuse/pdf.pdf");
    QPainter painter(&pdf);
    painter.setPen(Qt::red);
  painter.drawText(4000,400,"accuse ce N:"+id+"");
    painter.setPen(Qt::black);
    painter.drawText(4000,400,"accuse ce N:"+cin+"");
    painter.drawText(3000,1500,"nom:"+nom+"");
    painter.drawText(2000,1000,"prenom:"+prenom+"");
    painter.drawText(2000,1000,"avocat:"+avocat+"");
    painter.drawText(8000,5000,"type_de_crime:"+type_de_crime+"");

    painter.end();

}

void MainWindow::on_pushButton_statistique_clicked()
{/*
    QPieSeries * series1 = new QPieSeries();

         series1->append("crime",300);

         series1->append("DELIT",10);

         series1->append("CONTRAVENTION",10);

         QChart * chart1=new QChart();

         chart1->addSeries(series1);

         chart1->setTitle("statistique");

         QChartView * chartView1=new QChartView(chart1);

         chartView1->setRenderHints(QPainter::Antialiasing);
         QVBoxLayout *layout1 = new QVBoxLayout(ui->tabWidget);
         layout1->addWidget(chartView1);
*/
    QSqlQueryModel * model= new QSqlQueryModel();
                model->setQuery("select * from ACCUSE where IDENTIFIANT >= 100");
                float dispo1=model->rowCount();

                model->setQuery("select * from ACCUSE where IDENTIFIANT <100");
                float dispo=model->rowCount();

                float total=dispo1+dispo;
                    QString a=QString(" crime. " +QString::number((dispo1*100)/total,'f',2)+"%" );
                    QString b=QString(" delit et contravention.  "+QString::number((dispo*100)/total,'f',2)+"%" );
                    QPieSeries *series = new QPieSeries();
                    series->append(a,dispo1);
                    series->append(b,dispo);
                if (dispo1!=0)
                {QPieSlice *slice = series->slices().at(0);
                    slice->setLabelVisible();
                    slice->setPen(QPen());}
                if ( dispo!=0)
                {
                    QPieSlice *slice1 = series->slices().at(1);
                    slice1->setLabelVisible();
                }

                QChart *chart = new QChart();

                chart->addSeries(series);
                chart->setTitle("type des accuse  par rapport nombre d'id : "+ QString::number(total));
                chart->legend()->hide();

                QChartView *chartView = new QChartView(chart);
                chartView->setRenderHint(QPainter::Antialiasing);
                chartView->resize(1000,500);
                chartView->show();


}
/*
void MainWindow::on_pushButton_statistique_clicked()
{

QBarSet *set0=new QBarSet("altuve");
         QBarSet *set1=new QBarSet("martinez");
         QBarSet *set2=new QBarSet("segura");
         QBarSet *set3=new QBarSet("simons");
         QBarSet *set4=new QBarSet("trout");

         *set0 <<283<<341<<313<<338<<346<<335;
         *set1 <<250<<315<<282<<307<<303<<330;
         *set2 <<294<<346<<357<<319<<300<<325;
         *set3 <<248<<244<<265<<281<<278<<313;
         *set4 <<323<<287<<299<<315<<306<<313;

         QBarSeries *Series=new QBarSeries();
         Series->append(set0);
         Series->append(set1);
         Series->append(set2);
         Series->append(set3);
         Series->append(set4);

         QChart *chart=new QChart();
         chart->addSeries(Series);
         chart->setTitle("batting avg by type_de_crime");
         //no animation
         chart->setAnimationOptions(QChart::AllAnimations);
         QStringList categories;
         categories<<"2013"<<"2014"<<"2015"<<"2016"<<"2017";
        QBarCategoryAxis *axis=new  QBarCategoryAxis();
        axis->append(categories);
        chart->createDefaultAxes();
        //chart->setAxisX(axis,Series);
        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignBottom);


        QChartView *chartview=new QChartView(chart) ;
        chartview->setRenderHint(QPainter::Antialiasing);

        QVBoxLayout *layout2 = new QVBoxLayout(ui->tabWidget);
        layout2->addWidget(chartview);
}
*/

void MainWindow::on_pushButton_insererimage_clicked()
{
    QFileDialog dialog(this);
            dialog.setNameFilter(tr("Images (*.png *.xpm *.jpg)"));
            dialog.setViewMode(QFileDialog::Detail);
            QString fileName = QFileDialog::getOpenFileName(this,
               tr("Open Images"), "", tr("Image Files (*.png *.jpg *.bmp)"));
            if (!fileName.isEmpty())
            {
                 QImage image(fileName);
                 ui->label_9->setPixmap(QPixmap::fromImage(image));

            }


}


void MainWindow::on_pushButton_qr_code_clicked()
{
    QDesktopServices::openUrl(QUrl("https://qrcode.tec-it.com/fr"));
    QString filename = QFileDialog::getSaveFileName(this,tr("choose"),"",tr("Image(*.png )"));
    if (QString::compare(filename,QString()) !=0)
    {
        QImage image;
        bool valid = image.load(filename);
        if(valid)
        {
            image=image.scaledToWidth(ui->label_10->width(), Qt::SmoothTransformation);
                    ui->label_10->setPixmap(QPixmap::fromImage(image));
        }
        else
        {
            //ERROR HANDLING
        }
    }
}

void MainWindow::on_pushButton_excel_clicked()
{/*
    QString fileName = QFileDialog::getSaveFileName(this, tr("Exportation en fichier Excel"), qApp->applicationDirPath (),
                                                                tr("Fichiers d'extension Excel (*.xls)"));
                if (fileName.isEmpty())
                    return;

                Exel obj(fileName, "mydata", ui->tab_accuse);

                // you can change the column order and
                // choose which colum to export
                obj.addField(0, "id", "char(20)");
                obj.addField(1, "cin", "char(20)");
                obj.addField(2, "nom", "char(20)");
                obj.addField(2, "PRENOM", "char(20)");
                obj.addField(3, "avocat", "char(20)");
                obj.addField(4, "type_de_crime", "char(20)");



                int retVal = obj.export2Excel();

                if( retVal > 0)
                {
                    QMessageBox::information(this, tr("FAIS!"),
                                             QString(tr("%1 enregistrements exportés!")).arg(retVal)
                                             );
                }
                */
}
