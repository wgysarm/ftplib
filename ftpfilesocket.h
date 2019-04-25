/*
* FTPFileSocket
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

#ifndef FTPFILESOCKET_H
#define FTPFILESOCKET_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QByteArray>
#include <QString>
#include <QDir>
#include <QFileInfo>
#include <QDebug>
#include "ftpport.h"
#include "ftplistitem.h"
#include "ftpmlsitem.h"


class FTPFileSocket : public QTcpServer
{
    Q_OBJECT
public:
    explicit FTPFileSocket(QObject *parent = 0);

    /*!
    * Resturns a booling indicating if the socket is connected
    */
    bool isConnected();

signals:
    /*!
    * Emitted when the socket is connected
    */
    void OnConnected();

    /*!
    * Emitted when the socket is listening
    */
    void OnListening();

    /*!
    * Emitted when the socket has an error
    * @param Message The error message
    */
    void OnError(QString Message);

    /*!
    * Emitted when the socket completed successfully
    */
    void OnFinished();

    /*!
    * Emitted when the socket is disconnected
    */
    void OnDisconnected();

public slots:
    /*!
    * Connected to the client on the IP and port specified
    * @param PortInfo The client port info
    */
    void ConnectTo(FTPPort &PortInfo);

    /*!
    * Listens for
    * @param PortInfo The client port info
    * @param IPAddress The IP Address to bind to
    */
    void ListenFor(FTPPort &PortInfo, QString IPAddress);

    /*!
    * Client uploads file to server
    * @param Filename The Filename
    * @param Position The Position in the file
    */
    void Upload(QString Filename, qint64 Position);

    /*!
    * Client downloads file from the server
    * @param Filename The Filename
    * @param Position The Position in the file
    */
    void Download(QString Filename, qint64 Position);

    /*!
    * Sends a list of file names with extended info
    * @param Path The path
    */
    void LIST(QString Path);

    /*!
    * Sends a listing of files to the client
    * @param Path The specified path
    */
    void NLST(QString Path);

    /*!
    * Sends a listing of files to the client in standard format
    * @param Path The specified path
    * @param Requested The specified path
    */
    void MLSD(QString Path,QString Requested);

    /*!
    * Gets the request from the client
    */
    void SocketReadyRead();

    /*!
    * Slot for the TCP socket connected() signal
    */
    void SocketConnected();

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
    * @param data The QString to send
    */
    void SendResponse(const char* data);

    /*!
    * Closes the socket
    */
    void CloseSocket();



protected:

    /*!
    * Processes incomming TCP connections
    * @param socketDescriptor The descriptor of the conection
    */
    void incomingConnection(int socketDescriptor);


private:
    QTcpSocket *mSocket;        //! The TCP Socket
    int mSessionID;             //! The Session ID
    bool mUploading;            //! Determines if the client is uploading
    QString mFilename;          //! The name of the file the client is working with

    /*!
    * Connects the signals and slots
    */
    void ConnectEvents();
};

#endif // FTPFILESOCKET_H
