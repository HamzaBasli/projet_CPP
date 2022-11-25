#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <ard.h>

#include <QMainWindow>
#include <sal.h>
#include <QPieSeries>
#include<QChart>
#include<QPieSlice>

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


private:
    Ui::MainWindow *ui;
    sal S;
    QByteArray data; // variable contenant les données reçues

    ard A;
};
#endif // MAINWINDOW_H
