#
# Copyright (c) 2019 Nordic Semiconductor
#
# SPDX-License-Identifier: LicenseRef-BSD-5-Clause-Nordic
#

# Calculates relative path to the library to be uses taking into account
# build type of the library, SoC type, floating point ABI, supported FEM type.
# Note: Subdirectory layout is specific to nrf_802154_sl lib
function(calculate_lib_path lib_path)
  # Select build type of the library to link with
  set(build_type_dir "Release")

  # Select SoC
  if(CONFIG_SOC_NRF52840)
    set(soc_dir "nrf52840_xxAA")
  elseif(CONFIG_SOC_NRF52833)
    set(soc_dir "nrf52833_xxAA")
  elseif(CONFIG_SOC_NRF52820)
    set(soc_dir "nrf52820_xxAA")
  elseif(CONFIG_SOC_NRF52811)
    set(soc_dir "nrf52811_xxAA")
  else()
    message(WARNING "Selected SoC is not supported by the nrf_802154_sl lib.")
  endif()

  # Select floating ABI
  if(CONFIG_FLOAT)
    if(CONFIG_FP_HARDABI)
        set(float_dir hard)
    elseif(CONFIG_FP_SOFTABI)
        set(float_dir softfp)
    else()
        assert(0 "Unreachable code")
    endif()
  else()
	  set(float_dir soft)
  endif()

  # Select FEM type
  set(fem_type_dir "three_pin_gpio")

  # Construct relative path to the selected lib
  set(${lib_path} "lib/${build_type_dir}/${soc_dir}/${float_dir}/${fem_type_dir}" PARENT_SCOPE)
endfunction()


calculate_lib_path(lib_path)
set(NRF_802154_SL_LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/${lib_path})

if(NOT EXISTS ${NRF_802154_SL_LIB_PATH})
  message(WARNING "This combination of SoC and floating point ABI is not supported by the nrf_802154_sl lib."
                  "(${NRF_802154_SL_LIB_PATH} doesn't exist.)")
endif()

zephyr_include_directories(include)

zephyr_include_directories(include/fem/three_pin_gpio)

zephyr_link_libraries(${NRF_802154_SL_LIB_PATH}/libnrf_802154_sl.a)

