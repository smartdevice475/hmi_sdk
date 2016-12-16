#ifndef AUDIOPASSVIEW_H
#define AUDIOPASSVIEW_H

#include <QWidget>
#include "Common/AppBase.h"
#include "Common/CustomButton.h"

class CAudioPassView : public QWidget
{
    Q_OBJECT
public:
    explicit CAudioPassView(AppListInterface *pList,QWidget *parent = 0);
    ~CAudioPassView();
signals:
  void AudioPassThruHide(int);
public slots:
  void AudioPassThruHideSlot(int code);
  void OnButtonClicked(int id);
  void OnTimeOut();
protected:
    virtual void showEvent(QShowEvent * e);
private:
    AppListInterface *m_pList;

    QLabel *app_name_lab_;
    QLabel *audio_text_;
    QLabel *audio_icon_;
    CCustomButton *audio_button_;

    QTimer timer_;
};

#endif // AUDIOPASSVIEW_H
