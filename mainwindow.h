#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QDoubleValidator>
#include "accuse.h"
#include <QtCharts/QLineSeries>
#include<QtCharts>
#include<QPieSeries>
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

    void on_pushButton_tri_clicked();

    void on_pdf_clicked();

    void on_lineEdit_windowIconTextChanged(const QString &iconText);

    void on_pushButton_statistique_clicked();

    void on_pushButton_insererimage_clicked();

    void on_pushButton_qr_code_clicked();

    void on_pushButton_excel_clicked();

private:
    Ui::MainWindow *ui;
    Accuse A;
};
#endif // MAINWINDOW_H
