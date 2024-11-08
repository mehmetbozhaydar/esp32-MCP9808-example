# Example for MCP9808 driver

## What it does

The example configures a `mcp9808` device. It reads temperature from the
device and shows it in a loop.

The default I2C address is `CONFIG_EXAMPLE_I2C_ADDR`. The default is `0x18`.

## Wiring

Connect `SCL` and `SDA` pins to the following pins with appropriate pull-up
resistors.

Change the "EXTRA_COMPONENT_DIRS" file extension in CMakeList and Makefile to the file path where you saved the mcp9808 library.

| Name | Description | Defaults |
|------|-------------|----------|
| `CONFIG_EXAMPLE_I2C_MASTER_SCL` | GPIO number for `SCL` | "5" for `esp8266`, "6" for `esp32c3`, "4" for `esp32h2` , "19" for `esp32`, `esp32s2`, and `esp32s3` |
| `CONFIG_EXAMPLE_I2C_MASTER_SDA` | GPIO number for `SDA` | "4" for `esp8266`, "5" for `esp32c3`, "3" for `esp32h2` , "18" for `esp32`, `esp32s2`, and `esp32s3` |
