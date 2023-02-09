QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Model.cpp \
    Xenemy.cpp \
    Xenemyview.cpp \
    main.cpp \
    controller.cpp \
    mainwindow.cpp \
    modelview.cpp \
    normalennemyview.cpp \
    penemyview.cpp \
    poisonoustile.cpp \
    poisonoustileview.cpp \
    potionview.cpp \
    protagonistview.cpp \
    mapview.cpp \
    pathfinding.cpp \
    textscene.cpp \
    player_view.cpp
    textscene.cpp


HEADERS += \
    Model.h \
    Xenemy.h \
    Xenemyview.h \
    mainwindow.h \
    modelview.h \
    normalennemyview.h \
    penemyview.h \
    poisonoustile.h \
    poisonoustileview.h \
    potionview.h \
    protagonistview.h \
    tile_struct.h \
    #world.h \
    controller.h \
    #world_global.h \
    mapview.h \
    pathfinding.h \
    textscene.h \
    player_view.h



    textscene.h

FORMS += \
    mainwindow.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

unix:!macx: LIBS += -L$$PWD/../MP-FA-Library/ -lworld

INCLUDEPATH += $$PWD/../MP-FA-Library
DEPENDPATH += $$PWD/../MP-FA-Library




RESOURCES += \
    resources.qrc

DISTFILES += \
    world_images/amongus.png \
    world_images/bomb.png \
    world_images/empty.jpg \
    world_images/mario.jpeg \
    world_images/potion.png

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../worldlibfinal/release/ -lworld
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../worldlibfinal/debug/ -lworld

INCLUDEPATH += $$PWD/../../worldlibfinal/release
DEPENDPATH += $$PWD/../../worldlibfinal/release
