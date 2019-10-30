#ifndef QRDECODE_H
#define QRDECODE_H

#include <QObject>

class QrDecode : public QObject
{
    Q_OBJECT
public:
    explicit QrDecode(QObject *parent = nullptr);

signals:

public slots:
};

#endif // QRDECODE_H
