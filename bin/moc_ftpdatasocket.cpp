/****************************************************************************
** Meta object code from reading C++ file 'ftpdatasocket.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ftpdatasocket.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ftpdatasocket.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_FTPDataSocket_t {
    QByteArrayData data[58];
    char stringdata[421];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FTPDataSocket_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FTPDataSocket_t qt_meta_stringdata_FTPDataSocket = {
    {
QT_MOC_LITERAL(0, 0, 13), // "FTPDataSocket"
QT_MOC_LITERAL(1, 14, 15), // "SocketReadyRead"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 18), // "SocketDisconnected"
QT_MOC_LITERAL(4, 50, 12), // "SendResponse"
QT_MOC_LITERAL(5, 63, 4), // "data"
QT_MOC_LITERAL(6, 68, 12), // "ResponseCode"
QT_MOC_LITERAL(7, 81, 12), // "ResponseText"
QT_MOC_LITERAL(8, 94, 11), // "const char*"
QT_MOC_LITERAL(9, 106, 11), // "CloseSocket"
QT_MOC_LITERAL(10, 118, 15), // "OnFileConnected"
QT_MOC_LITERAL(11, 134, 15), // "OnFileListening"
QT_MOC_LITERAL(12, 150, 11), // "OnFileError"
QT_MOC_LITERAL(13, 162, 7), // "Message"
QT_MOC_LITERAL(14, 170, 14), // "OnFileFinished"
QT_MOC_LITERAL(15, 185, 18), // "OnFileDisconnected"
QT_MOC_LITERAL(16, 204, 15), // "RequestCommands"
QT_MOC_LITERAL(17, 220, 4), // "HELP"
QT_MOC_LITERAL(18, 225, 4), // "QUIT"
QT_MOC_LITERAL(19, 230, 4), // "USER"
QT_MOC_LITERAL(20, 235, 4), // "PASS"
QT_MOC_LITERAL(21, 240, 4), // "ACCT"
QT_MOC_LITERAL(22, 245, 3), // "CWD"
QT_MOC_LITERAL(23, 249, 4), // "CDUP"
QT_MOC_LITERAL(24, 254, 4), // "SMNT"
QT_MOC_LITERAL(25, 259, 4), // "REIN"
QT_MOC_LITERAL(26, 264, 4), // "PORT"
QT_MOC_LITERAL(27, 269, 4), // "PASV"
QT_MOC_LITERAL(28, 274, 4), // "TYPE"
QT_MOC_LITERAL(29, 279, 4), // "STRU"
QT_MOC_LITERAL(30, 284, 4), // "MODE"
QT_MOC_LITERAL(31, 289, 4), // "RETR"
QT_MOC_LITERAL(32, 294, 4), // "STOR"
QT_MOC_LITERAL(33, 299, 4), // "STOU"
QT_MOC_LITERAL(34, 304, 4), // "APPE"
QT_MOC_LITERAL(35, 309, 4), // "ALLO"
QT_MOC_LITERAL(36, 314, 4), // "RNFR"
QT_MOC_LITERAL(37, 319, 4), // "RNTO"
QT_MOC_LITERAL(38, 324, 4), // "ABOR"
QT_MOC_LITERAL(39, 329, 4), // "DELE"
QT_MOC_LITERAL(40, 334, 3), // "RMD"
QT_MOC_LITERAL(41, 338, 3), // "MKD"
QT_MOC_LITERAL(42, 342, 3), // "PWD"
QT_MOC_LITERAL(43, 346, 4), // "LIST"
QT_MOC_LITERAL(44, 351, 4), // "NLST"
QT_MOC_LITERAL(45, 356, 4), // "SITE"
QT_MOC_LITERAL(46, 361, 4), // "SYST"
QT_MOC_LITERAL(47, 366, 4), // "STAT"
QT_MOC_LITERAL(48, 371, 4), // "NOOP"
QT_MOC_LITERAL(49, 376, 4), // "SIZE"
QT_MOC_LITERAL(50, 381, 4), // "REST"
QT_MOC_LITERAL(51, 386, 4), // "MLSD"
QT_MOC_LITERAL(52, 391, 4), // "MLST"
QT_MOC_LITERAL(53, 396, 4), // "FEAT"
QT_MOC_LITERAL(54, 401, 4), // "XCUP"
QT_MOC_LITERAL(55, 406, 4), // "XMKD"
QT_MOC_LITERAL(56, 411, 4), // "XPWD"
QT_MOC_LITERAL(57, 416, 4) // "XRMD"

    },
    "FTPDataSocket\0SocketReadyRead\0\0"
    "SocketDisconnected\0SendResponse\0data\0"
    "ResponseCode\0ResponseText\0const char*\0"
    "CloseSocket\0OnFileConnected\0OnFileListening\0"
    "OnFileError\0Message\0OnFileFinished\0"
    "OnFileDisconnected\0RequestCommands\0"
    "HELP\0QUIT\0USER\0PASS\0ACCT\0CWD\0CDUP\0"
    "SMNT\0REIN\0PORT\0PASV\0TYPE\0STRU\0MODE\0"
    "RETR\0STOR\0STOU\0APPE\0ALLO\0RNFR\0RNTO\0"
    "ABOR\0DELE\0RMD\0MKD\0PWD\0LIST\0NLST\0SITE\0"
    "SYST\0STAT\0NOOP\0SIZE\0REST\0MLSD\0MLST\0"
    "FEAT\0XCUP\0XMKD\0XPWD\0XRMD"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FTPDataSocket[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       1,  106, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x0a /* Public */,
       3,    0,   80,    2, 0x0a /* Public */,
       4,    1,   81,    2, 0x0a /* Public */,
       4,    1,   84,    2, 0x0a /* Public */,
       4,    1,   87,    2, 0x0a /* Public */,
       4,    2,   90,    2, 0x0a /* Public */,
       4,    1,   95,    2, 0x0a /* Public */,
       9,    0,   98,    2, 0x0a /* Public */,
      10,    0,   99,    2, 0x0a /* Public */,
      11,    0,  100,    2, 0x0a /* Public */,
      12,    1,  101,    2, 0x0a /* Public */,
      14,    0,  104,    2, 0x0a /* Public */,
      15,    0,  105,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    5,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    6,    7,
    QMetaType::Void, 0x80000000 | 8,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::Void,
    QMetaType::Void,

 // enums: name, flags, count, data
      16, 0x0,   41,  110,

 // enum data: key, value
      17, uint(FTPDataSocket::HELP),
      18, uint(FTPDataSocket::QUIT),
      19, uint(FTPDataSocket::USER),
      20, uint(FTPDataSocket::PASS),
      21, uint(FTPDataSocket::ACCT),
      22, uint(FTPDataSocket::CWD),
      23, uint(FTPDataSocket::CDUP),
      24, uint(FTPDataSocket::SMNT),
      25, uint(FTPDataSocket::REIN),
      26, uint(FTPDataSocket::PORT),
      27, uint(FTPDataSocket::PASV),
      28, uint(FTPDataSocket::TYPE),
      29, uint(FTPDataSocket::STRU),
      30, uint(FTPDataSocket::MODE),
      31, uint(FTPDataSocket::RETR),
      32, uint(FTPDataSocket::STOR),
      33, uint(FTPDataSocket::STOU),
      34, uint(FTPDataSocket::APPE),
      35, uint(FTPDataSocket::ALLO),
      36, uint(FTPDataSocket::RNFR),
      37, uint(FTPDataSocket::RNTO),
      38, uint(FTPDataSocket::ABOR),
      39, uint(FTPDataSocket::DELE),
      40, uint(FTPDataSocket::RMD),
      41, uint(FTPDataSocket::MKD),
      42, uint(FTPDataSocket::PWD),
      43, uint(FTPDataSocket::LIST),
      44, uint(FTPDataSocket::NLST),
      45, uint(FTPDataSocket::SITE),
      46, uint(FTPDataSocket::SYST),
      47, uint(FTPDataSocket::STAT),
      48, uint(FTPDataSocket::NOOP),
      49, uint(FTPDataSocket::SIZE),
      50, uint(FTPDataSocket::REST),
      51, uint(FTPDataSocket::MLSD),
      52, uint(FTPDataSocket::MLST),
      53, uint(FTPDataSocket::FEAT),
      54, uint(FTPDataSocket::XCUP),
      55, uint(FTPDataSocket::XMKD),
      56, uint(FTPDataSocket::XPWD),
      57, uint(FTPDataSocket::XRMD),

       0        // eod
};

void FTPDataSocket::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FTPDataSocket *_t = static_cast<FTPDataSocket *>(_o);
        switch (_id) {
        case 0: _t->SocketReadyRead(); break;
        case 1: _t->SocketDisconnected(); break;
        case 2: _t->SendResponse((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 3: _t->SendResponse((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->SendResponse((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->SendResponse((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 6: _t->SendResponse((*reinterpret_cast< const char*(*)>(_a[1]))); break;
        case 7: _t->CloseSocket(); break;
        case 8: _t->OnFileConnected(); break;
        case 9: _t->OnFileListening(); break;
        case 10: _t->OnFileError((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: _t->OnFileFinished(); break;
        case 12: _t->OnFileDisconnected(); break;
        default: ;
        }
    }
}

const QMetaObject FTPDataSocket::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_FTPDataSocket.data,
      qt_meta_data_FTPDataSocket,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *FTPDataSocket::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FTPDataSocket::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_FTPDataSocket.stringdata))
        return static_cast<void*>(const_cast< FTPDataSocket*>(this));
    return QObject::qt_metacast(_clname);
}

int FTPDataSocket::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
