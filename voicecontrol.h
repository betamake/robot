#ifndef VOICECONTROL_H
#define VOICECONTROL_H

#include <QObject>
#include <QAudioRecorder>
#include <QAudioProbe>
#include <QMediaPlayer>
#include "qaudiolevel.h"
#include <QList>
#include <QCoreApplication>
#include <QDir>
#include <httprequest.h>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QNetworkRequest>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
/*
@brief:语音合成与声音控制
@time:2019-10-21
*/
class voiceControl : public QObject
{
    Q_OBJECT
public:
    explicit voiceControl(QObject *parent = nullptr);
    void initMedia();
    void setRecord();
    void startRecord();
    void stopRecord();
    void sendPlayText(QByteArray text);
    void printFile(QString dataFileName, QByteArray fdata);
    QAudioLevel *level;
    QMediaPlayer * player;
signals:

public slots:
    void voiceReply(QNetworkReply * reply);
    void playReply(QNetworkReply * reply);
    void playChanged();
    void processBuffer(const QAudioBuffer&);
private:
    QAudioRecorder *audioRecorder;
    QAudioProbe *probe;
    QList<QAudioLevel*> audioLevels;
    int recordNum;//音频样本数量
    int recordLow;//低音音频样本数量
    int recordHigh;//高音样本数量
    bool recordSend;//是否发送语音指令
    bool playStatus;//是否播放过音频文件
    //httpre
    httpRequest HttpRequest;
    QString address;
};

#endif // VOICECONTROL_H
