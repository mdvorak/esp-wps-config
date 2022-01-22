# wps_config

[![build](https://github.com/mdvorak/esp-wps-config/actions/workflows/build.yml/badge.svg)](https://github.com/mdvorak/esp-wps-config/actions/workflows/build.yml)

Wrapper around WPS Wi-Fi configuration.

## Usage

To reference this library by your project, add it as git submodule, using command

```shell
git submodule add https://github.com/mdvorak/esp-wps-config.git components/wps_config
```

and include either of the header files

```c
#include <wps_config.h>
```

For full example, see [wps_config_example_main.c](./example/main/wps_config_example_main.c).

## Development

Prepare [ESP-IDF development environment](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/index.html#get-started-get-prerequisites)
.

Configure example application with

```
cd example/
idf.py menuconfig
```

Flash it via (in the example dir)

```
idf.py build flash monitor
```

As an alternative, you can use [PlatformIO](https://docs.platformio.org/en/latest/core/installation.html) to build and
flash the example project.
