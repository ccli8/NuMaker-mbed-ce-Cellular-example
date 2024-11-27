# Copyright (c) 2020 ARM Limited. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

# SIMCOM SIM7020 driver supports legacy Mbed OS 5.15 only and doesn't
# support Mbed CE yet.
message(FATAL_ERROR "SIMCOM SIM7020 driver doesn't support Mbed CE yet")

target_include_directories(mbed-cellular
    PUBLIC
        .
)

target_sources(mbed-cellular
    PRIVATE
        SIMCOM_SIM7020_Serial.cpp
)

if(${MBED_TOOLCHAIN} STREQUAL "GCC_ARM")
    set(toolchain TOOLCHAIN_GCC)
elseif(${MBED_TOOLCHAIN} STREQUAL "ARM")
    set(toolchain TOOLCHAIN_ARM)
elseif(${MBED_TOOLCHAIN} STREQUAL "IAR")
    set(toolchain TOOLCHAIN_IAR)
endif()

if("M4" IN_LIST MBED_TARGET_LABELS)
    set(target TARGET_M4)
elseif("M23" IN_LIST MBED_TARGET_LABELS)
    set(target TARGET_M23)
endif()

target_link_libraries(mbed-cellular
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/${toolchain}/${target}/SIMCOM_SIM7020.o
        ${CMAKE_CURRENT_SOURCE_DIR}/${toolchain}/${target}/SIMCOM_SIM7020_CellularContext.o
        ${CMAKE_CURRENT_SOURCE_DIR}/${toolchain}/${target}/SIMCOM_SIM7020_CellularNetwork.o
        ${CMAKE_CURRENT_SOURCE_DIR}/${toolchain}/${target}/SIMCOM_SIM7020_CellularStack.o
)
    
# Link override object file coming from static library anyway
#
# NOTE: This linker option is to pretend undefined symbol and won't cause
#       undefined symbol error even though the override object file actually
#       doesn't provide such symbol definition.
if(${MBED_TOOLCHAIN} STREQUAL "GCC_ARM")
    target_link_options(mbed-cellular
        INTERFACE
            LINKER:--undefined=LINK_SIMCOM_SIM7020_SERIAL_CPP
    )
endif()
