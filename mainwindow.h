#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<avocat.h>
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


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pb_ajouter_clicked();

    void on_pb_supp_clicked();

    void on_pb_trier_clicked();

    void on_le_rechercher_textChanged();

    void on_le_pdf_clicked();

    void on_le_statique_clicked();

private:
    Ui::MainWindow *ui;
    Avocat A ;
};

#endif // MAINWINDOW_H
