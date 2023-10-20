QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addbooks.cpp \
    addstudents.cpp \
    borrownew.cpp \
    browse.cpp \
    deepsearch.cpp \
    deleterecords.cpp \
    details.cpp \
    history.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    mydb.cpp \
    return.cpp \
    studentregistry.cpp

HEADERS += \
    addbooks.h \
    addstudents.h \
    borrownew.h \
    browse.h \
    deepsearch.h \
    deleterecords.h \
    details.h \
    history.h \
    login.h \
    mainwindow.h \
    mydb.h \
    return.h \
    studentregistry.h

FORMS += \
    addbooks.ui \
    addstudents.ui \
    borrownew.ui \
    browse.ui \
    deepsearch.ui \
    deleterecords.ui \
    details.ui \
    history.ui \
    login.ui \
    mainwindow.ui \
    return.ui \
    studentregistry.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES +=

DISTFILES += \
    ../../Library Database/LibraryManagement.db
