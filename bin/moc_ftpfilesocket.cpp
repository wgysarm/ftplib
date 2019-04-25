/****************************************************************************
** Meta object code from reading C++ file 'ftpfilesocket.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ftpfilesocket.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ftpfilesocket.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_FTPFileSocket_t {
    QByteArrayData data[29];
    char stringdata[286];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FTPFileSocket_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FTPFileSocket_t qt_meta_stringdata_FTPFileSocket = {
    {
QT_MOC_LITERAL(0, 0, 13), // "FTPFileSocket"
QT_MOC_LITERAL(1, 14, 11), // "OnConnected"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 11), // "OnListening"
QT_MOC_LITERAL(4, 39, 7), // "OnError"
QT_MOC_LITERAL(5, 47, 7), // "Message"
QT_MOC_LITERAL(6, 55, 10), // "OnFinished"
QT_MOC_LITERAL(7, 66, 14), // "OnDisconnected"
QT_MOC_LITERAL(8, 81, 9), // "ConnectTo"
QT_MOC_LITERAL(9, 91, 8), // "FTPPort&"
QT_MOC_LITERAL(10, 100, 8), // "PortInfo"
QT_MOC_LITERAL(11, 109, 9), // "ListenFor"
QT_MOC_LITERAL(12, 119, 9), // "IPAddress"
QT_MOC_LITERAL(13, 129, 6), // "Upload"
QT_MOC_LITERAL(14, 136, 8), // "Filename"
QT_MOC_LITERAL(15, 145, 8), // "Position"
QT_MOC_LITERAL(16, 154, 8), // "Download"
QT_MOC_LITERAL(17, 163, 4), // "LIST"
QT_MOC_LITERAL(18, 168, 4), // "Path"
QT_MOC_LITERAL(19, 173, 4), // "NLST"
QT_MOC_LITERAL(20, 178, 4), // "MLSD"
QT_MOC_LITERAL(21, 183, 9), // "Requested"
QT_MOC_LITERAL(22, 193, 15), // "SocketReadyRead"
QT_MOC_LITERAL(23, 209, 15), // "SocketConnected"
QT_MOC_LITERAL(24, 225, 18), // "SocketDisconnected"
QT_MOC_LITERAL(25, 244, 12), // "SendResponse"
QT_MOC_LITERAL(26, 257, 4), // "data"
QT_MOC_LITERAL(27, 262, 11), // "const char*"
QT_MOC_LITERAL(28, 274, 11) // "CloseSocket"

    },
    "FTPFileSocket\0OnConnected\0\0OnListening\0"
    "OnError\0Message\0OnFinished\0OnDisconnected\0"
    "ConnectTo\0FTPPort&\0PortInfo\0ListenFor\0"
    "IPAddress\0Upload\0Filename\0Position\0"
    "Download\0LIST\0Path\0NLST\0MLSD\0Requested\0"
    "SocketReadyRead\0SocketConnected\0"
    "SocketDisconnected\0SendResponse\0data\0"
    "const char*\0CloseSocket"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FTPFileSocket[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  109,    2, 0x06 /* Public */,
       3,    0,  110,    2, 0x06 /* Public */,
       4,    1,  111,    2, 0x06 /* Public */,
       6,    0,  114,    2, 0x06 /* Public */,
       7,    0,  115,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    1,  116,    2, 0x0a /* Public */,
      11,    2,  119,    2, 0x0a /* Public */,
      13,    2,  124,    2, 0x0a /* Public */,
      16,    2,  129,    2, 0x0a /* Public */,
      17,    1,  134,    2, 0x0a /* Public */,
      19,    1,  137,    2, 0x0a /* Public */,
      20,    2,  140,    2, 0x0a /* Public */,
      22,    0,  145,    2, 0x0a /* Public */,
      23,    0,  146,    2, 0x0a /* Public */,
      24,    0,  147,    2, 0x0a /* Public */,
      25,    1,  148,    2, 0x0a /* Public */,
      25,    1,  151,    2, 0x0a /* Public */,
      25,    1,  154,    2, 0x0a /* Public */,
      28,    0,  157,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, 0x80000000 | 9, QMetaType::QString,   10,   12,
    QMetaType::Void, QMetaType::QString, QMetaType::LongLong,   14,   15,
    QMetaType::Void, QMetaType::QString, QMetaType::LongLong,   14,   15,
    QMetaType::Void, QMetaType::QString,   18,
    QMetaType::Void, QMetaType::QString,   18,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   18,   21,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,   26,
    QMetaType::Void, QMetaType::QString,   26,
    QMetaType::Void, 0x80000000 | 27,   26,
    QMetaType::Void,

       0        // eod
};

void FTPFileSocket::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FTPFileSocket *_t = static_cast<FTPFileSocket *>(_o);
        switch (_id) {
        case 0: _t->OnConnected(); break;
        case 1: _t->OnListening(); break;
        case 2: _t->OnError((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->OnFinished(); break;
        case 4: _t->OnDisconnected(); break;
        case 5: _t->ConnectTo((*reinterpret_cast< FTPPort(*)>(_a[1]))); break;
        case 6: _t->ListenFor((*reinterpret_cast< FTPPort(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 7: _t->Upload((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 8: _t->Download((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 9: _t->LIST((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->NLST((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: _t->MLSD((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 12: _t->SocketReadyRead(); break;
        case 13: _t->SocketConnected(); break;
        case 14: _t->SocketDisconnected(); break;
        case 15: _t->SendResponse((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 16: _t->SendResponse((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 17: _t->SendResponse((*reinterpret_cast< const char*(*)>(_a[1]))); break;
        case 18: _t->CloseSocket(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (FTPFileSocket::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FTPFileSocket::OnConnected)) {
                *result = 0;
            }
        }
        {
            typedef void (FTPFileSocket::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FTPFileSocket::OnListening)) {
                *result = 1;
            }
        }
        {
            typedef void (FTPFileSocket::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FTPFileSocket::OnError)) {
                *result = 2;
            }
        }
        {
            typedef void (FTPFileSocket::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FTPFileSocket::OnFinished)) {
                *result = 3;
            }
        }
        {
            typedef void (FTPFileSocket::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FTPFileSocket::OnDisconnected)) {
                *result = 4;
            }
        }
    }
}

const QMetaObject FTPFileSocket::staticMetaObject = {
    { &QTcpServer::staticMetaObject, qt_meta_stringdata_FTPFileSocket.data,
      qt_meta_data_FTPFileSocket,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *FTPFileSocket::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FTPFileSocket::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_FTPFileSocket.stringdata))
        return static_cast<void*>(const_cast< FTPFileSocket*>(this));
    return QTcpServer::qt_metacast(_clname);
}

int FTPFileSocket::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTcpServer::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 19)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 19;
    }
    return _id;
}

// SIGNAL 0
void FTPFileSocket::OnConnected()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void FTPFileSocket::OnListening()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void FTPFileSocket::OnError(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void FTPFileSocket::OnFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}

// SIGNAL 4
void FTPFileSocket::OnDisconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 4, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
