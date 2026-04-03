#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include <string.h>

// ── Implementación de variables nativas (EEZ Studio / LVGL) ──────────────────
// output_keyboard: buffer para el texto ingresado por el teclado virtual
static char g_output_keyboard[128] = "";

const char *get_var_output_keyboard() {
    return g_output_keyboard;
}

void set_var_output_keyboard(const char *value) {
    if (value) {
        strncpy(g_output_keyboard, value, sizeof(g_output_keyboard) - 1);
        g_output_keyboard[sizeof(g_output_keyboard) - 1] = '\0';
    } else {
        g_output_keyboard[0] = '\0';
    }
}
// ─────────────────────────────────────────────────────────────────────────────

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

static void event_handler_cb_menu_obj0(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 9, 0, e);
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
}

static void event_handler_cb_menu_button_minus(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_CLICKED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 32, 0, e);
    }
}

static void event_handler_cb_menu_obj1(lv_event_t *e) {
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

static void event_handler_cb_settings_obj2(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 0, 0, e);
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
            lv_label_set_text(obj, "Fisser HandBeam10d");
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
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff212121), LV_PART_ITEMS | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff11a1fb), LV_PART_ITEMS | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe30a36), LV_PART_ITEMS | LV_STATE_PRESSED);
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
            lv_label_set_text(obj, "Fisser HandBeam 10d");
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
            lv_label_set_text(obj, "Fisser HandBeam 10d");
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
            lv_obj_t *obj = lv_checkbox_create(parent_obj);
            objects.obj0 = obj;
            lv_obj_set_pos(obj, 88, 54);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_checkbox_set_text(obj, "");
            lv_obj_add_event_cb(obj, event_handler_cb_menu_obj0, LV_EVENT_ALL, flowState);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_34, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff007acc), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_checkbox_create(parent_obj);
            objects.obj3 = obj;
            lv_obj_set_pos(obj, 190, 55);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_checkbox_set_text(obj, "");
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_34, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff007acc), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_checkbox_create(parent_obj);
            objects.obj4 = obj;
            lv_obj_set_pos(obj, 139, 54);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_checkbox_set_text(obj, "");
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_34, LV_PART_MAIN | LV_STATE_DEFAULT);
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
                    // led_0
                    lv_obj_t *obj = lv_led_create(parent_obj);
                    objects.led_0 = obj;
                    lv_obj_set_pos(obj, 6, 14);
                    lv_obj_set_size(obj, 10, 8);
                    lv_led_set_color(obj, lv_color_hex(0xff9400d3));
                    lv_led_set_brightness(obj, 255);
                }
                {
                    // led_1
                    lv_obj_t *obj = lv_led_create(parent_obj);
                    objects.led_1 = obj;
                    lv_obj_set_pos(obj, 6, 34);
                    lv_obj_set_size(obj, 10, 8);
                    lv_led_set_color(obj, lv_color_hex(0xffff0000));
                    lv_led_set_brightness(obj, 255);
                }
                {
                    // led_2
                    lv_obj_t *obj = lv_led_create(parent_obj);
                    objects.led_2 = obj;
                    lv_obj_set_pos(obj, 6, 54);
                    lv_obj_set_size(obj, 10, 8);
                    lv_led_set_color(obj, lv_color_hex(0xff9e4f4f));
                    lv_led_set_brightness(obj, 255);
                }
                {
                    // led_3
                    lv_obj_t *obj = lv_led_create(parent_obj);
                    objects.led_3 = obj;
                    lv_obj_set_pos(obj, 26, 6);
                    lv_obj_set_size(obj, 10, 8);
                    lv_led_set_color(obj, lv_color_hex(0xff9400d3));
                    lv_led_set_brightness(obj, 255);
                }
                {
                    // led_4
                    lv_obj_t *obj = lv_led_create(parent_obj);
                    objects.led_4 = obj;
                    lv_obj_set_pos(obj, 26, 26);
                    lv_obj_set_size(obj, 10, 8);
                    lv_led_set_color(obj, lv_color_hex(0xff9e4f4f));
                    lv_led_set_brightness(obj, 255);
                }
                {
                    // led_5
                    lv_obj_t *obj = lv_led_create(parent_obj);
                    objects.led_5 = obj;
                    lv_obj_set_pos(obj, 26, 46);
                    lv_obj_set_size(obj, 10, 8);
                    lv_led_set_color(obj, lv_color_hex(0xffff0000));
                    lv_led_set_brightness(obj, 255);
                }
                {
                    // led_6
                    lv_obj_t *obj = lv_led_create(parent_obj);
                    objects.led_6 = obj;
                    lv_obj_set_pos(obj, 26, 66);
                    lv_obj_set_size(obj, 10, 8);
                    lv_led_set_color(obj, lv_color_hex(0xffff0000));
                    lv_led_set_brightness(obj, 255);
                }
                {
                    // led_7
                    lv_obj_t *obj = lv_led_create(parent_obj);
                    objects.led_7 = obj;
                    lv_obj_set_pos(obj, 44, 14);
                    lv_obj_set_size(obj, 10, 8);
                    lv_led_set_color(obj, lv_color_hex(0xff9400d3));
                    lv_led_set_brightness(obj, 255);
                }
                {
                    // led_8
                    lv_obj_t *obj = lv_led_create(parent_obj);
                    objects.led_8 = obj;
                    lv_obj_set_pos(obj, 44, 34);
                    lv_obj_set_size(obj, 10, 8);
                    lv_led_set_color(obj, lv_color_hex(0xffff0000));
                    lv_led_set_brightness(obj, 255);
                }
                {
                    // led_9
                    lv_obj_t *obj = lv_led_create(parent_obj);
                    objects.led_9 = obj;
                    lv_obj_set_pos(obj, 44, 54);
                    lv_obj_set_size(obj, 10, 8);
                    lv_led_set_color(obj, lv_color_hex(0xff9e4f4f));
                    lv_led_set_brightness(obj, 255);
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
                    lv_obj_set_pos(obj, 19, 58);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "0.00");
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
                    lv_obj_set_pos(obj, 42, 39);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "00:00");
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
                    lv_obj_set_pos(obj, 20, 58);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "0.00");
                }
            }
        }
        {
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.obj1 = obj;
            lv_obj_set_pos(obj, 5, 130);
            lv_obj_set_size(obj, 57, 30);
            lv_obj_add_event_cb(obj, event_handler_cb_menu_obj1, LV_EVENT_ALL, flowState);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff007acc), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
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
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff007acc), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
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
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff007acc), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
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
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff007acc), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
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
}

void create_screen_settings() {
    void *flowState = getFlowState(0, 3);
    (void)flowState;
    lv_obj_t *obj = lv_obj_create(0);
    objects.settings = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 240, 320);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.obj2 = obj;
            lv_obj_set_pos(obj, 70, 145);
            lv_obj_set_size(obj, 100, 50);
            lv_obj_add_event_cb(obj, event_handler_cb_settings_obj2, LV_EVENT_ALL, flowState);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Button");
                }
            }
        }
    }
    
    tick_screen_settings();
}

void tick_screen_settings() {
    void *flowState = getFlowState(0, 3);
    (void)flowState;
}


static const char *screen_names[] = { "SplashScreen", "login_SCREEN", "MENU", "SETTINGS" };
static const char *object_names[] = { "splash_screen", "login_screen", "menu", "settings", "button_matrix", "ojo_button", "ojo_button_1", "obj0", "button_plus", "button_minus", "obj1", "botton_settings", "botton_reset", "botton_stop", "obj2", "branch_fisser_hand_beam10d", "load_bar", "textarea_password", "ojo", "textarea_plain", "ojo_1", "benchmark_name_1", "benchmark_name_2", "bench_line", "charge_zero", "charge_quarter", "charge_half", "charge_three_quarter", "charge_full", "charge_on", "obj3", "obj4", "container_leds", "led_0", "led_1", "led_2", "led_3", "led_4", "led_5", "led_6", "led_7", "led_8", "led_9", "container_dosis_total", "container_time", "container_dosis_puntual" };


typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_splash_screen,
    tick_screen_login_screen,
    tick_screen_menu,
    tick_screen_settings,
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
}
