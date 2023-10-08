#ifndef __SHARINGDBUSADAPTOR_H__
#define __SHARINGDBUSADAPTOR_H__

#include <vector>
#include <string>

#include <QtDBus/QDBusAbstractAdaptor>

class SharingDBusAdaptor : public QDBusAbstractAdaptor {
    Q_OBJECT;

    Q_CLASSINFO("D-Bus Interface", "ru.pankrat.Sharing");

public:
    explicit SharingDBusAdaptor(QObject *parent);

public Q_SLOTS:
    void registerApp(QString appname);
    QStringList getRegisteredApps();
    void addFileType(QString appname, QString filetype);
    QStringList getAvailableFileTypes(QString appname);
    void addOpenWay(QString appname, QString st);
    QString open(QString appname, QString filetype, QString file);

Q_SIGNALS:

private:
    QMap<QString, QStringList> appToFileTypes;
    QMap<QString, QString> appToOpen;
};

#endif