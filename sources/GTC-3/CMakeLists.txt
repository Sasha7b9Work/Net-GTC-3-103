# (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by

project (GTC-3)

#set(CMAKE_UNITY_BUILD OFF)

message("------------------------------------------------------------------------ ${PROJECT_NAME}")

include_directories(../common/_VS_KEIL/CMSIS/
                    ../common/_VS_KEIL/std_includes/
                    ../common/STM32Cube_F1/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc/
                    ../common/STM32Cube_F1/Middlewares/ST/STM32_USB_Device_Library/Core/Inc/
                    ../common/STM32Cube_F1/Drivers/STM32F1xx_HAL_Driver/Inc/
                    ../common/STM32Cube_F1/Drivers/CMSIS/Device/ST/STM32F1xx/Include/
                    src/Hardware/HAL/
                    src/Hardware/CDC/
                    src/
                    )

add_definitions(-DSTM32F103xB)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -MP -Wall")

add_compile_options(/wd4201)
add_compile_options(/wd4310)
add_compile_options(/wd4514)    # 'function' : unreferenced inline function has been removed
add_compile_options(/wd4623)    # default constructor was implicitly defined as deleted
add_compile_options(/wd4626)    # assignment operator was implicitly defined as deleted
add_compile_options(/wd4820)    # 'xxx': '4' bytes padding added after data member 'yyy'
add_compile_options(/wd5027)    # move assignment operator was implicitly defined as deleted
add_compile_options(/wd5045)    # Compiler will insert Spectre mitigation for memory load if /Qspectre switch specified
add_compile_options(/wd5220)    # a non-static data member with a volatile qualified type no longer implies
add_compile_options(/wd5264)
add_compile_options(/wd26812)   # The enum type %type% is unscoped. Prefer 'enum class' over 'enum' (Enum.3)


file(GLOB STM32F1               ../common/STM32Cube_F1/Drivers/STM32F1xx_HAL_Driver/Src/*.c
                                ../common/STM32Cube_F1/Drivers/STM32F1xx_HAL_Driver/Inc/*.h)
file(GLOB SRC                   src/*.*)
file(GLOB DISPLAY               src/Display/*.*)
file(GLOB DISPLAY_FONT          src/Display/Font/*.*)
file(GLOB HARDWARE              src/Hardware/*.*)
file(GLOB HARDWARE_CMSIS        src/Hardware/CMSIS/*.*)
file(GLOB HARDWARE_CDC          src/Hardware/CDC/*.*)
file(GLOB HARDWARE_HAL          src/Hardware/HAL/*.*)
file(GLOB MENU                  src/Menu/*.*)
file(GLOB MENU_PAGES            src/Menu/Pages/*.*)
file(GLOB MODULES_BME280        src/Modules/BME280/*.*)
file(GLOB MODULES_HC12          src/Modules/HC12/*.*)
file(GLOB MODULES_ST7735        src/Modules/ST7735/*.*)
file(GLOB MODULES_W25Q80DV      src/Modules/W25Q80DV/*.*)
file(GLOB SETTINGS              src/Settings/*.*)
file(GLOB STORAGE               src/Storage/*.*)
file(GLOB UTILS                 src/Utils/*.*)
file(GLOB UTILS_TEXT            src/Utils/Text/*.*)

source_group(STM32F1            FILES ${STM32F1})
source_group(src                FILES ${SRC})
source_group(Display            FILES ${DISPLAY})
source_group(Display/Font       FILES ${DISPLAY_FONT})
source_group(Hardware           FILES ${HARDWARE})
source_group(Hardware/CMSIS     FILES ${HARDWARE_CMSIS})
source_group(Hardware/CDC       FILES ${HARDWARE_CDC})
source_group(Hardware/HAL       FILES ${HARDWARE_HAL})
source_group(Menu               FILES ${MENU})
source_group(Menu/Pages         FILES ${MENU_PAGES})
source_group(Modules/BME280     FILES ${MODULES_BME280})
source_group(Modules/HC12       FILES ${MODULES_HC12})
source_group(Modules/ST7735     FILES ${MODULES_ST7735})
source_group(Modules/W25Q80DV   FILES ${MODULES_W25Q80DV})
source_group(Settings           FILES ${SETTINGS})
source_group(Storage            FILES ${STORAGE})
source_group(Utils              FILES ${UTILS})
source_group(Utils/Text         FILES ${UTILS_TEXT})

set_source_files_properties(${STM32F1} ${HARDWARE_CMSIS}
                            src/Hardware/CDC/usbd_desc.c
                            src/Hardware/CDC/usb_device.c
                            src/Hardware/CDC/usbd_conf.c
                            PROPERTIES HEADER_FILE_ONLY TRUE)

add_library(${PROJECT_NAME}
            ${STM32F1}
            ${SRC}
            ${DISPLAY}
            ${DISPLAY_FONT}
            ${HARDWARE}
            ${HARDWARE_CMSIS}
            ${HARDWARE_CDC}
            ${HARDWARE_HAL}
            ${MENU}
            ${MENU_PAGES}
            ${MODULES_BME280}
            ${MODULES_HC12}
            ${MODULES_ST7735}
            ${MODULES_W25Q80DV}
            ${SETTINGS}
            ${STORAGE}
            ${UTILS}
            ${UTILS_TEXT}
)
