set(src_dirs
    i2c_devices
    wifi_manager
    key
)

set(include_dirs
    i2c_devices
    wifi_manager
    key
)

set(required_components
    driver
    esp_timer
    esp_driver_i2c
    esp_driver_spi
    esp_event
    esp_wifi
    esp_http_server
    spiffs
    nvs_flash
    json
)

idf_component_register(
    SRC_DIRS ${src_dirs}
    INCLUDE_DIRS ${include_dirs}
    REQUIRES ${required_components}
)

component_compile_options(
    -ffast-math -O3 -Wno-error=format=-Wno-format
)
