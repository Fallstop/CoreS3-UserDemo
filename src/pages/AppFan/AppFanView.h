#ifndef __APPFAN_VIEW_H
#define __APPFAN_VIEW_H

#include "../Page.h"

namespace Page {

class AppFanView {
   public:
    void Create(lv_obj_t* root);
    void Delete();

   public:
    struct {
        lv_obj_t* labelTitle;
        lv_obj_t* slider_speed;
        lv_obj_t* label_speed_value;
        lv_obj_t* sw_on_off;
        lv_obj_t* label_rpm_value;
        lv_obj_t* imgbtn_home;
    } ui;

   private:
};

}  // namespace Page

#endif  // !__VIEW_H
