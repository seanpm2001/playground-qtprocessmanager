CONFIG -= app_bundle
QT += processmanagerdeclarative jsonstream

include(../declarative.pri)

DESTDIR = ./
SOURCES = main.cpp
TARGET  = testSocketLauncher

target.path = $$[QT_INSTALL_TESTS]/$$TESTCASE_NAME/testSocketLauncher
INSTALLS += target