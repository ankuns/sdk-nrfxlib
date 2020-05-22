/*
 * Copyright (c) 2020 Nordic Semiconductor ASA. All Rights Reserved.
 *
 * The information contained herein is confidential property of Nordic Semiconductor ASA.
 * The use, copying, transfer or disclosure of such information is prohibited except by
 * express written agreement with Nordic Semiconductor ASA.
 */

#ifndef NRF_FEM_CONFIG_H_
#define NRF_FEM_CONFIG_H_

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Configuration parameters for pins that enable or disable (or both) either Power Amplifier (PA) or Low Noise Amplifier (LNA).
 */
typedef struct
{
    bool    enable;       /* Enable toggling for this pin. */
    bool    active_high;  /* If true, the pin will be active high. Otherwise, the pin will be active low. */
    uint8_t gpio_pin;     /* GPIO pin number for the pin. */
    uint8_t gpiote_ch_id; /* GPIOTE channel to be used for toggling pins. */
} nrf_fem_gpiote_pin_config_t;

/**
 * @brief Configuration parameters for the PA/LNA interface.
 */
typedef struct
{
    struct
    {
        uint32_t pa_time_gap_us;                /* Time between the activation of the PA pin and the start of the radio transmission. */
        uint32_t lna_time_gap_us;               /* Time between the activation of the LNA pin and the start of the radio reception. */
        uint32_t pdn_settle_us;                 /* The time between activating the PDN and asserting the PA/LNA pin. */
        uint32_t trx_hold_us;                   /* The time between deasserting the PA/LNA pin and deactivating PDN. */
        int8_t   pa_gain_db;                    /* Configurable PA gain. Ignored if the amplifier is not supporting this feature. */
        int8_t   lna_gain_db;                   /* Configurable LNA gain. Ignored if the amplifier is not supporting this feature. */
    }                           fem_config;

    nrf_fem_gpiote_pin_config_t pa_pin_config;  /* Power Amplifier pin configuration. */
    nrf_fem_gpiote_pin_config_t lna_pin_config; /* Low Noise Amplifier pin configuration. */
    nrf_fem_gpiote_pin_config_t pdn_pin_config; /* Power Down pin configuration. */

    uint8_t                     ppi_ch_id_set;  /* PPI channel to be used for setting pins. */
    uint8_t                     ppi_ch_id_clr;  /* PPI channel to be used for clearing pins. */
    uint8_t                     ppi_ch_id_pdn;  /* PPI channel to handle PDN pin. */
} nrf_fem_interface_config_t;

/**
 * @section Timings.
 */

/** Time in microseconds when PA GPIO is activated before the radio is ready for transmission. */
#define NRF_FEM_PA_TIME_IN_ADVANCE_US  13

/** Time in microseconds when LNA GPIO is activated before the radio is ready for reception. */
#define NRF_FEM_LNA_TIME_IN_ADVANCE_US 13

/** The time between activating the PDN and asserting the RX_EN/TX_EN. */
#define NRF_FEM_PDN_SETTLE_US          18

/** The time between deasserting the RX_EN/TX_EN and deactivating PDN. */
#define NRF_FEM_TRX_HOLD_US            5

#ifdef NRF52811_XXAA
/** Default Power Amplifier pin. */
#define NRF_FEM_CONTROL_DEFAULT_PA_PIN  19

/** Default Low Noise Amplifier pin. */
#define NRF_FEM_CONTROL_DEFAULT_LNA_PIN 20

#else

/** Default Power Amplifier pin. */
#define NRF_FEM_CONTROL_DEFAULT_PA_PIN  15

/** Default Low Noise Amplifier pin. */
#define NRF_FEM_CONTROL_DEFAULT_LNA_PIN 16
#endif

/** Default Eagle PDN pin. */
#define NRF_FEM_CONTROL_DEFAULT_PDN_PIN            13

/** Default PPI channel for pin setting. */
#define NRF_FEM_CONTROL_DEFAULT_SET_PPI_CHANNEL    15

/** Default PPI channel for pin clearing. */
#define NRF_FEM_CONTROL_DEFAULT_CLR_PPI_CHANNEL    16

/** Default PPI channel for PDN pin handling. */
#define NRF_FEM_CONTROL_DEFAULT_PDN_PPI_CHANNEL    5

/** Default GPIOTE channel for PDN control. */
#define NRF_FEM_CONTROL_DEFAULT_PDN_GPIOTE_CHANNEL 5

/** Default GPIOTE channel for LNA control. */
#define NRF_FEM_CONTROL_DEFAULT_LNA_GPIOTE_CHANNEL 6

/** Default GPIOTE channel for PA control. */
#define NRF_FEM_CONTROL_DEFAULT_PA_GPIOTE_CHANNEL  7

/** Mask of GPIO pins used for FEM control. */
#define NRF_802154_FEM_PINS_USED_MASK              ((1 << NRF_FEM_CONTROL_DEFAULT_PA_PIN) |  \
                                                    (1 << NRF_FEM_CONTROL_DEFAULT_LNA_PIN) | \
                                                    (1 << NRF_FEM_CONTROL_DEFAULT_PDN_PIN))

/** Mask of PPI channels used for FEM control. */
#define NRF_802154_FEM_PPI_CHANNELS_USED_MASK      ((1 << NRF_FEM_CONTROL_DEFAULT_SET_PPI_CHANNEL) | \
                                                    (1 << NRF_FEM_CONTROL_DEFAULT_CLR_PPI_CHANNEL) | \
                                                    (1 << NRF_FEM_CONTROL_DEFAULT_PDN_PPI_CHANNEL))

/** Mask of GPIOTE channels used for FEM control. */
#define NRF_802154_FEM_GPIOTE_CHANNELS_USED_MASK   (        \
        (1 << NRF_FEM_CONTROL_DEFAULT_PDN_GPIOTE_CHANNEL) | \
        (1 << NRF_FEM_CONTROL_DEFAULT_LNA_GPIOTE_CHANNEL) | \
        (1 << NRF_FEM_CONTROL_DEFAULT_PA_GPIOTE_CHANNEL))

#ifdef __cplusplus
}
#endif

#endif /* NRF_FEM_CONFIG_H_ */
