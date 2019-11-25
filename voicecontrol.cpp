#include "voicecontrol.h"

voiceControl::voiceControl(QObject *parent) : QObject(parent)
{
    address = "http://192.168.3.185:8000";
//    this->initMedia();

}
/*
@brief:初始化音频变量。
@param:无
@return:无
@time:2019-10-20
*/
void voiceControl::initMedia()
{
    //语音识别设置
    audioRecorder = new QAudioRecorder(this);
    probe = new QAudioProbe;

    connect(probe, SIGNAL(audioBufferProbed(QAudioBuffer)),this, SLOT(processBuffer(QAudioBuffer)));
    probe->setSource(audioRecorder);
    recordNum = 0;
    recordHigh = 0;
    recordLow = 0;
    recordSend = false;
    this->setRecord();
    this->startRecord();

    //初始化音频播放变量
    player = new QMediaPlayer;
    playStatus = false;
    connect(player,SIGNAL(stateChanged(QMediaPlayer::State)),this,SLOT(playChanged()));
    player->stop();
    this->sendPlayText("欢迎使用财务机器人,请选择登录方式");
}
/*
@brief:设置录音机
@param:无
@return:无
@time:2019-10-20
*/
void voiceControl::setRecord(){
    audioRecorder->setAudioInput(audioRecorder->audioInputs().at(0));
    audioRecorder->setContainerFormat("wav");
    QAudioEncoderSettings settings;// 音频编码设置
    settings.setCodec("audio/PCM");  //编码
    settings.setSampleRate(16000); //采样率
    settings.setBitRate(128000); //比特率
    settings.setChannelCount(1); //通道数
    settings.setQuality(QMultimedia::VeryHighQuality); //品质
    settings.setEncodingMode(QMultimedia::ConstantBitRateEncoding); //编码模式
    QString container = "wav";
    //    QString container = "audio/x-wav";

    //待解决
    audioRecorder->setAudioSettings (settings);
    //audioRecorder->setEncodingSettings(settings, QVideoEncoderSettings(), container);
}
/*
@brief:开始录音
@param:无
@return:无
@time:2019-10-20
*/
void voiceControl::startRecord(){
    QString baseDir = QCoreApplication::applicationDirPath();
    QString fileDir = baseDir.append("/files/records/");

    //创建目录
    QDir dir;
    if(!dir.exists(fileDir))
    {
        bool res = dir.mkpath(fileDir);
        qDebug() << "录音保存目录:" << res;
    }

    fileDir.append(HttpRequest.getCurrentTime());
    fileDir.append(".wav");
    audioRecorder->setOutputLocation(QUrl::fromLocalFile(fileDir));
    audioRecorder->record();
}
/*
@brief:结束录音
@param:无
@return:无
@time:2019-10-20
*/
void voiceControl::stopRecord(){
    audioRecorder->stop();
    QString fileDir = audioRecorder->outputLocation().toLocalFile();
    qDebug()<<audioRecorder->outputLocation().toLocalFile()<<endl;
    QFile file(fileDir);
    //发送语音指令，进行识别
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QObject::connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(voiceReply(QNetworkReply*)));

    if (!file.open(QIODevice::ReadOnly)||file.size()==0)
    {
        file.close();
        return ;
    }
    QByteArray fdata = file.readAll();
    file.close();
    fdata = fdata.toBase64();
    fdata = fdata.replace("+","-");
    fdata = fdata.replace("/","_");

    QUrlQuery params;

    params.addQueryItem("audio",fdata);
    params.addQueryItem("audioType",".wav");
    QString  data = params.toString();

    this->printFile("voice.txt",fdata);
    //    QString address = HOST.append("/understand/recognition/");

    QNetworkRequest request = HttpRequest.getHttpRequest(address.left(25).append("/understand/recognition/"));
    request.setHeader(QNetworkRequest::ContentLengthHeader, data.size());
    manager->post(request,params.toString().toUtf8());

    recordNum = 0;
    recordHigh = 0;
    recordLow = 0;
    recordSend = false;
    this->startRecord();
}
/*
@brief:打印日志输出到文件
@param:无
@return:无
@time:2019-10-20
*/
void voiceControl::printFile(QString dataFileName,QByteArray fdata)
{
    //打印请求参数(测试)
    //    QString dataFileName = "reply.txt";
    QFile datafile(dataFileName);
    if(!datafile.open(QIODevice::ReadWrite|QIODevice::Text))
    {
        qDebug()<<"not write";
    }
    QTextStream in(&datafile);
    in<<fdata<<"\n";
    datafile.close();
    qDebug()<<"--------get "+dataFileName+"-------"<<endl;
}
/*
@brief:发送文本，语音合成
@param:text:需要合成的文字。
@return:无
@time:2019-10-20
*/
void voiceControl::sendPlayText(QByteArray text){
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QObject::connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(playReply(QNetworkReply*)));

    QUrlQuery params;

    text = text.toBase64();
    text = text.replace("+","-");
    text = text.replace("/","_");
    params.addQueryItem("text",text);
    QString  data = params.toString();

    QNetworkRequest request = HttpRequest.getHttpRequest(address.left(25).append("/understand/synthesis/"));
    request.setHeader(QNetworkRequest::ContentLengthHeader, data.size());
    manager->post(request,params.toString().toUtf8());
}
/*
@brief:语音识别返回处理
@param:无
@return:无
@time:2019-10-20
*/
void voiceControl::voiceReply(QNetworkReply * reply){
    //    qDebug()<<"语音识别返回结果处理:"<< reply->error() << endl;

    if(reply->error() == QNetworkReply::NoError){
        QByteArray all = reply->readAll();
        //        qDebug()<<"开始识别语音："<<all<<endl;
        QJsonParseError jsonError;
        QJsonDocument doucment = QJsonDocument::fromJson(all, &jsonError);  // 转化为 JSON 文档
//        qDebug()<<"识别语音："<<QString(doucment.toJson()).replace("\n","").replace("\"","")<<endl;
        if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError)) {//JSON转换未出错
            if(doucment.isObject()){ // JSON 文档为对象
                QJsonObject object = doucment.object();
                int statusCode = 0;//定义statusCode
                if(object.contains("statusCode")){
                    QJsonValue statusCodeVal = object.value("statusCode");
                    statusCode = statusCodeVal.toString().toInt();
                    qDebug() << "statusCode:" << statusCode << endl;
                }

                //如果statusCode == 1,识别成功，获取指令编码和识别字符串
                if(statusCode == 1){
                    QString instruction_number;
                    QString resultStr;
                    //获取指令编码
                    if(object.contains("instruction_number")){
                        QJsonValue instructionVal = object.value("instruction_number");
                        if(instructionVal.isString()){
                            instruction_number = instructionVal.toString().trimmed();
                            qDebug() << "1111111"<<instruction_number;
                        }
                    }
                    qDebug()<<"instruction_number:"<<instruction_number<<endl;
                    //获取识别字符串并拼接
                    if(object.contains("content")){
                        QJsonValue contentVal = object.value("content");
                        if(contentVal.isObject()){
                            QJsonObject contentObj = contentVal.toObject();
                            if(contentObj.contains("result")){
                                QJsonValue resultsVal = contentObj.value("result");
                                if(resultsVal.isArray()){
                                    QJsonArray resultArray =resultsVal.toArray();
                                    int size = resultArray.size();
                                    for(int i = 0; i < size ; i++){
                                        QJsonValue resultVal = resultArray.at(i);
                                        if(resultVal.isString()){
                                            //                                            QString resultStrT = resultVal.toString().trimmed();
                                            //去掉逗号
                                            resultStr = resultVal.toString().trimmed();

                                            qDebug() << "resultStrT:" << resultStr << endl;
                                            //                                            resultStrT.replace(resultStrT.length()-1,1,"");
                                            //                                            resultStr.append(resultStrT);
                                        }
                                    }
                                }
                            }
                        }
                    }
//                    qDebug()<<"返回结果："<<resultStr<<endl;
//                    this->instructionExp(instruction_number);
                }

                else
                {
//                    qDebug()<<"语音识别失败:"<<endl;

                }
            }
        }
    }
}
/*
@brief:语音合成处理
@param:无
@return:无
@time:2019-10-20
*/
void voiceControl::playReply(QNetworkReply * reply){
    if(reply->error() ==    QNetworkReply::NoError){
        QByteArray all = reply->readAll();
        //        qDebug()<<"语音合成输出：";
        //        qDebug()<<"语音合成输出："<<all<<endl;
        QJsonParseError jsonError;
        QJsonDocument doucment = QJsonDocument::fromJson(all, &jsonError);  // 转化为 JSON 文档
        if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError)) {  // 解析未发生错误
            if(doucment.isObject()){
                QJsonObject object = doucment.object();
                int statusCode = 0;
                if(object.contains("statusCode")){
                    QJsonValue statusVal = object.value("statusCode");
                    if(statusVal.isString()){
                        statusCode = statusVal.toString().toInt();
                    }
                }
                qDebug()<<statusCode<<endl;
                if(statusCode == 1){
                    if(object.contains("content")){
                        QJsonValue contentVal = object.value("content");
                        QByteArray playData;
                        if(contentVal.isString()){
                            playData = contentVal.toString().toLocal8Bit();
                            playData = playData.replace("-","+");
                            playData = playData.replace("_","/");
                            playData = QByteArray::fromBase64(playData);

                            QString baseDir = QCoreApplication::applicationDirPath();
                            QString fileDir = baseDir.append("/files/player/");

                            //文件夹不存在的时候创建
                            QDir dir;
                            if(!dir.exists(fileDir))
                            {
                                bool res = dir.mkpath(fileDir);
                                qDebug() << "创建目录结果:" << res;
                            }

                            fileDir.append(HttpRequest.getCurrentTime());
                            fileDir.append(".wav");
                            QFile file(fileDir);
                            file.open(QIODevice::WriteOnly);
                            QDataStream out(&file);
                            out<<playData;
                            file.close();
                            //播放前，需停止语音识别功能
                            audioRecorder->stop();
                            player->setMedia(QUrl::fromLocalFile(fileDir));
                            player->play();
                            playStatus = true;
                        }
                    }
                }
            }
        }
    }
}
/*
@brief:音频播放状态改变时进行
@param:无
@return:无
@time:2019-10-20
*/
void voiceControl::playChanged()
{
    //    qDebug()<<"player状态："<<player->state()<<endl;
    if( QMediaPlayer::StoppedState==  player->state() && playStatus == true){
        //播放结束时，继续开启语音识别功能
        playStatus = false;
//        qDebug()<<"语音录制开始"<<endl;
        recordNum = 0;
        recordHigh = 0;
        recordLow = 0;
        recordSend = false;
        this->startRecord();
    }
}

/*
@brief:音量级别显示
@param:无
@return:无
@time:2019-10-20
*/
template <class T>
QVector<qreal> getBufferLevels(const T *buffer, int frames, int channels)
{
    QVector<qreal> max_values;
    max_values.fill(0, channels);

    for (int i = 0; i < frames; ++i) {
        for (int j = 0; j < channels; ++j) {
            qreal value = qAbs(qreal(buffer[i * channels + j]));
            if (value > max_values.at(j))
                max_values.replace(j, value);
        }
    }

    return max_values;
}

// This function returns the maximum possible sample value for a given audio format
qreal getPeakValue(const QAudioFormat& format)
{
    // Note: Only the most common sample formats are supported
    if (!format.isValid())
        return qreal(0);

    if (format.codec() != "audio/pcm")
        return qreal(0);

    switch (format.sampleType()) {
    case QAudioFormat::Unknown:
        break;
    case QAudioFormat::Float:
        if (format.sampleSize() != 32) // other sample formats are not supported
            return qreal(0);
        return qreal(1.00003);
    case QAudioFormat::SignedInt:
        if (format.sampleSize() == 32)
            return qreal(INT_MAX);
        if (format.sampleSize() == 16)
            return qreal(SHRT_MAX);
        if (format.sampleSize() == 8)
            return qreal(CHAR_MAX);
        break;
    case QAudioFormat::UnSignedInt:
        if (format.sampleSize() == 32)
            return qreal(UINT_MAX);
        if (format.sampleSize() == 16)
            return qreal(USHRT_MAX);
        if (format.sampleSize() == 8)
            return qreal(UCHAR_MAX);
        break;
    }

    return qreal(0);
}

// returns the audio level for each channel
QVector<qreal> getBufferLevels(const QAudioBuffer& buffer)
{
    QVector<qreal> values;

    if (!buffer.format().isValid() || buffer.format().byteOrder() != QAudioFormat::LittleEndian)
        return values;

    if (buffer.format().codec() != "audio/pcm")
        return values;

    int channelCount = buffer.format().channelCount();
    values.fill(0, channelCount);
    qreal peak_value = getPeakValue(buffer.format());
    if (qFuzzyCompare(peak_value, qreal(0)))
        return values;

    switch (buffer.format().sampleType()) {
    case QAudioFormat::Unknown:
    case QAudioFormat::UnSignedInt:
        if (buffer.format().sampleSize() == 32)
            values = getBufferLevels(buffer.constData<quint32>(), buffer.frameCount(), channelCount);
        if (buffer.format().sampleSize() == 16)
            values = getBufferLevels(buffer.constData<quint16>(), buffer.frameCount(), channelCount);
        if (buffer.format().sampleSize() == 8)
            values = getBufferLevels(buffer.constData<quint8>(), buffer.frameCount(), channelCount);
        for (int i = 0; i < values.size(); ++i)
            values[i] = qAbs(values.at(i) - peak_value / 2) / (peak_value / 2);
        break;
    case QAudioFormat::Float:
        if (buffer.format().sampleSize() == 32) {
            values = getBufferLevels(buffer.constData<float>(), buffer.frameCount(), channelCount);
            for (int i = 0; i < values.size(); ++i)
                values[i] /= peak_value;
        }
        break;
    case QAudioFormat::SignedInt:
        if (buffer.format().sampleSize() == 32)
            values = getBufferLevels(buffer.constData<qint32>(), buffer.frameCount(), channelCount);
        if (buffer.format().sampleSize() == 16)
            values = getBufferLevels(buffer.constData<qint16>(), buffer.frameCount(), channelCount);
        if (buffer.format().sampleSize() == 8)
            values = getBufferLevels(buffer.constData<qint8>(), buffer.frameCount(), channelCount);
        for (int i = 0; i < values.size(); ++i)
            values[i] /= peak_value;
        break;
    }

    return values;
}

void voiceControl::processBuffer(const QAudioBuffer& buffer)
{
    if (audioLevels.count() != buffer.format().channelCount()) {
        qDeleteAll(audioLevels);
        audioLevels.clear();
        for (int i = 0; i < buffer.format().channelCount(); ++i) {
            level = new QAudioLevel();
            audioLevels.append(level);
//            ui->levelLayout->addWidget(level);
        }
    }

    QVector<qreal> levels = getBufferLevels(buffer);
    for (int i = 0; i < levels.count(); ++i)
        audioLevels.at(i)->setLevel(levels.at(i));

    //    qDebug()<<"音量级别："<<levels<<endl;

    recordNum ++;
    if(levels.at(0) >= 0.35){
        recordHigh ++;
        recordLow = 0 ;
    }else{
        recordLow ++;
    }

    //    qDebug()<<"recordNum:"<<recordNum<<endl;
    if(recordNum <= 150){
        //当录音时间小于6秒时
        if(recordHigh >= 2){
            if(recordLow >= 12){
                //当1秒之内无声音时，结束录音
                recordSend = true;
                this->stopRecord();
            }
        }
    }else{
        //当录音时间大于6秒时，结束录音
        if(recordHigh >= 2){
            recordSend = true;
        }else{
            recordSend = false;
        }
        this->stopRecord();
    }
}
