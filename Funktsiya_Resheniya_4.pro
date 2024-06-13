QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    dialog.cpp

HEADERS += \
    dialog.h

FORMS += \
    dialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
//###########################################################################
######################################################################################################## отладка
#QMAKE_CXXFLAGS += -fsanitize=undefined
#QMAKE_CXXFLAGS += -g -fsanitize=address -fno-omit-frame-pointer
#LIBS += -lubsan
##To enable, e.g., address sanitizer you have to write:
#CONFIG += sanitizer sanitize_address
#CONFIG+=address_sanitizer
//###########################################################################
#QMAKE_CXXFLAGS += -fsanitize=address
#QMAKE_LDFLAGS += -fsanitize=address
#QMAKE_CXXFLAGS=-fsanitize=memory
#CONFIG += sanitizer sanitize_undefined
//###########################################################################
#CONFIG+=sanitizer 
//###########################################################################
# по одному включать:
#CONFIG+=sanitize_memory
CONFIG+=sanitize_address
#CONFIG+=sanitize_thread
#CONFIG+=sanitize_undefined
#sanitize_address
#sanitize_memory
#sanitize_thread
#sanitize_undefined






