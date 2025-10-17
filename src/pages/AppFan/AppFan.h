#ifndef __APPFAN_PRESENTER_H
#define __APPFAN_PRESENTER_H

#include "AppFanView.h"
#include "AppFanModel.h"

namespace Page {

class AppFan : public PageBase {
   public:
    AppFan();
    virtual ~AppFan();

    virtual void onCustomAttrConfig();
    virtual void onViewLoad();
    virtual void onViewDidLoad();
    virtual void onViewWillAppear();
    virtual void onViewDidAppear();
    virtual void onViewWillDisappear();
    virtual void onViewDidDisappear();
    virtual void onViewUnload();
    virtual void onViewDidUnload();

   private:
    void Update();
    void AttachEvent(lv_obj_t* obj) {
        AttachEvent(obj, LV_EVENT_ALL);
    }
    void AttachEvent(lv_obj_t* obj, lv_event_code_t code);
    static void onTimerUpdate(lv_timer_t* timer);
    static void onEvent(lv_event_t* event);

   private:
    AppFanView View;
    AppFanModel Model;
    lv_timer_t* timer;
    int fan_speed;
};

}  // namespace Page

#endif
