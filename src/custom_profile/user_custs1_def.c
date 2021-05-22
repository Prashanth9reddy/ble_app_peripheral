/**
 ****************************************************************************************
 *
 * @file user_custs1_def.c
 *
 * @brief Custom Server 1 (CUSTS1) profile database definitions.
 *
 * Copyright (C) 2016-2019 Dialog Semiconductor.
 * This computer program includes Confidential, Proprietary Information
 * of Dialog Semiconductor. All Rights Reserved.
 *
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @defgroup USER_CONFIG
 * @ingroup USER
 * @brief Custom server 1 (CUSTS1) profile database definitions.
 *
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */

#include <stdint.h>
#include "co_utils.h"
#include "prf_types.h"
#include "attm_db_128.h"
#include "user_custs1_def.h"

/*
 * LOCAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */
 
 
 ////////SPPLE SERVICE AREA////////////////////////////
 static const att_svc_desc128_t spple_svc 													= DEF_SPPLE_SERVICE_UUID_128;
 static const att_svc_desc128_t app_send_svc												=DEF_APP_SEND_DATA_UUID_128;
 static const att_svc_desc128_t ble_send_svc												=DEF_BLE_SEND_DATA_UUID_128;
  static const att_svc_desc128_t auth_svc														=DEF_AUTH_UUID_128;


 static const uint8_t SPPLE_APP_SEND_DATA[ATT_UUID_128_LEN] 			  =	DEF_APP_SEND_DATA_UUID_128;
 static const uint8_t SPPLE_BLE_SEND_DATA[ATT_UUID_128_LEN]					=	DEF_BLE_SEND_DATA_UUID_128;
 static const uint8_t SPPLE_AUTH[ATT_UUID_128_LEN]									=	DEF_AUTH_UUID_128;

// Service 1 of the custom server 1
static const att_svc_desc128_t custs1_svc1                      = DEF_SVC1_UUID_128;

static const uint8_t SVC1_CTRL_POINT_UUID_128[ATT_UUID_128_LEN]       = DEF_SVC1_CTRL_POINT_UUID_128;
static const uint8_t SVC1_LED_STATE_UUID_128[ATT_UUID_128_LEN]        = DEF_SVC1_LED_STATE_UUID_128;
static const uint8_t SVC1_ADC_VAL_1_UUID_128[ATT_UUID_128_LEN]        = DEF_SVC1_ADC_VAL_1_UUID_128;
static const uint8_t SVC1_ADC_VAL_2_UUID_128[ATT_UUID_128_LEN]        = DEF_SVC1_ADC_VAL_2_UUID_128;
static const uint8_t SVC1_BUTTON_STATE_UUID_128[ATT_UUID_128_LEN]     = DEF_SVC1_BUTTON_STATE_UUID_128;
static const uint8_t SVC1_INDICATEABLE_UUID_128[ATT_UUID_128_LEN]     = DEF_SVC1_INDICATEABLE_UUID_128;
static const uint8_t SVC1_LONG_VALUE_UUID_128[ATT_UUID_128_LEN]       = DEF_SVC1_LONG_VALUE_UUID_128;

// Service 2 of the custom server 1#######################APP TO DEVICE##############################
static const att_svc_desc128_t custs1_svc2                      = DEF_SVC2_UUID_128;

static const uint8_t SVC2_WRITE_VAL_1_UUID_128[ATT_UUID_128_LEN]      = DEF_SVC2_WRITE_VAL_1_UUID_128;
static const uint8_t SVC2_WRITE_VAL_2_UUID_128[ATT_UUID_128_LEN]      = DEF_SVC2_WRITE_VAL_2_UUID_128;

// Service 3 of the custom server 1
static const att_svc_desc128_t custs1_svc3                      = DEF_SVC3_UUID_128;

static const uint8_t SVC3_READ_VAL_1_UUID_128[ATT_UUID_128_LEN]       = DEF_SVC3_READ_VAL_1_UUID_128;
static const uint8_t SVC3_READ_VAL_2_UUID_128[ATT_UUID_128_LEN]       = DEF_SVC3_READ_VAL_2_UUID_128;
static const uint8_t SVC3_READ_VAL_3_UUID_128[ATT_UUID_128_LEN]       = DEF_SVC3_READ_VAL_3_UUID_128;
static const uint8_t SVC3_READ_VAL_4_UUID_128[ATT_UUID_128_LEN]       = DEF_SVC3_READ_VAL_4_UUID_128;



// * GLOBAL VARIABLE DEFINITIONS
 //****************************************************************************************
 


// Attribute specifications
static const uint16_t att_decl_svc       = ATT_DECL_PRIMARY_SERVICE;
static const uint16_t att_decl_char      = ATT_DECL_CHARACTERISTIC;
static const uint16_t att_desc_cfg       = ATT_DESC_CLIENT_CHAR_CFG;
static const uint16_t att_desc_user_desc = ATT_DESC_CHAR_USER_DESCRIPTION;

const uint8_t custs1_services[]  = {SPPLE_APP_SVC,SPPLE_BLE_SVC,SPPLE_AUTH_SVC,SPPLE_IDX_NB};
//const uint8_t custs1_services[]  = {SVC1_IDX_SVC, SVC2_IDX_SVC, CUSTS1_IDX_NB};//SVC3_IDX_SVC
const uint8_t custs1_services_size = ARRAY_LEN(custs1_services) - 1;
const uint16_t custs1_att_max_nb = SPPLE_IDX_NB;

/// Full CUSTS1 Database Description - Used to add attributes into the database

const struct attm_desc_128 custs1_att_db[SPPLE_IDX_NB] =
{
	
		[SPPLE_APP_SVC] 											= {(uint8_t*)&att_decl_svc, ATT_UUID_128_LEN, PERM(WR, ENABLE),
                                            sizeof(app_send_svc), sizeof(app_send_svc), (uint8_t*)&app_send_svc},/////MAIN SERVICE
		
		[SPPLE_IDX_APP_SEND_CHAR]											=	{(uint8_t*)&att_decl_char, ATT_UUID_16_LEN, PERM(WR, ENABLE),
                                            0, 1, NULL},
		
		[SPPLE_IDX_APP_SEND_VAL]											=	{SPPLE_APP_SEND_DATA, ATT_UUID_128_LEN, PERM(WR, ENABLE) | PERM(WRITE_COMMAND, ENABLE),
                                            PERM(RI, ENABLE) | DEF_SVC1_LED_STATE_CHAR_LEN, 0, NULL},
		
		[SPPLE_IDX_APP_SEND_USER_DESC] 				= {(uint8_t*)&att_desc_user_desc, ATT_UUID_16_LEN, PERM(RD, ENABLE),
                                            sizeof(DEF_APP_SEND_USER_DESC) - 1, sizeof(DEF_APP_SEND_USER_DESC) - 1,
                                            (uint8_t *) DEF_APP_SEND_USER_DESC},
		
		[SPPLE_BLE_SVC] 											= {(uint8_t*)&att_decl_svc, ATT_UUID_128_LEN, PERM(WR, ENABLE),
                                            sizeof(ble_send_svc), sizeof(ble_send_svc), (uint8_t*)&ble_send_svc},/////MAIN SERVICE
	

		[SPPLE_IDX_BLE_SEND_CHAR]											=	{(uint8_t*)&att_decl_char, ATT_UUID_16_LEN, PERM(WR, ENABLE),
                                            0, 0, NULL},
		
		[SPPLE_IDX_BLE_SEND_VAL]											=	{SPPLE_BLE_SEND_DATA, ATT_UUID_128_LEN, PERM(NTF, ENABLE),
                                            DEF_BLE_SEND_CHAR_LEN, 0, NULL},
		
		[SPPLE_IDX_BLE_SEND_USER_DESC] 				= {(uint8_t*)&att_desc_user_desc, ATT_UUID_16_LEN, PERM(RD, ENABLE),
                                            sizeof(DEF_BLE_SEND_USER_DESC) - 1, sizeof(DEF_BLE_SEND_USER_DESC) - 1,
                                            (uint8_t *) DEF_BLE_SEND_USER_DESC},
		
																						
		[SPPLE_AUTH_SVC] 											= {(uint8_t*)&auth_svc, ATT_UUID_128_LEN, PERM(WR, ENABLE) | PERM(RD, ENABLE),
                                            sizeof(auth_svc), sizeof(spple_svc), (uint8_t*)&auth_svc},/////MAIN SERVICE
	
																						
		[SPPLE_IDX_AUTH_CHAR]											=	{(uint8_t*)&att_decl_char, ATT_UUID_16_LEN, PERM(WR, ENABLE),
                                            0, 0, NULL},
		
		[SPPLE_IDX_AUTH_VAL]											=	{SPPLE_BLE_SEND_DATA, ATT_UUID_128_LEN, PERM(WR, ENABLE),
                                            DEF_AUTH_CHAR_LEN, 0, NULL},
		
		[SPPLE_IDX_AUTH_USER_DESC] 				= 		{(uint8_t*)&att_desc_user_desc, ATT_UUID_16_LEN,PERM(WR, ENABLE) | PERM(WRITE_COMMAND, ENABLE),
                                            PERM(RI, ENABLE) | DEF_AUTH_CHAR_LEN, 0, NULL}
};


/// @} USER_CONFIG
