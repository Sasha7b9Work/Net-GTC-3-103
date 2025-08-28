# (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by

project (GTC-3)

#set(CMAKE_UNITY_BUILD OFF)

set(CMAKE_UNITY_BUILD_BATCH_SIZE 16)


include_directories(.
                    ../../GTC-3/src
                    ../../GTC-3/src/Hardware/CDC
                    ../../GTC-3/src/Hardware/HAL
                    ../../VS/ThirdParty/wxWidgets/include
                    ../../generated/ThirdParty/lib/vc_dll/mswud
                    ../../common/_VS_KEIL/CMSIS
                    ../../common/_VS_LIBS/STM32F1
                    ../../common/STM32Cube_F1/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc
                    ../../common/STM32Cube_F1/Middlewares/ST/STM32_USB_Device_Library/Core/Inc
                    ../../common/STM32Cube_F1/Drivers/CMSIS/Device/ST/STM32F1xx/Include
                    ../../common/STM32Cube_F1/Drivers/STM32F1xx_HAL_Driver/Inc)

link_directories(../../generated/ThirdParty/lib/vc_dll)

add_definitions(-DSTM32F103xB -DWXUSINGDLL -DGUI -DDEVICE)

if(WIN32)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -MP -Wall")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")

    add_compile_options(/wd4100)    # 'xxx' : unreferenced formal parameter
    add_compile_options(/wd4310)
    add_compile_options(/wd4365)    # 'action' : conversion from 'type_1' to 'type_2', signed/unsigned mismatch
    add_compile_options(/wd4514)    # 'function' : unreferenced inline function has been removed
    add_compile_options(/wd4623)    # 'derived class' : default constructor was implicitly defined as deleted
    add_compile_options(/wd4625)    # 'derived class' : copy constructor was implicitly defined as deleted because
                                    # a base class copy constructor is inaccessible or deleted
    add_compile_options(/wd4626)    # 'derived class' : assignment operator was implicitly defined as deleted because
                                    # a base class assignment operator is inaccessible or deleted
    add_compile_options(/wd4774)    # 'string' : format string expected in argument number is not a string literal
    add_compile_options(/wd4820)    # 'xxx' bytes padding added after construct 'member_name'
    add_compile_options(/wd4996)    # deprecated
    add_compile_options(/wd5026)    # 'type': move constructor was implicitly defined as deleted
    add_compile_options(/wd5027)    # "type": оператор присваивания перемещения неявно определен как удаленный
    add_compile_options(/wd5039)    # 'xxx': pointer or reference to potentially throwing function passed to extern C
                                    # function under -EHc.
    add_compile_options(/wd5045)    # Compiler will insert Spectre mitigation for memory load if /Qspectre switch specified
    add_compile_options(/wd5220)    # 'xxx': a non-static data member with a volatile qualified type no longer implies that
                                    # compiler generated copy/move constructors and copy/move assignment operators are not trivial
                                    # add_compile_options(/wd26812)
    add_compile_options(/wd5267)
endif()

file(GLOB LIBS_STM32F1              ../../common/_VS_LIBS/STM32f1/*.*)
file(GLOB LIBS_STM32F1_INC          ../../common/STM32Cube_F1/Drivers/STM32F1xx_HAL_Driver/Inc/*.*)
file(GLOB LIBS_USBD                 ../../common/_VS_LIBS/USBD/*.*)
file(GLOB SRC                       *.h *.cpp
                                    ../../GTC-3/src/*.*)
file(GLOB DISPLAY                   ../../GTC-3/src/Display/*.*)
file(GLOB DISPLAY_FONT              ../../GTC-3/src/Display/Font/*.*)
file(GLOB HARDWARE                  ../../GTC-3/src/Hardware/*.*)
file(GLOB HARDWARE_CDC              ../../GTC-3/src/Hardware/CDC/*.*
                                                    Hardware/CDC/*.*)
file(GLOB HARDWARE_HAL              ../../GTC-3/src/Hardware/HAL/*.h
                                                    Hardware/HAL/*.*)
file(GLOB HARDWARE_LAN                              Hardware/LAN/*.*)
file(GLOB HARDWARE_LAN_LIBNET                       Hardware/LAN/libnet/*.*)
file(GLOB MENU                      ../../GTC-3/src/Menu/*.*)
file(GLOB MENU_PAGES                ../../GTC-3/src/Menu/Pages/*.*)
file(GLOB MODULES_BH1750            ../../GTC-3/src/Modules/BH1750/*.*)
file(GLOB MODULES_BME280            ../../GTC-3/src/Modules/BME280/*.*)
file(GLOB MODULES_HC12              ../../GTC-3/src/Modules/HC12/*.*)
file(GLOB MODULES_ST7735            ../../GTC-3/src/Modules/ST7735/*.*)
file(GLOB MODULES_W25Q80DV          ../../GTC-3/src/Modules/W25Q80DV/*.*)
file(GLOB SETTINGS                  ../../GTC-3/src/Settings/*.*)
file(GLOB UTILS                     ../../GTC-3/src/Utils/*.*)
file(GLOB UTILS_TEXT                ../../GTC-3/src/Utils/Text/*.*)

source_group(libs/STM32F1           FILES ${LIBS_STM32F1})
source_group(libs/STM32F1/Inc       FILES ${LIBS_STM32F1_INC})
source_group(libs/USBD              FILES ${LIBS_USBD})
source_group(src                    FILES ${SRC})
source_group(Display                FILES ${DISPLAY})
source_group(Display/Font           FILES ${DISPLAY_FONT})
source_group(Hardware               FILES ${HARDWARE})
source_group(Hardware/CDC           FILES ${HARDWARE_CDC})
source_group(Hardware/HAL           FILES ${HARDWARE_HAL})
source_group(Hardware/LAN           FILES ${HARDWARE_LAN})
source_group(Hardware/LAN/libnet    FILES ${HARDWARE_LAN_LIBNET})
source_group(Menu                   FILES ${MENU})
source_group(Menu/Pages             FILES ${MENU_PAGES})
source_group(Modules/BH1750         FILES ${MODULES_BH1750})
source_group(Modules/BME280         FILES ${MODULES_BME280})
source_group(Modules/HC12           FILES ${MODULES_HC12})
source_group(Modules/ST7735         FILES ${MODULES_ST7735})
source_group(Modules/W25Q80DV       FILES ${MODULES_W25Q80DV})
source_group(Settings               FILES ${SETTINGS})
source_group(Utils                  FILES ${UTILS})
source_group(Utils/Text             FILES ${UTILS_TEXT})


set_source_files_properties(Hardware/LAN/libnet/netserver.cpp
                            Hardware/LAN/libnet/netbase.cpp
                            Hardware/LAN/libnet/netclient.cpp
                            Hardware/LAN/libnet/netpacket.cpp
                            Hardware/LAN/ClientTCP.cpp
                            Application.cpp
                            Frame.cpp
                            main_win.cpp
                            PROPERTIES SKIP_UNITY_BUILD_INCLUSION ON)


set_source_files_properties(../../GTC-3/src/Hardware/CDC/usbd_conf.c
#                            ../../GTC-3/src/Hardware/CDC/usbd_desc.c
                            PROPERTIES HEADER_FILE_ONLY TRUE)

add_executable( ${PROJECT_NAME}
                ${LIBS_STM32F1}
                ${LIBS_STM32F1_INC}
                ${LIBS_USBD}
                ${SRC}
                ${DISPLAY}
                ${DISPLAY_FONT}
                ${HARDWARE}
                ${HARDWARE_CDC}
                ${HARDWARE_HAL}
                ${HARDWARE_LAN}
                ${HARDWARE_LAN_LIBNET}
                ${MENU}
                ${MENU_PAGES}
                ${MODULES_BH1750}
                ${MODULES_BME280}
                ${MODULES_HC12}
                ${MODULES_ST7735}
                ${MODULES_W25Q80DV}
                ${SETTINGS}
                ${UTILS}
                ${UTILS_TEXT}
                )

target_link_libraries(${PROJECT_NAME} wxbase32ud wxmsw32ud_core Ws2_32)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND copy ..\\..\\ThirdParty\\lib\\vc_dll\\wxbase32ud_vc_custom.dll $(OutputPath) /Y)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND copy ..\\..\\ThirdParty\\lib\\vc_dll\\wxmsw32ud_core_vc_custom.dll $(OutputPath) /Y)
