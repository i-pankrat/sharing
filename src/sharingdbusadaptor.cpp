#include "sharingdbusadaptor.h"
#include "QDebug"
#include "QDBusMessage"
#include "QDBusConnection"
#include "QDBusError"
#include <vector>

#define SHARING_FILE_PLACE "\%file"

SharingDBusAdaptor::SharingDBusAdaptor(QObject *parent) :
    QDBusAbstractAdaptor(parent) {
}

void SharingDBusAdaptor::registerApp(QString appname) {
    appToFileTypes[appname] = QStringList();
    return;
}

QStringList SharingDBusAdaptor::getRegisteredApps() {
    return appToFileTypes.keys();
}

void SharingDBusAdaptor::addFileType(QString appname, QString filetype) {
    if (appToFileTypes.contains(appname) && !appToFileTypes[appname].contains(filetype)) {
        appToFileTypes[appname].append(filetype);
    }
}

QStringList SharingDBusAdaptor::getAvailableFileTypes(QString appname) {
    if (appToFileTypes.contains(appname)) {
        return appToFileTypes[appname];
    } else {
        return QStringList();
    }
}

void SharingDBusAdaptor::addOpenWay(QString appname, QString str) {
    if (appToFileTypes.contains(appname) && str.contains(SHARING_FILE_PLACE)) {
        appToOpen[appname] = str;
    }
}

QString SharingDBusAdaptor::open(QString appname, QString filetype, QString file) {
    if (!appToFileTypes.contains(appname)) {
        qDebug() << "app is not registered";
        return QString("");
    }

    if (!appToOpen.contains(appname)) {
        qDebug() << "app does not provide way to open files";
        return QString("");
    }

    if (!appToFileTypes[appname].contains(filetype)) {
        qDebug() << "app does not support such filetype";
        return QString("");
    }

    auto result = appToOpen[appname];
    return result.replace(QString(SHARING_FILE_PLACE), file);
}
