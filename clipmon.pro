QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
DEFINES *= QT_USE_QSTRINGBUILDER

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
	src/ClipHelper.cpp \
	src/ClipHelper.cpp \
	src/ClipList.cpp \
	src/ClipMimeData.cpp \
	src/Clipboard.cpp \
    src/ItemBase.cpp \
	src/Preview.cpp \
	src/PreviewScene.cpp \
	src/Tray.cpp \
	src/Utils.cpp \
        src/ClipListItem.cpp \
	src/item/HtmlItem.cpp \
	src/item/ImageItem.cpp \
    src/item/TextItem.cpp \
        src/main.cpp \
        src/MainWindow.cpp

HEADERS += \
	src/ClipHelper.h \
	src/ClipHelper.h \
	src/ClipList.h \
	src/ClipMimeData.h \
	src/Clipboard.h \
    src/ItemBase.h \
	src/Preview.h \
	src/PreviewScene.h \
	src/Tray.h \
	src/Utils.h \
        src/ClipListItem.h \
        src/Global.h \
        src/MainWindow.h \
	src/item/HtmlItem.h \
	src/item/ImageItem.h \
    src/item/TextItem.h

TRANSLATIONS += \
	i18n\clipmon_en_US.ts

DISTFILES += \
	.gitignore

INCLUDEPATH += \
	src

DEPENDPATH += \
	src

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
