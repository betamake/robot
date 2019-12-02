#if _MSC_VER >= 1600	// MSVC2015 > 1899,	MSVC_VER = 14.0
#pragma execution_character_set("utf-8")
#endif
#include "scanpage.h"
#include <QDebug>
ScanPage::ScanPage(QObject *parent) : QThread(parent)
{

}
void ScanPage::run()
{
    QProcess p;
    QStringList params;
    QString pythonPath = "C:\\ProgramData\\Anaconda3\\python.exe";
    QString pythonScript = "C:/Users/betamake/Documents/qt/Scan/scan_test.py";
    params << pythonScript;
    p.start(pythonPath, params);
    p.waitForFinished(-1);
    QString p_stdout = p.readAll();
    QString p_stderr = p.readAllStandardError();
    if(!p_stderr.isEmpty())
    qDebug()<<"Python error:"<<p_stderr;
    qDebug()<<"Python result="<<p_stdout;
    emit scanDone();
}
