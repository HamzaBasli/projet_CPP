#include "login.h"
#include "ui_login.h"
#include <QMessageBox>

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;

}
void login::on_valider_clicked()
{
    QString id = ui->id->text();
     QString P = ui->motdepasse->text();
     if (id=="123456789" && P=="court")
     {
         QMessageBox::information(nullptr, QObject::tr("database is open"),
                     QObject::tr("welcome\n"
                                 "Click OK to enter."), QMessageBox::Ok);

         m =new MainWindow(this);
         m->show();

     }

else
     {
QMessageBox::critical(nullptr, QObject::tr("database is open"),
            QObject::tr("wrong admin or password.\n"
                        "Click Cancel to exit."), QMessageBox::Cancel);
     }
}
