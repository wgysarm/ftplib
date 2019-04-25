#include "CIVFDFtp.h"


CIVFDFtp::CIVFDFtp(QString hostAddr, QString portn, QString username, QString password, QString rootpath)
{

    qDebug() << "---------------CIVFDFtp Construct thread----------" << QThread::currentThread();
    m_FTPPlugin = new FTPPlugin(0);
    m_Settings = new AppSettings(0);

    m_Settings->beginGroup(m_Settings->DefaultGroup());

    m_Settings->setValue("anonymous",true);
    m_Settings->setValue("username",username.toLatin1());
    m_Settings->setValue("password",m_Settings->HashPassword(password.toLatin1()));
    m_Settings->setValue("ipaddress",hostAddr.toLatin1());
    m_Settings->setValue("port",portn.toLatin1());
//    m_Settings->setValue("rootpath","/HttpServer/Html/");
//    m_Settings->setValue("rootpath", rootpath.toLatin1());//"/mnt/sdcard/mmcblk1p1/1/"
    m_Settings->setValue("rootpath", rootpath);//"/mnt/sdcard/mmcblk1p1/1/"
    m_Settings->endGroup();
}
CIVFDFtp::~CIVFDFtp()
{
    if(m_Settings != NULL)
    {
        delete m_Settings;
        m_Settings = NULL;
    }

    if(m_FTPPlugin != NULL)
    {
        delete m_FTPPlugin;
        m_FTPPlugin = NULL;
    }


}

CIVFDFtp* CIVFDFtp::GetInstance(QString hostAddr, QString portn, QString username, QString password, QString rootpath)
{
    return new CIVFDFtp(hostAddr, portn, username, password, rootpath);

}
