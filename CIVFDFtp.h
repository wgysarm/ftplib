#ifndef CIVFDFTP_H
#define CIVFDFTP_H

#include "civfdftp_global.h"
#include "ftpplugin.h"
#include "appsettings.h"
#include <QString>
#include <QDir>
#include <QDebug>
#include "ftplistitem.h"
#include "QFileInfo"
#include "ftpmlsitem.h"
#include "ftpport.h"
#include <QThread>



class CIVFDFTPSHARED_EXPORT CIVFDFtp
{

public:
    static CIVFDFtp* GetInstance(QString hostAddr, QString portn, QString username, QString password, QString rootpath);
    AppSettings *m_Settings;
    FTPPlugin *m_FTPPlugin;
    ~CIVFDFtp();
private:
    explicit CIVFDFtp(QString hostAddr, QString portn, QString username, QString password, QString rootpath);


};

#endif // CIVFDFTP_H
