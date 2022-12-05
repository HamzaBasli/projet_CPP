#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <mainwindow.h>

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();


private slots:
    void on_valider_clicked();

private:
    Ui::login *ui;
    MainWindow *m;
};

#endif // LOGIN_H
