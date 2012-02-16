QT += network jsonstream

INCLUDEPATH += $$PWD

PUBLIC_HEADERS += \
  $$PWD/process.h \
  $$PWD/processfrontend.h \
  $$PWD/processbackend.h \
  $$PWD/processbackendfactory.h \
  $$PWD/processbackendmanager.h \
  $$PWD/matchdelegate.h \
  $$PWD/rewritedelegate.h \
  $$PWD/gdbrewritedelegate.h \
  $$PWD/infomatchdelegate.h \
  $$PWD/keymatchdelegate.h \
  $$PWD/processinfo.h \
  $$PWD/processmanager.h \
  $$PWD/standardprocessbackendfactory.h \
  $$PWD/prelaunchprocessbackendfactory.h \
  $$PWD/remoteprocessbackendfactory.h \
  $$PWD/pipeprocessbackendfactory.h \
  $$PWD/socketprocessbackendfactory.h \
  $$PWD/unixprocessbackend.h \
  $$PWD/standardprocessbackend.h \
  $$PWD/prelaunchprocessbackend.h \
  $$PWD/remoteprocessbackend.h \
  $$PWD/processmanager-global.h \
  $$PWD/launcherclient.h \
  $$PWD/pipelauncher.h \
  $$PWD/socketlauncher.h \
  $$PWD/procutils.h \
  $$PWD/remoteprotocol.h

HEADERS += \
  $$PUBLIC_HEADERS \
  $$PWD/unixsandboxprocess.h

SOURCES += \
  $$PWD/process.cpp \
  $$PWD/processfrontend.cpp \
  $$PWD/processbackend.cpp \
  $$PWD/processbackendfactory.cpp \
  $$PWD/processbackendmanager.cpp \
  $$PWD/matchdelegate.cpp \
  $$PWD/rewritedelegate.cpp \
  $$PWD/gdbrewritedelegate.cpp \
  $$PWD/infomatchdelegate.cpp \
  $$PWD/keymatchdelegate.cpp \
  $$PWD/processinfo.cpp \
  $$PWD/processmanager.cpp \
  $$PWD/unixprocessbackend.cpp \
  $$PWD/standardprocessbackendfactory.cpp \
  $$PWD/standardprocessbackend.cpp \
  $$PWD/unixsandboxprocess.cpp \
  $$PWD/prelaunchprocessbackendfactory.cpp \
  $$PWD/prelaunchprocessbackend.cpp \
  $$PWD/remoteprocessbackend.cpp \
  $$PWD/remoteprocessbackendfactory.cpp \
  $$PWD/pipeprocessbackendfactory.cpp \
  $$PWD/socketprocessbackendfactory.cpp \
  $$PWD/launcherclient.cpp \
  $$PWD/pipelauncher.cpp \
  $$PWD/socketlauncher.cpp \
  $$PWD/procutils.cpp
