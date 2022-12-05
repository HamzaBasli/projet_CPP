#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <ard.h>

#include <QMainWindow>
#include <sal.h>
#include <QPieSeries>
#include<QChart>
#include<QPieSlice>

#include "employe.h"
#include <QtCharts>
#include <QChartView>
#include <QPieSeries>

#include "affaire.h"
#include "avocat.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pb_ajouter_clicked();

    void on_pb_supprimer_clicked();

    void on_pb_modifier_clicked();

    void on_pb_update_clicked();

    void on_rechercher_salle_activated(const QString &arg1);

    void on_tri_salle_activated(const QString &arg1);

    void on_rechercher_salle_currentTextChanged(const QString &arg1);

    void on_rechercher_sal_currentTextChanged(const QString &arg1);

    void on_tri_sal_currentTextChanged(const QString &arg1);

    void on_rech_sal_clicked();

    void on_tri_sal_clicked();

    void on_tri_cap_clicked();

    void on_PDF_clicked();

    void on_pushButton_statistique_clicked();




    void on_tmp_butt_clicked();
    void on_pushButton_ajouter_clicked();
    void on_pushButton_supprimer_clicked();
    void on_pushbutton_modifier_clicked();
    void on_pushbutton_actualiser_clicked();
    void on_pushButton_chercher_clicked();



    void on_pb_supprimer_2_clicked();
    void on_pushbutton_2_clicked();
    void on_pushButton_update_2_clicked();
    void on_pushButton_10_clicked();
    void on_pushButton_trie_2_clicked();


    void on_pb_ajouter_clicked1();

    void on_pb_trier_clicked();

    void on_pb_supp_clicked();

    void on_le_statique_clicked();

    void on_le_pdf_clicked();

    void on_le_rechercher_textChanged();


    void on_pb_ajouter_3_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_16_clicked();
    void on_pushButton_17_clicked();
    void on_pushButton_18_clicked();
    void on_pushButton_19_clicked();

    void on_pb_ajouter_2_clicked();

private:
    Ui::MainWindow *ui;
    sal S;
    QByteArray data; // variable contenant les données reçues

    ard AR;
    employe  Etmp;
    QByteArray RPM;

    Affaire A;
    Avocat AV;
public slots:
    int createPDF();
};
#endif // MAINWINDOW_H
