#include "previewfile.h"

PreviewFile::PreviewFile(QObject *parent) : QThread(parent)
{
    ipAddress = "http://211.157.179.73:9580";
    mainMangerNetwork = new QNetworkAccessManager(this);
}
void PreviewFile::run()
{

}

