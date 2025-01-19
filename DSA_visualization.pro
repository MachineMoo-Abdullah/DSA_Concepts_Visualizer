QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    binarytree.cpp \
    binarytreemainwindow.cpp \
    bst_properties_window.cpp \
    circulardoublylinkedlist.cpp \
    circularsinglylinkedlist.cpp \
    doublylinkedlistvisualization.cpp \
    linkedlistvisualization.cpp \
    main.cpp \
    mainwindow.cpp \
    renderarea.cpp \
    stackvisualization.cpp


HEADERS += \
    binarysearchtree.h \
    binarytree.h \
    binarytreemainwindow.h \
    bst_properties_window.h \
    circulardoublylinkedlist.h \
    circularsinglylinkedlist.h \
    doublylinkedlistvisualization.h \
    doublynode.h \
    linkedlistvisualization.h \
    mainwindow.h \
    renderarea.h \
    singlynode.h \
    stackvisualization.h


FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
