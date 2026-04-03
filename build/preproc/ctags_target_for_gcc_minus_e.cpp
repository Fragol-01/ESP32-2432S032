# 1 "c:\\Users\\DANNY\\Desktop\\Laser Inteligente\\test\\test.ino"
/*******************************************************************************

 * Fisser HandBeam 10D - ESP32-2432S032 (3.2" Touch Display)

 * Display: ST7789 240x320 IPS (portrait mode, rotation=0)

 * Touch: GT911 capacitivo (I2C)

 * LVGL: v9.4.0

 * Basado en: https://github.com/kpeeem/3.2inch_ESP32-2432S032

 ******************************************************************************/
# 8 "c:\\Users\\DANNY\\Desktop\\Laser Inteligente\\test\\test.ino"
# 9 "c:\\Users\\DANNY\\Desktop\\Laser Inteligente\\test\\test.ino" 2
# 10 "c:\\Users\\DANNY\\Desktop\\Laser Inteligente\\test\\test.ino" 2
# 11 "c:\\Users\\DANNY\\Desktop\\Laser Inteligente\\test\\test.ino" 2
# 12 "c:\\Users\\DANNY\\Desktop\\Laser Inteligente\\test\\test.ino" 2
# 13 "c:\\Users\\DANNY\\Desktop\\Laser Inteligente\\test\\test.ino" 2
# 14 "c:\\Users\\DANNY\\Desktop\\Laser Inteligente\\test\\test.ino" 2

// ============== PINES DEL DISPLAY (SPI) ==============






// ============== PINES DEL TOUCH GT911 (I2C) ==============





// ============== CONFIGURACIÓN DE DISPLAY ==============
// ST7789 240x320 en modo portrait (rotation=0)
Arduino_DataBus *bus = new Arduino_ESP32SPI(2 /* Data/Command*/, 15 /* Chip Select*/, 14 /* Clock SPI*/, 13 /* Data out*/, -1);
Arduino_GFX *gfx = new Arduino_ST7789(bus, -1 /* RST */, 0 /* rotation: portrait */, true /* IPS */);

// ============== CONFIGURACIÓN DEL TOUCH GT911 ==============
// El GT911 reporta coordenadas en su orientación nativa (320x240 landscape)
// Para portrait 240x320 necesitamos intercambiar X/Y y ajustar el mapeo
Touch_GT911 ts(33, 32, -1 /* No usado*/, 25, 320, 240);

// Variables globales para touch
int touch_last_x = 0, touch_last_y = 0;

// ============== LVGL 9 ==============
static lv_display_t *lvgl_display = 
# 42 "c:\\Users\\DANNY\\Desktop\\Laser Inteligente\\test\\test.ino" 3 4
                                   __null
# 42 "c:\\Users\\DANNY\\Desktop\\Laser Inteligente\\test\\test.ino"
                                       ;
static lv_indev_t *lvgl_indev = 
# 43 "c:\\Users\\DANNY\\Desktop\\Laser Inteligente\\test\\test.ino" 3 4
                               __null
# 43 "c:\\Users\\DANNY\\Desktop\\Laser Inteligente\\test\\test.ino"
                                   ;
static uint8_t *draw_buf;



// ============== PROTOTIPOS ==============
void my_disp_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map);
void my_touchpad_read(lv_indev_t *indev, lv_indev_data_t *data);
void touch_init();
bool touch_touched();

void setup()
{
    Serial0.begin(115200);

    // Inicializar display
    gfx->begin(80000000); // 80MHz SPI
    gfx->fillScreen(((((248) & 0xF8) << 8) | (((252) & 0xFC) << 3) | ((248) >> 3)));

    // Backlight ON con PWM (ESP32 Core 3.x compatible)
    ledcAttach(27 /* Backlight (PWM)*/, 2000, 8); // ledcAttach(pin, freq, resolution)
    ledcWrite(27 /* Backlight (PWM)*/, 255); // ledcWrite(PIN, valor) - Brillo máximo

    // Inicializar LVGL 9
    lv_init();
    delay(20);

    // Inicializar Touch GT911
    touch_init();

    // Configurar tick source para LVGL 9
    lv_tick_set_cb((lv_tick_get_cb_t)millis);

    // Crear display LVGL 9
    draw_buf = (uint8_t *)heap_caps_malloc((240 * 40 * (16 / 8)), (1<<11) /*|< Memory must be internal; specifically it should not disappear when flash/spiram cache is switched off*/ | (1<<2) /*|< Memory must allow for 8/16/...-bit data accesses*/);
    if (!draw_buf) {
        Serial0.println("Error: No hay memoria para draw buffer");
        while(1);
    }

    lvgl_display = lv_display_create(240, 320);
    lv_display_set_flush_cb(lvgl_display, my_disp_flush);
    lv_display_set_buffers(lvgl_display, draw_buf, 
# 85 "c:\\Users\\DANNY\\Desktop\\Laser Inteligente\\test\\test.ino" 3 4
                                                  __null
# 85 "c:\\Users\\DANNY\\Desktop\\Laser Inteligente\\test\\test.ino"
                                                      , (240 * 40 * (16 / 8)), LV_DISPLAY_RENDER_MODE_PARTIAL);
    lv_display_set_color_format(lvgl_display, LV_COLOR_FORMAT_RGB565);

    // Configurar driver de touch LVGL 9
    lvgl_indev = lv_indev_create();
    lv_indev_set_type(lvgl_indev, LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(lvgl_indev, my_touchpad_read);

    // Inicializar UI
    ui_init();
}

void loop()
{
    lv_timer_handler();
    ui_tick();
    delay(5);
}

// ============== DISPLAY FLUSH CALLBACK (LVGL 9) ==============
void my_disp_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map)
{
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);
    gfx->draw16bitRGBBitmap(area->x1, area->y1, (uint16_t *)px_map, w, h);
    lv_display_flush_ready(disp);
}

// ============== TOUCH FUNCTIONS ==============
void touch_init()
{
    Wire.begin(33, 32);
    ts.begin();
    ts.setRotation((uint8_t)0); // Rotación para portrait mode
}

bool touch_touched()
{
    ts.read();
    if (ts.isTouched) {
        // El GT911 reporta en orientación landscape (320x240)
        // Para portrait 240x320 necesitamos: SWAP X/Y y ajustar mapeo
        int raw_x = ts.points[0].x; // 0-320 en landscape
        int raw_y = ts.points[0].y; // 0-240 en landscape

        // Para portrait (rotation=0): 
        // - display_x = raw_y (mapeado de 0-240 a 0-239)
        // - display_y = 319 - raw_x (mapeado de 0-320 a 319-0, invertido)
        touch_last_x = map(raw_y, 0, 240, 0, 239);
        touch_last_y = map(raw_x, 0, 320, 319, 0);

        // Limitar a rango válido
        if (touch_last_x < 0) touch_last_x = 0;
        if (touch_last_x > 239) touch_last_x = 239;
        if (touch_last_y < 0) touch_last_y = 0;
        if (touch_last_y > 319) touch_last_y = 319;

        return true;
    }
    return false;
}

// ============== TOUCH READ CALLBACK PARA LVGL 9 ==============
void my_touchpad_read(lv_indev_t *indev, lv_indev_data_t *data)
{
    if (touch_touched()) {
        data->state = LV_INDEV_STATE_PRESSED;
        data->point.x = touch_last_x;
        data->point.y = touch_last_y;
    } else {
        data->state = LV_INDEV_STATE_RELEASED;
    }
}
