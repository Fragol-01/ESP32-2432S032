#ifndef EEZ_LVGL_UI_VARS_H
#define EEZ_LVGL_UI_VARS_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// enum declarations



// Flow global variables

enum FlowGlobalVariables {
    FLOW_GLOBAL_VARIABLE_LOADING_VALUE = 0,
    FLOW_GLOBAL_VARIABLE_KEYS = 1,
    FLOW_GLOBAL_VARIABLE_EYE_OPEN = 2,
    FLOW_GLOBAL_VARIABLE_BATTERY_LEVEL = 3,
    FLOW_GLOBAL_VARIABLE_TRAITMENT_TIME = 4,
    FLOW_GLOBAL_VARIABLE_DOSIS_PUNTUAL = 5,
    FLOW_GLOBAL_VARIABLE_DOSIS_TOTAL = 6
};

// Native global variables

extern const char *get_var_output_keyboard();
extern void set_var_output_keyboard(const char *value);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/