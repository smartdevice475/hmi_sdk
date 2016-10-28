#ifndef CEVIDEOSTREAM_H
#define CEVIDEOSTREAM_H

#include <QWidget>

#include <QPainter>
#include <QQueue>
#include <QDebug>
#include "../hmi_sdk/HMI_SDK/Connect/IMessageInterface.h"

#include "Common/Button.h"
#include "AppListInterface.h"

#define TEST_FILE

typedef struct dataPackage{
    uchar buf[1024];
    int len;
}DataS;

class CeVideoStream : public QWidget, public IMessageInterface
{
    Q_OBJECT
public:
    explicit CeVideoStream(AppListInterface * pList,QWidget *parent = 0);
    ~CeVideoStream();

    void startStream();
    void stopStream();

public: //IMessageInterface
    Result onRequest(Json::Value) {return RESULT_SUCCESS;}
    void onNotification(Json::Value) {}
    void onResult(Json::Value) {}
    void onRawData(void * p, int iLength);
    void onError(std::string error) {}
signals:

public slots:

private:

#ifdef SDL_CALL_BACK
    static void callBack_send_data(const char *data, int size);
#endif

#ifdef TEST_FILE
    FILE *fp;
#endif
};

#endif // CEVIDEOSTREAM_H