#include "multitouchwidget.h"
#include <math.h>
#include "global_first.h"

MultiTouchWidget::MultiTouchWidget(QWidget *parent) : QWidget(parent),
    next_id_(0)
{

}

MultiTouchWidget::~MultiTouchWidget()
{

}

void MultiTouchWidget::mousePressEvent(QMouseEvent *e)
{
    LOGD("------x=%d,y=%d",e->x(),e->y());
    TouchTrack new_track;
    new_track.id = next_id_;
    ++next_id_;

    new_track.point_vec.push_back(e->pos());
    touch_track_list_.push_back(new_track);

    emit MultiTouchSignal(MOUSE_PRESS,new_track.id,e->pos());
}

void MultiTouchWidget::mouseMoveEvent(QMouseEvent *e)
{
    LOGD("------x=%d,y=%d",e->x(),e->y());
    std::list<TouchTrack>::iterator track = PointInTrack(e->pos());
    track->point_vec.push_back(e->pos());

    emit MultiTouchSignal(MOUSE_MOVE,track->id,e->pos());
}

void MultiTouchWidget::mouseReleaseEvent(QMouseEvent *e)
{
    LOGD("------x=%d,y=%d",e->x(),e->y());
    std::list<TouchTrack>::iterator release_track = PointInTrack(e->pos());
    if(release_track->id < next_id_) {
        next_id_ = release_track->id;
    }
    touch_track_list_.erase(release_track);

    emit MultiTouchSignal(MOUSE_RELEASE,release_track->id,e->pos());
}

std::list<MultiTouchWidget::TouchTrack>::iterator  MultiTouchWidget::PointInTrack(
        QPoint point)
{
    std::list<TouchTrack>::iterator track_find_it;
    double min_distance = 0;
    double distance = 0;

    if(1 == touch_track_list_.size()) {
        return touch_track_list_.begin();
    } else {
        std::list<TouchTrack>::iterator track_list_it = touch_track_list_.begin();
        while(track_list_it != touch_track_list_.end()) {
            distance = sqrt(
                        pow(point.x() - track_list_it->point_vec.back().x()
                            ,2.0) +
                        pow(point.y() - track_list_it->point_vec.back().y()
                            ,2.0));

            if(0 == min_distance || distance < min_distance) {
                min_distance = distance;
                track_find_it = track_list_it;
            }

            ++track_list_it;
        }

        return track_find_it;
    }
}
