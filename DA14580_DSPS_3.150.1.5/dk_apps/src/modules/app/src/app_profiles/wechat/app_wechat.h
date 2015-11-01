/**
 ****************************************************************************************
 *
 * @file wechat.h
 *
 * @brief Device Information Service Application entry point
 *
 * Copyright (C) RivieraWaves 2009-2013
 *
 *
 ****************************************************************************************
 */

#ifndef APP_WECHAT_H_
#define APP_WECHAT_H_

/**
 ****************************************************************************************
 * @addtogroup APP
 *
 * @brief Device Information Service Application entry point.
 *
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */

#include "rwip_config.h"     // SW Configuration

#if (BLE_WECHAT_SERVER)

#include <stdint.h>          // Standard Integer Definition
#include <co_bt.h>
#include "ble_580_sw_version.h"
#include "app_sw_version.h"
/*
 * DEFINES
 ****************************************************************************************
 */


#if (BLE_APP_PRESENT)

/// Manufacturer Name (up to 18 chars)
#define APP_WECHAT_MANUFACTURER_NAME       ("Dialog Semi")
#define APP_WECHAT_MANUFACTURER_NAME_LEN   (11)
/// Model Number String (up to 18 chars)
#define APP_WECHAT_MODEL_NB_STR            ("DA14580")
#define APP_WECHAT_MODEL_NB_STR_LEN        (7)
/// System ID - LSB -> MSB (FIXME)
#define APP_WECHAT_SYSTEM_ID               ("\x12\x34\x56\xFF\xFE\x9A\xBC\xDE")
#define APP_WECHAT_SYSTEM_ID_LEN           (8)
#define APP_WECHAT_SW_REV                  DA14580_REFDES_SW_VERSION
#define APP_WECHAT_FIRM_REV                DA14580_SW_VERSION
#define APP_WECHAT_FEATURES                (DIS_MANUFACTURER_NAME_CHAR_SUP | DIS_MODEL_NB_STR_CHAR_SUP | DIS_SYSTEM_ID_CHAR_SUP | DIS_SW_REV_STR_CHAR_SUP | DIS_FIRM_REV_STR_CHAR_SUP | DIS_PNP_ID_CHAR_SUP)
/// PNP ID
#define APP_WECHAT_PNP_COMPANY_ID_TYPE    (0x01)
#define APP_WECHAT_PNP_VENDOR_ID          (0x00D2)
#define APP_WECHAT_PNP_PRODUCT_ID         (0x0580)
#define APP_WECHAT_PNP_PRODUCT_VERSION    (0x0100)

#else

#define APP_WECHAT_FEATURES                (0)

#endif //(BLE_APP_PRESENT)

/*
 * FUNCTIONS DECLARATION
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 *
 * Device Information Service Application Functions
 *
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @brief Initialize Device Information Service Application
 ****************************************************************************************
 */
void app_wechat_init(void);

/**
 ****************************************************************************************
 * @brief Add a Device Information Service instance in the DB
 ****************************************************************************************
 */
void app_wechat_create_db_send(void);

/**
 ****************************************************************************************
 * @brief Enable the Device Information Service
 ****************************************************************************************
 */
void app_wechat_enable_prf(uint16_t);

#endif //BLE_DIS_SERVER

/// @} APP

#endif //APP_WECHAT_H_