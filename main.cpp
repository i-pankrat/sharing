#include <QCoreApplication>
#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusConnectionInterface>
#include <QtDebug>

#include "sharingdbusadaptor.h"

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    SharingDBusAdaptor sharing(&app);

    auto dbusConnection = QDBusConnection::sessionBus();
    if (!dbusConnection.isConnected()) {
        qDebug() << "can not connect to dbus";
        return 1;
    }

    if (!dbusConnection.registerService("ru.pankrat.Sharing")) {
        qDebug() << "can not reg service";
        return 1;
    }
    qInfo() << "service registered...";

    if (!dbusConnection.registerObject("/", &sharing, QDBusConnection::ExportAllSlots)) {
        qDebug() << "can not reg object";
        return 1;
    }

    qInfo() << "object registered...";

    qInfo() << "waiting";
    return app.exec();
}