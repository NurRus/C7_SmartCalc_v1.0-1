QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    basecalc.c \
    creditcalc.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp \
    rpn.c \
    verification.c \
    work_functions.c
    basecalc.c
    rpn.c
    verification.c
    work_functions.c
    qcustomplot.cpp

HEADERS += \
    creditcalc.h \
    mainwindow.h \
    qcustomplot.h \
    smartcalc.h

FORMS += \
    creditcalc.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
