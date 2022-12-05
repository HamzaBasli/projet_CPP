QT       += gui sql axcontainer printsupport
QT       += gui printsupport charts serialport network core


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT +=core gui serialport

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    affaire.cpp \
    arduino.cpp \
    avocat.cpp \
    connexion.cpp \
    employe.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    sal.cpp

HEADERS += \
    affaire.h \
    arduino.h \
    avocat.h \
    calendrier.h \
    connexion.h \
    employe.h \
    fichierexel.h \
    login.h \
    mainwindow.h \
    sal.h

FORMS += \
    login.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

STATECHARTS += \
    emp .scxml \
    statistic.scxml
