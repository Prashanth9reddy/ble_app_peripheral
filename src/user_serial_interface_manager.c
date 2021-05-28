#include "uart.h"
#include "uart_utils.h"
#include "arch_system.h"
#include "arch_console.h"
#include "user_serial_interface_manager.h"
#include "custs1_task.h"
#include "gpio.h"
#include "app_api.h"
#include "app.h"
#include "prf_utils.h"
#include "custs1.h"
#include "custs1_task.h"
#include "user_custs1_def.h"
#include "user_custs1_impl.h"
#include "user_peripheral.h"
#include "user_periph_setup.h"
#include "user_profiles_config.h"
#include <stdint.h>
#include "ke_task.h"
#include "prf_types.h"
#include "compiler.h"        // compiler definition
#include "att.h"
#include "attm_db_128.h"
#include "rwprf_config.h"

#include "rwip_config.h"


		
		
		


volatile uint16_t data_sent_cnt = 0;
static const char OUTPUT_STRING[250]; 

 char *output=(char * )(OUTPUT_STRING);

static void sim_uart_send_cb(uint16_t length,ke_msg_id_t const msgid,
                                           struct custs1_att_info_req  const *param,
                                            ke_task_id_t const dest_id,
                                            ke_task_id_t const src_id)
{
    data_sent_cnt = length;

	struct tx_complete *rsp =KE_MSG_ALLOC(TX_COMPLETE,
                                                   src_id,
                                                   dest_id,
                                                   tx_complete);
	rsp->tx_status = app_env[param->conidx].conidx;
	//strcpy(rsp->msg,param->m1);
	ke_msg_send(rsp);
	
	
}


void sim_uart_send_interrupt(uart_t* uart,char *output)
{
    printf_string(uart, "\n\r\n\r****************************************\n\r");
    if (uart == UART1)
    {
        printf_string(uart, "* UART1 Send Interrupt example *\n\r");
    }
    else
    {
        printf_string(uart, "* UART2 Send Interrupt example *\n\r");
    }
    printf_string(uart, "****************************************\n\r\n\r");

    
    data_sent_cnt = 0;

    uart_register_tx_cb(uart, sim_uart_send_cb);
    uart_send(uart, (uint8_t *)output, sizeof(output) - 1, UART_OP_INTR);
  
    printf_string(uart, "\n\rData sent: 0x");
    //print_hword(uart, data_sent_cnt);
    //printf_string(uart, " Bytes\n\r\n\r");
   // printf_string(uart, "****************************************\n\r\n\r");
}



const int READ_CHAR_COUNT = 260;
static char buffer[READ_CHAR_COUNT + 1];
volatile bool uart_receive_finished = false;
volatile uint16_t data_received_cnt = 0;

static void sim_uart_receive_cb(uint16_t length,ke_msg_id_t const msgid,
                                            struct custs1_att_info_req const *param,
                                            ke_task_id_t const dest_id,
                                            ke_task_id_t const src_id)
{
    data_received_cnt = length;
	
	struct rx_dataready *res =KE_MSG_ALLOC(RX_DATAREADY,
                                                   src_id,
                                                   dest_id,
                                                   rx_dataready);
	res->receive_buffer_length= app_env[param->conidx].conidx;
	strcpy(res->receive_buffer_data,param->m1);
	ke_msg_send(res);
  
}


void sim_uart_receive_interrupt(uart_t* uart)
{
    printf_string(uart, "\n\r\n\r****************************************\n\r");
    if (uart == UART1)
    {
        printf_string(uart, "* UART1 Receive Interrupt example *\n\r");
    }
    else
    {
        printf_string(uart, "* UART2 Receive Interrupt example *\n\r");
    }
    printf_string(uart, "****************************************\n\r\n\r");

   
    data_received_cnt = 0;
    uart_register_rx_cb(uart, sim_uart_receive_cb);

    printf_string(uart, "Type 5 characters.\r\n");

    uart_receive(uart, (uint8_t *)buffer, READ_CHAR_COUNT, UART_OP_INTR);
    
    buffer[READ_CHAR_COUNT] = 0; // make it a null terminated string

    printf_string(uart, "You typed the following characters:\r\n");
    printf_string(uart, buffer);
    printf_string(uart, "\r\n");

    printf_string(uart, "****************************************\n\r\n\r");
}



