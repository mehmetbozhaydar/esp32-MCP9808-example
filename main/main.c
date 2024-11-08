#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_system.h>
#include <string.h>
#include <esp_err.h>
#include <mcp9808.h>

#ifndef APP_CPU_NUM
#define APP_CPU_NUM PRO_CPU_NUM
#endif

// Görev fonksiyonu
void task(void *pvParameters)
{
    float temperature; // Sıcaklık değeri
    esp_err_t res; // Hata kodu

    i2c_dev_t dev; // I2C cihaz tanımı
    memset(&dev, 0, sizeof(i2c_dev_t)); // Cihaz yapısını sıfırla

    // MCP9808 sensörünü başlat
    ESP_ERROR_CHECK(mcp9808_init_desc(&dev, CONFIG_EXAMPLE_I2C_ADDR, 0, CONFIG_EXAMPLE_I2C_MASTER_SDA, CONFIG_EXAMPLE_I2C_MASTER_SCL));
    /*(&dev, CONFIG_EXAMPLE_I2C_ADDR, 0, CONFIG_EXAMPLE_I2C_MASTER_SDA, CONFIG_EXAMPLE_I2C_MASTER_SCL)
    Kconfig dosyası içinde pinler tanımlı */ 

    // Sensörü başlat
    ESP_ERROR_CHECK(mcp9808_init(&dev));

    while (1)
    {
        // Sıcaklık değerini oku ve işle
        if ((res = mcp9808_get_temperature(&dev, &temperature, NULL, NULL, NULL)) == ESP_OK)
            printf("Sıcaklık: %.2f °C\n", temperature); // Sıcaklık değerini yazdır
        else
            printf("Sonuç alınamadı: %d (%s)", res, esp_err_to_name(res)); // Hata mesajını yazdır

        vTaskDelay(pdMS_TO_TICKS(1000)); // 1 saniye bekle
    }
}

// Ana uygulama fonksiyonu
void app_main()
{
    ESP_ERROR_CHECK(i2cdev_init()); // I2C cihazını başlat

    // Yeni bir görev oluştur ve belirtilen çekirdeğe bağla
    xTaskCreatePinnedToCore(task, "mcp9808_test", configMINIMAL_STACK_SIZE * 8, NULL, 5, NULL, APP_CPU_NUM);
}

