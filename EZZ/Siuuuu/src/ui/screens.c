#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include <string.h>

objects_t objects;
lv_obj_t *tick_value_change_obj;

static void event_handler_cb_login_screen_button_matrix(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 0, 0, e);
    }
}

static void event_handler_cb_login_screen_textarea_password(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            const char *value = lv_textarea_get_text(ta);
            assignStringProperty(flowState, 2, 4, value, "Failed to assign Text in Textarea widget");
        }
    }
}

static void event_handler_cb_login_screen_ojo_button(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 3, 0, e);
    }
}

static void event_handler_cb_login_screen_textarea_plain(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            const char *value = lv_textarea_get_text(ta);
            assignStringProperty(flowState, 5, 4, value, "Failed to assign Text in Textarea widget");
        }
    }
}

static void event_handler_cb_login_screen_ojo_button_1(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 6, 0, e);
    }
}

static void event_handler_cb_menu_checkbox_r(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 9, 4, value, "Failed to assign Checked state");
        }
    }
}

static void event_handler_cb_menu_checkbox_ir(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 10, 4, value, "Failed to assign Checked state");
        }
    }
}

static void event_handler_cb_menu_checkbox_v(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 11, 4, value, "Failed to assign Checked state");
        }
    }
}

static void event_handler_cb_menu_led_0_v(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 16, 3, value, "Failed to assign Checked state");
        }
    }
}

static void event_handler_cb_menu_led_1_r(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 17, 3, value, "Failed to assign Checked state");
        }
    }
}

static void event_handler_cb_menu_led_2_ir(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 18, 3, value, "Failed to assign Checked state");
        }
    }
}

static void event_handler_cb_menu_led_3_v(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 19, 3, value, "Failed to assign Checked state");
        }
    }
}

static void event_handler_cb_menu_led_4_ir(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 20, 3, value, "Failed to assign Checked state");
        }
    }
}

static void event_handler_cb_menu_led_5_r(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 21, 3, value, "Failed to assign Checked state");
        }
    }
}

static void event_handler_cb_menu_led_6_r(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 22, 3, value, "Failed to assign Checked state");
        }
    }
}

static void event_handler_cb_menu_led_7_v(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 23, 3, value, "Failed to assign Checked state");
        }
    }
}

static void event_handler_cb_menu_led_8_r(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 24, 3, value, "Failed to assign Checked state");
        }
    }
}

static void event_handler_cb_menu_led_9_ir(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 25, 3, value, "Failed to assign Checked state");
        }
    }
}

static void event_handler_cb_menu_button_plus(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_CLICKED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 30, 0, e);
    }
    if (event == LV_EVENT_LONG_PRESSED_REPEAT) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 30, 1, e);
    }
}

static void event_handler_cb_menu_button_minus(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_CLICKED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 32, 0, e);
    }
    if (event == LV_EVENT_LONG_PRESSED_REPEAT) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 32, 1, e);
    }
}

static void event_handler_cb_menu_button_play(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_CLICKED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 39, 0, e);
    }
}

static void event_handler_cb_menu_botton_settings(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_CLICKED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 41, 0, e);
    }
}

static void event_handler_cb_menu_botton_reset(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_CLICKED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 43, 0, e);
    }
}

static void event_handler_cb_menu_botton_stop(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_CLICKED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 45, 0, e);
    }
}

static void event_handler_cb_settings_button_idioma(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 11, 0, e);
    }
}

static void event_handler_cb_settings_button_change_pwrd(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 15, 0, e);
    }
}

static void event_handler_cb_settings_switch_wifi(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 25, 3, value, "Failed to assign Checked state");
        }
    }
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 25, 0, e);
    }
}

static void event_handler_cb_settings_button_back(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_CLICKED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 26, 0, e);
    }
}

static void event_handler_cb_cambio_password_textarea_current(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            const char *value = lv_textarea_get_text(ta);
            assignStringProperty(flowState, 11, 3, value, "Failed to assign Text in Textarea widget");
        }
    }
    
    if (event == LV_EVENT_FOCUSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 11, 0, e);
    }
}

static void event_handler_cb_cambio_password_textarea_new(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            const char *value = lv_textarea_get_text(ta);
            assignStringProperty(flowState, 13, 3, value, "Failed to assign Text in Textarea widget");
        }
    }
    
    if (event == LV_EVENT_FOCUSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 13, 0, e);
    }
}

static void event_handler_cb_cambio_password_textarea_confirm(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            const char *value = lv_textarea_get_text(ta);
            assignStringProperty(flowState, 15, 3, value, "Failed to assign Text in Textarea widget");
        }
    }
    
    if (event == LV_EVENT_FOCUSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 15, 0, e);
    }
}

static void event_handler_cb_cambio_password_button_back_1(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_CLICKED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 17, 0, e);
    }
}

static void event_handler_cb_cambio_password_button_guardar(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 19, 0, e);
    }
}

static void event_handler_cb_cambio_password_button_matrix_1(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 21, 0, e);
    }
}

void create_screen_splash_screen() {
    void *flowState = getFlowState(0, 0);
    (void)flowState;
    lv_obj_t *obj = lv_obj_create(0);
    objects.splash_screen = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 240, 320);
    {
        lv_obj_t *parent_obj = obj;
        {
            // branch_Fisser_HandBeam10d
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.branch_fisser_hand_beam10d = obj;
            lv_obj_set_pos(obj, 44, 33);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff2196f3), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Fisser HandBeam10D");
        }
        {
            // load_bar
            lv_obj_t *obj = lv_bar_create(parent_obj);
            objects.load_bar = obj;
            lv_obj_set_pos(obj, 45, 249);
            lv_obj_set_size(obj, 150, 10);
        }
    }
    
    tick_screen_splash_screen();
}

void tick_screen_splash_screen() {
    void *flowState = getFlowState(0, 0);
    (void)flowState;
    {
        int32_t new_val = evalIntegerProperty(flowState, 2, 3, "Failed to evaluate Value in Bar widget");
        int32_t cur_val = lv_bar_get_value(objects.load_bar);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.load_bar;
            lv_bar_set_value(objects.load_bar, new_val, LV_ANIM_ON);
            tick_value_change_obj = NULL;
        }
    }
}

void create_screen_login_screen() {
    void *flowState = getFlowState(0, 1);
    (void)flowState;
    lv_obj_t *obj = lv_obj_create(0);
    objects.login_screen = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 240, 320);
    {
        lv_obj_t *parent_obj = obj;
        {
            // button_matrix
            lv_obj_t *obj = lv_buttonmatrix_create(parent_obj);
            objects.button_matrix = obj;
            lv_obj_set_pos(obj, 24, 86);
            lv_obj_set_size(obj, 193, 234);
            static const char *map[16] = {
                "1",
                "2",
                "3",
                "\n",
                "4",
                "5",
                "6",
                "\n",
                "7",
                "8",
                "9",
                "\n",
                "DEL",
                "0",
                "OK",
                NULL,
            };
            lv_buttonmatrix_set_map(obj, map);
            lv_obj_add_event_cb(obj, event_handler_cb_login_screen_button_matrix, LV_EVENT_ALL, flowState);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff11a1fb), LV_PART_ITEMS | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff11a1fb), LV_PART_ITEMS | LV_STATE_PRESSED);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfff5f5f5), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // textarea_password
            lv_obj_t *obj = lv_textarea_create(parent_obj);
            objects.textarea_password = obj;
            lv_obj_set_pos(obj, 13, 41);
            lv_obj_set_size(obj, 216, 37);
            lv_textarea_set_max_length(obj, 20);
            lv_textarea_set_placeholder_text(obj, "           Ingrese el PIN");
            lv_textarea_set_one_line(obj, true);
            lv_textarea_set_password_mode(obj, true);
            lv_obj_add_event_cb(obj, event_handler_cb_login_screen_textarea_password, LV_EVENT_ALL, flowState);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff0da2ef), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_grad_stop(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff1d54d3), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // ojo_button
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.ojo_button = obj;
                    lv_obj_set_pos(obj, 163, 0);
                    lv_obj_set_size(obj, 24, 17);
                    lv_obj_add_event_cb(obj, event_handler_cb_login_screen_ojo_button, LV_EVENT_ALL, flowState);
                    lv_obj_set_style_shadow_color(obj, lv_color_hex(0xff0da2ef), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff0da2ef), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_image_recolor(obj, lv_color_hex(0xff0da2ef), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // ojo
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.ojo = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "\uF06E");
                        }
                    }
                }
            }
        }
        {
            // textarea_plain
            lv_obj_t *obj = lv_textarea_create(parent_obj);
            objects.textarea_plain = obj;
            lv_obj_set_pos(obj, 13, 41);
            lv_obj_set_size(obj, 216, 37);
            lv_textarea_set_max_length(obj, 20);
            lv_textarea_set_placeholder_text(obj, "           Ingrese el PIN");
            lv_textarea_set_one_line(obj, true);
            lv_textarea_set_password_mode(obj, false);
            lv_obj_add_event_cb(obj, event_handler_cb_login_screen_textarea_plain, LV_EVENT_ALL, flowState);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff0da2ef), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_grad_stop(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff1d54d3), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // ojo_button_1
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.ojo_button_1 = obj;
                    lv_obj_set_pos(obj, 163, 0);
                    lv_obj_set_size(obj, 24, 17);
                    lv_obj_add_event_cb(obj, event_handler_cb_login_screen_ojo_button_1, LV_EVENT_ALL, flowState);
                    lv_obj_set_style_shadow_color(obj, lv_color_hex(0xff0da2ef), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff0da2ef), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_image_recolor(obj, lv_color_hex(0xff0da2ef), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // ojo_1
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.ojo_1 = obj;
                            lv_obj_set_pos(obj, -2, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, " \uF070");
                        }
                    }
                }
            }
        }
        {
            // Benchmark_name_1
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.benchmark_name_1 = obj;
            lv_obj_set_pos(obj, 43, 10);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff1f90d6), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Fisser HandBeam 10D");
        }
        {
            // CONTAINER_NOTIFICATION_PIN_WRONG
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.container_notification_pin_wrong = obj;
            lv_obj_set_pos(obj, 76, 26);
            lv_obj_set_size(obj, 89, 38);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffff8a8a), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff81ff92), LV_PART_MAIN | LV_STATE_CHECKED);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 3);
                    lv_obj_set_size(obj, LV_PCT(100), LV_SIZE_CONTENT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "PIN\nIncorrecto");
                }
            }
        }
    }
    
    tick_screen_login_screen();
}

void tick_screen_login_screen() {
    void *flowState = getFlowState(0, 1);
    (void)flowState;
    {
        bool new_val = evalBooleanProperty(flowState, 2, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.textarea_password, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.textarea_password;
            if (new_val) lv_obj_add_flag(objects.textarea_password, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.textarea_password, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 2, 4, "Failed to evaluate Text in Textarea widget");
        const char *cur_val = lv_textarea_get_text(objects.textarea_password);
        uint32_t max_length = lv_textarea_get_max_length(objects.textarea_password);
        if (strncmp(new_val, cur_val, max_length) != 0) {
            tick_value_change_obj = objects.textarea_password;
            lv_textarea_set_text(objects.textarea_password, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 5, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.textarea_plain, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.textarea_plain;
            if (new_val) lv_obj_add_flag(objects.textarea_plain, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.textarea_plain, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 5, 4, "Failed to evaluate Text in Textarea widget");
        const char *cur_val = lv_textarea_get_text(objects.textarea_plain);
        uint32_t max_length = lv_textarea_get_max_length(objects.textarea_plain);
        if (strncmp(new_val, cur_val, max_length) != 0) {
            tick_value_change_obj = objects.textarea_plain;
            lv_textarea_set_text(objects.textarea_plain, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 9, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.container_notification_pin_wrong, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.container_notification_pin_wrong;
            if (new_val) lv_obj_add_flag(objects.container_notification_pin_wrong, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.container_notification_pin_wrong, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
}

void create_screen_menu() {
    void *flowState = getFlowState(0, 2);
    (void)flowState;
    lv_obj_t *obj = lv_obj_create(0);
    objects.menu = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 240, 320);
    {
        lv_obj_t *parent_obj = obj;
        {
            // Benchmark_name_2
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.benchmark_name_2 = obj;
            lv_obj_set_pos(obj, 10, 8);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff1f90d6), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Fisser HandBeam 10D");
        }
        {
            // bench_line
            lv_obj_t *obj = lv_line_create(parent_obj);
            objects.bench_line = obj;
            lv_obj_set_pos(obj, 6, 24);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            static lv_point_precise_t line_points[] = {
                { 0, 0 },
                { 0, 0 },
                { 0, 0 },
                { 0, 0 },
                { 230, 0 }
            };
            lv_line_set_points(obj, line_points, 5);
            lv_obj_set_style_line_color(obj, lv_color_hex(0xff1f90d6), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // charge_zero
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.charge_zero = obj;
            lv_obj_set_pos(obj, 206, 8);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "\uF244 ");
        }
        {
            // charge_quarter
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.charge_quarter = obj;
            lv_obj_set_pos(obj, 206, 8);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "\uF243");
        }
        {
            // charge_half
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.charge_half = obj;
            lv_obj_set_pos(obj, 206, 8);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "\uF242");
        }
        {
            // charge_threeQuarter
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.charge_three_quarter = obj;
            lv_obj_set_pos(obj, 202, 8);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, " \uF241 ");
        }
        {
            // charge_full
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.charge_full = obj;
            lv_obj_set_pos(obj, 206, 8);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "\uF240");
        }
        {
            // charge_on
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.charge_on = obj;
            lv_obj_set_pos(obj, 210, 8);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "\uF0E7");
        }
        {
            // checkbox_R
            lv_obj_t *obj = lv_checkbox_create(parent_obj);
            objects.checkbox_r = obj;
            lv_obj_set_pos(obj, 88, 54);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_checkbox_set_text(obj, "");
            lv_obj_add_event_cb(obj, event_handler_cb_menu_checkbox_r, LV_EVENT_ALL, flowState);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_34, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfff5f5f5), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff007acc), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }
        {
            // checkbox_IR
            lv_obj_t *obj = lv_checkbox_create(parent_obj);
            objects.checkbox_ir = obj;
            lv_obj_set_pos(obj, 190, 55);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_checkbox_set_text(obj, "");
            lv_obj_add_event_cb(obj, event_handler_cb_menu_checkbox_ir, LV_EVENT_ALL, flowState);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_34, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfff5f5f5), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff007acc), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }
        {
            // checkbox_V
            lv_obj_t *obj = lv_checkbox_create(parent_obj);
            objects.checkbox_v = obj;
            lv_obj_set_pos(obj, 139, 54);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_checkbox_set_text(obj, "");
            lv_obj_add_event_cb(obj, event_handler_cb_menu_checkbox_v, LV_EVENT_ALL, flowState);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_34, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfff5f5f5), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff007acc), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 100, 31);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "R");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 152, 31);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "V");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 200, 32);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "IR");
        }
        {
            // CONTAINER_LEDS
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.container_leds = obj;
            lv_obj_set_pos(obj, 6, 36);
            lv_obj_set_size(obj, 65, 80);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // led_0V
                    lv_obj_t *obj = lv_led_create(parent_obj);
                    objects.led_0_v = obj;
                    lv_obj_set_pos(obj, 6, 14);
                    lv_obj_set_size(obj, 10, 8);
                    lv_led_set_brightness(obj, 255);
                    lv_obj_add_event_cb(obj, event_handler_cb_menu_led_0_v, LV_EVENT_ALL, flowState);
                }
                {
                    // led_1R
                    lv_obj_t *obj = lv_led_create(parent_obj);
                    objects.led_1_r = obj;
                    lv_obj_set_pos(obj, 6, 34);
                    lv_obj_set_size(obj, 10, 8);
                    lv_led_set_brightness(obj, 255);
                    lv_obj_add_event_cb(obj, event_handler_cb_menu_led_1_r, LV_EVENT_ALL, flowState);
                }
                {
                    // led_2IR
                    lv_obj_t *obj = lv_led_create(parent_obj);
                    objects.led_2_ir = obj;
                    lv_obj_set_pos(obj, 6, 54);
                    lv_obj_set_size(obj, 10, 8);
                    lv_led_set_brightness(obj, 255);
                    lv_obj_add_event_cb(obj, event_handler_cb_menu_led_2_ir, LV_EVENT_ALL, flowState);
                }
                {
                    // led_3V
                    lv_obj_t *obj = lv_led_create(parent_obj);
                    objects.led_3_v = obj;
                    lv_obj_set_pos(obj, 26, 6);
                    lv_obj_set_size(obj, 10, 8);
                    lv_led_set_brightness(obj, 255);
                    lv_obj_add_event_cb(obj, event_handler_cb_menu_led_3_v, LV_EVENT_ALL, flowState);
                }
                {
                    // led_4IR
                    lv_obj_t *obj = lv_led_create(parent_obj);
                    objects.led_4_ir = obj;
                    lv_obj_set_pos(obj, 26, 26);
                    lv_obj_set_size(obj, 10, 8);
                    lv_led_set_brightness(obj, 255);
                    lv_obj_add_event_cb(obj, event_handler_cb_menu_led_4_ir, LV_EVENT_ALL, flowState);
                }
                {
                    // led_5R
                    lv_obj_t *obj = lv_led_create(parent_obj);
                    objects.led_5_r = obj;
                    lv_obj_set_pos(obj, 26, 46);
                    lv_obj_set_size(obj, 10, 8);
                    lv_led_set_brightness(obj, 255);
                    lv_obj_add_event_cb(obj, event_handler_cb_menu_led_5_r, LV_EVENT_ALL, flowState);
                }
                {
                    // led_6R
                    lv_obj_t *obj = lv_led_create(parent_obj);
                    objects.led_6_r = obj;
                    lv_obj_set_pos(obj, 26, 66);
                    lv_obj_set_size(obj, 10, 8);
                    lv_led_set_brightness(obj, 255);
                    lv_obj_add_event_cb(obj, event_handler_cb_menu_led_6_r, LV_EVENT_ALL, flowState);
                }
                {
                    // led_7V
                    lv_obj_t *obj = lv_led_create(parent_obj);
                    objects.led_7_v = obj;
                    lv_obj_set_pos(obj, 44, 14);
                    lv_obj_set_size(obj, 10, 8);
                    lv_led_set_brightness(obj, 255);
                    lv_obj_add_event_cb(obj, event_handler_cb_menu_led_7_v, LV_EVENT_ALL, flowState);
                }
                {
                    // led_8R
                    lv_obj_t *obj = lv_led_create(parent_obj);
                    objects.led_8_r = obj;
                    lv_obj_set_pos(obj, 44, 34);
                    lv_obj_set_size(obj, 10, 8);
                    lv_led_set_brightness(obj, 255);
                    lv_obj_add_event_cb(obj, event_handler_cb_menu_led_8_r, LV_EVENT_ALL, flowState);
                }
                {
                    // led_9IR
                    lv_obj_t *obj = lv_led_create(parent_obj);
                    objects.led_9_ir = obj;
                    lv_obj_set_pos(obj, 44, 54);
                    lv_obj_set_size(obj, 10, 8);
                    lv_led_set_brightness(obj, 255);
                    lv_obj_add_event_cb(obj, event_handler_cb_menu_led_9_ir, LV_EVENT_ALL, flowState);
                }
            }
        }
        {
            // CONTAINER_DOSIS_TOTAL
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.container_dosis_total = obj;
            lv_obj_set_pos(obj, 155, 232);
            lv_obj_set_size(obj, 81, 86);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff9cd6ff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 7, 7);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_radius(obj, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "DOSIS\nTOTAL (J)");
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj0 = obj;
                    lv_obj_set_pos(obj, 19, 58);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "");
                }
            }
        }
        {
            // CONTAINER_TIME
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.container_time = obj;
            lv_obj_set_pos(obj, 72, 106);
            lv_obj_set_size(obj, 164, 124);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff9cd6ff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // button_plus
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.button_plus = obj;
                    lv_obj_set_pos(obj, 16, 80);
                    lv_obj_set_size(obj, 57, 30);
                    lv_obj_add_event_cb(obj, event_handler_cb_menu_button_plus, LV_EVENT_ALL, flowState);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff007acc), LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, " \uF067 ");
                        }
                    }
                }
                {
                    // button_minus
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.button_minus = obj;
                    lv_obj_set_pos(obj, 90, 80);
                    lv_obj_set_size(obj, 57, 30);
                    lv_obj_add_event_cb(obj, event_handler_cb_menu_button_minus, LV_EVENT_ALL, flowState);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff007acc), LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, " \uF068 ");
                        }
                    }
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 42, 6);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "TIEMPO");
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj1 = obj;
                    lv_obj_set_pos(obj, 51, 37);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "");
                }
            }
        }
        {
            // CONTAINER_Dosis_PUNTUAL
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.container_dosis_puntual = obj;
            lv_obj_set_pos(obj, 71, 232);
            lv_obj_set_size(obj, 82, 86);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff9cd6ff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 10, 7);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "DOSIS\nPUNT. (J)");
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj2 = obj;
                    lv_obj_set_pos(obj, 20, 58);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "");
                }
            }
        }
        {
            // button_play
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.button_play = obj;
            lv_obj_set_pos(obj, 5, 130);
            lv_obj_set_size(obj, 57, 30);
            lv_obj_add_event_cb(obj, event_handler_cb_menu_button_play, LV_EVENT_ALL, flowState);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff007acc), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // label_play
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_play = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, " \uF04B ");
                }
            }
        }
        {
            // botton_settings
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.botton_settings = obj;
            lv_obj_set_pos(obj, 5, 248);
            lv_obj_set_size(obj, 57, 30);
            lv_obj_add_event_cb(obj, event_handler_cb_menu_botton_settings, LV_EVENT_ALL, flowState);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff007acc), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // label_settings
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_settings = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, " \uF013 ");
                }
            }
        }
        {
            // botton_reset
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.botton_reset = obj;
            lv_obj_set_pos(obj, 5, 209);
            lv_obj_set_size(obj, 57, 30);
            lv_obj_add_event_cb(obj, event_handler_cb_menu_botton_reset, LV_EVENT_ALL, flowState);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff007acc), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // label_reset
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_reset = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "RESET");
                }
            }
        }
        {
            // botton_stop
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.botton_stop = obj;
            lv_obj_set_pos(obj, 5, 170);
            lv_obj_set_size(obj, 57, 30);
            lv_obj_add_event_cb(obj, event_handler_cb_menu_botton_stop, LV_EVENT_ALL, flowState);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff007acc), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // label_stop
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_stop = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, " \uF04D ");
                }
            }
        }
    }
    
    tick_screen_menu();
}

void tick_screen_menu() {
    void *flowState = getFlowState(0, 2);
    (void)flowState;
    {
        bool new_val = evalBooleanProperty(flowState, 3, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.charge_zero, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.charge_zero;
            if (new_val) lv_obj_add_flag(objects.charge_zero, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.charge_zero, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 4, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.charge_quarter, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.charge_quarter;
            if (new_val) lv_obj_add_flag(objects.charge_quarter, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.charge_quarter, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 5, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.charge_half, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.charge_half;
            if (new_val) lv_obj_add_flag(objects.charge_half, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.charge_half, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 6, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.charge_three_quarter, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.charge_three_quarter;
            if (new_val) lv_obj_add_flag(objects.charge_three_quarter, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.charge_three_quarter, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 7, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.charge_full, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.charge_full;
            if (new_val) lv_obj_add_flag(objects.charge_full, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.charge_full, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 8, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.charge_on, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.charge_on;
            if (new_val) lv_obj_add_flag(objects.charge_on, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.charge_on, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 9, 4, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.checkbox_r, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.checkbox_r;
            if (new_val) lv_obj_add_state(objects.checkbox_r, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.checkbox_r, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 9, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.checkbox_r, LV_OBJ_FLAG_CLICKABLE);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.checkbox_r;
            if (new_val) lv_obj_add_flag(objects.checkbox_r, LV_OBJ_FLAG_CLICKABLE);
            else lv_obj_clear_flag(objects.checkbox_r, LV_OBJ_FLAG_CLICKABLE);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 10, 4, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.checkbox_ir, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.checkbox_ir;
            if (new_val) lv_obj_add_state(objects.checkbox_ir, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.checkbox_ir, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 10, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.checkbox_ir, LV_OBJ_FLAG_CLICKABLE);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.checkbox_ir;
            if (new_val) lv_obj_add_flag(objects.checkbox_ir, LV_OBJ_FLAG_CLICKABLE);
            else lv_obj_clear_flag(objects.checkbox_ir, LV_OBJ_FLAG_CLICKABLE);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 11, 4, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.checkbox_v, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.checkbox_v;
            if (new_val) lv_obj_add_state(objects.checkbox_v, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.checkbox_v, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 11, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.checkbox_v, LV_OBJ_FLAG_CLICKABLE);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.checkbox_v;
            if (new_val) lv_obj_add_flag(objects.checkbox_v, LV_OBJ_FLAG_CLICKABLE);
            else lv_obj_clear_flag(objects.checkbox_v, LV_OBJ_FLAG_CLICKABLE);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 16, 3, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.led_0_v, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.led_0_v;
            if (new_val) lv_obj_add_state(objects.led_0_v, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.led_0_v, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        uint32_t new_val = evalUnsignedIntegerProperty(flowState, 16, 4, "Failed to evaluate Color in Led widget");
        new_val = lv_color_to_u32(lv_color_hex(new_val));
        uint32_t cur_val = lv_color_to_u32(((lv_led_t *)objects.led_0_v)->color);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.led_0_v;
            lv_led_set_color(objects.led_0_v, lv_color_hex(new_val));
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 17, 3, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.led_1_r, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.led_1_r;
            if (new_val) lv_obj_add_state(objects.led_1_r, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.led_1_r, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        uint32_t new_val = evalUnsignedIntegerProperty(flowState, 17, 4, "Failed to evaluate Color in Led widget");
        new_val = lv_color_to_u32(lv_color_hex(new_val));
        uint32_t cur_val = lv_color_to_u32(((lv_led_t *)objects.led_1_r)->color);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.led_1_r;
            lv_led_set_color(objects.led_1_r, lv_color_hex(new_val));
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 18, 3, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.led_2_ir, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.led_2_ir;
            if (new_val) lv_obj_add_state(objects.led_2_ir, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.led_2_ir, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        uint32_t new_val = evalUnsignedIntegerProperty(flowState, 18, 4, "Failed to evaluate Color in Led widget");
        new_val = lv_color_to_u32(lv_color_hex(new_val));
        uint32_t cur_val = lv_color_to_u32(((lv_led_t *)objects.led_2_ir)->color);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.led_2_ir;
            lv_led_set_color(objects.led_2_ir, lv_color_hex(new_val));
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 19, 3, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.led_3_v, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.led_3_v;
            if (new_val) lv_obj_add_state(objects.led_3_v, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.led_3_v, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        uint32_t new_val = evalUnsignedIntegerProperty(flowState, 19, 4, "Failed to evaluate Color in Led widget");
        new_val = lv_color_to_u32(lv_color_hex(new_val));
        uint32_t cur_val = lv_color_to_u32(((lv_led_t *)objects.led_3_v)->color);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.led_3_v;
            lv_led_set_color(objects.led_3_v, lv_color_hex(new_val));
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 20, 3, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.led_4_ir, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.led_4_ir;
            if (new_val) lv_obj_add_state(objects.led_4_ir, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.led_4_ir, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        uint32_t new_val = evalUnsignedIntegerProperty(flowState, 20, 4, "Failed to evaluate Color in Led widget");
        new_val = lv_color_to_u32(lv_color_hex(new_val));
        uint32_t cur_val = lv_color_to_u32(((lv_led_t *)objects.led_4_ir)->color);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.led_4_ir;
            lv_led_set_color(objects.led_4_ir, lv_color_hex(new_val));
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 21, 3, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.led_5_r, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.led_5_r;
            if (new_val) lv_obj_add_state(objects.led_5_r, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.led_5_r, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        uint32_t new_val = evalUnsignedIntegerProperty(flowState, 21, 4, "Failed to evaluate Color in Led widget");
        new_val = lv_color_to_u32(lv_color_hex(new_val));
        uint32_t cur_val = lv_color_to_u32(((lv_led_t *)objects.led_5_r)->color);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.led_5_r;
            lv_led_set_color(objects.led_5_r, lv_color_hex(new_val));
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 22, 3, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.led_6_r, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.led_6_r;
            if (new_val) lv_obj_add_state(objects.led_6_r, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.led_6_r, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        uint32_t new_val = evalUnsignedIntegerProperty(flowState, 22, 4, "Failed to evaluate Color in Led widget");
        new_val = lv_color_to_u32(lv_color_hex(new_val));
        uint32_t cur_val = lv_color_to_u32(((lv_led_t *)objects.led_6_r)->color);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.led_6_r;
            lv_led_set_color(objects.led_6_r, lv_color_hex(new_val));
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 23, 3, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.led_7_v, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.led_7_v;
            if (new_val) lv_obj_add_state(objects.led_7_v, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.led_7_v, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        uint32_t new_val = evalUnsignedIntegerProperty(flowState, 23, 4, "Failed to evaluate Color in Led widget");
        new_val = lv_color_to_u32(lv_color_hex(new_val));
        uint32_t cur_val = lv_color_to_u32(((lv_led_t *)objects.led_7_v)->color);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.led_7_v;
            lv_led_set_color(objects.led_7_v, lv_color_hex(new_val));
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 24, 3, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.led_8_r, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.led_8_r;
            if (new_val) lv_obj_add_state(objects.led_8_r, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.led_8_r, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        uint32_t new_val = evalUnsignedIntegerProperty(flowState, 24, 4, "Failed to evaluate Color in Led widget");
        new_val = lv_color_to_u32(lv_color_hex(new_val));
        uint32_t cur_val = lv_color_to_u32(((lv_led_t *)objects.led_8_r)->color);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.led_8_r;
            lv_led_set_color(objects.led_8_r, lv_color_hex(new_val));
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 25, 3, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.led_9_ir, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.led_9_ir;
            if (new_val) lv_obj_add_state(objects.led_9_ir, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.led_9_ir, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        uint32_t new_val = evalUnsignedIntegerProperty(flowState, 25, 4, "Failed to evaluate Color in Led widget");
        new_val = lv_color_to_u32(lv_color_hex(new_val));
        uint32_t cur_val = lv_color_to_u32(((lv_led_t *)objects.led_9_ir)->color);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.led_9_ir;
            lv_led_set_color(objects.led_9_ir, lv_color_hex(new_val));
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 28, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj0);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj0;
            lv_label_set_text(objects.obj0, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 30, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.button_plus, LV_OBJ_FLAG_CLICKABLE);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.button_plus;
            if (new_val) lv_obj_add_flag(objects.button_plus, LV_OBJ_FLAG_CLICKABLE);
            else lv_obj_clear_flag(objects.button_plus, LV_OBJ_FLAG_CLICKABLE);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 32, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.button_minus, LV_OBJ_FLAG_CLICKABLE);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.button_minus;
            if (new_val) lv_obj_add_flag(objects.button_minus, LV_OBJ_FLAG_CLICKABLE);
            else lv_obj_clear_flag(objects.button_minus, LV_OBJ_FLAG_CLICKABLE);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 35, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj1);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj1;
            lv_label_set_text(objects.obj1, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 38, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj2);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj2;
            lv_label_set_text(objects.obj2, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 39, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.button_play, LV_OBJ_FLAG_CLICKABLE);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.button_play;
            if (new_val) lv_obj_add_flag(objects.button_play, LV_OBJ_FLAG_CLICKABLE);
            else lv_obj_clear_flag(objects.button_play, LV_OBJ_FLAG_CLICKABLE);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 41, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.botton_settings, LV_OBJ_FLAG_CLICKABLE);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.botton_settings;
            if (new_val) lv_obj_add_flag(objects.botton_settings, LV_OBJ_FLAG_CLICKABLE);
            else lv_obj_clear_flag(objects.botton_settings, LV_OBJ_FLAG_CLICKABLE);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 43, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.botton_reset, LV_OBJ_FLAG_CLICKABLE);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.botton_reset;
            if (new_val) lv_obj_add_flag(objects.botton_reset, LV_OBJ_FLAG_CLICKABLE);
            else lv_obj_clear_flag(objects.botton_reset, LV_OBJ_FLAG_CLICKABLE);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 45, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.botton_stop, LV_OBJ_FLAG_CLICKABLE);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.botton_stop;
            if (new_val) lv_obj_add_flag(objects.botton_stop, LV_OBJ_FLAG_CLICKABLE);
            else lv_obj_clear_flag(objects.botton_stop, LV_OBJ_FLAG_CLICKABLE);
            tick_value_change_obj = NULL;
        }
    }
}

void create_screen_settings() {
    void *flowState = getFlowState(0, 3);
    (void)flowState;
    lv_obj_t *obj = lv_obj_create(0);
    objects.settings = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 240, 320);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xfff5f5f5), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // Benchmark_name_3
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.benchmark_name_3 = obj;
            lv_obj_set_pos(obj, 41, 8);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff1f90d6), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Fisser HandBeam 10D");
        }
        {
            // bench_line_1
            lv_obj_t *obj = lv_line_create(parent_obj);
            objects.bench_line_1 = obj;
            lv_obj_set_pos(obj, 6, 24);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            static lv_point_precise_t line_points[] = {
                { 0, 0 },
                { 0, 0 },
                { 0, 0 },
                { 0, 0 },
                { 230, 0 }
            };
            lv_line_set_points(obj, line_points, 5);
            lv_obj_set_style_line_color(obj, lv_color_hex(0xff1f90d6), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // charge_zero_1
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.charge_zero_1 = obj;
            lv_obj_set_pos(obj, 206, 8);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "\uF244 ");
        }
        {
            // charge_quarter_1
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.charge_quarter_1 = obj;
            lv_obj_set_pos(obj, 206, 8);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "\uF243");
        }
        {
            // charge_half_1
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.charge_half_1 = obj;
            lv_obj_set_pos(obj, 206, 8);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "\uF242");
        }
        {
            // charge_threeQuarter_1
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.charge_three_quarter_1 = obj;
            lv_obj_set_pos(obj, 202, 8);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, " \uF241 ");
        }
        {
            // charge_full_1
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.charge_full_1 = obj;
            lv_obj_set_pos(obj, 206, 8);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "\uF240");
        }
        {
            // charge_on_1
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.charge_on_1 = obj;
            lv_obj_set_pos(obj, 210, 8);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "\uF0E7");
        }
        {
            // CONTAINER_AJUSTES_GENERALES
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.container_ajustes_generales = obj;
            lv_obj_set_pos(obj, 15, 32);
            lv_obj_set_size(obj, 209, 96);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff9cd6ff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // label_ajustes_generales
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_ajustes_generales = obj;
                    lv_obj_set_pos(obj, 9, 3);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff007acc), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Ajustes Generales");
                }
                {
                    // button_idioma
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.button_idioma = obj;
                    lv_obj_set_pos(obj, 8, 20);
                    lv_obj_set_size(obj, 193, 30);
                    lv_obj_add_event_cb(obj, event_handler_cb_settings_button_idioma, LV_EVENT_ALL, flowState);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xfff5f5f5), LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // label_language_selected
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.label_language_selected = obj;
                            lv_obj_set_pos(obj, 131, -1);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xff212121), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // label_idioma
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.label_idioma = obj;
                            lv_obj_set_pos(obj, 26, -1);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xff212121), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Idioma:");
                        }
                        {
                            // icono_global
                            lv_obj_t *obj = lv_image_create(parent_obj);
                            objects.icono_global = obj;
                            lv_obj_set_pos(obj, -4, -3);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_image_set_src(obj, &img_global_icon);
                            lv_image_set_pivot(obj, 0, 0);
                        }
                    }
                }
                {
                    // button_change_pwrd
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.button_change_pwrd = obj;
                    lv_obj_set_pos(obj, 8, 58);
                    lv_obj_set_size(obj, 193, 30);
                    lv_obj_add_event_cb(obj, event_handler_cb_settings_button_change_pwrd, LV_EVENT_ALL, flowState);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xfff5f5f5), LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.obj3 = obj;
                            lv_obj_set_pos(obj, 151, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xff212121), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, " \uF054 ");
                        }
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.obj4 = obj;
                            lv_obj_set_pos(obj, 26, -1);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xff212121), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Cambio de PIN:");
                        }
                        {
                            // icono_password
                            lv_obj_t *obj = lv_image_create(parent_obj);
                            objects.icono_password = obj;
                            lv_obj_set_pos(obj, -4, -4);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_image_set_src(obj, &img_password_icon);
                            lv_image_set_pivot(obj, 0, 0);
                        }
                    }
                }
            }
        }
        {
            // CONTAINER_CONECTIVIDAD
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.container_conectividad = obj;
            lv_obj_set_pos(obj, 15, 130);
            lv_obj_set_size(obj, 209, 53);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff9cd6ff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // label_conectividad
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_conectividad = obj;
                    lv_obj_set_pos(obj, 9, 3);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff007acc), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Conectividad");
                }
                {
                    // CONTAINER_WIFI
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.container_wifi = obj;
                    lv_obj_set_pos(obj, 8, 18);
                    lv_obj_set_size(obj, 193, 28);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 7, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xfff5f5f5), LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // label_wifi_name
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.label_wifi_name = obj;
                            lv_obj_set_pos(obj, 34, 4);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xff212121), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // icono_wifi
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.icono_wifi = obj;
                            lv_obj_set_pos(obj, 6, 4);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xff2790dd), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "\uF1EB ");
                        }
                        {
                            // label_connection_state
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.label_connection_state = obj;
                            lv_obj_set_pos(obj, 34, 15);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xff212121), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // switch_wifi
                            lv_obj_t *obj = lv_switch_create(parent_obj);
                            objects.switch_wifi = obj;
                            lv_obj_set_pos(obj, 147, 3);
                            lv_obj_set_size(obj, 39, 23);
                            lv_obj_add_event_cb(obj, event_handler_cb_settings_switch_wifi, LV_EVENT_ALL, flowState);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff9cd6ff), LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                    }
                }
            }
        }
        {
            // button_back
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.button_back = obj;
            lv_obj_set_pos(obj, 5, 6);
            lv_obj_set_size(obj, 28, 16);
            lv_obj_add_event_cb(obj, event_handler_cb_settings_button_back, LV_EVENT_ALL, flowState);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfff5f5f5), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_opa(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj5 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff1f90d6), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "\uF053");
                }
            }
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj6 = obj;
            lv_obj_set_pos(obj, 50, 187);
            lv_obj_set_size(obj, 140, 129);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff9cd6ff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 7, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfff5f5f5), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // QR_APP
                    lv_obj_t *obj = lv_qrcode_create(parent_obj);
                    objects.qr_app = obj;
                    lv_obj_set_pos(obj, 5, 19);
                    lv_obj_set_size(obj, 126, 99);
                    lv_qrcode_set_size(obj, 99);
                    lv_qrcode_set_dark_color(obj, lv_color_hex(0xff20429f));
                    lv_qrcode_set_light_color(obj, lv_color_hex(0xffffffff));
                    lv_qrcode_update(obj, "https://google.com/", 19);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                }
                {
                    // label_QR
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_qr = obj;
                    lv_obj_set_pos(obj, 10, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "Descarga la App");
                }
            }
        }
    }
    
    tick_screen_settings();
}

void tick_screen_settings() {
    void *flowState = getFlowState(0, 3);
    (void)flowState;
    {
        bool new_val = evalBooleanProperty(flowState, 3, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.charge_zero_1, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.charge_zero_1;
            if (new_val) lv_obj_add_flag(objects.charge_zero_1, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.charge_zero_1, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 4, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.charge_quarter_1, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.charge_quarter_1;
            if (new_val) lv_obj_add_flag(objects.charge_quarter_1, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.charge_quarter_1, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 5, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.charge_half_1, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.charge_half_1;
            if (new_val) lv_obj_add_flag(objects.charge_half_1, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.charge_half_1, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 6, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.charge_three_quarter_1, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.charge_three_quarter_1;
            if (new_val) lv_obj_add_flag(objects.charge_three_quarter_1, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.charge_three_quarter_1, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 7, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.charge_full_1, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.charge_full_1;
            if (new_val) lv_obj_add_flag(objects.charge_full_1, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.charge_full_1, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 8, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.charge_on_1, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.charge_on_1;
            if (new_val) lv_obj_add_flag(objects.charge_on_1, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.charge_on_1, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 12, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.label_language_selected);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.label_language_selected;
            lv_label_set_text(objects.label_language_selected, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 22, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.label_wifi_name);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.label_wifi_name;
            lv_label_set_text(objects.label_wifi_name, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 24, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.label_connection_state);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.label_connection_state;
            lv_label_set_text(objects.label_connection_state, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 25, 3, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.switch_wifi, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.switch_wifi;
            if (new_val) lv_obj_add_state(objects.switch_wifi, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.switch_wifi, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
}

void create_screen_cambio_password() {
    void *flowState = getFlowState(0, 4);
    (void)flowState;
    lv_obj_t *obj = lv_obj_create(0);
    objects.cambio_password = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 240, 320);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xfff5f5f5), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // Benchmark_name_4
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.benchmark_name_4 = obj;
            lv_obj_set_pos(obj, 41, 8);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff1f90d6), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Fisser HandBeam 10D");
        }
        {
            // bench_line_2
            lv_obj_t *obj = lv_line_create(parent_obj);
            objects.bench_line_2 = obj;
            lv_obj_set_pos(obj, 6, 24);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            static lv_point_precise_t line_points[] = {
                { 0, 0 },
                { 0, 0 },
                { 0, 0 },
                { 0, 0 },
                { 230, 0 }
            };
            lv_line_set_points(obj, line_points, 5);
            lv_obj_set_style_line_color(obj, lv_color_hex(0xff1f90d6), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // charge_zero_2
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.charge_zero_2 = obj;
            lv_obj_set_pos(obj, 206, 8);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "\uF244 ");
        }
        {
            // charge_quarter_2
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.charge_quarter_2 = obj;
            lv_obj_set_pos(obj, 206, 8);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "\uF243");
        }
        {
            // charge_half_2
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.charge_half_2 = obj;
            lv_obj_set_pos(obj, 206, 8);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "\uF242");
        }
        {
            // charge_threeQuarter_2
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.charge_three_quarter_2 = obj;
            lv_obj_set_pos(obj, 202, 8);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, " \uF241 ");
        }
        {
            // charge_full_2
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.charge_full_2 = obj;
            lv_obj_set_pos(obj, 206, 8);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "\uF240");
        }
        {
            // charge_on_2
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.charge_on_2 = obj;
            lv_obj_set_pos(obj, 210, 8);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "\uF0E7");
        }
        {
            // CONTAINER_AJUSTES_GENERALES_1
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.container_ajustes_generales_1 = obj;
            lv_obj_set_pos(obj, 10, 32);
            lv_obj_set_size(obj, 218, 198);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff9cd6ff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // label_ajustes_generales_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_ajustes_generales_1 = obj;
                    lv_obj_set_pos(obj, 9, 3);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff007acc), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Cambio de PIN");
                }
                {
                    // textarea_current
                    lv_obj_t *obj = lv_textarea_create(parent_obj);
                    objects.textarea_current = obj;
                    lv_obj_set_pos(obj, 6, 27);
                    lv_obj_set_size(obj, 209, 37);
                    lv_textarea_set_max_length(obj, 20);
                    lv_textarea_set_placeholder_text(obj, "    Ingrese el PIN actual");
                    lv_textarea_set_one_line(obj, true);
                    lv_textarea_set_password_mode(obj, false);
                    lv_obj_add_event_cb(obj, event_handler_cb_cambio_password_textarea_current, LV_EVENT_ALL, flowState);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff0da2ef), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_grad_stop(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(0xff1d54d3), LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // ojo_button_2
                            lv_obj_t *obj = lv_button_create(parent_obj);
                            objects.ojo_button_2 = obj;
                            lv_obj_set_pos(obj, 165, 0);
                            lv_obj_set_size(obj, 24, 17);
                            lv_obj_set_style_shadow_color(obj, lv_color_hex(0xff0da2ef), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff0da2ef), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_image_recolor(obj, lv_color_hex(0xff0da2ef), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                    }
                }
                {
                    // textarea_new
                    lv_obj_t *obj = lv_textarea_create(parent_obj);
                    objects.textarea_new = obj;
                    lv_obj_set_pos(obj, 6, 88);
                    lv_obj_set_size(obj, 209, 37);
                    lv_textarea_set_max_length(obj, 20);
                    lv_textarea_set_placeholder_text(obj, "    Ingrese el PIN nuevo");
                    lv_textarea_set_one_line(obj, true);
                    lv_textarea_set_password_mode(obj, false);
                    lv_obj_add_event_cb(obj, event_handler_cb_cambio_password_textarea_new, LV_EVENT_ALL, flowState);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff0da2ef), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_grad_stop(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(0xff1d54d3), LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // ojo_button_3
                            lv_obj_t *obj = lv_button_create(parent_obj);
                            objects.ojo_button_3 = obj;
                            lv_obj_set_pos(obj, 165, 0);
                            lv_obj_set_size(obj, 24, 17);
                            lv_obj_set_style_shadow_color(obj, lv_color_hex(0xff0da2ef), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff0da2ef), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_image_recolor(obj, lv_color_hex(0xff0da2ef), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                    }
                }
                {
                    // textarea_confirm
                    lv_obj_t *obj = lv_textarea_create(parent_obj);
                    objects.textarea_confirm = obj;
                    lv_obj_set_pos(obj, 6, 148);
                    lv_obj_set_size(obj, 209, 37);
                    lv_textarea_set_max_length(obj, 20);
                    lv_textarea_set_placeholder_text(obj, "    Repita el PIN nuevo");
                    lv_textarea_set_one_line(obj, true);
                    lv_textarea_set_password_mode(obj, false);
                    lv_obj_add_event_cb(obj, event_handler_cb_cambio_password_textarea_confirm, LV_EVENT_ALL, flowState);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff0da2ef), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_grad_stop(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(0xff1d54d3), LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // ojo_button_4
                            lv_obj_t *obj = lv_button_create(parent_obj);
                            objects.ojo_button_4 = obj;
                            lv_obj_set_pos(obj, 165, 0);
                            lv_obj_set_size(obj, 24, 17);
                            lv_obj_set_style_shadow_color(obj, lv_color_hex(0xff0da2ef), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff0da2ef), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_image_recolor(obj, lv_color_hex(0xff0da2ef), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                    }
                }
            }
        }
        {
            // button_back_1
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.button_back_1 = obj;
            lv_obj_set_pos(obj, 5, 6);
            lv_obj_set_size(obj, 28, 16);
            lv_obj_add_event_cb(obj, event_handler_cb_cambio_password_button_back_1, LV_EVENT_ALL, flowState);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfff5f5f5), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_opa(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj7 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff1f90d6), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "\uF053");
                }
            }
        }
        {
            // button_guardar
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.button_guardar = obj;
            lv_obj_set_pos(obj, 79, 245);
            lv_obj_set_size(obj, 80, 41);
            lv_obj_add_event_cb(obj, event_handler_cb_cambio_password_button_guardar, LV_EVENT_ALL, flowState);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff007acc), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // label_guardar
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_guardar = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "GUARDAR");
                }
            }
        }
        {
            // button_matrix_1
            lv_obj_t *obj = lv_buttonmatrix_create(parent_obj);
            objects.button_matrix_1 = obj;
            lv_obj_set_pos(obj, -1, 0);
            lv_obj_set_size(obj, 240, 320);
            static const char *map[16] = {
                "1",
                "2",
                "3",
                "\n",
                "4",
                "5",
                "6",
                "\n",
                "7",
                "8",
                "9",
                "\n",
                "DEL",
                "0",
                "OK",
                NULL,
            };
            lv_buttonmatrix_set_map(obj, map);
            lv_obj_add_event_cb(obj, event_handler_cb_cambio_password_button_matrix_1, LV_EVENT_ALL, flowState);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff11a1fb), LV_PART_ITEMS | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff11a1fb), LV_PART_ITEMS | LV_STATE_PRESSED);
        }
        {
            // CONTAINER_NOTIFICATION_TEXT
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.container_notification_text = obj;
            lv_obj_set_pos(obj, 16, 17);
            lv_obj_set_size(obj, 210, 31);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffff8a8a), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff81ff92), LV_PART_MAIN | LV_STATE_CHECKED);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj8 = obj;
                    lv_obj_set_pos(obj, -1, 8);
                    lv_obj_set_size(obj, LV_PCT(100), LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "");
                }
            }
        }
    }
    
    tick_screen_cambio_password();
}

void tick_screen_cambio_password() {
    void *flowState = getFlowState(0, 4);
    (void)flowState;
    {
        bool new_val = evalBooleanProperty(flowState, 3, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.charge_zero_2, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.charge_zero_2;
            if (new_val) lv_obj_add_flag(objects.charge_zero_2, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.charge_zero_2, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 4, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.charge_quarter_2, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.charge_quarter_2;
            if (new_val) lv_obj_add_flag(objects.charge_quarter_2, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.charge_quarter_2, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 5, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.charge_half_2, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.charge_half_2;
            if (new_val) lv_obj_add_flag(objects.charge_half_2, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.charge_half_2, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 6, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.charge_three_quarter_2, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.charge_three_quarter_2;
            if (new_val) lv_obj_add_flag(objects.charge_three_quarter_2, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.charge_three_quarter_2, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 7, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.charge_full_2, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.charge_full_2;
            if (new_val) lv_obj_add_flag(objects.charge_full_2, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.charge_full_2, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 8, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.charge_on_2, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.charge_on_2;
            if (new_val) lv_obj_add_flag(objects.charge_on_2, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.charge_on_2, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 11, 3, "Failed to evaluate Text in Textarea widget");
        const char *cur_val = lv_textarea_get_text(objects.textarea_current);
        uint32_t max_length = lv_textarea_get_max_length(objects.textarea_current);
        if (strncmp(new_val, cur_val, max_length) != 0) {
            tick_value_change_obj = objects.textarea_current;
            lv_textarea_set_text(objects.textarea_current, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 13, 3, "Failed to evaluate Text in Textarea widget");
        const char *cur_val = lv_textarea_get_text(objects.textarea_new);
        uint32_t max_length = lv_textarea_get_max_length(objects.textarea_new);
        if (strncmp(new_val, cur_val, max_length) != 0) {
            tick_value_change_obj = objects.textarea_new;
            lv_textarea_set_text(objects.textarea_new, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 15, 3, "Failed to evaluate Text in Textarea widget");
        const char *cur_val = lv_textarea_get_text(objects.textarea_confirm);
        uint32_t max_length = lv_textarea_get_max_length(objects.textarea_confirm);
        if (strncmp(new_val, cur_val, max_length) != 0) {
            tick_value_change_obj = objects.textarea_confirm;
            lv_textarea_set_text(objects.textarea_confirm, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 21, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.button_matrix_1, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.button_matrix_1;
            if (new_val) lv_obj_add_flag(objects.button_matrix_1, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.button_matrix_1, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 22, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.container_notification_text, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.container_notification_text;
            if (new_val) lv_obj_add_flag(objects.container_notification_text, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.container_notification_text, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 23, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj8);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj8;
            lv_label_set_text(objects.obj8, new_val);
            tick_value_change_obj = NULL;
        }
    }
}


static const char *screen_names[] = { "SplashScreen", "login_SCREEN", "MENU", "SETTINGS", "CAMBIO_PASSWORD" };
static const char *object_names[] = { "splash_screen", "login_screen", "menu", "settings", "cambio_password", "button_matrix", "ojo_button", "ojo_button_1", "checkbox_r", "checkbox_ir", "checkbox_v", "led_0_v", "led_1_r", "led_2_ir", "led_3_v", "led_4_ir", "led_5_r", "led_6_r", "led_7_v", "led_8_r", "led_9_ir", "button_plus", "button_minus", "button_play", "botton_settings", "botton_reset", "botton_stop", "button_idioma", "button_change_pwrd", "switch_wifi", "button_back", "textarea_current", "textarea_new", "textarea_confirm", "button_back_1", "button_guardar", "button_matrix_1", "branch_fisser_hand_beam10d", "load_bar", "textarea_password", "ojo", "textarea_plain", "ojo_1", "benchmark_name_1", "container_notification_pin_wrong", "benchmark_name_2", "bench_line", "charge_zero", "charge_quarter", "charge_half", "charge_three_quarter", "charge_full", "charge_on", "container_leds", "container_dosis_total", "container_time", "container_dosis_puntual", "label_play", "label_settings", "label_reset", "label_stop", "obj0", "obj1", "obj2", "benchmark_name_3", "bench_line_1", "charge_zero_1", "charge_quarter_1", "charge_half_1", "charge_three_quarter_1", "charge_full_1", "charge_on_1", "container_ajustes_generales", "label_ajustes_generales", "label_language_selected", "label_idioma", "icono_global", "obj3", "obj4", "icono_password", "container_conectividad", "label_conectividad", "container_wifi", "label_wifi_name", "icono_wifi", "label_connection_state", "obj5", "obj6", "qr_app", "label_qr", "benchmark_name_4", "bench_line_2", "charge_zero_2", "charge_quarter_2", "charge_half_2", "charge_three_quarter_2", "charge_full_2", "charge_on_2", "container_ajustes_generales_1", "label_ajustes_generales_1", "ojo_button_2", "ojo_button_3", "ojo_button_4", "obj7", "label_guardar", "container_notification_text", "obj8" };


typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_splash_screen,
    tick_screen_login_screen,
    tick_screen_menu,
    tick_screen_settings,
    tick_screen_cambio_password,
};
void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}
void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen_funcs[screenId - 1]();
}

void create_screens() {
    eez_flow_init_screen_names(screen_names, sizeof(screen_names) / sizeof(const char *));
    eez_flow_init_object_names(object_names, sizeof(object_names) / sizeof(const char *));
    
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    create_screen_splash_screen();
    create_screen_login_screen();
    create_screen_menu();
    create_screen_settings();
    create_screen_cambio_password();
}
