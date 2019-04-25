#include "ftpserver.h"

FTPServer::FTPServer(QObject *parent)
{
}

void FTPServer::StartServer(qint16 port)
{ 
    if(!this->listen(QHostAddress::Any,port))
    {
        qDebug() << "Could not start ftp server";
    }
    else
    {
        qDebug() << "FTP Server Listening  on port " << port;

        //notify connected objects
        emit OnStarted();
    }
}

void FTPServer::StopServer()
{
    this->close();
    qDebug() << "Server stopped";

    //notify connected objects
    emit OnStopped();
}

void FTPServer::incomingConnection(qintptr handle)
{
    qDebug() << "FTPServer::incomingConnection Connecting..." << handle;

    //Accept the incomming client
    FTPDataSocket *cClient = new FTPDataSocket(handle,this);
    connect(this,SIGNAL(OnStopped()),cClient,SLOT(CloseSocket()));
}
