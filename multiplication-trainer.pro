# Add files and directories to ship with the application 
# by adapting the examples below.
# file1.source = myfile
# dir1.source = mydir
DEPLOYMENTFOLDERS = # file1 dir1

# If your application uses the Qt Mobility libraries, uncomment
# the following lines and add the respective components to the 
# MOBILITY variable. 
# CONFIG += mobility
# MOBILITY +=

SOURCES += main.cpp mainwindow.cpp \
    game.cpp \
    scoreform.cpp
HEADERS += mainwindow.h \
    game.h \
    scoreform.h
FORMS += mainwindow.ui \
    scoreform.ui

# Please do not modify the following two lines. Required for deployment.
include(deployment.pri)
qtcAddDeployment()

maemo5 {
    desktopfile.files = multiplication-trainer.desktop
    desktopfile.path = /usr/share/applications/hildon
    INSTALLS += desktopfile
}

maemo5 {
    icon.files = multiplication-trainer.png
    icon.path = /usr/share/icons/hicolor/64x64/apps
    INSTALLS += icon
}
