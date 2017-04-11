# Restroom Revolution
Как сделать счастливыми всех и каждого в офисе? Правильно - приобщить туалет к IoT!

## Внимание!
Проект находится на стадии Pre-alpha и служит для первичного ознакомления с функционалом.

## Прошивка ESP8266 Witty Cloud
- Скачиваем прошивку http://www.espruino.com/Download и переходим в дерикторию с прошивкой для ESP8266
- Загружаем прошивку на устройство:
    - sudo esptool.py --port /dev/tty.wchusbserial1410 --baud 115200 \
    write_flash --flash_freq 40m --flash_mode qio --flash_size 4m \
    0x0000 "boot_v1.6.bin" 0x1000 espruino_esp8266_user1.bin \
    0x7C000 esp_init_data_default.bin 0x7E000 blank.bin
- Подлючаемся через screen:
    - Linux: screen /dev/ttyUSB0 115200
    - macOS: screen /dev/tty.wchusbserial1410 115200
- И при помощи JavaScript настраиваем Wi-Fi соединение на устройстве:
    - var wifi = require("Wifi");
    - wifi.connect("WIFI_NAME", {password: "WIFI_PASSWORD"}, function(err){if(err)console.log(err);else console.log("connected!");});
    - wifi.getIP();
    - wifi.save();
- Выходим из screen:
    - Ctrl + A + D
