#include "ftpdatasocket.h"
#include <QThread>

FTPDataSocket::FTPDataSocket(int SocketDescriptor, QObject *parent) :
    QObject(parent)
{
    try
    {
        qDebug() << "FTPDataSocket::FTPDataSocket current thread is:" << QThread::currentThread();
        LoadResponses();
        LoadSettings();

        mSessionID = SocketDescriptor;

        mSocket = new QTcpSocket(this);
        if(!mSocket->setSocketDescriptor(mSessionID))
        {
            qDebug() << mSessionID << " Error binding socket";
            return;
        }

        //connect the signals
        connect(mSocket,SIGNAL(readyRead()),this,SLOT(SocketReadyRead()),Qt::DirectConnection);
        connect(mSocket,SIGNAL(disconnected()),this,SLOT(SocketDisconnected()),Qt::DirectConnection);

        qDebug() << mSessionID << " session Connected";

        //Send the banner
        SendResponse(GetResponse(220));

    }
    catch(QString err)
    {
        SendResponse(550,err);
    }
    catch(...)
    {
        SendResponse(550,"Unknown error in Constructor()");
    }
}

void FTPDataSocket::LoadResponses()
{
    try
    {
        mResponseCodes.insert(110,"Restart marker reply.");
        mResponseCodes.insert(120,"Service ready in nnn minutes.");
        mResponseCodes.insert(125,"Data connection already open; transfer starting.");
        mResponseCodes.insert(150,"File status okay; about to open data connection.");
        mResponseCodes.insert(200,"Command okay.");
        mResponseCodes.insert(202,"Command not implemented, superfluous at this site.");
        mResponseCodes.insert(211,"System status, nothing to report.");
        mResponseCodes.insert(212,"Directory status.");
        mResponseCodes.insert(213,"End of status.");
        mResponseCodes.insert(214,"Help command successful.");
        mResponseCodes.insert(215,"NAME system type.");
        mResponseCodes.insert(220,"Service ready for new user.");
        mResponseCodes.insert(221,"Service closing control connection.");
        mResponseCodes.insert(225,"Data connection open; no transfer in progress.");
        mResponseCodes.insert(226,"Closing data connection.");
        mResponseCodes.insert(227,"Entering Passive Mode (h1,h2,h3,h4,p1,p2).");
        mResponseCodes.insert(230,"User logged in, proceed.");
        mResponseCodes.insert(250,"Requested file action okay, completed.");
        mResponseCodes.insert(257,"Path was created.");
        mResponseCodes.insert(331,"Password required.");
        mResponseCodes.insert(332,"Need account for login.");
        mResponseCodes.insert(350,"Requested file action pending further information.");
        mResponseCodes.insert(421,"Service not available, closing control connection.");
        mResponseCodes.insert(425,"Can't open data connection.");
        mResponseCodes.insert(426,"Connection closed; transfer aborted.");
        mResponseCodes.insert(450,"Requested file action not taken.");
        mResponseCodes.insert(451,"Requested action aborted: local error in processing.");
        mResponseCodes.insert(452,"Requested action not taken.");
        mResponseCodes.insert(500,"Syntax error, command unrecognized.");
        mResponseCodes.insert(501,"Syntax error in parameters or arguments.");
        mResponseCodes.insert(502,"Command not implemented.");
        mResponseCodes.insert(503,"Bad sequence of commands.");
        mResponseCodes.insert(504,"Command not implemented for that parameter.");
        mResponseCodes.insert(530,"Not logged in.");
        mResponseCodes.insert(532,"Need account for storing files.");
        mResponseCodes.insert(550,"Requested action not taken.");
        mResponseCodes.insert(551,"Requested action aborted: page type unknown.");
        mResponseCodes.insert(552,"Requested file action aborted.");
        mResponseCodes.insert(553,"Requested action not taken.");
        mResponseCodes.insert(550,"The filename, directory name, or volume label syntax is incorrect.");
    }
    catch(QString err)
    {
        SendResponse(550,err);
    }
    catch(...)
    {
        SendResponse(550,"Unknown error in LoadResponses()");
    }
}

void FTPDataSocket::CreateFileSocket()
{
    try
    {
        //Create the file socket
        mFileSocket = new FTPFileSocket(this);

        //Connect the events
        connect(mFileSocket,SIGNAL(OnConnected()),this,SLOT(OnFileConnected()));
        connect(mFileSocket,SIGNAL(OnDisconnected()),this,SLOT(OnFileDisconnected()));
        connect(mFileSocket,SIGNAL(OnError(QString)),this,SLOT(OnFileError(QString)));
        connect(mFileSocket,SIGNAL(OnFinished()),this,SLOT(OnFileFinished()));
        connect(mFileSocket,SIGNAL(OnListening()),this,SLOT(OnFileListening()));
    }
    catch(QString err)
    {
        SendResponse(550,err);
    }
    catch(...)
    {
        SendResponse(550,"Unknown error in CreateFileSocket()");
    }
}

void FTPDataSocket::SocketReadyRead()
{
    try
    {
        //Append to the command buffer
        mCommandBuffer.append(mSocket->readAll());

        //Check to see if it is the end of line
        if(mCommandBuffer.endsWith('\n'))
        {
            ProcessCommand(mCommandBuffer);
            mCommandBuffer.clear();
        }

    }
    catch(QString err)
    {
        SendResponse(550,err);
    }
    catch(...)
    {
        SendResponse(550,"Unknown error in SocketReadyRead()");
    }


}

void FTPDataSocket::SocketDisconnected()
{
    try
    {
        qDebug() << mSessionID << "************************ DISCONNECTED **************************";

        //Cleanup
        mSocket->deleteLater();
        this->deleteLater();
    }
    catch(QString err)
    {
        SendResponse(550,err);
    }
    catch(...)
    {
        SendResponse(550,"Unknown error in SocketDisconnected()");
    }
}

void FTPDataSocket::SendResponse(const char* data)
{

    try
    {
        SendResponse(QString::fromLatin1(data));
    }
    catch(QString err)
    {
        SendResponse(550,err);
    }
    catch(...)
    {
        SendResponse(550,"Unknown error in SendResponse()");
    }
}

void FTPDataSocket::SendResponse(QString data)
{

    try
    {
        SendResponse(data.toLatin1());
    }
    catch(QString err)
    {
        SendResponse(550,err);
    }
    catch(...)
    {
        SendResponse(550,"Unknown error in SendResponse()");
    }
}

void FTPDataSocket::SendResponse(int ResponseCode)
{

    try
    {
        SendResponse(GetResponse(ResponseCode));
    }
    catch(QString err)
    {
        SendResponse(550,err);
    }
    catch(...)
    {
        SendResponse(550,"Unknown error in SendResponse()");
    }
}

void FTPDataSocket::SendResponse(int ResponseCode, QString ResponseText)
{
    try
    {
        QString ret = QString::number(ResponseCode) + " " + ResponseText + "\r\n";
        SendResponse(ret);
    }
    catch(QString err)
    {
        SendResponse(550,err);
    }
    catch(...)
    {
        SendResponse(550,"Unknown error in SendResponse()");
    }

}

void FTPDataSocket::SendResponse(QByteArray data)
{
    try
    {
        qDebug() << "Server: " << data;

        //Send the data to the client
        mSocket->write(data);
        //mSocket->waitForBytesWritten();
    }
    catch(QString err)
    {
        SendResponse(550,err);
    }
    catch(...)
    {
        SendResponse(550,"Unknown error in SendResponse()");
    }

}

void FTPDataSocket::CloseSocket()
{

    try
    {
        // mSocket->waitForBytesWritten();
         mSocket->close();
    }
    catch(QString err)
    {
        SendResponse(550,err);
    }
    catch(...)
    {
        SendResponse(550,"Unknown error in CloseSocket()");
    }
}

int FTPDataSocket::ID()
{
    return mSessionID;
}

QString FTPDataSocket::GetResponse(int ResponseCode)
{
    QString ret = "";

    try
    {
        if(mResponseCodes.contains(ResponseCode))
        {
            ret = QString::number(ResponseCode) + " " + mResponseCodes.value(ResponseCode);
        }
        else
        {
             ret = QString::number(550) + " " + mResponseCodes.value(550);
        }


    }
    catch(QString err)
    {
        SendResponse(550,err);
    }
    catch(...)
    {
        SendResponse(550,"Unknown error in GetResponse()");
    }

    return ret + "\r\n";
}

void FTPDataSocket::ProcessCommand(QString ClientCommand)
{
    try
    {
        //Some clients like to put multiple commands on a single packet command1<crlf>command2<crlf>
        //Bad form yes but we have to deal with it regardless

        QStringList Commands = ClientCommand.split("\n");

        foreach(QString Command, Commands)
        {
            QString ClientCommand = Command.trimmed();
            if(ClientCommand != "")
            {
                //Execute the command
                ExecuteCommand(ClientCommand);
            }
        }
    }
    catch(QString err)
    {
        SendResponse(550,err);
    }
    catch(...)
    {
        SendResponse(550,"Unknown error in ProcessCommand()");
    }
}

void FTPDataSocket::ExecuteCommand(QString ClientCommand)
{
    try
    {
        QString Command = "";
        QString Arg = "";

        if(ClientCommand.contains(" "))
        {
            //Contains arquments
            int pos = ClientCommand.indexOf(" ");
            Command = ClientCommand.mid(0,pos).trimmed();
            Arg = ClientCommand.mid(pos + 1).trimmed();
        }
        else
        {
            //No arquments
            Command = ClientCommand.trimmed();
        }

        qDebug() << "Client: " << Command << " " << Arg;

        QMetaObject metaObject = this->staticMetaObject;
        QMetaEnum metaEnum = metaObject.enumerator(metaObject.indexOfEnumerator("RequestCommands"));

        switch(metaEnum.keysToValue(Command.toUpper().toLatin1()))
        {

            // RFC 959  --------------------------------------------------
            case HELP: // Lists all available commands
            DoHelp();
            break;

            case QUIT: // Log out
            DoQuit();
            break;

            case USER: // Username
            DoUser(Arg);
            break;

            case PASS: // Password
            DoPass(Arg);
            break;

            case ACCT: // Account
            DoACCT(Arg);
            break;

            case CWD: // Change working directory
            DoCWD(Arg);
            break;

            case CDUP: // Change to parent directory
            DoCDUP();
            break;

            case SMNT: // Structure Mount
            DoSMNT(Arg);
            break;

            case REIN: // Reinitialize
            DoREIN();
            break;

            case PORT: // PORT h1,h2,h3,h4,p1,p2
            DoPORT(Arg);
            break;

            case PASV: // Passive mode
            DoPASV(Arg);
            break;

            case TYPE: // Representation Type
            DoTYPE(Arg);
            break;

            case STRU: // File Structure
            DoSTRU(Arg);
            break;

            case MODE: // Transfer Mode
            DoMODE(Arg);
            break;

            case RETR: // Retrieve a file
            DoRETR(Arg);
            break;

            case STOR: // Store a file
            DoSTOR(Arg);
            break;

            case STOU: // Store a Unique file
            DoSTOU(Arg);
            break;

            case APPE: // Append a file
            DoAPPE(Arg);
            break;

            case ALLO: // Allocate space
            DoALLO(Arg);
            break;

            case RNFR: // Rename from
            DoRNFR(Arg);
            break;

            case RNTO: // Rename to
            DoRNTO(Arg);
            break;

            case ABOR: // Abort
            DoABOR(Arg);
            break;

            case DELE: // Delete
            DoDELE(Arg);
            break;

            case RMD: // Remove Directory
            DoRMD(Arg);
            break;

            case MKD: // Make Directory
            DoMKD(Arg);
            break;

            case PWD: // Print Working Directory
            DoPWD();
            break;

            case LIST: // List a directory
            DoLIST(Arg);
            break;

            case NLST: // Name List
            DoNLST(Arg);
            break;

            case SITE: // Site Parameters
            DoSITE(Arg);
            break;

            case SYST: // System
            DoSYST();
            break;

            case STAT: // Status
            DoSTAT(Arg);
            break;

            case NOOP: // No Operation
            SendResponse(200);
            break;

            //RFC 3659 --------------------------------------------------
            case SIZE: // Returns the size of a file
            DoSize(Arg);
            break;

            case REST: // Restart failed transfer
            DoREST(Arg);
            break;

            case MLST: // Get information about an entity
            DoMLST(Arg);
            break;

            case MLSD: // Get information about an directory entity
            DoMLSD(Arg);
            break;

            case FEAT: // Client wants a detailed list of features
            DoFEAT();
            break;

            //RFC 755  --------------------------------------------------
            case XCUP: // Changes to the parent
            DoCDUP();
            break;

            case XMKD: // Creates a directory
            DoMKD(Arg);
            break;

            case XPWD: // Prints the current directory
            DoPWD();
            break;

            case XRMD: // Removes a directory
            DoRMD(Arg);
            break;


            default://Command not recognized
            SendResponse(500);
            break;
        }
    }
    catch(QString err)
    {
        SendResponse(550,err);
    }
    catch(...)
    {
        SendResponse(550,"Unknown error in ExecuteCommand()");
    }
}

void FTPDataSocket::DoHelp()
{
    try
    {
        QString ret;
        ret.append("214 The following commands are available:");

        ret.append(" ABOR\r\n");
        ret.append(" ALLO\r\n");
        ret.append(" APPE\r\n");
        ret.append(" CDUP\r\n");
        ret.append(" CWD\r\n");
        ret.append(" DELE\r\n");
        ret.append(" FEAT\r\n");
        ret.append(" HELP\r\n");
        ret.append(" LIST\r\n");
        ret.append(" MLSD\r\n");
        ret.append(" MLST\r\n");
        ret.append(" MKD\r\n");
        ret.append(" MODE\r\n");
        ret.append(" NLST\r\n");
        ret.append(" NOOP\r\n");
        ret.append(" PASS\r\n");
        ret.append(" PASV\r\n");
        ret.append(" PWD\r\n");
        ret.append(" QUIT\r\n");
        ret.append(" REIN\r\n");
        ret.append(" REST\r\n");
        ret.append(" RETR\r\n");
        ret.append(" RMD\r\n");
        ret.append(" RNFR\r\n");
        ret.append(" RNTO\r\n");
        ret.append(" SIZE\r\n");
        ret.append(" SMNT\r\n");
        ret.append(" STAT\r\n");
        ret.append(" STOR\r\n");
        ret.append(" STOU\r\n");
        ret.append(" STRU\r\n");
        ret.append(" SYST\r\n");
        ret.append(" TYPE\r\n");
        ret.append(" USER\r\n");
        ret.append(" XCDUP\r\n");
        ret.append(" XPWD\r\n");
        ret.append(" XRMD\r\n");

        SendResponse(ret);
        SendResponse(214);
    }
    catch(QString err)
    {
        SendResponse(550,err);
    }
    catch(...)
    {
        SendResponse(550,"Unknown error in DoHelp()");
    }
}

void FTPDataSocket::DoFEAT()
{
    try
    {

        QString ret;
        ret.append("211-Extension supported\r\n");

        ret.append("ABOR\r\n");
        ret.append("ALLO\r\n");
        ret.append("APPE\r\n");
        ret.append("CDUP\r\n");
        ret.append("CWD\r\n");
        ret.append("DELE\r\n");
        ret.append("FEAT\r\n");
        ret.append("HELP\r\n");
        ret.append("LIST\r\n");
        ret.append("MLSD Type*;Size*;Create;Modify*;Win32.ea*;\r\n");
        ret.append("MLST Type*;Size*;Create;Modify*;Win32.ea*;\r\n");
        ret.append("MKD\r\n");
        ret.append("MODE\r\n");
        ret.append("NLST\r\n");
        ret.append("NOOP\r\n");
        ret.append("PASS\r\n");
        ret.append("PASV\r\n");
        ret.append("PWD\r\n");
        ret.append("QUIT\r\n");
        ret.append("REIN\r\n");
        ret.append("REST\r\n");
        ret.append("RETR\r\n");
        ret.append("RMD\r\n");
        ret.append("RNFR\r\n");
        ret.append("RNTO\r\n");
        ret.append("SIZE\r\n");
        ret.append("SMNT\r\n");
        ret.append("STAT\r\n");
        ret.append("STOR\r\n");
        ret.append("STOU\r\n");
        ret.append("STRU\r\n");
        ret.append("SYST\r\n");
        ret.append("TYPE\r\n");
        ret.append("USER\r\n");
        ret.append("XCDUP\r\n");
        ret.append("XPWD\r\n");
        ret.append("XRMD\r\n");

        SendResponse(ret);
        SendResponse(211);
    }
    catch(QString err)
    {
        SendResponse(550,err);
    }
    catch(...)
    {
        SendResponse(550,"Unknown error in DoFEAT()");
    }
}

void FTPDataSocket::DoQuit()
{

    try
    {
        SendResponse(221);
        //mSocket->waitForBytesWritten();
        CloseSocket();
    }
    catch(QString err)
    {
        SendResponse(550,err);
    }
    catch(...)
    {
        SendResponse(550,"Unknown error in DoQuit()");
    }
}

bool FTPDataSocket::CheckAuthenticated()
{
    if(!mAuthenticated)
    {
        SendResponse(530);
    }

    return mAuthenticated;
}

QString FTPDataSocket::RelativePath()
{
    QString RelPath;

    try
    {
        if(RelPath.toUpper() == mRootPath.toUpper())
        {
            RelPath = "/";
        }
        else
        {
            RelPath = mCurrentPath.mid(mRootPath.length());
            if(RelPath.length() == 0)
            {
                RelPath = "/";
            }
        }
    }
    catch(QString err)
    {
        SendResponse(550,err);
    }
    catch(...)
    {
        SendResponse(550,"Unknown error in RelativePath()");
    }

    return RelPath;
}

QString FTPDataSocket::ClientPath(QString Requested)
{
    //Some clients ask for a full path others only give a name

    QString temp = "";
    QString ret = "";
    try
    {

        //make sure the root path is configured
        if(mRootPath == "") return "";

        //Make sure the client has a current path
        if(mCurrentPath == "") mCurrentPath = mRootPath;

        //If we get a blank request, set it ot the current path
        if(Requested == "") Requested = mCurrentPath;

        //Find the local path
        if(Requested.startsWith("/"))
        {
            //They are requesting with a full path
            if(Requested == "/")
            {
                //they want the root path
                temp = mRootPath;
            }
            else
            {
                //they want a sub path
                temp = mRootPath + Requested;
            }
        }
        else
        {
            //they are only requesting with a name
            if(!mCurrentPath.endsWith("/"))
            {
                mCurrentPath.append("/");
            }
            temp = mCurrentPath + Requested;
        }



        ret = QDir::cleanPath(temp);

        qDebug() << "PATH temp = " << temp;
        qDebug() << "PATH ret = " << ret;

        //TO DO - make sure the path is allowed - ie, within the root
        QDir rootpath(temp);
        QDir retpath(ret);

        //make sure it is within root
        if(!retpath.absolutePath().contains(rootpath.absolutePath()))
        {
            ret = "";
        }



    }
    catch(QString err)
    {
        SendResponse(550,err);
    }
    catch(...)
    {
        SendResponse(550,"Unknown error in ClientPath()");
    }

    //return a cleaned path
    return ret;
}

bool FTPDataSocket::ConnectFileSocket()
{
    qDebug() << "*** ConnectFileSocket";

    bool ret = false;
    try
    {
        if(!mPassive)
        {
            //Tell the client we are going to open the file socket
            SendResponse(150);

            //Open a file socket and connect to the port specified
            mFileSocket->ConnectTo(mPortInfo);
        }
        else
        {
            //make sure we are listening as they should have send a PASV command
            SendResponse(125);
        }

        if(mFileSocket)
        {
            qDebug() << "*** mFileSocket not null";
            qDebug() << mFileSocket->isConnected();
            qDebug() << "mFileSocket " << mFileSocket;


            if(mFileSocket->isConnected())
            {
                qDebug() << "** FileSocket is connected **";
                ret = true;
            }
            else
            {
                qDebug() << "-- FileSocket not connected --";
                qDebug() << "-- Passive -- " << mPassive;
                qDebug() << "-- Connected -- " << mFileSocket->isConnected();
                qDebug() << "-- Listening -- " << mFileSocket->isListening();
                SendResponse(503, "FILE SOCKET NOT CONNECTED!");
                ret = false;
            }
        }
        else
        {
            qDebug() << "No File Socket";
        }
    }
    catch(QString err)
    {
        SendResponse(550,err);
    }
    catch(...)
    {
        SendResponse(550,"Unknown error in ConnectFileSocket()");
    }

    return ret;
}

void FTPDataSocket::LogonUser()
{
    try
    {
        //Set the Authenticated flag
        mAuthenticated = true;

        //Send the Logged in message
        SendResponse(230);
    }
    catch(QString err)
    {
        SendResponse(550,err);
    }
    catch(...)
    {
        SendResponse(550,"Unknown error in LogonUser()");
    }
}

void FTPDataSocket::LoadSettings()
{
    try
    {
        //Load the general settings
        AppSettings Settings;
        Settings.beginGroup(Settings.DefaultGroup());
        mAuthenticated = false;
        mAnonymous = Settings.value("anonymous", false).toBool();
        mUsername = Settings.value("username","").toString();
        mPassword = Settings.value("password","").toString();
        mAccount = Settings.value("account","").toString();
        mRootPath = Settings.value("rootpath","").toString().replace("\\","/");;
        mCurrentPath = mRootPath;
        mListRoots = Settings.value("listroots",false).toBool();
        mPassive = false;
        mAllowSMNT = false;
        mFilePosition = 0;
        mIPAddress = Settings.value("ipaddress","127.0.0.1").toString();

        if(!mRootPath.endsWith("/"))
        {
            mRootPath.append("/");
        }

        Settings.endGroup();
    }
    catch(QString err)
    {
        SendResponse(550,err);
    }
    catch(...)
    {
        SendResponse(550,"Unknown error in LoadSettings()");
    }
}


void FTPDataSocket::OnFileConnected()
{
    qDebug() << mSessionID << " OnFileConnected";
}

void FTPDataSocket::OnFileListening()
{
    qDebug() << mSessionID << " OnFileListening";
    qDebug() << "Listening on: " + mPortInfo.IPAddress() + ":" + QString::number(mPortInfo.Port());

    //tell the client we are listening
    SendResponse(227,"Entering Passive Mode (" + mPortInfo.ToString() + ").");
}

void FTPDataSocket::OnFileError(QString Message)
{
     qDebug() << mSessionID << " OnFileError";

     //Close the file socket
     mFileSocket->CloseSocket();
     mFilePosition = 0;

    //Send the error message back to the client
    SendResponse(550,Message);
}

void FTPDataSocket::OnFileFinished()
{
    qDebug() << mSessionID << " OnFileFinished";

    //Remove the reference to the file
    mFilename = "";
    mFilePosition = 0;

    //Inform the client we are finished
    SendResponse(250);
}

void FTPDataSocket::OnFileDisconnected()
{
    qDebug() << mSessionID << " OnFileDisconnected";

    //Inform the client we are closing the file socket
    SendResponse(226);

    mFilePosition = 0;
    mFileSocket = NULL;
}

void FTPDataSocket::DoUser(QString Arg)
{
    try
    {
        if(mAnonymous)
        {
            SendResponse(331);
            return;
        }

        //If there is no matching username tell them to enter one
        if(mUsername == "")
        {
            SendResponse(530, "Username has not been configured.");
            return;
        }

        if(mUsername.toUpper() != Arg.toUpper())
        {
            SendResponse(530, "Username not valid.");
            return;
        }

        mUsername = Arg;

        //Ask for a password
        SendResponse(331);

    }
    catch(QString err)
    {
        SendResponse(550,err);
    }
    catch(...)
    {
        SendResponse(550,"Unknown error in DoUser()");
    }
}

void FTPDataSocket::DoPass(QString Arg)
{
    try
    {
        if(mAnonymous)
        {
            LogonUser();
            return;
        }

        AppSettings Settings;
        QString Hash = Settings.HashPassword(Arg);

        if(Hash == mPassword && mUsername != "")
        {
            LogonUser();
        }
        else
        {
            SendResponse(530);
        }
    }
    catch(QString err)
    {
        SendResponse(550,err);
    }
    catch(...)
    {
        SendResponse(550,"Unknown error in DoPass()");
    }
}

void FTPDataSocket::DoACCT(QString Arg)
{
    try
    {
        //Make sure they are authenticated
        if(!CheckAuthenticated()) return;

        mAccount = Arg;

        //Send the OK message
        SendResponse(200);
    }
    catch(QString err)
    {
        SendResponse(550,err);
    }
    catch(...)
    {
        SendResponse(550,"Unknown error in DoACCT()");
    }
}

void FTPDataSocket::DoCWD(QString Arg)
{
    try
    {
        //Make sure they are authenticated
        if(!CheckAuthenticated()) return;

        QString Requested = ClientPath(Arg);

        //Make sure we have a valid path
        if(Requested == "")
        {
            SendResponse(550, "Requested path not valid.");
            return;
        }

        //make sure the path exists
        QDir path(Requested);
        if(!path.exists())
        {
            SendResponse(550, "Requested path not found.");
        }
        else
        {
             mCurrentPath = Requested;
             SendResponse(250, "CWD command successful.");
        }
    }
    catch(QString err)
    {
        SendResponse(550,err);
    }
    catch(...)
    {
        SendResponse(550,"Unknown error in DoCWD()");
    }

}

void FTPDataSocket::DoPWD()
{
    try
    {
        //Make sure they are authenticated
        if(!CheckAuthenticated()) return;

        SendResponse(257, "\"" + RelativePath() +"\" is the current path.");
    }
    catch(QString err)
    {
        SendResponse(550,err);
    }
    catch(...)
    {
        SendResponse(550,"Unknown error in DoPWD()");
    }

}

void FTPDataSocket::DoCDUP()
{
    try
    {
        //Make sure they are authenticated
        if(!CheckAuthenticated()) return;

        if(RelativePath() != "/")
        {
            QDir path(mCurrentPath);
            if(path.cdUp())
            {
                mCurrentPath = path.absolutePath();
                SendResponse(250, "CWD command successful.");
            }
            else
            {
                //could not change to parent
                SendResponse(550, "Could not change to parent");
            }
        }
        else
        {
            //could not change to parent
            SendResponse(550, "Could not change to parent");
        }
    }
    catch(QString err)
    {
        SendResponse(550,err);
    }
    catch(...)
    {
        SendResponse(550,"Unknown error in DoCDUP()");
    }

}

void FTPDataSocket::DoSMNT(QString Arg)
{
    try
    {
        //Make sure they are authenticated
        if(!CheckAuthenticated()) return;

        //Warning...this is a HUGE security issue
        if(mAllowSMNT)
        {
            QDir path(Arg);
            if(path.exists())
            {
                mRootPath = path.absolutePath();
                SendResponse(250, "SMNT command successful.");
            }
            else
            {
                //could not change to parent
                SendResponse(550, "Could not change root directory");
            }
        }
        else
        {
            //could not change to parent
            SendResponse(550, "SMNT not allowed.");
        }
    }
    catch(QString err)
    {
        SendResponse(550,err);
    }
    catch(...)
    {
        SendResponse(550,"Unknown error in DoSMNT()");
    }

}

void FTPDataSocket::DoREIN()
{    try
     {
        //Make sure they are authenticated
        if(!CheckAuthenticated()) return;

        //Load the general settings
        AppSettings Settings;
        Settings.beginGroup(Settings.DefaultGroup());
        mAccount = Settings.value("account","").toString();
        mRootPath = Settings.value("rootpath","").toString();
        mCurrentPath = mRootPath;
        mListRoots = Settings.value("listroots",false).toBool();
        mPassive = false;
        mAllowSMNT = false;
        mFilename = "";
        mFilePosition = 0;
        Settings.endGroup();

        SendResponse(250);
     }
     catch(QString err)
     {
         SendResponse(550,err);
     }
     catch(...)
     {
         SendResponse(550,"Unknown error in DoREIN()");
     }
}

void FTPDataSocket::DoPORT(QString Arg)
{
    try
    {
        //Make sure they are authenticated
        if(!CheckAuthenticated()) return;

        //Cleear the old port information
        mPortInfo.Clear();
        mPortInfo.FromString(Arg);

        //There is a glaring issue with the PORT command, the client will send their interal IP
        //This is obviously of no use to us if they are behind a NAT based router
        //Do not trust their PORT info, instead use the IP address od the connected socket
        mPortInfo.SetIPAddress(mSocket->peerAddress().toString());

        //Client is not in passive mode
        mPassive = false;

        //Create the file socket
        CreateFileSocket();

        //tell the client we are ready
        SendResponse(200);
    }
    catch(QString err)
    {
        SendResponse(550,err);
    }
    catch(...)
    {
        SendResponse(550,"Unknown error in DoPORT()");
    }
}


void FTPDataSocket::DoPASV(QString Arg)
{
    try
    {
        //Make sure they are authenticated
        if(!CheckAuthenticated()) return;

        //Clear the old port info
        mPortInfo.Clear();

        //Client is not in passive mode
        mPassive = true;

        //Create the file socket and start listening
        CreateFileSocket();

        //Find an open port in the range and start listening
        mFileSocket->ListenFor(mPortInfo,mIPAddress);
    }
    catch(QString err)
    {
        SendResponse(550,err);
    }
    catch(...)
    {
        SendResponse(550,"Unknown error in DoPASV()");
    }
}

void FTPDataSocket::DoNLST(QString Arg)
{
    try
    {
        //Make sure they are authenticated
        if(!CheckAuthenticated()) return;

        QString Requested;
        if(Arg == "")
        {
            //They want the current path
            Requested = mCurrentPath;
        }
        else
        {
            Requested = ClientPath(Arg);
            if(Requested == "")
            {
                SendResponse(550, "Requested path not valid.");
                return;
            }
        }

        if(ConnectFileSocket())
        {
            qDebug() << "** FileSocket NLST **";
            mFileSocket->NLST(Requested);
        }
    }
    catch(QString err)
    {
        SendResponse(550,err);
    }
    catch(...)
    {
        SendResponse(550,"Unknown error in DoNLST()");
    }
}

void FTPDataSocket::DoLIST(QString Arg)
{
    try
    {
        //Make sure they are authenticated
        if(!CheckAuthenticated()) return;

        QString Requested;
        if(Arg == "")
        {
            //They want the current path
            Requested = mCurrentPath;
        }
        else
        {
            Requested = ClientPath(Arg);
            if(Requested == "")
            {
                SendResponse(550, "Requested path not valid.");
                return;
            }
        }

        //Make sure we have a valid path
        if(Requested == "")
        {
            SendResponse(550, "Requested path not valid.");
            return;
        }

        if(ConnectFileSocket())
        {
            qDebug() << "** FileSocket LIST **";
            mFileSocket->LIST(Requested);
        }
    }
    catch(QString err)
    {
        SendResponse(550,err);
    }
    catch(...)
    {
        SendResponse(550,"Unknown error in DoLIST()");
    }
}

void FTPDataSocket::DoTYPE(QString Arg)
{
    try
    {
        //We don't do any byte transformations so just send the OK message
        SendResponse(200);
    }
    catch(QString err)
    {
        SendResponse(550,err);
    }
    catch(...)
    {
        SendResponse(550,"Unknown error in DoTYPE()");
    }
}

void FTPDataSocket::DoMKD(QString Arg)
{
    try
    {
        //Make sure they are authenticated
        if(!CheckAuthenticated()) return;


        QString Requested = ClientPath(Arg);

        //Make sure we have a valid path
        if(Requested == "")
        {
            SendResponse(550, "Requested path not valid.");
            return;
        }

        QDir path(Requested);
        if(!path.mkdir(Requested))
        {
            SendResponse(530);
        }
        else
        {
            SendResponse(257);
        }
    }
    catch(QString err)
    {
        SendResponse(550,err);
    }
    catch(...)
    {
        SendResponse(550,"Unknown error in DoMKD()");
    }
}

void FTPDataSocket::DoRNFR(QString Arg)
{
    try
    {
        //Make sure they are authenticated
        if(!CheckAuthenticated()) return;

        QString Requested = ClientPath(Arg);
        mFilename = "";

        //Make sure we have a valid path
        if(Requested == "")
        {
            SendResponse(550, "Requested path not valid.");
            return;
        }

        QFileInfo path(Requested);
        if(!path.exists())
        {
            SendResponse(550, "Could not find '" + Arg + "'");
        }
        else
        {
            mFilename = Requested;
            SendResponse(350);
        }
    }
    catch(QString err)
    {
        SendResponse(550,err);
    }
    catch(...)
    {
        SendResponse(550,"Unknown error in DoRNFR()");
    }
}

void FTPDataSocket::DoRNTO(QString Arg)
{
    try
    {
        //Make sure they are authenticated
        if(!CheckAuthenticated()) return;

        //Make sure the filename was configured
        if(mFilename == "")
        {
            SendResponse(503);
            return;
        }

        QString Requested = ClientPath(Arg);
        QDir dir(mFilename);

        if(dir.rename(mFilename,Requested))
        {
            mFilename = "";
            SendResponse(250);
        }
        else
        {
            mFilename = "";
            SendResponse(553);
        }
    }
    catch(QString err)
    {
        SendResponse(550,err);
    }
    catch(...)
    {
        SendResponse(550,"Unknown error in DoRNTO()");
    }
}

void FTPDataSocket::DoSTRU(QString Arg)
{
    try
    {
        //Little used command, we don't play with file names just send ok
        SendResponse(200);
    }
    catch(QString err)
    {
        SendResponse(550,err);
    }
    catch(...)
    {
        SendResponse(550,"Unknown error in DoSTRU()");
    }
}

void FTPDataSocket::DoMODE(QString Arg)
{
    try
    {
        //Little used command, we don't play with file modes just send ok
        SendResponse(200);
    }
    catch(QString err)
    {
        SendResponse(550,err);
    }
    catch(...)
    {
        SendResponse(550,"Unknown error in DoMODE()");
    }
}

void FTPDataSocket::DoRETR(QString Arg)
{
    try
    {
        //Make sure they are authenticated
        if(!CheckAuthenticated()) return;

        QString Requested = ClientPath(Arg);

        //make sure the file exists
        QFile file(Requested);

        if(!file.exists())
        {
            SendResponse(450);
            return;
        }

        if(ConnectFileSocket())
        {
            qDebug() << "** FileSocket RETR **";
            mFileSocket->Download(Requested, mFilePosition);
        }
    }
    catch(QString err)
    {
        SendResponse(550,err);
    }
    catch(...)
    {
        SendResponse(550,"Unknown error in DoRETR()");
    }
}

void FTPDataSocket::DoSTOR(QString Arg)
{
    try
    {
        //Make sure they are authenticated
        if(!CheckAuthenticated()) return;

        QString Requested = ClientPath(Arg);
        QFile file(Requested);

        //if the file exists, overwrite it
        if(file.exists())
        {
            if(!file.remove())
            {
                SendResponse(551, "File could not be overwritten");
                return;
            }
        }

        if(ConnectFileSocket())
        {
            qDebug() << "** FileSocket STOR **";
            mFileSocket->Upload(Requested,mFilePosition);
        }
    }
    catch(QString err)
    {
        SendResponse(550,err);
    }
    catch(...)
    {
        SendResponse(550,"Unknown error in DoSTOR()");
    }
}

void FTPDataSocket::DoSize(QString Arg)
{
    try
    {
        //Make sure they are authenticated
        if(!CheckAuthenticated()) return;

        QString Requested = ClientPath(Arg);

        //make sure the file does not exists
        QFile file(Requested);

        if(!file.exists())
        {
            SendResponse(550, "File not found");
            return;
        }

        SendResponse(213, QString::number(file.size()));
    }
    catch(QString err)
    {
        SendResponse(550,err);
    }
    catch(...)
    {
        SendResponse(550,"Unknown error in DoSize()");
    }

}

void FTPDataSocket::DoSTOU(QString Arg)
{
    try
    {
        //Make sure they are authenticated
        if(!CheckAuthenticated()) return;

        QString Requested = ClientPath(Arg);
        QFile file(Requested);

        //if the file exists, send an error
        if(file.exists())
        {
            SendResponse(551, "File already exists!");
            return;
        }

        if(ConnectFileSocket())
        {
            qDebug() << "** FileSocket STOU **";
            mFileSocket->Upload(Requested,mFilePosition);
        }
    }
    catch(QString err)
    {
        SendResponse(550,err);
    }
    catch(...)
    {
        SendResponse(550,"Unknown error in DoSTOU()");
    }
}

void FTPDataSocket::DoAPPE(QString Arg)
{
    try
    {
        //Make sure they are authenticated
        if(!CheckAuthenticated()) return;

        QString Requested = ClientPath(Arg);

        if(ConnectFileSocket())
        {
            qDebug() << "** FileSocket STOR **";
            mFileSocket->Upload(Requested, mFilePosition);
        }
    }
    catch(QString err)
    {
        SendResponse(550,err);
    }
    catch(...)
    {
        SendResponse(550,"Unknown error in DoAPPE()");
    }
}

void FTPDataSocket::DoALLO(QString Arg)
{
    try
    {
        //We dont allocate space as we can not be certain of the OS file system
        SendResponse(200);
    }
    catch(QString err)
    {
        SendResponse(550,err);
    }
    catch(...)
    {
        SendResponse(550,"Unknown error in DoALLO()");
    }
}

void FTPDataSocket::DoREST(QString Arg)
{
    try
    {
        //Make sure they are authenticated
        if(!CheckAuthenticated()) return;

        //make sure we have a filename
        if(mFilename == "")
        {
            SendResponse(550);
            return;
        }

        //Set the file position
        bool ok;
        mFilePosition = Arg.toInt(&ok);

        if(ok)
        {
            SendResponse(350);
        }
        else
        {
            mFilePosition = 0;
            SendResponse(500);
        }
    }
    catch(QString err)
    {
        SendResponse(550,err);
    }
    catch(...)
    {
        SendResponse(550,"Unknown error in DoREST()");
    }
}

void FTPDataSocket::DoABOR(QString Arg)
{
    try
    {
        //Make sure they are authenticated
        if(!CheckAuthenticated()) return;

        if(mFileSocket)
        {
            if(mFileSocket->isConnected() || mFileSocket->isListening())
            {
                mFileSocket->CloseSocket();
                mFileSocket = NULL;

                SendResponse(226);
            }
            else
            {
                SendResponse(226);
            }
        }
        else
        {
            SendResponse(226);
        }
    }
    catch(QString err)
    {
        SendResponse(550,err);
    }
    catch(...)
    {
        SendResponse(550,"Unknown error in DoABOR()");
    }
}

void FTPDataSocket::DoDELE(QString Arg)
{
    try
    {
        //Make sure they are authenticated
        if(!CheckAuthenticated()) return;

        QString Requested = ClientPath(Arg);

        QFile file(Requested);
        if(file.exists())
        {

            if(file.remove())
            {
                SendResponse(250);
            }
            else
            {
                SendResponse(550,"Could not delete file!");
            }
        }
        else
        {
            SendResponse(550,"File not found!");
        }
    }
    catch(QString err)
    {
        SendResponse(550,err);
    }
    catch(...)
    {
        SendResponse(550,"Unknown error in DoDELE()");
    }
}

void FTPDataSocket::DoRMD(QString Arg)
{
    try
    {
        //Make sure they are authenticated
        if(!CheckAuthenticated()) return;

        QString Requested = ClientPath(Arg);

        QDir dir(Requested);
        if(dir.exists())
        {

            if(dir.rmdir(Requested))
            {
                SendResponse(250);
            }
            else
            {
                SendResponse(550,"Could not delete directory!");
            }
        }
        else
        {
            SendResponse(550,"Directory not found!");
        }
    }
    catch(QString err)
    {
        SendResponse(550,err);
    }
    catch(...)
    {
        SendResponse(550,"Unknown error in DoRMD()");
    }
}

void FTPDataSocket::DoSITE(QString Arg)
{
    try
    {
        //Make sure they are authenticated
        if(!CheckAuthenticated()) return;


        //We don't impliment the site command
        //We could add a signal and let the connected objects deal with it
        SendResponse(202);
    }
    catch(QString err)
    {
        SendResponse(550,err);
    }
    catch(...)
    {
        SendResponse(550,"Unknown error in DoSITE()");
    }
}

void FTPDataSocket::DoSYST()
{
    try
    {
        //Make sure they are authenticated
        if(!CheckAuthenticated()) return;

        //This is typically not allowed due to security reasons

#ifdef Q_OS_WIN
        SendResponse(215,"Windows");
        return;
#endif

#ifdef Q_OS_MAC
        SendResponse(215,"Mac");
        return;
#endif

#ifdef Q_OS_UNIX
        SendResponse(215,"Unix");
        return;
#endif

#ifdef Q_OS_LINUX
        SendResponse(215,"Linux");
        return;
#endif

        SendResponse(215,"Unknown");
    }
    catch(QString err)
    {
        SendResponse(550,err);
    }
    catch(...)
    {
        SendResponse(550,"Unknown error in DoSYST()");
    }
}

void FTPDataSocket::DoSTAT(QString Arg)
{

    try
    {
        //Make sure they are authenticated
        if(!CheckAuthenticated()) return;

        //This command works in three ways
        //1 - no arg and no transfers
        //2 - a arg and no transfers
        //3 - no arg and a transfer in progress

        //No File transfer and a argument
        if(Arg != "")
        {
            SendResponse("213-status of " + Arg + "\r\n");

            //send the directory listing
            QString Requested = ClientPath(Arg);

            QDir dir(Requested);
            if(dir.exists())
            {
                foreach(QFileInfo item, dir.entryInfoList())
                {
                    FTPListItem ftpList;
                    SendResponse(ftpList.Convert(item));
                }
            }
            else
            {
                SendResponse("Not found!");
            }

            SendResponse(213);
            return;
        }


        //We are in a transfer
        if(mFileSocket)
        {
            SendResponse(211, "Transfering data.");
            return;
        }

        //No File transfer and no argument
        if(!mFileSocket && Arg == "")
        {
            SendResponse(211);
            return;
        }
    }
    catch(QString err)
    {
        SendResponse(550,err);
    }
    catch(...)
    {
        SendResponse(550,"Unknown error in DoSTAT()");
    }
}

void FTPDataSocket::DoMLST(QString Arg)
{
    try
    {
        //Make sure they are authenticated
        if(!CheckAuthenticated()) return;

        //get the requested file
        QString Requested = ClientPath(Arg);

        QFileInfo fi(Requested);
        if(fi.exists())
        {
            SendResponse("250-Listing " + Arg);
            FTPMLSItem item;
            SendResponse(item.Convert(fi));
            SendResponse(250,"End.");
        }
        else
        {
            SendResponse(550);
        }
    }
    catch(QString err)
    {
        SendResponse(550,err);
    }
    catch(...)
    {
        SendResponse(550,"Unknown error in DoMLST()");
    }
}

void FTPDataSocket::DoMLSD(QString Arg)
{
    qDebug() << "*** DoMLSD";
    try
    {
        //Make sure they are authenticated
        if(!CheckAuthenticated()) return;

        QString Requested;
        if(Arg == "")
        {
            //They want the current path
            Requested = mCurrentPath;
        }
        else
        {
            Requested = ClientPath(Arg);
            if(Requested == "")
            {
                SendResponse(550, "Requested path not valid.");
                return;
            }
        }

        qDebug() << "*** PATH = " << Requested;


        //Make sure we have a valid path
        if(Requested == "")
        {
            SendResponse(550, "Requested path not valid.");
            return;
        }


        qDebug() << "*** DoMLSD attempting";
        if(ConnectFileSocket())
        {
            qDebug() << "** FileSocket LIST **";
            mFileSocket->MLSD(Requested, Arg);
        }
    }
    catch(QString err)
    {
        SendResponse(550,err);
    }
    catch(...)
    {
        SendResponse(550,"Unknown error in DoMLSD()");
    }
}








