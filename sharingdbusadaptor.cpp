#include "sharingdbusadaptor.h"
#include "QDebug"
#include <vector>

#define FILE_PLACE "\%file"

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
    // TODO: check that appname is registered
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
        // TODO: return error
        return QStringList();
    }
}

void SharingDBusAdaptor::addOpenWay(QString appname, QString str) {

    if (!registeredApps.contains(appname)) {
        // TODO: throw error
        return;
    }


    if (!str.contains(FILE_PLACE)) {
        // TODO: return error
        return;
    } else {
        appToOpen[appname] = str;
        return;
    }
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
    return result.replace(QString(FILE_PLACE), file);
}

