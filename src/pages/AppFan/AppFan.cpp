#include "AppFan.h"
#include "m5_module_fan.hpp"

using namespace Page;

static M5ModuleFan fan;

AppFan::AppFan() : timer(nullptr), fan_speed(50) {

    if (!fan.begin(&Wire1, MODULE_FAN_BASE_ADDR, 12, 11, 400000L)) {
        USBSerial.println("Fan initialization failed");
    } else {
        // Print firmware version
        uint8_t fwVersion = fan.getFirmwareVersion();
        USBSerial.print("Fan firmware version: ");
        USBSerial.println(fwVersion, HEX);
        fan.setPWMFrequency(PWM_48KHZ);
        fan.setStatus(MODULE_FAN_ENABLE);
    }
}

AppFan::~AppFan() {
}

void AppFan::onCustomAttrConfig() {
}

void AppFan::onViewLoad() {
    View.Create(_root);
    lv_label_set_text(View.ui.labelTitle, _Name);

    AttachEvent(View.ui.imgbtn_home, LV_EVENT_CLICKED);
    AttachEvent(View.ui.slider_speed);
    AttachEvent(View.ui.sw_on_off, LV_EVENT_VALUE_CHANGED);

    fan.setPWMDutyCycle(fan_speed);
    lv_slider_set_value(View.ui.slider_speed, fan_speed, LV_ANIM_OFF);
    lv_label_set_text_fmt(View.ui.label_speed_value, "%d%%", fan_speed);

    if (fan.getStatus() == MODULE_FAN_ENABLE) {
        lv_obj_add_state(View.ui.sw_on_off, LV_STATE_CHECKED);
        lv_obj_clear_state(View.ui.slider_speed, LV_STATE_DISABLED);
    } else {
        lv_obj_clear_state(View.ui.sw_on_off, LV_STATE_CHECKED);
        lv_obj_add_state(View.ui.slider_speed, LV_STATE_DISABLED);
    }
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
    int rpm = fan.getRPM();
    lv_label_set_text_fmt(View.ui.label_rpm_value, "%d", rpm);
}

void AppFan::onTimerUpdate(lv_timer_t* timer) {
    AppFan* instance = (AppFan*)timer->user_data;
    instance->Update();
}

void AppFan::onEvent(lv_event_t* event) {
    AppFan* instance = (AppFan*)lv_event_get_user_data(event);
    LV_ASSERT_NULL(instance);

    lv_obj_t* obj        = lv_event_get_current_target(event);
    lv_event_code_t code = lv_event_get_code(event);

    if (obj == instance->View.ui.imgbtn_home) {
        USBSerial.print("AppFan::onEvent: Home button:");
        USBSerial.println(code);
        if (code == LV_EVENT_CLICKED) {
            instance->_Manager->Replace("Pages/HomeMenu");
        }
        return;
    }

    if (obj == instance->View.ui.slider_speed) {
        if (code == LV_EVENT_RELEASED || code == LV_EVENT_VALUE_CHANGED) {
            USBSerial.print("AppFan::onEvent: Slider value changed");
            USBSerial.print(" Value: ");
            instance->fan_speed = lv_slider_get_value(obj);
            USBSerial.println(instance->fan_speed);
            fan.setPWMDutyCycle(instance->fan_speed);

            lv_label_set_text_fmt(instance->View.ui.label_speed_value, "%d%%", instance->fan_speed);

            if (code == LV_EVENT_RELEASED) {
                fan.saveConfig();
            }
        }
    } else if (obj == instance->View.ui.sw_on_off) {
        if (code == LV_EVENT_VALUE_CHANGED) {
            USBSerial.println("AppFan::onEvent: Switch toggled");
            if (lv_obj_has_state(obj, LV_STATE_CHECKED)) {
                fan.setStatus(MODULE_FAN_ENABLE);
                fan.saveConfig();
                lv_obj_clear_state(instance->View.ui.slider_speed, LV_STATE_DISABLED);
            } else {
                fan.setStatus(MODULE_FAN_DISABLE);
                fan.saveConfig();
                lv_obj_add_state(instance->View.ui.slider_speed, LV_STATE_DISABLED);
            }
        }
    }
}
