#include "mainwindow.h"
#include <QMessageBox>
#include <QApplication>
#include "connexion.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connexion c;
    bool test=c.createConnexion();
    MainWindow w;

    w.show();
    if (test)
    {
        w.show();
        QMessageBox::information(nullptr , QObject::tr("connexion est ouverte"),
        QObject::tr("connexion successful"));
    }
    return a.exec();
}
