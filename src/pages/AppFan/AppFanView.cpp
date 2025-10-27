#include "AppFanView.h"

using namespace Page;

void AppFanView::Create(lv_obj_t* root) {
    ui.imgbtn_home = lv_imgbtn_create(root);
    lv_obj_set_size(ui.imgbtn_home, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_imgbtn_set_src(ui.imgbtn_home, LV_IMGBTN_STATE_RELEASED, NULL,
                      ResourcePool::GetImage("home_r"), NULL);
    lv_imgbtn_set_src(ui.imgbtn_home, LV_IMGBTN_STATE_PRESSED, NULL,
                      ResourcePool::GetImage("home_p"), NULL);
    lv_obj_align(ui.imgbtn_home, LV_ALIGN_TOP_LEFT, 0, 0);

    lv_obj_t* label = lv_label_create(root);
    lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 20);
    lv_label_set_text(label, "");
    ui.labelTitle = label;

    // Create a switch to control the fan on/off
    lv_obj_t* sw = lv_switch_create(root);
    lv_obj_align(sw, LV_ALIGN_TOP_RIGHT, -20, 60);
    ui.sw_on_off = sw;

    label = lv_label_create(root);
    lv_label_set_text(label, "Fan ON/OFF");
    lv_obj_align_to(label, sw, LV_ALIGN_OUT_LEFT_MID, -10, 0);

    // Create a slider to control the fan speed
    lv_obj_t* slider = lv_slider_create(root);
    lv_obj_set_width(slider, 200);
    lv_obj_align(slider, LV_ALIGN_CENTER, 0, 20);
    lv_slider_set_range(slider, 0, 100);
    lv_slider_set_value(slider, 50, LV_ANIM_OFF);
    ui.slider_speed = slider;

    label = lv_label_create(root);
    lv_label_set_text(label, "Speed");
    lv_obj_align_to(label, slider, LV_ALIGN_OUT_LEFT_MID, -10, 0);

    label = lv_label_create(root);
    lv_label_set_text(label, "50%");
    lv_obj_align_to(label, slider, LV_ALIGN_OUT_RIGHT_MID, 10, 0);
    ui.label_speed_value = label;

    // Create a label to show the fan RPM
    label = lv_label_create(root);
    lv_label_set_text(label, "RPM: ");
    lv_obj_align(label, LV_ALIGN_BOTTOM_LEFT, 20, -20);

    label = lv_label_create(root);
    lv_label_set_text(label, "0");
    lv_obj_align_to(label, ui.labelTitle, LV_ALIGN_BOTTOM_LEFT, 10, -20);
    ui.label_rpm_value = label;
}

void AppFanView::Delete() {
}
