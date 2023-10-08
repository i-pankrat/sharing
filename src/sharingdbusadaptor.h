#ifndef __SHARINGDBUSADAPTOR_H__
#define __SHARINGDBUSADAPTOR_H__

#include <vector>

#include <QtDBus/QDBusAbstractAdaptor>

class SharingDBusAdaptor : public QDBusAbstractAdaptor {
    Q_OBJECT;

    Q_CLASSINFO("D-Bus Interface", "ru.pankrat.Sharing");
    Q_CLASSINFO("D-Bus Introspection",
        ""
        "  <interface name=\"ru.i-pankrat.Sharing\">\n"
        "    <method name=\"registerApp\">\n"
        "      <arg direction=\"in\" type=\"s\" name=\"appname\"/>\n"
        "    </method>\n"
        "    <method name=\"getRegisteredApps\">\n"
        "      <arg direction=\"out\" type=\"as\"/>\n"
        "    </method>\n"
        "    <method name=\"addFileType\">\n"
        "      <arg direction=\"in\" type=\"s\" name=\"appname\"/>\n"
        "      <arg direction=\"in\" type=\"s\" name=\"filetype\"/>\n"
        "    </method>\n"
        "    <method name=\"getAvailableFileTypes\">\n"
        "      <arg direction=\"in\" type=\"s\" name=\"appname\"/>\n"
        "      <arg direction=\"out\" type=\"as\"/>\n"
        "    </method>\n"
        "    <method name=\"addOpenWay\">\n"
        "      <arg direction=\"in\" type=\"s\" name=\"appname\"/>\n"
        "      <arg direction=\"in\" type=\"s\" name=\"str\"/>\n"
        "    </method>\n"
        "    <method name=\"addOpenWay\">\n"
        "      <arg direction=\"in\" type=\"s\" name=\"appname\"/>\n"
        "      <arg direction=\"in\" type=\"s\" name=\"filetype\"/>\n"
        "      <arg direction=\"in\" type=\"s\" name=\"file\"/>\n"
        "      <arg direction=\"out\" type=\"s\"/>\n"
        "    </method>\n"
        "  </interface>\n"
        "");

public:
    explicit SharingDBusAdaptor(QObject *parent);

public Q_SLOTS:
    void registerApp(QString appname);
    QStringList getRegisteredApps();
    void addFileType(QString appname, QString filetype);
    QStringList getAvailableFileTypes(QString appname);
    void addOpenWay(QString appname, QString str);
    QString open(QString appname, QString filetype, QString file);

Q_SIGNALS:

private:
    QMap<QString, QStringList> appToFileTypes;
    QMap<QString, QString> appToOpen;
};

#endif