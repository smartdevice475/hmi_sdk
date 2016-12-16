#include "AudioPassView.h"
#include <QBoxLayout>

CAudioPassView::CAudioPassView(AppListInterface * pList, QWidget *parent) : QWidget(parent)
{
    if (parent) {
        setGeometry(0,0,parent->width(),parent->height());
    }
    m_pList = pList;

    setAutoFillBackground(true);
    QPixmap pixmap(":/images/choicevr_back.png");
    pixmap = pixmap.scaled(width(),height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(pixmap));
    setPalette(palette);


    QVBoxLayout *main_layout = new QVBoxLayout(this);

    QHBoxLayout *center_layout = new QHBoxLayout;
    QHBoxLayout *bottom_layout = new QHBoxLayout;
    QVBoxLayout *text_layout = new QVBoxLayout;

    app_name_lab_ = new QLabel;
    audio_text_ = new QLabel[2];
    audio_icon_ = new QLabel;
    audio_button_ = new CCustomButton[3];

    main_layout->addWidget(app_name_lab_);
    main_layout->addLayout(center_layout,1);
    main_layout->addLayout(bottom_layout);
    center_layout->addWidget(audio_icon_,1);
    center_layout->addLayout(text_layout,4);
    text_layout->addWidget(&audio_text_[0]);
    text_layout->addWidget(&audio_text_[1]);

    for(int i = 0;i != 3;++i) {
        bottom_layout->addWidget(&audio_button_[i]);
    }

    app_name_lab_->setStyleSheet(
                "font: 36px \"Liberation Serif\";color:rgb(0,0,0)");
    app_name_lab_->setAlignment(Qt::AlignCenter);

    for (int i = 0; i != 2; ++i) {
      audio_text_[i].setStyleSheet(
                  "font: 32px \"Liberation Serif\";color:rgb(0,0,0)");
      audio_text_[i].setAlignment(Qt::AlignCenter);
    }

    for (int i = 0; i != 3; ++i) {
        audio_button_[i].SetTextStyle(
                    "font: 32px \"Liberation Serif\";color:rgb(0,0,0)");
        connect(audio_button_ + i,SIGNAL(Clicked(int)),
                this,SLOT(OnButtonClicked(int)));
    }
    audio_button_[0].Init(width()*0.22,width()*0.07,"重试",
                       ":/images/alert_softbtn_normal.png",
                       ":/images/alert_softbtn_press.png");
    audio_button_[1].Init(width()*0.22,width()*0.07,"完成",
                       ":/images/alert_softbtn_normal.png",
                       ":/images/alert_softbtn_press.png");
    audio_button_[2].Init(width()*0.22,width()*0.07,"返回",
                       ":/images/alert_softbtn_normal.png",
                       ":/images/alert_softbtn_press.png");

    connect(&timer_,SIGNAL(timeout()),SLOT(OnTimeOut()));
    connect(this,SIGNAL(AudioPassThruHide(int)),SLOT(AudioPassThruHideSlot(int)));
}


CAudioPassView::~CAudioPassView()
{

}

void CAudioPassView::OnTimeOut()
{
    timer_.stop();
    emit AudioPassThruHide(PERFORMAUDIOPASSTHRU_TIMEOUT);
}

void CAudioPassView::OnButtonClicked(int id)
{
    if(id >= 0)
    {
        timer_.stop();
        emit AudioPassThruHide(id);
    }
}

void CAudioPassView::AudioPassThruHideSlot(int code)
{
    AppControl->OnPerformAudioPassThru(code);
}

void CAudioPassView::showEvent(QShowEvent * e)
{
  if (AppControl) {
    AppBase::SetEdlidedText(app_name_lab_,AppControl->getAppName().c_str(),
                            width()*0.9);

    Json::Value m_jsonData = AppControl->getAudioPassThruJson();
    LOGD("---CAudioPassThru::showEvent   %s",m_jsonData.toStyledString().c_str());
    if(!m_jsonData.isMember("id") || !m_jsonData.isMember("params")) {
      return;
    }

    timer_.start(m_jsonData["params"]["maxDuration"].asInt());

    Json::Value text_json = m_jsonData["params"]["audioPassThruDisplayTexts"];

    for (int i = 0; i < text_json.size(); i++) {
      if ("audioPassThruDisplayText1" == text_json[i]["fieldName"].asString()){
        AppBase::SetEdlidedText(&audio_text_[i],
                                text_json[i]["fieldText"].asString().c_str(),
                                width()*0.9);
      }
      else if ("audioPassThruDisplayText2" == text_json[i]["fieldName"].asString()) {
        AppBase::SetEdlidedText(&audio_text_[i],
                                text_json[i]["fieldText"].asString().c_str(),
                                width()*0.9);
      }
    }
  }
}
