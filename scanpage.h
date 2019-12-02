#if _MSC_VER >= 1600	// MSVC2015 > 1899,	MSVC_VER = 14.0
#pragma execution_character_set("utf-8")
#endif
#ifndef SCANPAGE_H
#define SCANPAGE_H

#include <QObject>
#include <QThread>
#include <QProcess>
class ScanPage : public QThread
{
    Q_OBJECT
public:
    explicit ScanPage(QObject *parent = nullptr);
    void run();

signals:
    void scanDone();
public slots:
private:
};

#endif // SCANPAGE_H
