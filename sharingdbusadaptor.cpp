#include "sharingdbusadaptor.h"
#include "QDebug"
#include "QDBusMessage"
#include "QDBusConnection"
#include "QDBusError"
#include <vector>

#define SB_FILE_PLACE "\%file"

SharingDBusAdaptor::SharingDBusAdaptor(QObject *parent) :
    QDBusAbstractAdaptor(parent) {
}

void SharingDBusAdaptor::registerApp(QString appname) {
    registeredApps.append(appname);
    return;
}

QStringList SharingDBusAdaptor::getRegisteredApps() {
    return registeredApps;
}

void SharingDBusAdaptor::addFileType(QString appname, QString filetype) {
    if (appToFileTypes.contains(appname)) {
        appToFileTypes[appname].append(filetype);
    } else {
        appToFileTypes[appname] = QStringList(filetype);
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

    if (!registeredApps.contains(appname)) {
        return;
    }

    if (str.contains(SB_FILE_PLACE)) {
        appToOpen[appname] = str;
    }

    return;
}

QString SharingDBusAdaptor::open(QString appname, QString filetype, QString file) {
    if (!registeredApps.contains(appname)) {
        qDebug() << "app is not registered";
        // TODO: throw error
        return QString("");
    }

    if (!appToOpen.contains(appname)) {
        // TODO: throw error
        qDebug() << "app does not provide way to open files";
        return QString("");
    }

    if (!appToFileTypes[appname].contains(filetype)) {
        // TODO: throw error
        qDebug() << "app does not support such filetype";
        return QString("");
    }

    auto result = appToOpen[appname];
    return result.replace(QString(SB_FILE_PLACE), file);
}

