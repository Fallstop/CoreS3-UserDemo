#include "AppFan.h"
#include "m5_module_fan.hpp"

using namespace Page;

static M5ModuleFan fan;

AppFan::AppFan() : timer(nullptr), fan_speed(50) {
}

AppFan::~AppFan() {
}

void AppFan::onCustomAttrConfig() {
}

void AppFan::onViewLoad() {
    View.Create(_root);
    lv_label_set_text(View.ui.labelTitle, _Name);

    AttachEvent(View.ui.imgbtn_home, LV_EVENT_CLICKED);
    AttachEvent(View.ui.slider_speed, LV_EVENT_VALUE_CHANGED);
    AttachEvent(View.ui.sw_on_off, LV_EVENT_VALUE_CHANGED);
    USBSerial.println("Test");
    fan.begin();
    USBSerial.println("Fan initialized");
}

void AppFan::onViewDidLoad() {
}

void AppFan::onViewWillAppear() {
    timer = lv_timer_create(onTimerUpdate, 1000, this);
}

void AppFan::onViewDidAppear() {
}

void AppFan::onViewWillDisappear() {
}

void AppFan::onViewDidDisappear() {
    lv_timer_del(timer);
}

void AppFan::onViewUnload() {
    View.Delete();
}

void AppFan::onViewDidUnload() {
}

void AppFan::AttachEvent(lv_obj_t* obj, lv_event_code_t code) {
    lv_obj_set_user_data(obj, this);
    lv_obj_add_event_cb(obj, onEvent, code, this);
}

void AppFan::Update() {
    USBSerial.println("Update");

    // int rpm = fan.getRPM();
    USBSerial.println("Update Completed");

    // lv_label_set_text_fmt(View.ui.label_rpm_value, "%d", rpm);
}

void AppFan::onTimerUpdate(lv_timer_t* timer) {
    AppFan* instance = (AppFan*)timer->user_data;
    instance->Update();
}

void AppFan::onEvent(lv_event_t* event) {
    USBSerial.println("AppFan::onEvent called");
    AppFan* instance = (AppFan*)lv_event_get_user_data(event);
    LV_ASSERT_NULL(instance);

    lv_obj_t* obj        = lv_event_get_current_target(event);
    lv_event_code_t code = lv_event_get_code(event);

    if (obj == instance->View.ui.imgbtn_home) {
        USBSerial.print("AppFan::onEvent: Home button:");
        USBSerial.println(code);
        if (code == LV_EVENT_CLICKED) {
            instance->_Manager->Pop();
        }
        return;
    }

    if (obj == instance->View.ui.slider_speed) {
        if (code == LV_EVENT_VALUE_CHANGED) {
            USBSerial.println("AppFan::onEvent: Slider value changed");

            instance->fan_speed = lv_slider_get_value(obj);
            fan.setPWMDutyCycle(instance->fan_speed);
            lv_label_set_text_fmt(instance->View.ui.label_speed_value, "%d%%", instance->fan_speed);
        }
    } else if (obj == instance->View.ui.sw_on_off) {
        if (code == LV_EVENT_VALUE_CHANGED) {
            USBSerial.println("AppFan::onEvent: Switch toggled");
            if (lv_obj_has_state(obj, LV_STATE_CHECKED)) {
                fan.setPWMDutyCycle(instance->fan_speed);
                lv_obj_add_state(instance->View.ui.slider_speed, LV_STATE_DEFAULT);
            } else {
                fan.setPWMDutyCycle(0);
                lv_obj_add_state(instance->View.ui.slider_speed, LV_STATE_DISABLED);
            }
        }
    }
}
