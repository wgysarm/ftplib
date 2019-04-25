#include "ftpplugin.h"
#include <QThread>
#include <QDebug>
//Q_EXPORT_PLUGIN2( FTPPlugin, FTPPlugin )

FTPPlugin::FTPPlugin(QObject *parent) : QObject(parent)
{
    Server = new FTPServer();
}

QString FTPPlugin::Name() const
{
    return "FTP Server Plugin";
}

QString FTPPlugin::Description() const
{
    return "Allows remote file transfers.";
}

QString FTPPlugin::Status() const
{
    QString ret = "Unknown";

    if(Server->isListening())
    {
        ret = "Started";
    }
    else
    {
        ret = "Stopped";
    }

    return ret;
}

QString FTPPlugin::Install() const
{
    return "Complete";
}

QString FTPPlugin::Uninstall() const
{
    return "Complete";
}

QString FTPPlugin::Start() const
{
    qDebug() << "-----------FTPPlugin::Start()-------"<< QThread::currentThread();
    AppSettings Settings;//this point the settings to /Settings.ini file

    Settings.beginGroup(Settings.DefaultGroup());
    QVariant vPort = Settings.value("port");
    Settings.endGroup();

    Server->StartServer(vPort.toUInt());

    return Status();
}

QString FTPPlugin::Stop() const
{
    Server->StopServer();

    return Status();
}

QStringList FTPPlugin::Commands() const
{
    QStringList List;
    List.append("setusername (username) - Sets the username for the ftp server.");
    List.append("setpassword (password) - Sets the password for the ftp server.");
    List.append("setport (port) - Sets the port to run the telnet server on.");

    return List;
}

QString FTPPlugin::Exec(QString command, QStringList args) const
{

    return "not implimented";
}

