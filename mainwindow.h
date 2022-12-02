#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "affaire.h"
#include "arduino.h"

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

    void on_pb_supprimer_clicked();

    void on_pushbutton_clicked();

    void on_pushButton_update_clicked();

    void on_pushButton_clicked();

    void on_pushButton_trie_clicked();

    void on_export_excel_clicked();

    void on_export_fichier_clicked();

private:
    Ui::MainWindow *ui;
    Affaire A;
    arduino Ar;
    QByteArray data;
public slots:
    int createPDF();
};

#endif // MAINWINDOW_H
