#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *splash_screen;
    lv_obj_t *login_screen;
    lv_obj_t *menu;
    lv_obj_t *settings;
    lv_obj_t *button_matrix;
    lv_obj_t *ojo_button;
    lv_obj_t *ojo_button_1;
    lv_obj_t *obj0;
    lv_obj_t *button_plus;
    lv_obj_t *button_minus;
    lv_obj_t *obj1;
    lv_obj_t *botton_settings;
    lv_obj_t *botton_reset;
    lv_obj_t *botton_stop;
    lv_obj_t *obj2;
    lv_obj_t *branch_fisser_hand_beam10d;
    lv_obj_t *load_bar;
    lv_obj_t *textarea_password;
    lv_obj_t *ojo;
    lv_obj_t *textarea_plain;
    lv_obj_t *ojo_1;
    lv_obj_t *benchmark_name_1;
    lv_obj_t *benchmark_name_2;
    lv_obj_t *bench_line;
    lv_obj_t *charge_zero;
    lv_obj_t *charge_quarter;
    lv_obj_t *charge_half;
    lv_obj_t *charge_three_quarter;
    lv_obj_t *charge_full;
    lv_obj_t *charge_on;
    lv_obj_t *obj3;
    lv_obj_t *obj4;
    lv_obj_t *container_leds;
    lv_obj_t *led_0;
    lv_obj_t *led_1;
    lv_obj_t *led_2;
    lv_obj_t *led_3;
    lv_obj_t *led_4;
    lv_obj_t *led_5;
    lv_obj_t *led_6;
    lv_obj_t *led_7;
    lv_obj_t *led_8;
    lv_obj_t *led_9;
    lv_obj_t *container_dosis_total;
    lv_obj_t *container_time;
    lv_obj_t *container_dosis_puntual;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_SPLASH_SCREEN = 1,
    SCREEN_ID_LOGIN_SCREEN = 2,
    SCREEN_ID_MENU = 3,
    SCREEN_ID_SETTINGS = 4,
};

void create_screen_splash_screen();
void tick_screen_splash_screen();

void create_screen_login_screen();
void tick_screen_login_screen();

void create_screen_menu();
void tick_screen_menu();

void create_screen_settings();
void tick_screen_settings();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/