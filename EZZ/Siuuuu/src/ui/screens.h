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
    lv_obj_t *cambio_password;
    lv_obj_t *button_matrix;
    lv_obj_t *ojo_button;
    lv_obj_t *ojo_button_1;
    lv_obj_t *checkbox_r;
    lv_obj_t *checkbox_ir;
    lv_obj_t *checkbox_v;
    lv_obj_t *led_0_v;
    lv_obj_t *led_1_r;
    lv_obj_t *led_2_ir;
    lv_obj_t *led_3_v;
    lv_obj_t *led_4_ir;
    lv_obj_t *led_5_r;
    lv_obj_t *led_6_r;
    lv_obj_t *led_7_v;
    lv_obj_t *led_8_r;
    lv_obj_t *led_9_ir;
    lv_obj_t *button_plus;
    lv_obj_t *button_minus;
    lv_obj_t *button_play;
    lv_obj_t *botton_settings;
    lv_obj_t *botton_reset;
    lv_obj_t *botton_stop;
    lv_obj_t *button_idioma;
    lv_obj_t *button_change_pwrd;
    lv_obj_t *switch_wifi;
    lv_obj_t *button_back;
    lv_obj_t *textarea_current;
    lv_obj_t *textarea_new;
    lv_obj_t *textarea_confirm;
    lv_obj_t *button_back_1;
    lv_obj_t *button_guardar;
    lv_obj_t *button_matrix_1;
    lv_obj_t *branch_fisser_hand_beam10d;
    lv_obj_t *load_bar;
    lv_obj_t *textarea_password;
    lv_obj_t *ojo;
    lv_obj_t *textarea_plain;
    lv_obj_t *ojo_1;
    lv_obj_t *benchmark_name_1;
    lv_obj_t *container_notification_pin_wrong;
    lv_obj_t *benchmark_name_2;
    lv_obj_t *bench_line;
    lv_obj_t *charge_zero;
    lv_obj_t *charge_quarter;
    lv_obj_t *charge_half;
    lv_obj_t *charge_three_quarter;
    lv_obj_t *charge_full;
    lv_obj_t *charge_on;
    lv_obj_t *container_leds;
    lv_obj_t *container_dosis_total;
    lv_obj_t *container_time;
    lv_obj_t *container_dosis_puntual;
    lv_obj_t *label_play;
    lv_obj_t *label_settings;
    lv_obj_t *label_reset;
    lv_obj_t *label_stop;
    lv_obj_t *obj0;
    lv_obj_t *obj1;
    lv_obj_t *obj2;
    lv_obj_t *benchmark_name_3;
    lv_obj_t *bench_line_1;
    lv_obj_t *charge_zero_1;
    lv_obj_t *charge_quarter_1;
    lv_obj_t *charge_half_1;
    lv_obj_t *charge_three_quarter_1;
    lv_obj_t *charge_full_1;
    lv_obj_t *charge_on_1;
    lv_obj_t *container_ajustes_generales;
    lv_obj_t *label_ajustes_generales;
    lv_obj_t *label_language_selected;
    lv_obj_t *label_idioma;
    lv_obj_t *icono_global;
    lv_obj_t *obj3;
    lv_obj_t *obj4;
    lv_obj_t *icono_password;
    lv_obj_t *container_conectividad;
    lv_obj_t *label_conectividad;
    lv_obj_t *container_wifi;
    lv_obj_t *label_wifi_name;
    lv_obj_t *icono_wifi;
    lv_obj_t *label_connection_state;
    lv_obj_t *obj5;
    lv_obj_t *obj6;
    lv_obj_t *qr_app;
    lv_obj_t *label_qr;
    lv_obj_t *benchmark_name_4;
    lv_obj_t *bench_line_2;
    lv_obj_t *charge_zero_2;
    lv_obj_t *charge_quarter_2;
    lv_obj_t *charge_half_2;
    lv_obj_t *charge_three_quarter_2;
    lv_obj_t *charge_full_2;
    lv_obj_t *charge_on_2;
    lv_obj_t *container_ajustes_generales_1;
    lv_obj_t *label_ajustes_generales_1;
    lv_obj_t *ojo_button_2;
    lv_obj_t *ojo_button_3;
    lv_obj_t *ojo_button_4;
    lv_obj_t *obj7;
    lv_obj_t *label_guardar;
    lv_obj_t *container_notification_text;
    lv_obj_t *obj8;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_SPLASH_SCREEN = 1,
    SCREEN_ID_LOGIN_SCREEN = 2,
    SCREEN_ID_MENU = 3,
    SCREEN_ID_SETTINGS = 4,
    SCREEN_ID_CAMBIO_PASSWORD = 5,
};

void create_screen_splash_screen();
void tick_screen_splash_screen();

void create_screen_login_screen();
void tick_screen_login_screen();

void create_screen_menu();
void tick_screen_menu();

void create_screen_settings();
void tick_screen_settings();

void create_screen_cambio_password();
void tick_screen_cambio_password();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/