TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    sqlite3.c \
    animal.c

HEADERS += \
    sqlite3.h \
    animal.h

DISTFILES += \
    Practice data base.db
