#include "App.h"
#include <string.h>

void App_init(void) {
    report_dirty = false;  
    g_led_dirty = true;
    memset(last_key_state, 0, sizeof(last_key_state));
    memset(last_fn_state, 0, sizeof(last_fn_state));
    g_light_mode = LIGHT_MODE_OFF;
}
