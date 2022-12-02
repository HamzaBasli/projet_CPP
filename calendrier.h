#ifndef CALENDRIER_H
#define CALENDRIER_H


#include <QPushButton>
#include <QDateEdit>
#include <QRadioButton>
#include <QWidget>


class Calendrier: public QWidget
{
    Q_OBJECT

public:
    explicit Calendrier(QWidget *parent = 0);
       ~Calendrier();
public slots:
    void Clickpers();
    void Clickjour();
    void Clickmois();
    void ClickValider();

private:
       QPushButton *butjour;
       QPushButton *butmois;
       QDateEdit *datepers ;
       QRadioButton *pers ;
       QPushButton *butvalider;
};

#endif // CALENDRIER_H
