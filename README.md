# HandBeam 10D — Interfaz médica embebida

Firmware e interfaz de un dispositivo médico portátil de **terapia láser de baja intensidad (LLLT)**, sobre **ESP32** (placa Sunton CYD 3.2" táctil) con UI en **LVGL** y runtime EEZ Flow.

## Características
- 10 diodos láser en 3 ramas: rojo ~660 nm, verde ~532 nm, infrarrojo ~808 nm
- Control por DAC MCP4728, realimentación de corriente (INA199) y MOSFETs IRLR8259
- Interfaz táctil (5 pantallas) + gestión de energía con deep-sleep
- Dosimetría calibrada para uso clínico; app móvil por WiFi

## Stack
`ESP32` · `C/C++` · `LVGL` · `KiCad` · `EEZ Flow`

---
🌐 Portafolio: https://fragol-01.github.io
