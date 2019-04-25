/*
* FTPDataSocket
* This is the data socket used by the client
* Follows rfc 959, 3659, 755
*
* http://www.w3.org/Protocols/rfc959/
* http://en.wikipedia.org/wiki/File_Transfer_Protocol
*
* Created in 2012
* Bryan Cairns - bcairns@voidrealms.com
* http://www.voidrealms.com
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
* CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
* EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
* PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
* PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


#ifndef FTPDATASOCKET_H
#define FTPDATASOCKET_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QMetaEnum>
#include <QMap>
#include <QTcpSocket>
#include <QDir>
#include <QHostAddress>
#include "appsettings.h"
#include "ftpport.h"
#include "ftpfilesocket.h"
#include "ftplistitem.h"
#include "ftpmlsitem.h"

class FTPDataSocket : public QObject
{
    Q_OBJECT
    Q_ENUMS(RequestCommands)
public:
    explicit FTPDataSocket(int SocketDescriptor, QObject *parent = 0);

    /*!
    * Commands enumeration
    */
    enum RequestCommands
    {
        // RFC 959  -complete
        HELP,               //! Lists all available commands
        QUIT,               //! Log out
        USER,               //! Username
        PASS,               //! Password
        ACCT,               //! Account
        CWD,                //! Change working directory
        CDUP,               //! Change to parent directory
        SMNT,               //! Structure Mount
        REIN,               //! Reinitialize
        PORT,               //! PORT h1,h2,h3,h4,p1,p2
        PASV,               //! Passive mode
        TYPE,               //! Representation Type
        STRU,               //! File Structure
        MODE,               //! Transfer Mode
        RETR,               //! Retrieve a file
        STOR,               //! Store a file
        STOU,               //! Store a Unique file
        APPE,               //! Append a file
        ALLO,               //! Allocate space
        RNFR,               //! Rename from
        RNTO,               //! Rename to
        ABOR,               //! Abort
        DELE,               //! Delete
        RMD,                //! Remove Directory
        MKD,                //! Make Directory
        PWD,                //! Print Working Directory
        LIST,               //! List a directory
        NLST,               //! Name List
        SITE,               //! Site Parameters
        SYST,               //! System
        STAT,               //! Status
        NOOP,               //! No Operation

        //RFC 3695 - not complete
        SIZE,               //! Return the size of a file
        REST,               //! Restart
        MLSD,               //! List a directory in standard format
        MLST,               //! List a single entity in standard format
        FEAT,               //! Show a list of supported features

        //755 - complete
        XCUP,               //! Change to parent directory
        XMKD,               //! Make Directory
        XPWD,               //! Prints the current directory
        XRMD                //! Removes a directory
    };

    /*!
    * Returns the socket ID
    */
    int ID();

signals:

public slots:
    /*!
    * Gets the request from the client
    */
    void SocketReadyRead();

    /*!
    * Slot for the TCP socket disconnected() signal
    */
    void SocketDisconnected();

    /*!
    * Sends the response to the client socket
    * @param data The QByteArray to send
    */
    void SendResponse(QByteArray data);

    /*!
    * Sends the response to the client socket
    * @param data The QString to send
    */
    void SendResponse(QString data);

    /*!
    * Sends the response to the client socket
    * @param ResponseCode The response code
    */
    void SendResponse(int ResponseCode);

    /*!
    * Sends the response to the client socket
    * @param ResponseCode The response code
    * @param ResponseText The response text
    */
    void SendResponse(int ResponseCode, QString ResponseText);

    /*!
    * Sends the response to the client socket
    * @param data The char array to send
    */
    void SendResponse(const char* data);

    /*!
    * Closes the socket
    */
    void CloseSocket();

    /*!
    * Called when the file socket is connected
    */
    void OnFileConnected();

    /*!
    * Called when the file socket is listening
    */
    void OnFileListening();

    /*!
    * Called when the file socket has an error
    * @param Message The error message
    */
    void OnFileError(QString Message);

    /*!
    * Called when the file socket completed successfully
    */
    void OnFileFinished();

    /*!
    * Called when the file socket is disconnected
    */
    void OnFileDisconnected();

private:
    int mSessionID;                      //! The Socket ID
    QTcpSocket *mSocket;                 //! The TCP Socket
    QString mCommandBuffer;              //! The buffer holding the command
    QMap<int,QString> mResponseCodes;    //! A QMap of Response Codes
    int mAuthenticated;                  //! Determines if the user is authenticated
    bool mAnonymous;                     //! Determines if Anonymous logons are allowed
    QString mUsername;                   //! The Username
    QString mPassword;                   //! The Hashed password
    QString mAccount;                    //! The Account
    QString mCurrentPath;                //! The directory the user is in.
    QString mRootPath;                   //! The root path
    bool mListRoots;                     //! Lists the system roots in the RootPath
    bool mPassive;                       //! The user is in passive mode
    QString mFilename;                   //! The current file
    bool mAllowSMNT;                     //! Allow the user to mount different file system
    QString mIPAddress;                  //! The external address of the server
    FTPFileSocket *mFileSocket;          //! The FTP File Socket used for data transfers
    FTPPort mPortInfo;                   //! The Port information for file transfer connections
    qint64 mFilePosition;                //! Sets the file position

    /*!
    * Load the response codes
    */
    void LoadResponses();

    /*!
    * Process the command
    * @param ClientCommand The client command
    */
    void ProcessCommand(QString ClientCommand);

    /*!
    * Executes the command
    * @param ClientCommand The client command
    */
    void ExecuteCommand(QString ClientCommand);

    /*!
    * Returns a string form a response code
    * @param ResponseCode The response code
    */
    QString GetResponse(int ResponseCode);

    /*!
    * Loads the general settings
    */
    void LoadSettings();

    /*!
    * Sets the user to Authenticated
    */
    void LogonUser();

    /*!
    * Checks to see if the account is authenticated
    */
    bool CheckAuthenticated();

    /*!
    * Creates a fiel socket and connects the events
    */
    void CreateFileSocket();

    /*!
    * Returns the current path relative to the root path
    */
    QString RelativePath();

    /*!
    * Returns the a local path from a client request or a blank string
    * @param Requested The requested path
    */
    QString ClientPath(QString Requested);

    /*!
    * Connects the file socket and returns a boolean
    */
    bool ConnectFileSocket();

    /*!
    * Sends the HELP list to the client
    */
    void DoHelp();

    /*!
    * Closes the session
    */
    void DoQuit();

    /*!
    * Set the username
    * @param Arg The arqument
    */
    void DoUser(QString Arg);

    /*!
    * Set the password
    * @param Arg The arqument
    */
    void DoPass(QString Arg);

    /*!
    * Set the account
    * @param Arg The arqument
    */
    void DoACCT(QString Arg);

    /*!
    * Changes the working directory
    * @param Arg The arqument
    */
    void DoCWD(QString Arg);

    /*!
    * Prints the working Directory
    */
    void DoPWD();

    /*!
    * Changes to the parent directory
    */
    void DoCDUP();

    /*!
    * Allows the user the mount a different file structor
    * @param Arg The arqument
    */
    void DoSMNT(QString Arg);

    /*!
    * Reinitalizes the connection
    */
    void DoREIN();

    /*!
    * Sets the port information from the PORT command
    * @param Arg The arqument
    */
    void DoPORT(QString Arg);

    /*!
    * Client wants to connect to us
    * @param Arg The arqument
    */
    void DoPASV(QString Arg);

    /*!
    * Sends a list of file names in the current path
    * @param Arg The arqument
    */
    void DoNLST(QString Arg);

    /*!
    * Sets the data type
    * @param Arg The arqument
    */
    void DoTYPE(QString Arg);

    /*!
    * Sends a list of file names with extended data in the current path
    * @param Arg The arqument
    */
    void DoLIST(QString Arg);

    /*!
    * Creates a directory
    * @param Arg The arqument
    */
    void DoMKD(QString Arg);

    /*!
    * Sets the name to rename
    * @param Arg The arqument
    */
    void DoRNFR(QString Arg);

    /*!
    * Sets the new name to rename
    * @param Arg The arqument
    */
    void DoRNTO(QString Arg);

    /*!
    * Single Telnet character code specifying file structure
    * @param Arg The arqument
    */
    void DoSTRU(QString Arg);

    /*!
    * Single Telnet character code specifying data transfer mode
    * @param Arg The arqument
    */
    void DoMODE(QString Arg);

    /*!
    * Client wants to download a file
    * @param Arg The arqument
    */
    void DoRETR(QString Arg);

    /*!
    * Client wants to upload a file
    * @param Arg The arqument
    */
    void DoSTOR(QString Arg);

    /*!
    * Client wants to upload a file to a unique name
    * @param Arg The arqument
    */
    void DoSTOU(QString Arg);

    /*!
    * Returns the size of a file in oct
    * @param Arg The arqument
    */
    void DoSize(QString Arg);

    /*!
    * Client wants to upload a file in append mode
    * @param Arg The arqument
    */
    void DoAPPE(QString Arg);

    /*!
    * Client wants to allocate space for a file
    * @param Arg The arqument
    */
    void DoALLO(QString Arg);

    /*!
    * Client wants to restart a failed transfer
    * @param Arg The arqument
    */
    void DoREST(QString Arg);

    /*!
    * Client wants to abort the transfer
    * @param Arg The arqument
    */
    void DoABOR(QString Arg);

    /*!
    * Deletes a file
    * @param Arg The arqument
    */
    void DoDELE(QString Arg);

    /*!
    * Deletes a directory
    * @param Arg The arqument
    */
    void DoRMD(QString Arg);

    /*!
    * Executes a SITE command
    * @param Arg The arqument
    */
    void DoSITE(QString Arg);

    /*!
    * Executes a SYST command
    */
    void DoSYST();

    /*!
    * Executes a STAT command
    * @param Arg The arqument
    */
    void DoSTAT(QString Arg);

    /*!
    * Executes a MLST command
    * @param Arg The arqument
    */
    void DoMLST(QString Arg);

    /*!
    * Executes a MLSD command
    * @param Arg The arqument
    */
    void DoMLSD(QString Arg);

    /*!
    * Client wants a detailed list of features
    */
    void DoFEAT();

};

#endif // FTPDATASOCKET_H
