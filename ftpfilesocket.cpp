#include "ftpfilesocket.h"

FTPFileSocket::FTPFileSocket(QObject *parent)
{
    mUploading = false;
    mFilename = "";
}

void FTPFileSocket::ConnectEvents()
{
    try
    {
        //connect the signals
        connect(mSocket,SIGNAL(readyRead()),this,SLOT(SocketReadyRead()),Qt::DirectConnection);
        connect(mSocket,SIGNAL(disconnected()),this,SLOT(SocketDisconnected()),Qt::DirectConnection);
        connect(mSocket,SIGNAL(connected()),this,SLOT(SocketConnected()),Qt::DirectConnection);
    }
    catch(QString err)
    {
        emit OnError(err);
    }
    catch(...)
    {
        emit OnError("Unknown error in ConnectEvents()");
    }
}

bool FTPFileSocket::isConnected()
{
    try
    {
        if(!mSocket) qDebug() << "Socket is NULL!";

        if(mSocket->state() == QTcpSocket::ConnectedState)
        {
            qDebug() << "isConnected = true";
            return true;
        }
        else
        {
            qDebug() << "isConnected = false";
            return false;
        }
    }
    catch(QString err)
    {
        emit OnError(err);
        return false;
    }
    catch(...)
    {
        emit OnError("Unknown error in isConnected()");
        return false;
    }
}

void FTPFileSocket::ConnectTo(FTPPort &PortInfo)
{
    try
    {
        mSocket = new QTcpSocket(this);

        //connect the signals
        ConnectEvents();

        qDebug() << "-- File Socket Connecting to --" << PortInfo.IPAddress() << ":" << PortInfo.Port();

        //Connect to the remote computer
        mSocket->connectToHost(PortInfo.IPAddress(),PortInfo.Port());
        mSocket->waitForConnected();

        qDebug() << "-- File Socket State --" << mSocket->state();
        qDebug() << "-- File Socket Error String --" << mSocket->errorString();
    }
    catch(QString err)
    {
        emit OnError(err);
    }
    catch(...)
    {
        emit OnError("Unknown error in ConnectTo()");
    }
}

void FTPFileSocket::ListenFor(FTPPort &PortInfo, QString IPAddress)
{
    try
    {
        //Pick a random port and start listening
        if(listen(QHostAddress::Any))
        {
            //We found an open port, update the port info
            PortInfo.SetIPAddress(IPAddress);
            PortInfo.SetPort(serverPort());

            //Let connected objects know we are listening
            emit OnListening();
        }
        else
        {
            emit OnError("File socket is not listening!");
        }
    }
    catch(QString err)
    {
        emit OnError(err);
    }
    catch(...)
    {
        emit OnError("Unknown error in ListenFor()");
    }
}

void FTPFileSocket::Upload(QString Filename, qint64 Position)
{
    try
    {
        //Set the transfer variables
        mUploading = true;
        mFilename = Filename;

        //Truncate the file if needed
        if(Position > 0)
        {
            QFile file(mFilename);
            if(!file.resize(Position))
            {
                emit OnError("File could not be truncated!");
                return;
            }
        }

        //Wait for data to come in - see SocketReadyRead()
    }
    catch(QString err)
    {
        emit OnError(err);
    }
    catch(...)
    {
        emit OnError("Unknown error in Upload()");
    }
}

void FTPFileSocket::Download(QString Filename, qint64 Position)
{
    try
    {
        //Set the transfer variables
        mUploading = false;
        mFilename = Filename;

        //Open the file
        QFile file(Filename);

        if(!file.open(QFile::ReadOnly))
        {
            emit OnError("Could not open file!");
            return;
        }

        qDebug() << "*** FileSocket *** " << Filename;

        //Move to the requested position
        if(Position > 0)
        {
            file.seek(Position);
        }

        //Send the contents of the file
        while (!file.atEnd()) {
            QByteArray buffer = file.read(1024 * 8);
            SendResponse(buffer);
        }

        //Close the file
        file.close();

        //Tell connected objects we are done
        emit OnFinished();

        //Close the socket once we are done
        CloseSocket();
    }
    catch(QString err)
    {
        emit OnError(err);
    }
    catch(...)
    {
        emit OnError("Unknown error in Download()");
    }
}

void FTPFileSocket::incomingConnection(int socketDescriptor)
{
    try
    {
        //Clients will connect to the server in passive mode
        mSessionID = socketDescriptor;
        mSocket = new QTcpSocket(this);

        //connect the signals
        ConnectEvents();

        if(!mSocket->setSocketDescriptor(mSessionID))
        {
            qDebug() << "-- File Socket --" << mSessionID << " Error binding socket: " << mSocket->errorString();
            emit OnError("Error binding socket");
        }
        else
        {
            qDebug() << "-- File Socket --" << mSessionID << " session Connected";
            //Let connected objects know we are connected
            emit OnConnected();
        }

        //Stop listing for connections
        this->close();
    }
    catch(QString err)
    {
        emit OnError(err);
    }
    catch(...)
    {
        emit OnError("Unknown error in incomingConnection()");
    }
}

void FTPFileSocket::SocketReadyRead()
{
    try
    {
        //Put the data into the file if the client is uploading
        if(mUploading == true && mFilename != "")
        {
            //for the sake of simplicity we store all files in append mode
            QFile file(mFilename);

            if(!file.open(QFile::Append))
            {
                emit OnError("Could not open file!");
                return;
            }
            //Read the data in from the socket
            QByteArray buffer = mSocket->readAll();

            //Write the data to the file
            file.write(buffer);

            //Close the file incase the connection drops
            file.close();
        }
    }
    catch(QString err)
    {
        emit OnError(err);
    }
    catch(...)
    {
        emit OnError("Unknown error in SocketReadyRead()");
    }
}

void FTPFileSocket::SocketConnected()
{
    try
    {
        //Let connected objects know we are connected
        emit OnConnected();
    }
    catch(QString err)
    {
        emit OnError(err);
    }
    catch(...)
    {
        emit OnError("Unknown error in SocketConnected()");
    }
}


void FTPFileSocket::SocketDisconnected()
{
    try
    {
        qDebug() << "******************** File Socket Disconnected";
        //Let connected objects know we disconnected
        emit OnDisconnected();

        //Cleanup
        mSocket->deleteLater();
        this->deleteLater();
    }
    catch(QString err)
    {
        emit OnError(err);
    }
    catch(...)
    {
        emit OnError("Unknown error in SocketDisconnected()");
    }
}

void FTPFileSocket::SendResponse(QByteArray data)
{
    try
    {
        //qDebug() << "FILE: " << data;
        //Write the data to the socket
        mSocket->write(data);
    }
    catch(QString err)
    {
        emit OnError(err);
    }
    catch(...)
    {
        emit OnError("Unknown error in SendResponse()");
    }
}

void FTPFileSocket::SendResponse(QString data)
{
    try
    {
       SendResponse(data.toLatin1());
    }
    catch(QString err)
    {
        emit OnError(err);
    }
    catch(...)
    {
        emit OnError("Unknown error in SendResponse()");
    }
}

void FTPFileSocket::SendResponse(const char* data)
{
    try
    {
        SendResponse(QString::fromLatin1(data));
    }
    catch(QString err)
    {
        emit OnError(err);
    }
    catch(...)
    {
        emit OnError("Unknown error in ConnectEvents()");
    }
}

void FTPFileSocket::CloseSocket()
{
    //mSocket->waitForBytesWritten();
    mSocket->close();
}

void FTPFileSocket::LIST(QString Path)
{
    try
    {
        //if we are not connected then we have a major problem
        if(!isConnected())
        {
            qDebug() << "!!!!!! FILE SOCKET NOT CONNECTED !!!!!!!!!!";
        }


        //Set the transfer variables
        mUploading = false;
        mFilename = "";

        qDebug() << "SENDING LIST";

        //permissions[space]number?[space]owner[space]group[space]filesize[space]date[space]filename

        QFileInfo fi(Path);

        if(!fi.exists())
        {
            //Not found
            emit OnError("Directory not found");
        }
        else
        {
            //Found
            if(fi.isDir())
            {
                QDir dir(Path);

                //list a directory
                qDebug() << "LIST SEND DIRECTORY";
                foreach(QFileInfo item, dir.entryInfoList())
                {
                    FTPListItem ftpList;
                    SendResponse(ftpList.Convert(item));

                    //mSocket->waitForBytesWritten();
                }
                emit OnFinished();
            }
            else
            {
                //list a single file
                qDebug() << "LIST SEND FILE";
                FTPListItem ftpList;
                SendResponse(ftpList.Convert(fi));
                emit OnFinished();
            }
        }

        //close the socket once we are done
        CloseSocket();

    }
    catch(QString err)
    {
        emit OnError(err);
    }
    catch(...)
    {
        emit OnError("Unknown error in LIST()");
    }
}

void FTPFileSocket::NLST(QString Path)
{

    try
    {
        //if we are not connected then we have a major problem
        if(!isConnected())
        {
            qDebug() << "!!!!!! FILE SOCKET NOT CONNECTED !!!!!!!!!!";
        }

        //Set the transfer variables
        mUploading = false;
        mFilename = "";

        QDir dir(Path);

        if(!dir.exists())
        {
            emit OnError("Directory not found");
        }
        else
        {
            qDebug() << "NLST SEND";
            foreach(QString item, dir.entryList())
            {
                SendResponse(item + "\r\n");
                //mSocket->waitForBytesWritten();
            }
            emit OnFinished();

        }

        //close the socket once we are done
        CloseSocket();
    }
    catch(QString err)
    {
        emit OnError(err);
    }
    catch(...)
    {
        emit OnError("Unknown error in NLST()");
    }
}

void FTPFileSocket::MLSD(QString Path,QString Requested)
{
    try
    {
        //if we are not connected then we have a major problem
        if(!isConnected())
        {
            qDebug() << "!!!!!! FILE SOCKET NOT CONNECTED !!!!!!!!!!";
        }

        //Set the transfer variables
        mUploading = false;
        mFilename = "";


        QFileInfo fi(Path);
        QDir dir(Path);

        if(!fi.exists())
        {
            emit OnError("Directory not found");
        }
        else
        {
            FTPMLSItem mls;

            qDebug() << "MLSD SEND";
            SendResponse(mls.RequestedPath(fi,Requested));

            foreach(QFileInfo item, dir.entryInfoList())
            {

                SendResponse(mls.Convert(item));
            }
            emit OnFinished();

        }

        //close the socket once we are done
        CloseSocket();

    }
    catch(QString err)
    {
        emit OnError(err);
    }
    catch(...)
    {
        emit OnError("Unknown error in MLSD()");
    }
}



