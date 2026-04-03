================================================================================
GUÍA DE CONFIGURACIÓN - ESP32 + ST7789 + Arduino_GFX_Library
================================================================================

HARDWARE UTILIZADO:
- Microcontrolador: ESP32 Dev Module
- Pantalla: ST7789 (1.3" típicamente)
- Librería: Arduino_GFX_Library v1.4.x+
- Arduino IDE: 1.8.19+

================================================================================
CONFIGURACIÓN DE PINES SPI (CRÍTICA)
================================================================================

Los siguientes pines deben conectarse EXACTAMENTE así en tu pantalla ST7789:

  PANTALLA (ST7789)  ←→  ESP32
  ─────────────────────────────
  DC (Data/Command)  ←→  Pin 2
  CS (Chip Select)   ←→  Pin 15
  SCK (Clock)        ←→  Pin 14
  MOSI (Data In)     ←→  Pin 13
  BL (Backlight)     ←→  Pin 27
  RST (Reset)        ←→ NO CONECTADO (-1 en código, usa el RST/EN del ESP32)
  MISO               ←→ NO SE USA

⚠️ IMPORTANTE: Estos pines SPI DEBEN estar configurados manualmente en el código
   porque cada ESP32/pantalla tiene una combinación diferente. Los pines por defecto
   de la librería NO siempre funcionan.

================================================================================
CAMBIOS PRINCIPALES EN ESP32 CORE v3.x
================================================================================

1. CONTROL DE BACKLIGHT (BL):
   ❌ INCORRECTO (versión antigua):
      ledcAttach(TFT_BL, 2000, 8);
      ledcWrite(0, 255);  // Esto intenta escribir en el CANAL 0, no en el pin

   ✅ CORRECTO (versión nueva):
      pinMode(TFT_BL, OUTPUT);
      digitalWrite(TFT_BL, HIGH);  // Enciende la luz 100%
      
      O para controlar brillo con PWM:
      ledcAttach(TFT_BL, 2000, 8);
      ledcWrite(TFT_BL, 255);  // Nota: ahora es ledcWrite(PIN, valor)

   → El cambio es que ledcWrite() ahora espera el NÚMERO DE PIN, no el canal.

2. DEFINICIÓN DE COLORES:
   En versiones antiguas de ESP32 Core, los colores se definían como macros.
   En versiones nuevas (v3.x), Arduino_GFX proporciona colores como:
   - RGB565_RED
   - RGB565_WHITE
   - RGB565_BLACK
   - etc.

================================================================================
INICIALIZACIÓN CORRECTA DE LA PANTALLA
================================================================================

ESTRUCTURA CORRECTA DEL CÓDIGO:

#include <Arduino_GFX_Library.h>

#define TFT_BL 27  // Pin de backlight

// ✅ DEFINE EXPLÍCITAMENTE LOS PINES (no uses defaults)
Arduino_DataBus *bus = new Arduino_ESP32SPI(
    2,    // DC (Data/Command)
    15,   // CS (Chip Select)
    14,   // SCK (Clock)
    13,   // MOSI (Master Out Slave In)
    GFX_NOT_DEFINED  // MISO (no se usa)
);

Arduino_GFX *gfx = new Arduino_ST7789(
    bus,
    -1,   // RST (Reset) = -1 significa que no está conectado
    1,    // Rotación (0-3)
    true  // IPS (true = pantalla IPS)
);

void setup(void) {
    gfx->begin();
    gfx->fillScreen(RGB565_BLACK);
    
    // Enciende el backlight
    #ifdef TFT_BL
    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, HIGH);
    #endif
    
    // Dibuja algo para verificar que funciona
    gfx->setCursor(10, 10);
    gfx->setTextColor(RGB565_RED);
    gfx->println("Hello World!");
}

void loop() {
    // Tu código aquí
}

================================================================================
PROBLEMAS COMUNES Y SOLUCIONES
================================================================================

PROBLEMA 1: "Pantalla negra después de compilación exitosa"
CAUSAS:
  a) El backlight (BL) no está encendido → La pantalla no recibe luz
  b) Los pines SPI son incorrectos → La pantalla no recibe datos
  c) ledcWrite(0, 255) en lugar de digitalWrite(TFT_BL, HIGH)

SOLUCIÓN:
  ✅ Asegúrate de que TFT_BL está definido correctamente (Pin 27)
  ✅ Verifica la conexión física del pin BL
  ✅ Usa digitalWrite(TFT_BL, HIGH) en lugar de ledcWrite()
  ✅ Comprueba que los pines SPI (2, 15, 14, 13) coinciden con tu conexión

PROBLEMA 2: "Compilación falla con Arduino_GFX_Library"
CAUSAS:
  a) Versión incompatible de ESP32 Core
  b) Librería no instalada correctamente

SOLUCIÓN:
  ✅ Desinstala y vuelve a instalar Arduino_GFX_Library
  ✅ Asegúrate de que tienes ESP32 Core v2.0.0 o superior
  ✅ Reinicia Arduino IDE después de instalar

PROBLEMA 3: "El ejemplo genérico de Arduino_GFX no funciona"
CAUSA:
  Ejemplo usa create_default_Arduino_GFX() que intenta auto-detectar pines
  pero no siempre funciona

SOLUCIÓN:
  ✅ NUNCA uses create_default_Arduino_GFX() o create_default_Arduino_DataBus()
  ✅ SIEMPRE define manualmente los pines con:
     new Arduino_ESP32SPI(DC, CS, SCK, MOSI, MISO)
     new Arduino_ST7789(bus, RST, rotation, IPS)

================================================================================
INCOMPATIBILIDADES CON LVGL (si usas LVGL v9)
================================================================================

Si intentas usar LVGL v9 con este proyecto, ten en cuenta:

1. LVGL v8 vs v9 - CAMBIO DE API MAYOR:
   ❌ LVGL v8:
      lv_disp_buf_t disp_buf;
      lv_disp_drv_t disp_drv;
      lv_disp_drv_register(&disp_drv);

   ✅ LVGL v9:
      lv_display_t * disp = lv_display_create(320, 240);
      lv_display_set_flush_cb(disp, my_disp_flush);

2. ARCHIVO lv_conf.h - UBICACIÓN CRÍTICA:
   ❌ INCORRECTO: lvgl/src/lv_conf.h (dentro de la carpeta de la librería)
   ✅ CORRECTO:   Raíz del proyecto (mismo nivel que test.ino)

3. PROBLEMA DE ASSEMBLY ARM:
   El archivo lv_blend_helium.S es incompatible con ESP32 (es para ARM)
   SOLUCIÓN: Renómbralo a lv_blend_helium.S.disabled

================================================================================
CHECKLIST ANTES DE COMPILAR
================================================================================

☐ 1. Los pines SPI están definidos correctamente:
      - DC = 2
      - CS = 15
      - SCK = 14
      - MOSI = 13
      - BL = 27

☐ 2. El código usa Arduino_ST7789 (no ILI9341 u otro)

☐ 3. Se usa Arduino_ESP32SPI con los pines explícitamente definidos
      (no create_default_Arduino_DataBus)

☐ 4. El backlight se enciende con digitalWrite(TFT_BL, HIGH)
      (no con ledcWrite(0, 255))

☐ 5. gfx->begin() se llama antes de dibujar nada

☐ 6. Arduino IDE está configurado para:
      - Board: ESP32 Dev Module
      - Flash Frequency: 80 MHz
      - Flash Size: 4MB

☐ 7. Las conexiones físicas coinciden con los pines del código

================================================================================
REFERENCIA RÁPIDA: SINTAXIS ARDUINO_GFX v9
================================================================================

// Inicializar bus SPI
Arduino_DataBus *bus = new Arduino_ESP32SPI(DC, CS, SCK, MOSI, MISO);

// Inicializar pantalla ST7789
Arduino_GFX *gfx = new Arduino_ST7789(bus, RST, rotation, IPS);

// Inicializar pantalla (DEBE hacerse primero)
gfx->begin();

// Limpiar pantalla
gfx->fillScreen(RGB565_BLACK);

// Escribir texto
gfx->setCursor(x, y);
gfx->setTextColor(color);
gfx->println("Texto");

// Dibujar formas
gfx->drawRect(x, y, width, height, color);       // Rectángulo vacío
gfx->fillRect(x, y, width, height, color);       // Rectángulo lleno
gfx->drawCircle(x, y, radius, color);            // Círculo vacío
gfx->fillCircle(x, y, radius, color);            // Círculo lleno
gfx->drawLine(x1, y1, x2, y2, color);            // Línea

// Colores disponibles
RGB565_BLACK, RGB565_WHITE, RGB565_RED, RGB565_GREEN, RGB565_BLUE, etc.

================================================================================
RECURSOS ÚTILES
================================================================================

Arduino_GFX Library GitHub:
https://github.com/moononournation/Arduino_GFX

Documentación de pines por placa:
https://github.com/moononournation/Arduino_GFX/wiki/Dev-Device-Declaration

LVGL Documentación (si usas LVGL v9):
https://docs.lvgl.io/

================================================================================
HISTORIAL DE CAMBIOS
================================================================================

v1.0 (14 Enero 2026):
- Documentación inicial completa
- Pines SPI configurados para ST7789
- Solución de pantalla negra
- Notas sobre ESP32 Core v3.x
- Referencia de sintaxis Arduino_GFX v9

v2.0 (15 Enero 2026):
- Integración con EZZ Studio v8 + LVGL v8
- Documentación del callback de flush
- Explicación de errores comunes de compilación
- Guía de coordenadas de pantalla

================================================================================
================================================================================
        BITÁCORA: INTEGRACIÓN EZZ STUDIO + LVGL + ARDUINO_GFX
================================================================================
================================================================================

Fecha: 15 de Enero de 2026
Pantalla: ST7789 360×240 píxeles
Librerías: LVGL 8.3.3, Arduino_GFX_Library 1.6.4, ESP32 Core 3.3.5

================================================================================
PARTE 1: ¿QUÉ ES EZZ STUDIO?
================================================================================

EZZ Studio es un programa visual (WYSIWYG) donde diseñas interfaces gráficas
(botones, textos, imágenes, etc.) y luego EXPORTA código C que puedes usar
directamente en tu microcontrolador.

FLUJO DE TRABAJO:
┌─────────────────┐    ┌─────────────────┐    ┌─────────────────┐
│   EZZ STUDIO    │ →  │ ARCHIVOS .c/.h  │ →  │   ARDUINO IDE   │
│ (Diseño visual) │    │   (Exportados)  │    │  (Compilación)  │
└─────────────────┘    └─────────────────┘    └─────────────────┘

================================================================================
PARTE 2: ARCHIVOS EXPORTADOS POR EZZ STUDIO
================================================================================

Cuando exportas desde EZZ, obtienes estos archivos:

  ARCHIVO          │ PROPÓSITO
  ─────────────────┼──────────────────────────────────────────────
  ui.h / ui.c      │ Funciones principales: ui_init(), ui_tick()
  screens.h/.c     │ Definición de pantallas y widgets (botones, labels)
  images.h/.c      │ Imágenes convertidas a arrays C (formato RGB565)
  fonts.h          │ Fuentes personalizadas
  styles.h/.c      │ Estilos visuales (colores, bordes, sombras)
  vars.h           │ Variables globales del proyecto
  actions.h        │ Acciones/eventos (cuando presionas un botón, etc.)
  structs.h        │ Estructuras de datos

================================================================================
PARTE 3: ESTRUCTURA DE CARPETAS PARA ARDUINO
================================================================================

⚠️ REGLA CRÍTICA DE ARDUINO IDE:
   Arduino SOLO compila automáticamente archivos .c/.cpp que estén en:
   - La carpeta RAÍZ del proyecto
   - Una carpeta llamada "src/"
   
   Arduino NO compila archivos en carpetas con otros nombres (ej: "assets/")

ESTRUCTURA CORRECTA:
  test/
  ├── test.ino              ← Código principal
  ├── compile_commands.json ← Para IntelliSense de VSCode (opcional)
  ├── Readme.txt            ← Esta documentación
  ├── src/                  ← ¡NOMBRE OBLIGATORIO!
  │   ├── ui.h
  │   ├── ui.c
  │   ├── screens.h
  │   ├── screens.c
  │   ├── images.h
  │   ├── images.c
  │   ├── fonts.h
  │   ├── styles.h
  │   ├── styles.c
  │   ├── vars.h
  │   ├── actions.h
  │   └── structs.h
  └── .vscode/              ← Configuración de VSCode
      ├── c_cpp_properties.json
      ├── arduino.json
      └── settings.json

================================================================================
PARTE 4: CONEXIÓN ENTRE LVGL Y ARDUINO_GFX (CALLBACK DE FLUSH)
================================================================================

PROBLEMA:
- LVGL es la librería que "pinta" la interfaz gráfica en memoria
- Arduino_GFX es la librería que controla físicamente tu pantalla ST7789
- ¡Pero no se conocen entre sí!

SOLUCIÓN: CALLBACK DE FLUSH (el "traductor")

ANALOGÍA:
  LVGL        = Un PINTOR que crea cuadros (píxeles en memoria)
  Arduino_GFX = Un MENSAJERO que lleva cuadros al museo (pantalla física)
  Callback    = El TRADUCTOR que conecta al pintor con el mensajero

FLUJO:
┌─────────────────────────────────────────────────────────────────────┐
│  1. LVGL dibuja widgets (botón, texto, etc.) en un buffer           │
│                           ↓                                         │
│  2. LVGL llama al callback: "¡Tengo píxeles listos!"                │
│                           ↓                                         │
│  3. Callback recibe:                                                │
│     - area: coordenadas del rectángulo a dibujar                    │
│     - color_p: puntero al array de píxeles RGB565                   │
│                           ↓                                         │
│  4. Callback usa Arduino_GFX para enviar píxeles a la pantalla      │
│     gfx->draw16bitRGBBitmap(x, y, píxeles, ancho, alto)             │
│                           ↓                                         │
│  5. Callback notifica: "¡LVGL, ya terminé!"                         │
│     lv_disp_flush_ready(disp)                                       │
│                           ↓                                         │
│  6. LVGL puede continuar dibujando más cosas                        │
└─────────────────────────────────────────────────────────────────────┘

CÓDIGO DEL CALLBACK:

  void lvgl_flush_cb(lv_disp_drv_t *disp, const lv_area_t *area, 
                     lv_color_t *color_p)
  {
      // Calcular tamaño del área
      int32_t w = area->x2 - area->x1 + 1;  // Ancho
      int32_t h = area->y2 - area->y1 + 1;  // Alto
      
      // Enviar píxeles a la pantalla
      gfx->draw16bitRGBBitmap(area->x1, area->y1, 
                              (uint16_t *)color_p, w, h);
      
      // Notificar a LVGL que terminamos
      lv_disp_flush_ready(disp);
  }

================================================================================
PARTE 5: MATEMÁTICA DE COORDENADAS DE PANTALLA
================================================================================

PANTALLA: 360×240 píxeles
- Coordenada X: de 0 a 359 (360 valores)
- Coordenada Y: de 0 a 239 (240 valores)

SISTEMA DE COORDENADAS:
  (0,0)─────────────────────────────────(359,0)
    │                                       │
    │              PANTALLA                 │
    │              360×240                  │
    │                                       │
  (0,239)───────────────────────────────(359,239)

FÓRMULAS IMPORTANTES:

  Para calcular x2, y2 dado un rectángulo:
  ────────────────────────────────────────────
  x2 = x1 + ancho - 1
  y2 = y1 + alto - 1

  Para calcular ancho, alto dado x1,y1,x2,y2:
  ────────────────────────────────────────────
  ancho = x2 - x1 + 1
  alto  = y2 - y1 + 1

EJEMPLO: Rectángulo de 50×30 en posición (100, 150)
  x1 = 100
  y1 = 150
  x2 = 100 + 50 - 1 = 149
  y2 = 150 + 30 - 1 = 179

VERIFICACIÓN:
  ancho = 149 - 100 + 1 = 50 ✓
  alto  = 179 - 150 + 1 = 30 ✓

POSICIONES EN LAS 4 ESQUINAS (rectángulo 50×30):
  ┌─────────────────────────────────────────────────────────────┐
  │ Esquina              │  x1  │  y1  │  x2  │  y2  │         │
  │──────────────────────│──────│──────│──────│──────│         │
  │ Superior izquierda   │   0  │   0  │  49  │  29  │         │
  │ Superior derecha     │ 310  │   0  │ 359  │  29  │         │
  │ Inferior izquierda   │   0  │ 210  │  49  │ 239  │         │
  │ Inferior derecha     │ 310  │ 210  │ 359  │ 239  │         │
  └─────────────────────────────────────────────────────────────┘

================================================================================
PARTE 6: ERRORES DE COMPILACIÓN Y CÓMO DETECTARLOS
================================================================================

ERROR TIPO 1: ERROR DE COMPILACIÓN
─────────────────────────────────────
Mensaje típico:
  error: 'class Arduino_GFX' has no member named 'pushImage'

Significado: El código usa algo que NO EXISTE
  - Una función que no existe en esa librería
  - Una variable mal escrita
  - Un include que falta

Cómo detectarlo: El compilador te dice EXACTAMENTE:
  - Qué clase tiene el problema ('class Arduino_GFX')
  - Qué miembro no encontró ('pushImage')

Solución: Revisar la documentación de la librería para encontrar
          el método correcto (en este caso era 'draw16bitRGBBitmap')


ERROR TIPO 2: ERROR DE LINKER (ENLAZADOR)
─────────────────────────────────────────
Mensaje típico:
  undefined reference to `ui_init'

Significado: 
  - El compilador ENCONTRÓ la DECLARACIÓN (en ui.h)
  - Pero NO ENCONTRÓ la IMPLEMENTACIÓN (en ui.c)

Diferencia clave:
  - Declaración (en .h): "Existe una función llamada ui_init()"
  - Implementación (en .c): "Aquí está el código de ui_init()"

Causas comunes:
  a) El archivo .c no está siendo compilado
  b) El archivo .c está en una carpeta que Arduino ignora
  c) Olvidaste incluir el archivo .c en el proyecto

Solución: Mover los archivos .c a la carpeta "src/" porque
          Arduino SOLO compila archivos en raíz o en src/


ERROR TIPO 3: ERROR DEL SISTEMA DE ARCHIVOS
───────────────────────────────────────────
Mensaje típico:
  GetFileInformationByHandle C:\...\test\nul: Incorrect function

Significado: Hay un archivo con nombre inválido en la carpeta

En este caso: "nul" es un nombre reservado de Windows (como /dev/null)
              y el compilador no puede procesarlo

Solución: Eliminar el archivo problemático


RESUMEN VISUAL:
┌──────────────────────────────────────────────────────────────────┐
│  TIPO DE ERROR         │  FASE      │  QUÉ BUSCAR               │
│────────────────────────│────────────│───────────────────────────│
│  Compilación           │  Compile   │  "error:" + nombre/línea  │
│  Linker                │  Link      │  "undefined reference"    │
│  Sistema de archivos   │  Pre-build │  "GetFileInformation"     │
└──────────────────────────────────────────────────────────────────┘

================================================================================
PARTE 7: ¿QUÉ ES compile_commands.json?
================================================================================

Es un archivo que le dice a VSCode/IntelliSense CÓMO se compila tu proyecto:
- Qué compilador se usa (xtensa-esp32-elf-g++)
- Qué flags tiene (-DARDUINO, -DESP32, etc.)
- Dónde están los headers (-IC:/Users/.../include)

PROPÓSITO:
┌────────────────────────────────┬────────────────────────────────┐
│  SIN compile_commands.json    │  CON compile_commands.json     │
│────────────────────────────────│────────────────────────────────│
│  VSCode no encuentra headers   │  VSCode encuentra todo         │
│  Líneas rojas falsas           │  IntelliSense funciona bien    │
│  Autocompletado limitado       │  Autocompletado completo       │
└────────────────────────────────┴────────────────────────────────┘

¿ES OBLIGATORIO?
- Para COMPILAR: NO. Arduino IDE no lo necesita.
- Para VSCODE: SÍ ayuda mucho con IntelliSense.

¿DÓNDE DEBE ESTAR?
- En la RAÍZ del proyecto (no en .vscode/)
- Las herramientas lo buscan ahí automáticamente

¿PUEDO BORRARLO?
- Sí, no afecta la compilación
- Pero perderás funcionalidad de IntelliSense en VSCode

================================================================================
PARTE 8: CÓDIGO COMPLETO DE INTEGRACIÓN
================================================================================

#include <Arduino.h>
#include <Arduino_GFX_Library.h>
#include <lvgl.h>
#include "src/ui.h"           // ← Archivos de EZZ Studio

#define TFT_BL 27

// Configuración de pines SPI
Arduino_DataBus *bus = new Arduino_ESP32SPI(
    2,   // DC
    15,  // CS
    14,  // SCK
    13,  // MOSI
    GFX_NOT_DEFINED  // MISO
);
Arduino_GFX *gfx = new Arduino_ST7789(bus, -1, 1, true);

void setup(void)
{
    gfx->begin();
    
    // Backlight
    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, HIGH);
    
    // Inicializar LVGL
    lv_init();
    
    // Buffer de dibujo (360 píxeles ancho × 40 líneas)
    // Usa 28,800 bytes de RAM (360 × 40 × 2 bytes por píxel)
    static lv_color_t buf1[360 * 40];
    static lv_disp_draw_buf_t draw_buf;
    lv_disp_draw_buf_init(&draw_buf, buf1, NULL, 360 * 40);
    
    // Configurar driver de pantalla
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = gfx->width();     // 360
    disp_drv.ver_res = gfx->height();    // 240
    disp_drv.draw_buf = &draw_buf;
    disp_drv.flush_cb = lvgl_flush_cb;   // ← Callback de flush
    lv_disp_drv_register(&disp_drv);
    
    // Inicializar UI de EZZ Studio
    ui_init();
}

void loop()
{
    lv_timer_handler();  // LVGL procesa eventos y redibuja
    delay(5);            // ~200 FPS máximo
}

// CALLBACK DE FLUSH: Conecta LVGL con Arduino_GFX
void lvgl_flush_cb(lv_disp_drv_t *disp, const lv_area_t *area, 
                   lv_color_t *color_p)
{
    int32_t w = area->x2 - area->x1 + 1;
    int32_t h = area->y2 - area->y1 + 1;
    gfx->draw16bitRGBBitmap(area->x1, area->y1, (uint16_t *)color_p, w, h);
    lv_disp_flush_ready(disp);
}

================================================================================
PARTE 9: CHECKLIST PARA NUEVOS PROYECTOS CON EZZ STUDIO
================================================================================

☐ 1. Crear proyecto en EZZ Studio con resolución correcta (360×240)

☐ 2. Diseñar la interfaz (pantallas, botones, textos, imágenes)

☐ 3. Exportar desde EZZ Studio (genera archivos .c y .h)

☐ 4. Crear carpeta "src/" en tu proyecto Arduino

☐ 5. Copiar TODOS los archivos exportados a "src/"
      (ui.h, ui.c, screens.h, screens.c, images.h, images.c, etc.)

☐ 6. En test.ino, añadir:
      #include <lvgl.h>
      #include "src/ui.h"

☐ 7. Configurar el buffer de LVGL con TU resolución:
      static lv_color_t buf1[TU_ANCHO * 40];
      lv_disp_draw_buf_init(&draw_buf, buf1, NULL, TU_ANCHO * 40);

☐ 8. Implementar el callback de flush con Arduino_GFX

☐ 9. Llamar ui_init() en setup()

☐ 10. Llamar lv_timer_handler() en loop()

☐ 11. Compilar y verificar errores

☐ 12. Subir al ESP32 y probar

================================================================================
PARTE 10: NOTAS FINALES
================================================================================

MEMORIA RAM:
- El buffer de 360×40 usa 28,800 bytes
- ESP32 tiene ~320KB de RAM disponible
- Si necesitas más RAM, reduce las líneas del buffer (ej: 360×20)

RENDIMIENTO:
- delay(5) en loop() limita a ~200 FPS
- Para animaciones más suaves, usa delay(1) o elimínalo
- Para ahorrar CPU, usa delay(10) o más

ACTUALIZAR UI DESDE EZZ:
- Cada vez que cambies algo en EZZ Studio, vuelve a exportar
- Reemplaza los archivos en src/ con los nuevos
- Recompila

DEPURACIÓN:
- Si la pantalla está negra, verifica el backlight
- Si no se ve la UI, verifica que ui_init() se está llamando
- Si hay errores de compilación, revisa que src/ contenga todos los .c

================================================================================
FIN DE LA BITÁCORA
================================================================================

================================================================================
================================================================================
        BITÁCORA 2: TOUCH GT911 + PORTRAIT MODE + ERRORES COMUNES
================================================================================
================================================================================

Fecha: 21 de Enero de 2026
Pantalla: ESP32-2432S032 (3.2" 240×320 IPS)
Touch: GT911 Capacitivo (I2C)
Librerías: LVGL 8.3.3, Arduino_GFX_Library 1.6.4, Touch_GT911, ESP32 Core 3.3.5

================================================================================
PARTE 1: ESPECIFICACIONES DEL HARDWARE ESP32-2432S032
================================================================================

DISPLAY:
- Controlador: ST7789
- Resolución: 240×320 (portrait) o 320×240 (landscape)
- Interface: SPI
- Tipo: IPS

TOUCH:
- Controlador: GT911 (capacitivo, NO resistivo)
- Interface: I2C
- Multi-touch: Soporta hasta 5 puntos

PINES DISPLAY (SPI):
  Función      │  Pin ESP32
  ─────────────┼───────────
  DC           │  2
  CS           │  15
  SCK          │  14
  MOSI         │  13
  Backlight    │  27
  RST          │  -1 (no conectado)

PINES TOUCH GT911 (I2C):
  Función      │  Pin ESP32
  ─────────────┼───────────
  SDA          │  33
  SCL          │  32
  INT          │  -1 (no usado)
  RST          │  25

================================================================================
PARTE 2: CONFIGURACIÓN CORRECTA DEL TOUCH GT911 PARA PORTRAIT MODE
================================================================================

⚠️ PROBLEMA CRÍTICO:
El GT911 viene calibrado de fábrica para LANDSCAPE (320×240).
Si usas el display en PORTRAIT (240×320), las coordenadas están rotadas.

El ejemplo oficial del fabricante usa:
- Display: rotation=3 (landscape 320×240)
- Touch: ROTATION_RIGHT, coordenadas X:320→0, Y:240→0

Para PORTRAIT (rotation=0, 240×320) necesitamos:
1. Inicializar GT911 con dimensiones 320×240 (lo que reporta internamente)
2. Intercambiar X↔Y (SWAP)
3. Mapear las coordenadas correctamente

CÓDIGO CORRECTO PARA PORTRAIT:

```cpp
// Inicialización del GT911 (usar 320, 240 aunque sea portrait)
Touch_GT911 ts(TOUCH_GT911_SDA, TOUCH_GT911_SCL, TOUCH_GT911_INT, 
               TOUCH_GT911_RST, 320, 240);

void touch_init() {
    Wire.begin(TOUCH_GT911_SDA, TOUCH_GT911_SCL);
    ts.begin();
    ts.setRotation(ROTATION_LEFT);  // Rotación para portrait mode
}

bool touch_touched() {
    ts.read();
    if (ts.isTouched) {
        int raw_x = ts.points[0].x;  // 0-320 en landscape
        int raw_y = ts.points[0].y;  // 0-240 en landscape
        
        // Transformación para portrait (rotation=0):
        // display_x = raw_y (0-240 → 0-239)
        // display_y = 319 - raw_x (0-320 → 319-0, invertido)
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
```

TABLA DE TRANSFORMACIONES SEGÚN ROTACIÓN:
┌──────────────┬─────────────────────────────────────────────────────┐
│  Display     │  Transformación de coordenadas                      │
│  Rotation    │  (raw_x, raw_y del GT911 → x, y de pantalla)        │
│──────────────┼─────────────────────────────────────────────────────│
│  0 (portrait)│  x = raw_y;  y = 319 - raw_x                        │
│  1 (land R)  │  x = raw_x;  y = raw_y  (sin transformación)        │
│  2 (port inv)│  x = 239 - raw_y;  y = raw_x                        │
│  3 (land L)  │  x = 319 - raw_x;  y = 239 - raw_y                  │
└──────────────┴─────────────────────────────────────────────────────┘

================================================================================
PARTE 3: ERRORES COMUNES CON ESP32 CORE 3.x
================================================================================

ERROR 1: ledcSetup() y ledcAttachPin() deprecados
─────────────────────────────────────────────────

❌ CÓDIGO ANTIGUO (ESP32 Core 2.x):
   ledcSetup(0, 2000, 8);
   ledcAttachPin(TFT_BL, 0);
   ledcWrite(0, 255);  // Escribe en canal 0

✅ CÓDIGO NUEVO (ESP32 Core 3.x):
   ledcAttach(TFT_BL, 2000, 8);  // Combina setup + attach
   ledcWrite(TFT_BL, 255);       // Escribe en PIN, no canal


ERROR 2: Color BLACK no declarado
──────────────────────────────────

❌ INCORRECTO:
   gfx->fillScreen(BLACK);
   
✅ CORRECTO (Arduino_GFX 1.6.x):
   gfx->fillScreen(RGB565_BLACK);

Colores disponibles: RGB565_BLACK, RGB565_WHITE, RGB565_RED, 
                     RGB565_GREEN, RGB565_BLUE, etc.


ERROR 3: Archivo "nul" causa error en Windows
─────────────────────────────────────────────

Mensaje: "GetFileInformationByHandle C:\...\nul: Incorrect function"

Causa: Se creó accidentalmente un archivo llamado "nul" que es un
       nombre reservado de Windows (equivalente a /dev/null).

Solución: Eliminar el archivo con:
   rm -f "ruta/al/proyecto/nul"

================================================================================
PARTE 4: ERRORES COMUNES CON LVGL 8.3
================================================================================

ERROR 1: lv_obj_set_style_transform_zoom() causa problemas
──────────────────────────────────────────────────────────

⚠️ PROBLEMA:
En LVGL 8.3, usar transform_zoom para escalar texto puede causar:
- Texto que desaparece
- Elementos que no se renderizan
- Layout corrupto

❌ EVITAR:
   lv_obj_set_style_transform_zoom(label, 350, 0);  // 3.5x scale

✅ ALTERNATIVA:
   - Habilitar fuentes más grandes en lv_conf.h
   - #define LV_FONT_MONTSERRAT_20  1
   - #define LV_FONT_MONTSERRAT_28  1
   - Luego usar: lv_obj_set_style_text_font(label, &lv_font_montserrat_28, 0);


ERROR 2: Fuentes no disponibles
───────────────────────────────

❌ PROBLEMA:
   lv_obj_set_style_text_font(label, &lv_font_montserrat_28, 0);
   // Error: lv_font_montserrat_28 not declared

✅ SOLUCIÓN:
   Editar lv_conf.h y habilitar la fuente:
   #define LV_FONT_MONTSERRAT_28  1

Fuentes disponibles en LVGL por defecto: montserrat_14
Fuentes que necesitan habilitarse: 10, 12, 16, 20, 22, 24, 28, 30, etc.


ERROR 3: Paneles/widgets no visibles
────────────────────────────────────

CAUSAS COMUNES:
a) Widget posicionado fuera del área visible (x>240 o y>320)
b) Widget tiene tamaño 0
c) Widget oculto por otro widget encima
d) Estilo con opacidad 0

DEPURACIÓN:
- Verificar posición: lv_obj_get_x(), lv_obj_get_y()
- Verificar tamaño: lv_obj_get_width(), lv_obj_get_height()
- Agregar borde temporal para ver límites:
  lv_obj_set_style_border_width(obj, 2, 0);
  lv_obj_set_style_border_color(obj, lv_color_hex(0xFF0000), 0);

================================================================================
PARTE 5: DIFERENCIAS ENTRE TOUCH RESISTIVO Y CAPACITIVO
================================================================================

                    │  RESISTIVO (XPT2046)  │  CAPACITIVO (GT911)
────────────────────┼───────────────────────┼──────────────────────
Interface           │  SPI                  │  I2C
Multi-touch         │  NO (1 punto)         │  SÍ (hasta 5 puntos)
Precisión           │  Media                │  Alta
Necesita presión    │  SÍ                   │  NO
Necesita calibración│  SÍ (frecuente)       │  NO (fábrica)
Librería            │  XPT2046_Touchscreen  │  Touch_GT911

⚠️ IMPORTANTE:
La pantalla ESP32-2432S032 usa GT911 CAPACITIVO, no XPT2046 resistivo.
Usar la librería incorrecta resultará en touch que no funciona.

================================================================================
PARTE 6: INSTALACIÓN DE LIBRERÍA TOUCH_GT911
================================================================================

La librería Touch_GT911 no está en el gestor de librerías de Arduino.
Debe instalarse manualmente:

PASOS:
1. Copiar carpeta "Touch_GT911" desde el demo del fabricante:
   C:\...\3.2inch_ESP32-2432S032-main\1-Demo\Demo_Arduino\Libraries\Touch_GT911

2. Pegar en la carpeta de librerías de Arduino:
   C:\Users\TU_USUARIO\Documents\Arduino\libraries\Touch_GT911

3. Crear archivo library.properties:
   name=Touch_GT911
   version=1.0.0
   author=TAMCTec
   maintainer=TAMCTec
   sentence=GT911 capacitive touch driver
   category=Device Control
   architectures=esp32

4. Reiniciar Arduino IDE

================================================================================
PARTE 7: CÓDIGO COMPLETO PARA ESP32-2432S032 EN PORTRAIT MODE
================================================================================

#include <Arduino.h>
#include <Arduino_GFX_Library.h>
#include <lvgl.h>
#include <Wire.h>
#include <Touch_GT911.h>
#include "src/ui.h"

// Pines Display SPI
#define TFT_BL   27
#define TFT_DC   2
#define TFT_CS   15
#define TFT_SCK  14
#define TFT_MOSI 13

// Pines Touch I2C
#define TOUCH_GT911_SDA 33
#define TOUCH_GT911_SCL 32
#define TOUCH_GT911_INT -1
#define TOUCH_GT911_RST 25

// Display ST7789 en portrait (rotation=0)
Arduino_DataBus *bus = new Arduino_ESP32SPI(TFT_DC, TFT_CS, TFT_SCK, TFT_MOSI, GFX_NOT_DEFINED);
Arduino_GFX *gfx = new Arduino_ST7789(bus, -1, 0, true);

// Touch GT911 (dimensiones internas 320x240)
Touch_GT911 ts(TOUCH_GT911_SDA, TOUCH_GT911_SCL, TOUCH_GT911_INT, TOUCH_GT911_RST, 320, 240);

int touch_last_x = 0, touch_last_y = 0;

// LVGL buffers
static lv_disp_draw_buf_t draw_buf;
static lv_color_t *disp_draw_buf;
static lv_disp_drv_t disp_drv;

void setup() {
    gfx->begin(80000000);
    gfx->fillScreen(RGB565_BLACK);

    // Backlight (ESP32 Core 3.x)
    ledcAttach(TFT_BL, 2000, 8);
    ledcWrite(TFT_BL, 255);

    lv_init();
    delay(20);
    touch_init();

    uint32_t screenWidth = gfx->width();
    uint32_t screenHeight = gfx->height();

    disp_draw_buf = (lv_color_t *)heap_caps_malloc(
        sizeof(lv_color_t) * screenWidth * 40, 
        MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
    
    lv_disp_draw_buf_init(&draw_buf, disp_draw_buf, NULL, screenWidth * 40);

    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = my_touchpad_read;
    lv_indev_drv_register(&indev_drv);

    ui_init();
}

void loop() {
    lv_timer_handler();
    ui_tick();
    delay(5);
}

void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p) {
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);
    gfx->draw16bitRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);
    lv_disp_flush_ready(disp);
}

void touch_init() {
    Wire.begin(TOUCH_GT911_SDA, TOUCH_GT911_SCL);
    ts.begin();
    ts.setRotation(ROTATION_LEFT);
}

bool touch_touched() {
    ts.read();
    if (ts.isTouched) {
        int raw_x = ts.points[0].x;
        int raw_y = ts.points[0].y;
        
        touch_last_x = map(raw_y, 0, 240, 0, 239);
        touch_last_y = map(raw_x, 0, 320, 319, 0);
        
        if (touch_last_x < 0) touch_last_x = 0;
        if (touch_last_x > 239) touch_last_x = 239;
        if (touch_last_y < 0) touch_last_y = 0;
        if (touch_last_y > 319) touch_last_y = 319;
        
        return true;
    }
    return false;
}

void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data) {
    if (touch_touched()) {
        data->state = LV_INDEV_STATE_PR;
        data->point.x = touch_last_x;
        data->point.y = touch_last_y;
    } else {
        data->state = LV_INDEV_STATE_REL;
    }
}

================================================================================
FIN DE LA BITÁCORA 2
================================================================================

================================================================================
================================================================================
        BITÁCORA 3: MIGRACIÓN A LVGL 9.4.0 + OPTIMIZACIÓN COMPILACIÓN
================================================================================
================================================================================

Fecha: 24 de Febrero de 2026
Pantalla: ESP32-2432S032 (3.2" 240×320 IPS)
Touch: GT911 Capacitivo (I2C)
Librerías: LVGL 9.4.0, Arduino_GFX_Library 1.6.4, Touch_GT911, ESP32 Core 3.3.5

================================================================================
PARTE 1: ACTUALIZACIÓN DE LVGL 8 → 9.4.0
================================================================================

OBJETIVO:
- Dejar de usar LVGL 8.3.x (y los bugs de la rama EEZ/LVGL8) y migrar todo el
  proyecto principal "Fisser HandBeam 10D" a LVGL 9.4.0.

CAMBIOS CLAVE:
- Librería LVGL actualizada a 9.4.0 en:
  C:/Users/DANNY/Documents/Arduino/libraries/lvgl
  (lv_version.h: LVGL_VERSION_MAJOR 9, MINOR 4, PATCH 0)

- Archivo de configuración lv_conf.h:
  - Ubicación correcta para Arduino:
    C:/Users/DANNY/Documents/Arduino/libraries/lv_conf.h
  - Basado en el template oficial lv_conf_template.h de LVGL 9.4.0.
  - Adaptado a ESP32-2432S032:
    * LV_COLOR_DEPTH = 16 (RGB565 para ST7789)
    * LV_MEM_SIZE = 48 KB
    * LV_USE_STDLIB_MALLOC/STRING/SPRINTF = LV_STDLIB_BUILTIN
    * LV_USE_OS = LV_OS_NONE
    * LV_USE_LOG = 0
    * Assert básicos habilitados (NULL, MALLOC) para depuración ligera.
    * Fuentes habilitadas: montserrat_14, montserrat_20, montserrat_28
    * LV_FONT_DEFAULT = &lv_font_montserrat_14

BUG IMPORTANTE SOLUCIONADO (ENSAMBLADOR):
- Error: "unknown opcode or format name 'typedef'" en headers del toolchain
  (machine/_default_types.h, stdint.h) cuando el ensamblador procesaba lv_conf.h.

CAUSA:
- Se había añadido #include <stdint.h> directo en lv_conf.h.
- Algunos archivos .S (assembly) del SDK ESP32 incluyen indirectamente lv_conf.h
  y el ensamblador intenta interpretar typedef como instrucciones ASM.

SOLUCIÓN:
- Eliminar #include <stdint.h> de lv_conf.h y dejar que LVGL use sus macros
  internas (LV_STDINT_INCLUDE, etc.).

================================================================================
PARTE 2: CAMBIOS EN EL SKETCH PRINCIPAL test.ino (LVGL 9)
================================================================================

Referencia: test/test.ino

ANTES (LVGL 8):
- Se utilizaban lv_disp_draw_buf_t, lv_disp_drv_t, callbacks con firmas
  viejas y lv_disp_drv_register, lv_indev_drv_register, etc.

DESPUÉS (LVGL 9.4.0):
- Inicialización general:
  - lv_init();
  - lv_tick_set_cb((lv_tick_get_cb_t)millis);  → LVGL usa millis() como tick.

- Display (ST7789 + Arduino_GFX):
  - Buffer de dibujo:
    - DRAW_BUF_SIZE = 240 * 40 * (LV_COLOR_DEPTH / 8)
    - Se reserva con heap_caps_malloc(DRAW_BUF_SIZE,
      MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT) para usar RAM interna.

  - Nuevo flujo LVGL 9:
    - lv_display_t *disp = lv_display_create(240, 320);
    - lv_display_set_flush_cb(disp, my_disp_flush);
    - lv_display_set_buffers(disp, draw_buf, NULL, DRAW_BUF_SIZE,
      LV_DISPLAY_RENDER_MODE_PARTIAL);
    - lv_display_set_color_format(disp, LV_COLOR_FORMAT_RGB565);

  - Callback de flush (adaptado a LVGL 9):
    - Firma nueva: void my_disp_flush(lv_display_t *disp,
      const lv_area_t *area, uint8_t *px_map)
    - Conversión del buffer: (uint16_t *)px_map para draw16bitRGBBitmap.
    - Llamada de finalización: lv_display_flush_ready(disp);

- Input (Touch GT911):
  - Inicialización touch: touch_init() mantiene la misma lógica
    (Wire.begin, ts.begin, ts.setRotation(ROTATION_LEFT)).
  - Nuevo flujo LVGL 9:
    - lv_indev_t *indev = lv_indev_create();
    - lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
    - lv_indev_set_read_cb(indev, my_touchpad_read);

  - Callback de input (LVGL 9):
    - Firma: void my_touchpad_read(lv_indev_t *indev, lv_indev_data_t *data)
    - Estados: LV_INDEV_STATE_PRESSED / LV_INDEV_STATE_RELEASED.

- Bucle principal:
  - lv_timer_handler();
  - ui_tick();
  - delay(5);

================================================================================
PARTE 3: MIGRACIÓN DE CÓDIGO UI (screens.c, ui.c, styles.c)
================================================================================

Archivo: src/screens.c
-----------------------
- Cambios clave para LVGL 9:
  - lv_obj_create(NULL);  (se mantiene, evitando 0 como puntero)
  - lv_btn_create() → lv_button_create() (nuevo nombre del widget botón).
  - El resto de API de estilos/labels/align se mantiene compatible.

- Widgets principales documentados (desde Bitácora previa):
  - Header: "Fisser HandBeam", "10D", icono de batería, línea divisoria.
  - Diodos: patrón rombo 2–3–3–2, color azul oscuro 0x003366.
  - Checkboxes R, V, IR: tamaño 42×42, estilo borde blanco+azul,
    icono LV_SYMBOL_OK.
  - Botones izquierda: PLAY, STOP, RESET, ESP con estilo azul.
  - Panel TIEMPO: fondo azul claro, título "TIEMPO" (20 pt), valor "00:00"
    (28 pt), botones ± grandes.
  - Paneles DOSIS PUNTUAL/TOTAL: paneles 82×75, títulos en dos líneas,
    valores 0.00 con montserrat_20.

Archivo: src/styles.c
----------------------
- API de estilos casi idéntica en LVGL 8 y 9:
  - style_btn_blue: fondo 0x007ACC, texto blanco, radio 6,
    fuente montserrat_14.
  - style_btn_white_border: fondo blanco, borde 0x007ACC 2px, radio 4.
  - style_panel_lightblue: fondo 0xD6EAF8, radio 6.
  - style_text_header, style_text_segment, style_text_small ajustan
    colores/fuentes según la maqueta.

Archivo: src/ui.c
------------------
- Rama sin EEZ (EEZ_FOR_LVGL no definido):
  - lv_scr_load_anim() → lv_screen_load_anim() (nueva API LVGL 9).
  - loadScreen() ahora usa lv_screen_load_anim(screen,
    LV_SCR_LOAD_ANIM_FADE_IN, 200, 0, false);
  - create_screens() + loadScreen(SCREEN_ID_MAIN); siguen como punto de
    entrada de la UI.

================================================================================
PARTE 4: CONFIGURACIÓN VS CODE + COMPILACIÓN RÁPIDA
================================================================================

PROBLEMA:
- Al abrir VS Code, la extensión de Arduino mostraba:
  "Output path is not specified. Unable to reuse previously compiled files."
- Aunque ya existía la carpeta build/ con objetos precompilados.

CAUSA:
- Había dos archivos arduino.json:
  1) Raíz del workspace: .vscode/arduino.json (SIN campo output)
  2) Proyecto test: test/.vscode/arduino.json (CON "output": "../build")

- La extensión Arduino usa principalmente el arduino.json de la RAÍZ, así que
  ignoraba el output definido en test/.vscode/arduino.json.

SOLUCIÓN:
- Unificar configuración en .vscode/arduino.json (raíz):
  - Board:  esp32:esp32:esp32
  - Port:   COM3
  - Sketch: test\\test.ino
  - Output: build
  - Configuration: misma cadena de opciones usada en el proyecto test
    (FlashMode=dio, PSRAM=disabled, etc.).

RESULTADO:
- Desaparece la advertencia sobre el output.
- La extensión Arduino reutiliza los objetos en build/ y las compilaciones
  posteriores son mucho más rápidas.

================================================================================
PARTE 5: WARNING DEL LINKER SOBRE PILA EJECUTABLE
================================================================================

Mensaje observado al compilar:
- ld.exe: warning: _floatdidf.o: missing .note.GNU-stack section implies
  executable stack

INTERPRETACIÓN:
- Es un warning del toolchain (ld) del ESP32, indicando que una librería
  precompilada no tiene la sección .note.GNU-stack.
- No afecta la ejecución del firmware en el ESP32.
- No está relacionado con nuestro código ni con LVGL.

ACCIONES:
- Se deja documentado, pero no se realiza ningún cambio en el proyecto porque
  depende del toolchain oficial de ESP32.

================================================================================
PARTE 6: RESUMEN RÁPIDO PARA FUTURAS MIGRACIONES
================================================================================

1) LVGL 9 en Arduino:
   - Colocar lv_conf.h en C:/Users/DANNY/Documents/Arduino/libraries/
   - Evitar incluir headers C directos en lv_conf.h para no romper los .S.
   - Usar nueva API: lv_display_create, lv_display_set_buffers,
     lv_indev_create, lv_indev_set_read_cb, lv_tick_set_cb.

2) ESP32-2432S032:
   - SPI: SCK=14, MOSI=13, DC=2, CS=15, BL=27.
   - Touch GT911: SDA=33, SCL=32, INT=-1, RST=25,
     dimensiones internas 320×240, rotación ROTATION_LEFT y transformación
     de coordenadas para portrait.

3) VS Code + Arduino extension:
   - Usar un único arduino.json en la raíz con "output": "build".
   - Mantener la carpeta build/ en la raíz del workspace para reutilizar
     artefactos de compilación.

4) Rendimiento:
   - Buffer parcial (240×40 líneas) balancea RAM vs velocidad.
   - delay(5) en loop() es un compromiso razonable; se puede ajustar según
     el comportamiento real del equipo.

================================================================================
FIN DE LA BITÁCORA 3
================================================================================

================================================================================
================================================================================
        BITÁCORA 4: ERRORES DE COMPILACIÓN CON EEZ STUDIO + LVGL 9
================================================================================
================================================================================

Fecha: 24 de Febrero de 2026 (continuación)
Contexto: Primera compilación completa con archivos regenerados por EEZ Studio

================================================================================
PROBLEMA 1: FUENTES MONTSERRAT NO DECLARADAS (montserrat_18, _22, _34)
================================================================================

ERROR:
  screens.c:483: error: 'lv_font_montserrat_34' undeclared
  screens.c:508: error: 'lv_font_montserrat_22' undeclared
  screens.c:800: error: 'lv_font_montserrat_18' undeclared

CAUSA:
  EEZ Studio usa en sus pantallas fuentes que no estaban habilitadas en lv_conf.h.
  LVGL solo compila las fuentes marcadas con valor 1.
  Por defecto solo viene activa montserrat_14.

SOLUCIÓN:
  Habilitar en C:/Users/DANNY/Documents/Arduino/libraries/lv_conf.h:

    #define LV_FONT_MONTSERRAT_18 1
    #define LV_FONT_MONTSERRAT_22 1
    #define LV_FONT_MONTSERRAT_34 1

NOTA:
  Cada vez que EEZ Studio use una fuente nueva, aparece el mismo error.
  La solución siempre es habilitar esa fuente en lv_conf.h.

================================================================================
PROBLEMA 2: CONVERSIÓN INVÁLIDA int → lv_part_t EN eez-flow.cpp
================================================================================

ERROR:
  eez-flow.cpp:3837: error: invalid conversion from 'int' to 'lv_part_t'
  eez-flow.cpp:4404: error: invalid conversion from 'int' to 'lv_part_t'

CAUSA:
  EEZ Studio genera eez-flow.cpp para LVGL 8, donde el segundo argumento de
  lv_obj_get_style_opa() se pasaba como entero literal 0.
  En LVGL 9, lv_part_t es un enum tipado y el compilador C++ rechaza la
  conversión implícita desde int.

  Líneas exactas afectadas:
    // ~3837
    lv_obj_get_style_opa((lv_obj_t *)a->user_data, 0)
    // ~4404
    lv_obj_get_style_opa(obj, 0)

SOLUCIÓN:
  Añadir cast explícito (lv_part_t) en ambas llamadas:

    lv_obj_get_style_opa((lv_obj_t *)a->user_data, (lv_part_t)LV_PART_MAIN)
    lv_obj_get_style_opa(obj, (lv_part_t)LV_PART_MAIN)

PROCEDIMIENTO RÁPIDO (aplicar tras cada exportación de EEZ Studio):
  1. Abrir eez-flow.cpp en VS Code.
  2. Ctrl+H (buscar y reemplazar en archivo actual).
  3. Buscar:  lv_obj_get_style_opa((lv_obj_t *)a->user_data, 0)
     Cambiar: lv_obj_get_style_opa((lv_obj_t *)a->user_data, (lv_part_t)LV_PART_MAIN)
  4. Buscar:  lv_obj_get_style_opa(obj, 0)
     Cambiar: lv_obj_get_style_opa(obj, (lv_part_t)LV_PART_MAIN)
  5. Guardar. Listo. Tiempo: ~10 segundos.

⚠️ ADVERTENCIA:
  eez-flow.cpp se regenera completo cada vez que exportas desde EEZ Studio.
  Estos dos cambios DEBEN aplicarse después de cada exportación antes de compilar.

================================================================================
PROBLEMA 3: CACHÉ DE COMPILACIÓN OBSOLETO (build/)
================================================================================

ERROR:
  ld.exe: cannot find build\libraries\lvgl\stdlib\builtin\objs.a:
  No such file or directory

CAUSA:
  La carpeta build/ tenía objetos precompilados (.a) de LVGL 8.
  Al actualizar a LVGL 9 la estructura interna cambió, pero el linker seguía
  buscando los archivos viejos en el caché.

SOLUCIÓN:
  Eliminar todo el contenido de build/ para forzar compilación limpia:

    rm -rf "C:/Users/DANNY/Desktop/Laser Inteligente/build/"*

  o desde el Explorador de Windows: seleccionar todo dentro de build/ y borrar.

NOTA:
  La primera compilación tarda más (varios minutos). Las siguientes son rápidas.
  Solo es necesario limpiar el caché al cambiar la versión de LVGL.

================================================================================
PROBLEMA 4: VARIABLE NATIVA SIN IMPLEMENTAR (get_var_output_keyboard)
================================================================================

ERROR:
  ld.exe: undefined reference to 'get_var_output_keyboard'
  ld.exe: undefined reference to 'set_var_output_keyboard'

CAUSA:
  EEZ Studio siempre genera en ui.c una tabla de variables nativas que incluye
  estas funciones aunque el teclado virtual no se use activamente.
  ui.c referencia los punteros de esas funciones, por lo que el linker las exige.
  En vars.h solo estaban DECLARADAS (extern), pero en ningún .c IMPLEMENTADAS.

SOLUCIÓN:
  Implementarlas en screens.c con un buffer estático mínimo:

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

REGLA GENERAL:
  Toda variable marcada como "Native" en EEZ Studio debe tener implementación
  en algún .c del proyecto, aunque no se use directamente.
  Si EEZ agrega nuevas variables nativas, aparecerá el mismo error con su nombre.

================================================================================
PROBLEMA 5: FUENTES ADICIONALES (montserrat_10, _12) + WIDGET QR CODE
================================================================================

ERROR (pantallas SETTINGS y CAMBIO_PASSWORD):
  screens.c:1690: error: 'lv_font_montserrat_12' undeclared
  screens.c:1821: error: 'lv_font_montserrat_10' undeclared
  screens.c:1900: error: implicit declaration of function 'lv_qrcode_create'
  screens.c:1904: error: implicit declaration of function 'lv_qrcode_set_size'
  screens.c:1905: error: implicit declaration of function 'lv_qrcode_set_dark_color'
  screens.c:1906: error: implicit declaration of function 'lv_qrcode_set_light_color'
  screens.c:1907: error: implicit declaration of function 'lv_qrcode_update'

CAUSA:
  Las pantallas nuevas generadas por EEZ usan las fuentes muy pequeñas (_10, _12)
  y la pantalla SETTINGS incluye un widget QR code.
  LV_USE_QRCODE no existía en lv_conf.h.

SOLUCIÓN:
  En lv_conf.h:

    #define LV_FONT_MONTSERRAT_10 1
    #define LV_FONT_MONTSERRAT_12 1
    #define LV_USE_QRCODE         1   // añadir junto a los otros LV_USE_*

================================================================================
RESUMEN: CHECKLIST TRAS REGENERAR DESDE EEZ STUDIO
================================================================================

Después de exportar el proyecto desde EEZ Studio y antes de compilar:

  ☐ 1. Aplicar los 2 reemplazos de (lv_part_t) en eez-flow.cpp
        (Ctrl+H en VS Code, ~10 segundos, ver Problema 2)

  ☐ 2. Verificar que todas las fuentes usadas en screens.c estén en lv_conf.h
        con valor 1 (ver Problemas 1 y 5)

  ☐ 3. Si hay nuevas variables nativas en vars.h, implementarlas en screens.c
        (ver Problema 4)

  ☐ 4. Si se cambió versión de LVGL, limpiar la carpeta build/ primero
        (ver Problema 3)

  ☐ 5. Si hay widget QR code, verificar LV_USE_QRCODE = 1 (ver Problema 5)

================================================================================
FIN DE LA BITÁCORA 4
================================================================================

================================================================================
================================================================================
        BITÁCORA 5: LÓGICA DE UI CON EEZ FLOW - FISSER HANDBEAM 10D
================================================================================
================================================================================

Fecha: 8 de Marzo de 2026
Herramientas: EEZ Studio, LVGL 9.4.0, EEZ Flow, Python 3.12, pngquant

================================================================================
DESCRIPCIÓN DEL PROYECTO
================================================================================

Dispositivo: Fisser HandBeam 10D
Tipo: Equipo médico/estético de terapia láser de baja intensidad
Hardware: 10 LEDs distribuidos en 3 longitudes de onda
  - 4 LEDs rojos (R)
  - 3 LEDs violetas (V)
  - 3 LEDs infrarrojos (IR)
Potencia por LED: 40 mW → máximo total: 400 mW (0.4 W)

PANTALLAS IMPLEMENTADAS:
  1. SplashScreen      — Pantalla de arranque con animación de carga
  2. login_SCREEN      — Acceso con PIN de 4 dígitos y teclado numérico
  3. MENU              — Pantalla principal de tratamiento
  4. SETTINGS          — Configuración general (incluye código QR)
  5. CAMBIO_PASSWORD   — Cambiar el PIN de acceso

================================================================================
PARTE 1: PANTALLA DE LOGIN (login_SCREEN)
================================================================================

OBJETIVO:
  Autenticación con teclado numérico (ButtonMatrix), PIN de 4 dígitos.
  Botón de ojo para mostrar/ocultar la contraseña.

----------------------------------------------------------------------
#1 BOTÓN OJO: TOGGLE MOSTRAR/OCULTAR CONTRASEÑA
----------------------------------------------------------------------

PROBLEMA:
  Alternar entre ícono de ojo abierto (\uF06E) y cerrado (\uF070) al
  presionar el botón, y cambiar el modo contraseña del TextArea.

SOLUCIÓN INCORRECTA (error del asistente):
  Buscar un ícono f(x) junto al checkbox de Password mode para vincularlo
  con una expression. ESE ÍCONO NO EXISTE. Password mode es un campo
  estático sin expression binding en EEZ Studio.

SOLUCIÓN CORRECTA:
  1. Crear variable global 'eyeOpen' (boolean, valor inicial: true).
  2. Crear DOS TextAreas superpuestos en la misma posición:
     - 'textarea_password': Password mode = ON, Hidden = !eyeOpen
     - 'textarea_plain':   Password mode = OFF, Hidden = eyeOpen
     Ambos vinculados a la misma variable 'output_keyboard'.
  3. En el Flow del botón ojo (evento CLICKED):
     - Nodo IsTrue evaluando 'eyeOpen'
     - Rama Yes: Label Set Text → \uF070, SetVariable eyeOpen → false
     - Rama No:  Label Set Text → \uF06E, SetVariable eyeOpen → true

APRENDIZAJE:
  No todos los campos de EEZ Studio aceptan expressions. Solo campos de
  tipo texto/número tienen selector Literal/Expression. Los checkboxes
  booleanos (como Password mode) son siempre estáticos.
  Usar una variable booleana es siempre más robusto que SwitchCase sobre texto.

----------------------------------------------------------------------
#2 TECLADO NUMÉRICO: LÓGICA DE ESCRITURA
----------------------------------------------------------------------

VARIABLES NECESARIAS:
  - output_keyboard (string, valor inicial: '')
  - KEYS (array:string, valores de cada botón de la ButtonMatrix)

LÓGICA EN EL EVENTO DE LA BUTTONMATRIX:
  - Evaluate: key = KEYS[Event.getKey(e)]
  - IsTrue: String.length(key) == 1  → filtra DEL y OK
  - IsTrue: String.length(output_keyboard) < 4 → límite de 4 dígitos
  - SetVariable: output_keyboard → output_keyboard + key
  Para DEL:
    String.slice(output_keyboard, 0, String.length(output_keyboard) - 1)

APRENDIZAJE:
  Event.getKey(e) devuelve el índice del botón presionado en la ButtonMatrix.
  El array KEYS mapea cada índice a su carácter correspondiente.

================================================================================
PARTE 2: INDICADOR DE BATERÍA (Header global)
================================================================================

OBJETIVO:
  Mostrar nivel de batería con 6 íconos Font Awesome. Solo uno visible
  a la vez, excepto el estado de "cargando" que muestra dos.

----------------------------------------------------------------------
#3 SISTEMA DE VISIBILIDAD DE ÍCONOS DE BATERÍA (Variable integer)
----------------------------------------------------------------------

PROBLEMA INICIAL:
  Primer enfoque: array:boolean con 6 posiciones. Dos podían quedar en
  true simultáneamente. El estado "cargando" necesita DOS íconos a la vez.

SOLUCIÓN CORRECTA:
  Variable global 'battery_state' (integer, valor inicial: 0).

  Convención de valores:
    0 = vacío
    1 = un cuarto
    2 = medio
    3 = tres cuartos
    4 = lleno
    5 = cargando

  Expression en FLAGS → Hidden de cada label:
    charge_zero:        battery_state != 0 && battery_state != 5
    charge_quarter:     battery_state != 1
    charge_half:        battery_state != 2
    charge_threeQuarter:battery_state != 3
    charge_full:        battery_state != 4
    charge_on (rayo):   battery_state != 5

  Para estado 5 (cargando): se ven charge_zero Y charge_on simultáneamente.

APRENDIZAJE:
  Un integer es más seguro que un array de booleanos para estados mutuamente
  excluyentes. El flag Hidden con expression es reactivo automáticamente.

================================================================================
PARTE 3: PANTALLA DE MENÚ PRINCIPAL (MENU)
================================================================================

----------------------------------------------------------------------
#4 PANELES CON FONDO DE COLOR (Containers)
----------------------------------------------------------------------

PROBLEMA:
  Containers con fondo transparente por defecto. Cambiar Color en STYLE
  no mostraba ningún cambio visible.

SOLUCIÓN:
  En STYLE → Main part → DEFAULT → BACKGROUND:
  1. Activar el checkbox 'Opacity' y poner valor 255.
  2. Activar el checkbox 'Color' y seleccionar el color.
  Sin Opacity en 255, el color de fondo es invisible sin importar el color.

  Para esquinas redondeadas: STYLE → POSITION AND SIZE → Radius → 10 a 20.

APRENDIZAJE:
  En LVGL, background opacity y background color son propiedades independientes.
  Opacity debe estar explícitamente en 255 (LV_OPA_COVER) para ver el color.

----------------------------------------------------------------------
#5 CHECKBOXES R/V/IR VINCULADOS A VARIABLES Y COLOR DE LEDs
----------------------------------------------------------------------

VARIABLES:
  check_R, check_V, check_IR (boolean, valor inicial: false)

CONFIGURACIÓN:
  En STATES → Checked de cada Checkbox: cambiar a Assignable y escribir
  la variable correspondiente (binding bidireccional automático).

  Color de LEDs en widget LED → SPECIFIC → Color → Expression:
    LEDs rojos (4):     check_R  ? 0xff0000 : 0x000000
    LEDs violetas (3):  check_V  ? 0x8800ff : 0x000000
    LEDs IR (3):        check_IR ? 0x8b0000 : 0x000000

  ⚠️ Los colores se expresan como enteros hexadecimales (0x...), NO como
     strings (#...).

ERROR DEL ASISTENTE (#7):
  Se sugirió configurar el color mediante STYLE → CHECKED → Background Color.
  El rojo (#ff0000) aparecía como marrón oscuro.
  CAUSA: el widget Led aplica un factor de brillo mínimo (LV_LED_BRIGHT_MIN
  = 80/255 ≈ 31%) al color en estado DEFAULT, convirtiendo #ff0000 a ~#500000.
  El violeta resiste mejor porque mezcla canales azul y rojo.

APRENDIZAJE:
  El widget Led tiene su propio sistema de brillo interno que oscurece los
  colores configurados via STYLE. La única forma confiable de controlar el
  color es usando SPECIFIC → Color → Expression (lv_led_set_color() directo).

----------------------------------------------------------------------
#6 TIMER: FORMATO MM:SS
----------------------------------------------------------------------

ERROR DEL ASISTENTE (#8):
  Se sugirió IntegerToString() → NO EXISTE en EEZ Flow.
  Luego se sugirió (treatment_time / 60) + ":" + ... → producía decimales
  ('1.33333333:20') porque la división en EEZ Flow es siempre flotante.

SOLUCIÓN CORRECTA (expression en el label de tiempo):
  Math.floor(treatment_time / 60) + ":" + (treatment_time % 60 < 10 ? "0" : "") + (treatment_time % 60)

APRENDIZAJE:
  EEZ Flow NO tiene IntegerToString() ni FloatToString() confiables.
  La conversión a string se logra concatenando con otro string.
  Math.floor() es la forma correcta de truncar a entero.
  El operador % (módulo) funciona correctamente para obtener segundos.

----------------------------------------------------------------------
#7 BOTONES + Y -: PULSACIÓN CONTINUA (LONG_PRESSED_REPEAT)
----------------------------------------------------------------------

PROBLEMA:
  Con evento PRESSED el tiempo subía demasiado rápido.

SOLUCIÓN:
  Dos event handlers por botón:
    CLICKED: suma/resta 5 segundos inmediatamente.
    LONG_PRESSED_REPEAT: suma/resta 5 con Delay de 300ms antes.

  LONG_PRESSED_REPEAT se dispara repetidamente mientras se mantiene presionado.
  Validación en ambos:
    - Restar: IsTrue treatment_time > 0
    - Sumar:  IsTrue treatment_time < 3600

APRENDIZAJE:
  LV_EVENT_LONG_PRESSED_REPEAT es el evento nativo de LVGL para repetición.
  El Delay controla la velocidad: 200ms=rápido, 300-500ms=cómodo.

----------------------------------------------------------------------
#8 CÁLCULO DE DOSIS (fórmulas con 2 decimales)
----------------------------------------------------------------------

ERROR DEL ASISTENTE (#10):
  Se sugirió FloatToString() y String.Format() → no disponibles o con bug
  conocido (issue #643 de EEZ Studio).

SOLUCIÓN:
  Usar variables intermedias enteras multiplicadas por 100:
    dosis_p_c (integer) = Math.round(0.04 * treatment_time * 100)
    dosis_t_c (integer) = Math.round(
      ((check_R ? 4 : 0) * 0.04 +
       (check_V ? 3 : 0) * 0.04 +
       (check_IR ? 3 : 0) * 0.04) * treatment_time * 100)

  Expression label DOSIS PUNTUAL:
    Math.floor(dosis_p_c / 100) + "." + (dosis_p_c % 100 < 10 ? "0" : "") + dosis_p_c % 100

  Expression label DOSIS TOTAL: igual, usando dosis_t_c.

APRENDIZAJE:
  Para mostrar flotantes con decimales en EEZ Flow: multiplicar por 100,
  trabajar con enteros, y formatear manualmente la parte decimal.
  Math.round() evita errores de redondeo de punto flotante.

----------------------------------------------------------------------
#9 SISTEMA PLAY/STOP/RESET CON CONTADOR REGRESIVO
----------------------------------------------------------------------

VARIABLES:
  is_running (boolean, valor inicial: false)
  treatment_time (integer)

CONTROL DE BOTONES DESHABILITADOS (FLAGS → DISABLED → Expression):
  PLAY:   is_running || treatment_time == 0
  STOP:   !is_running
  RESET:  is_running
  + y -:  is_running

USER ACTION 'countdown_tick' (bucle via Label IN/OUT):
  Label IN: tick
    → IsTrue: is_running && treatment_time > 0
      → No:  SetVariable is_running → false → End
      → Yes: Delay 1000ms
              → SetVariable treatment_time → treatment_time - 1
              → IsTrue: treatment_time == 0
                → Yes: SetVariable is_running → false → End
                → No:  Label OUT: tick  (regresa al inicio del bucle)

  PLAY:  SetVariable is_running → true → Call User Action countdown_tick
  STOP:  SetVariable is_running → false (el bucle detecta el cambio y termina)
  RESET: SetVariable treatment_time → 0
         SetVariable check_R/V/IR → false

APRENDIZAJE:
  Label IN / Label OUT es la forma nativa de crear bucles en EEZ Flow.
  Call User Action es asíncrono: no bloquea la UI mientras el countdown corre.
  FLAGS DISABLED con Expression evita comportamientos no esperados sin código C.

================================================================================
PARTE 4: PANTALLA CAMBIO DE CONTRASEÑA (CAMBIO_PASSWORD)
================================================================================

----------------------------------------------------------------------
#10 TECLADO CONTEXTUAL: APARECE/DESAPARECE CON EL FOCO
----------------------------------------------------------------------

VARIABLES:
  keyboard_visible (boolean, valor inicial: false)
  active_field (integer, valor inicial: 0)

LÓGICA:
  ButtonMatrix: FLAGS → Hidden → Expression: !keyboard_visible

  Cada TextArea tiene dos eventos:
    FOCUSED:    SetVariable active_field → N (1, 2 o 3)
                SetVariable keyboard_visible → true
    DEFOCUSED:  SetVariable keyboard_visible → false

  La ButtonMatrix escribe en la variable del campo activo via SwitchCase:
    caso 1: pass_current  → pass_current + key
    caso 2: pass_new      → pass_new + key
    caso 3: pass_confirm  → pass_confirm + key

APRENDIZAJE:
  FOCUSED y DEFOCUSED son los eventos nativos de LVGL para interacción
  con campos. Hidden con Expression hace el show/hide completamente automático.

----------------------------------------------------------------------
#11 VARIABLE stored_password SEPARADA DEL CAMPO DE ENTRADA (Error de diseño)
----------------------------------------------------------------------

PROBLEMA (error de usuario #13):
  pass_current tenía valor inicial '1234' porque también se usaba para
  validación del login. Al entrar a la pantalla, el TextArea mostraba '1234',
  revelando la contraseña al usuario.

DISEÑO CORRECTO:
  pass_current (string, valor ''):  lo que el usuario escribe (siempre inicia vacío)
  stored_password (string):         la contraseña real guardada (NUNCA vinculada a widget visible)

  En el login: comparar output_keyboard == stored_password
  Al guardar nueva contraseña (flujo de validación):
    1. IsTrue pass_current == stored_password   (si no: notificación error)
    2. IsTrue pass_new == pass_confirm           (si no: notificación error)
    3. IsTrue String.length(pass_new) == 4      (si no: aviso '4 dígitos')
    4. SetVariable stored_password → pass_new
    5. Limpiar: pass_current, pass_new, pass_confirm → ''

APRENDIZAJE:
  Una variable no debe tener dos responsabilidades simultáneamente.
  La fuente de verdad (stored_password) nunca debe vincularse a un widget visible.
  Los campos de entrada siempre deben iniciar vacíos ('').

----------------------------------------------------------------------
#12 PERSISTENCIA DE VARIABLES ENTRE SESIONES
----------------------------------------------------------------------

COMPORTAMIENTO OBSERVADO:
  Al salir de debug y volver a entrar, stored_password siempre regresaba
  a '1234' aunque se hubiera cambiado. ¿Bug o comportamiento esperado?

RESPUESTA:
  Es comportamiento NORMAL y esperado. Las variables de EEZ Flow viven en RAM.
  Al reiniciar debug o encender el hardware, la RAM se inicializa y las
  variables toman sus valores por defecto definidos en el proyecto.

PARA PERSISTENCIA REAL EN ESP32:
  Usar NVS (Non-Volatile Storage) implementado en código C nativo,
  llamado desde EEZ Flow via User Actions.
  EEZ Flow no tiene mecanismo automático de persistencia.

================================================================================
PARTE 5: WIDGETS, ESTILOS Y SOLUCIONES VISUALES
================================================================================

----------------------------------------------------------------------
#13 TAMAÑO DEL CHECKBOX Y TEXTO ENCIMA DEL INDICADOR
----------------------------------------------------------------------

LIMITACIÓN:
  EEZ Studio no permite redimensionar el cuadro indicador del Checkbox
  directamente. LVGL no soporta texto del Checkbox encima del indicador.

SOLUCIÓN:
  Para tamaño: asignar un font de mayor tamaño en STYLE. El cuadro crece
  con la altura del font.

  Para texto encima: construir el Checkbox manualmente dentro de un Container:
    - Un Label con la letra (R, V, IR) en la parte superior del Container.
    - Un Checkbox sin texto (campo vacío) debajo del Label.
    Los eventos del Checkbox funcionan normalmente, solo cambia el layout.

----------------------------------------------------------------------
#14 SISTEMA DE NOTIFICACIONES CON AUTO-DESAPARICIÓN Y COLORES POR TIPO
----------------------------------------------------------------------

PROBLEMA:
  MessageBox de EEZ Studio está marcado como 'work in progress' con
  funcionalidad muy limitada.

SOLUCIÓN:
  Variables: show_notification (boolean), notification_text (string).
  Container de notificación con Text Label vinculado a notification_text.
  FLAGS → Hidden → Expression: !show_notification

  Para color según tipo (STYLE → DEFAULT = rojo, STYLE → CHECKED = verde):
    Error:  LVGL Widget-States Remove State CHECKED (muestra rojo)
    Éxito:  LVGL Widget-States Add State CHECKED (muestra verde)

  Flujo completo:
    SetVariable notification_text → 'mensaje'
    SetVariable show_notification → true
    Delay 1000-2000ms
    SetVariable show_notification → false

  Para centrar el texto: Width del Label = 100%, STYLE → TEXT → Text align = CENTER.

APRENDIZAJE:
  No se puede cambiar background color via Expression directamente (issue #450).
  La alternativa es usar el sistema de States (CHECKED/DEFAULT) con estilos
  por estado. LVGL Widget-States Add/Remove State es la acción correcta desde Flow.

----------------------------------------------------------------------
#15 IMAGEN (ÍCONO) DENTRO DE UN BUTTON
----------------------------------------------------------------------

PROBLEMA:
  LVGL 9.x no incluye ciertos íconos en sus fuentes de símbolos.
  Se necesitaba usar una imagen PNG como ícono dentro de un botón.

SOLUCIÓN:
  1. Preparar PNG con fondo transparente (canal alpha).
  2. EEZ Studio: pestaña Bitmaps → + → importar PNG → asignar nombre.
  3. Crear el Button con campo de texto vacío en SPECIFIC.
  4. En Widgets Structure: arrastrar un widget Image como hijo del Button.
  5. En SPECIFIC del Image widget: campo Bitmap → seleccionar el bitmap.
  6. Usar íconos de alineación de EEZ Studio para centrar la imagen.

APRENDIZAJE:
  Los widgets LVGL pueden tener hijos. Image hijo de Button es el patrón
  correcto para botones con íconos de imagen.
  ⚠️ El PNG debe ser PNG real. Un SVG/WebP renombrado con extensión .png dará
  error: 'PNG file has invalid signature'. Solución: abrir en GIMP/Paint y
  exportar/guardar explícitamente como PNG.

================================================================================
PARTE 6: COMPILACIÓN Y HERRAMIENTAS EXTERNAS
================================================================================

----------------------------------------------------------------------
#16 ERROR: pypng, lz4 y pngquant faltantes al compilar imágenes
----------------------------------------------------------------------

ERROR:
  'An error occurred while building images for LVGL 9.x'

CAUSA:
  EEZ Studio usa LVGLImage.py para convertir PNG a arrays C.
  Este script requiere Python 3, pypng, lz4 y pngquant.

SOLUCIÓN:
  1. python -m pip install pypng==0.20220715.0
  2. python -m pip install lz4
  3. Descargar pngquant desde https://pngquant.org
  4. Agregar la carpeta de pngquant.exe al PATH de Windows.
  5. CRÍTICO: Cerrar y volver a abrir EEZ Studio después de modificar el PATH.

APRENDIZAJE:
  Las variables de entorno solo se aplican a procesos iniciados después del cambio.
  EEZ Studio no recarga el PATH en caliente.
  Verificar con una terminal NUEVA: pngquant --version → debe responder '2.17.0'

----------------------------------------------------------------------
#17 WARNINGS EN EEZ FLOW: nullstring y booleanstring
----------------------------------------------------------------------

WARNING:
  'Connection line incompatible data types: null → string'
  'Connection line incompatible data types: boolean → string'

CAUSA:
  Confundir cables de secuencia con cables de datos en EEZ Flow:
  - La salida de ejecución de un nodo LVGL (no emite valor) se conectaba
    a la entrada de datos 'key' de un SetVariable.
  - La salida 'Yes' de IsTrue (boolean) se conectaba a entrada de datos.

SOLUCIÓN:
  Los valores de 'key' y 'value' en SetVariable se escriben directamente
  como texto en los campos del nodo, NO se conectan con cables desde otros nodos.
  Los cables entre nodos = señal de secuencia (ejecución).
  Los campos de texto en los nodos = datos.

APRENDIZAJE:
  En EEZ Flow, datos y secuencia de ejecución son conceptos separados.
  ❌ No mezclar los dos tipos de conexión.

================================================================================
PARTE 7: REFERENCIA RÁPIDA DE EXPRESIONES EEZ FLOW (VALIDADAS)
================================================================================

  Propósito                    Expresión
  ─────────────────────────────────────────────────────────────────────────────
  Tiempo MM:SS                 Math.floor(treatment_time / 60) + ":" +
                               (treatment_time % 60 < 10 ? "0" : "") +
                               (treatment_time % 60)

  Dosis puntual (2 dec.)       Math.floor(dosis_p_c / 100) + "." +
                               (dosis_p_c % 100 < 10 ? "0" : "") +
                               dosis_p_c % 100

  Dosis total (2 dec.)         Math.floor(dosis_t_c / 100) + "." +
                               (dosis_t_c % 100 < 10 ? "0" : "") +
                               dosis_t_c % 100

  LED rojo encendido           check_R  ? 0xff0000 : 0x000000
  LED violeta encendido        check_V  ? 0x8800ff : 0x000000
  LED IR encendido             check_IR ? 0x8b0000 : 0x000000

  Ocultar batería vacía        battery_state != 0 && battery_state != 5
  Ocultar icono carga (rayo)   battery_state != 5
  Deshabilitar PLAY            is_running || treatment_time == 0
  Deshabilitar STOP            !is_running
  Ocultar teclado              !keyboard_visible
  TextArea plain visible       eyeOpen
  TextArea password visible    !eyeOpen

================================================================================
PARTE 8: INVENTARIO COMPLETO DE VARIABLES GLOBALES EEZ STUDIO
================================================================================

  Variable            Tipo       Valor inicial  Propósito
  ──────────────────────────────────────────────────────────────────────────────
  output_keyboard     string     ''             Texto del teclado numérico
  eyeOpen             boolean    true           Estado del botón ojo (login)
  stored_password     string     '1234'         Contraseña real almacenada
  pass_current        string     ''             Campo entrada contraseña actual
  pass_new            string     ''             Campo entrada contraseña nueva
  pass_confirm        string     ''             Campo confirmación contraseña
  battery_state       integer    0              Nivel batería (0-5)
  check_R             boolean    false          LED rojo activo
  check_V             boolean    false          LED violeta activo
  check_IR            boolean    false          LED infrarrojo activo
  treatment_time      integer    0              Tiempo tratamiento (segundos)
  is_running          boolean    false          Estado del contador
  dosis_p_c           integer    0              Dosis puntual × 100
  dosis_t_c           integer    0              Dosis total × 100
  keyboard_visible    boolean    false          Visibilidad del teclado
  active_field        integer    0              Campo activo (1=actual, 2=nueva, 3=confirm)
  show_notification   boolean    false          Visibilidad notificación
  notification_text   string     ''             Texto de la notificación
  KEYS                array:str  [...]          Mapa índice→carácter del teclado
  loading_value       integer    0              Progreso de la animación splash

================================================================================
FIN DE LA BITÁCORA 5
================================================================================

================================================================================
================================================================================
        BITÁCORA 6: ERROR CRÍTICO — MESSAGEBOX DE EEZ STUDIO EN LVGL 9
================================================================================
================================================================================

Fecha: 8 de Marzo de 2026
Contexto: Pantalla login freezeada tras contraseña incorrecta

================================================================================
DESCRIPCIÓN DEL PROBLEMA
================================================================================

SÍNTOMA OBSERVADO:
  Al ingresar una contraseña incorrecta en login_SCREEN, la pantalla se
  "congela" completamente. Ningún botón responde al touch. El comportamiento
  es idéntico a un freeze total del sistema.

CAUSA REAL:
  El widget MessageBox de EEZ Studio está marcado internamente como
  "work in progress". Su implementación generada para LVGL 9 es incompleta.

MECANISMO DEL BUG:
  1. EEZ Studio genera código que crea una superposición modal (un objeto
     lv_obj_t posicionado encima de toda la UI).
  2. Este modal captura el 100% de los eventos de touch mientras está activo.
  3. El botón OK dentro del MessageBox DEBERÍA cerrar ese objeto y devolver
     el control a la pantalla.
  4. Pero el código generado para LVGL 9 NO implementa correctamente ese cierre.
  5. Resultado: el modal permanece activo indefinidamente.

POR QUÉ PARECE UN FREEZE PERO NO LO ES:
  - LVGL sigue corriendo normalmente (lv_timer_handler() ejecutándose).
  - La pantalla sigue renderizando.
  - Los objetos de la UI siguen existiendo en memoria.
  - PERO el modal invisible intercepta todos los eventos de touch antes de
    que lleguen a cualquier botón visible.
  - Para el usuario, el efecto es indistinguible de un freeze total.

================================================================================
SOLUCIÓN: REEMPLAZAR MESSAGEBOX CON NOTIFICACIÓN PROPIA
================================================================================

LA SOLUCIÓN INCORRECTA (descartada):
  Intentar reparar el código del MessageBox generado por EEZ.
  → El problema es estructural: EEZ no implementa el cierre del modal en LVGL 9.
  → Repararlo manualmente se perdería en la siguiente exportación de EEZ Studio.

LA SOLUCIÓN CORRECTA:
  No usar MessageBox. Implementar el sistema de notificaciones propio
  documentado en la Bitácora 5 (sección #14), que ya está completamente
  funcional, no crea superposiciones modales y se controla con variables
  EEZ Flow normales.

  SISTEMA DE NOTIFICACIÓN NO-MODAL:
    Variables: show_notification (boolean), notification_text (string)
    Container flotante con Hidden → Expression: !show_notification
    Para error:  LVGL Widget-States Remove State CHECKED (estilo rojo)
    Para éxito:  LVGL Widget-States Add State CHECKED  (estilo verde)

  Flujo completo para "contraseña incorrecta":
    1. SetVariable notification_text → 'Contraseña incorrecta'
    2. LVGL Widget-States: Remove State CHECKED (rojo)
    3. SetVariable show_notification → true
    4. Delay 1500ms
    5. SetVariable show_notification → false
    6. SetVariable pass_current → ''  (limpiar campo)

VENTAJAS SOBRE MESSAGEBOX:
  ✓ No crea objetos modales, la UI siempre responde al touch.
  ✓ Auto-desaparece (no requiere que el usuario haga clic en OK).
  ✓ Completamente controlado desde EEZ Flow sin código C manual.
  ✓ Sobrevive a exportaciones de EEZ Studio sin necesitar reparaciones.
  ✓ Color diferenciado por tipo (rojo = error, verde = éxito).

================================================================================
REGLA: NUNCA USAR MESSAGEBOX DE EEZ STUDIO
================================================================================

  El widget MessageBox de EEZ Studio NO funciona correctamente con LVGL 9.
  Está marcado 'work in progress' en el repositorio oficial de EEZ.

  En cualquier pantalla que requiera mostrar información al usuario:
  ❌ NO usar: Widgets → MessageBox
  ✓ USAR:     Sistema de notificación propio (Container + Label + show/hide)

================================================================================
FIN DE LA BITÁCORA 6
================================================================================

================================================================================
================================================================================
        BITÁCORA 4: ERRORES DE COMPILACIÓN CON EEZ STUDIO + LVGL 9
================================================================================
================================================================================

Fecha: 24 de Febrero de 2026
Contexto: Primera compilación completa del proyecto con LVGL 9.4.0
          usando los archivos generados por EEZ Studio (eez-flow.cpp, ui.c, etc.)

================================================================================
PROBLEMA 1: FUENTES MONTSERRAT NO DECLARADAS
================================================================================

ERROR:
  screens.c:483: error: 'lv_font_montserrat_34' undeclared
  screens.c:508: error: 'lv_font_montserrat_22' undeclared
  screens.c:800: error: 'lv_font_montserrat_18' undeclared

CAUSA:
  Los archivos generados por EEZ Studio usan fuentes que no estaban habilitadas
  en lv_conf.h. LVGL solo compila las fuentes que están marcadas con 1.

SOLUCIÓN:
  Habilitar las tres fuentes faltantes en lv_conf.h:
  (C:/Users/DANNY/Documents/Arduino/libraries/lv_conf.h)

    #define LV_FONT_MONTSERRAT_18 1   // Para etiquetas medianas
    #define LV_FONT_MONTSERRAT_22 1   // Para valores secundarios
    #define LV_FONT_MONTSERRAT_34 1   // Para display numérico grande

NOTA PARA EL FUTURO:
  Cada vez que EEZ Studio use una fuente nueva, hay que habilitarla en
  lv_conf.h. El compilador avisará con "undeclared identifier" si falta.

================================================================================
PROBLEMA 2: CONVERSIÓN INVÁLIDA int → lv_part_t EN eez-flow.cpp
================================================================================

ERROR:
  eez-flow.cpp:3837: error: invalid conversion from 'int' to 'lv_part_t'
  eez-flow.cpp:4404: error: invalid conversion from 'int' to 'lv_part_t'

CAUSA:
  EEZ Studio genera eez-flow.cpp para LVGL 8, donde LV_PART_MAIN era un simple
  entero. En LVGL 9, lv_part_t es un enum tipado y el compilador C++ rechaza
  la conversión implícita desde int o desde otro enum sin cast explícito.

  Líneas afectadas:
    // Línea ~3837
    lv_obj_get_style_opa((lv_obj_t *)a->user_data, 0)
    // Línea ~4404
    lv_obj_get_style_opa(obj, 0)

SOLUCIÓN:
  Añadir cast explícito (lv_part_t) en ambas llamadas:

    // Línea ~3837
    lv_obj_get_style_opa((lv_obj_t *)a->user_data, (lv_part_t)LV_PART_MAIN)
    // Línea ~4404
    lv_obj_get_style_opa(obj, (lv_part_t)LV_PART_MAIN)

PROCEDIMIENTO RÁPIDO TRAS REGENERAR DESDE EEZ STUDIO:
  1. Abrir eez-flow.cpp en VS Code.
  2. Ctrl+H (buscar y reemplazar).
  3. Buscar:   lv_obj_get_style_opa((lv_obj_t *)a->user_data, 0)
     Cambiar:  lv_obj_get_style_opa((lv_obj_t *)a->user_data, (lv_part_t)LV_PART_MAIN)
  4. Buscar:   lv_obj_get_style_opa(obj, 0)
     Cambiar:  lv_obj_get_style_opa(obj, (lv_part_t)LV_PART_MAIN)
  5. Guardar. Listo.
  Tiempo estimado: 10 segundos.

ADVERTENCIA:
  Este archivo se regenera cada vez que exportas desde EEZ Studio. Recuerda
  aplicar estos dos cambios después de cada exportación antes de compilar.

================================================================================
PROBLEMA 3: CACHÉ DE COMPILACIÓN OBSOLETO (build/)
================================================================================

ERROR:
  ld.exe: cannot find build\libraries\lvgl\stdlib\builtin\objs.a:
  No such file or directory

CAUSA:
  La carpeta build/ tenía objetos precompilados (.a) de LVGL 8. Al actualizar
  a LVGL 9 la estructura interna cambió, pero el linker seguía buscando los
  archivos viejos del caché.

SOLUCIÓN:
  Eliminar todo el contenido de la carpeta build/ para forzar compilación limpia:

    rm -rf "C:/Users/DANNY/Desktop/Laser Inteligente/build/"*

  o desde el Explorador de Windows: seleccionar todo dentro de build/ y borrar.

NOTA:
  La primera compilación tras limpiar el caché tarda más (varios minutos).
  Las siguientes serán rápidas porque construyen el nuevo caché con LVGL 9.
  Solo es necesario limpiar el caché al cambiar la versión de LVGL.

================================================================================
PROBLEMA 4: VARIABLE NATIVA EEZ SIN IMPLEMENTAR (output_keyboard)
================================================================================

ERROR:
  ld.exe: undefined reference to 'get_var_output_keyboard'
  ld.exe: undefined reference to 'set_var_output_keyboard'

CAUSA:
  EEZ Studio siempre genera en ui.c una tabla de variables nativas que incluye
  get_var_output_keyboard y set_var_output_keyboard aunque el teclado virtual
  no se use activamente en el proyecto. ui.c referencia los punteros de esas
  funciones, por lo que el linker las exige aunque el código nunca las llame
  directamente.

  En vars.h solo estaban DECLARADAS (extern), pero en ningún .c IMPLEMENTADAS.

SOLUCIÓN:
  Implementarlas en screens.c con un buffer estático mínimo:

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

  Si en el futuro se agrega una nueva variable nativa en EEZ Studio, aparecerá
  el mismo error "undefined reference" con su nombre. La solución siempre es
  la misma: implementarla con un stub o con la lógica real.

REGLA GENERAL:
  Toda variable marcada como "Native" en EEZ Studio debe tener implementación
  en algún archivo .c del proyecto, independientemente de si se usa o no.

================================================================================
RESUMEN: CHECKLIST TRAS REGENERAR DESDE EEZ STUDIO
================================================================================

Después de exportar el proyecto desde EEZ Studio y antes de compilar:

  ☐ 1. Abrir eez-flow.cpp y aplicar los 2 reemplazos de lv_part_t
        (ver Problema 2 arriba, ~10 segundos con Ctrl+H)

  ☐ 2. Verificar en lv_conf.h que todas las fuentes usadas en screens.c
        estén habilitadas con valor 1 (ver Problema 1 arriba)

  ☐ 3. Si se agregaron nuevas variables nativas en EEZ, implementarlas
        en screens.c (ver Problema 4 arriba)

  ☐ 4. Si se cambió la versión de LVGL, limpiar la carpeta build/
        antes de compilar (ver Problema 3 arriba)

================================================================================
FIN DE LA BITÁCORA 4
================================================================================