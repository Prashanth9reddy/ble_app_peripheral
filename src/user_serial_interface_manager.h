#include "prf_utils.h"
#include "custs1.h"
#include "custs1_task.h"
#include "user_custs1_def.h"
#include "user_custs1_impl.h"
#include "user_peripheral.h"
#include "user_periph_setup.h"
#include "rwip_config.h"             // SW configuration
/*#include "gap.h"
#include "app_easy_timer.h"
#include "co_bt.h"
#include "app_diss_task.h"
#include "app_task.h"
#include "app_easy_security.h"
#include "llc_cntl.h"
#include "lld.h"
#include<stdlib.h>
#include "app_callback.h"
#include "app_customs.h"
#include "app_customs_task.h"
#include "app_default_handlers.h"*/
#include  "app_easy_msg_utils.h"
#include  "app_mid.h"
#include "ke_msg.h"
#include "ke_task.h" 

#include "ke_mem.h" 
#include "ke_timer.h"




void sim_uart_send_interrupt(uart_t* uart, char *output);

static void sim_uart_send_cb(uint16_t length,ke_msg_id_t const msgid,
                                            struct custs1_att_info_req  const *param,
                                            ke_task_id_t const dest_id,
                                            ke_task_id_t const src_id);
static void sim_uart_receive_cb(uint16_t length,ke_msg_id_t const msgid,
                                            struct custs1_att_info_req const *param,
                                            ke_task_id_t const dest_id,
                                            ke_task_id_t const src_id);
																						
																						
void sim_uart_receive_interrupt(uart_t* uart);
																						
																						
																						

struct tx_complete
	{
		uint16_t  tx_status;
		char msg[250];
	};
	
	struct rx_dataready
	{
		
		uint16_t  receive_buffer_length ;
		char  receive_buffer_data [250];
	};
