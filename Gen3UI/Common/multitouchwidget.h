#ifndef MULTITOUCHWIDGET_H
#define MULTITOUCHWIDGET_H

#include <QWidget>
#include <vector>
#include <list>
#include <QMouseEvent>

class MultiTouchWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MultiTouchWidget(QWidget *parent = 0);
    ~MultiTouchWidget();

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

    enum TouchType{MOUSE_PRESS,MOUSE_MOVE,MOUSE_RELEASE};
signals:
    void MultiTouchSignal(TouchType type,unsigned char id,QPoint ponit);
public slots:

private:
    struct TouchTrack
    {
        unsigned char id;
        std::vector<QPoint> point_vec;
    };

    std::list<TouchTrack> touch_track_list_;
    unsigned char next_id_;

    std::list<TouchTrack>::iterator PointInTrack(QPoint point);
};

#endif // MULTITOUCHWIDGET_H
