/*!
 * \file 
 * \brief Gsm3 Click example
 * 
 * # Description
 * This example reads and processes data from GSM 3 clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver and wake-up module.
 * 
 * ## Application Task  
 * Reads the received data and parses it.
 * 
 * ## Additional Function
 * - gsm3_process ( ) - The general process of collecting presponce 
 *                                   that sends a module.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "gsm3.h"
#include "string.h"

#define PROCESS_COUNTER 10
#define PROCESS_RX_BUFFER_SIZE 500
#define PROCESS_PARSER_BUFFER_SIZE 1000

// ------------------------------------------------------------------ VARIABLES

#define DEMO_APP_RECEIVER
//#define DEMO_APP_TRANSMITER

static gsm3_t gsm3;
static log_t logger;

static char current_parser_buf[ PROCESS_PARSER_BUFFER_SIZE ];
static uint8_t send_data_cnt = 0; 

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void gsm3_process ( void )
{
    int32_t rsp_size;
    uint16_t rsp_cnt = 0;
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint16_t check_buf_cnt;
    uint8_t process_cnt = PROCESS_COUNTER;
    
    // Clear parser buffer
    memset( current_parser_buf, 0 , PROCESS_PARSER_BUFFER_SIZE ); 
    
    while( process_cnt != 0 )
    {
        rsp_size = gsm3_generic_read( &gsm3, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

        if ( rsp_size > 0 )
        {  
            // Validation of the received data
            for ( check_buf_cnt = 0; check_buf_cnt < rsp_size; check_buf_cnt++ )
            {
                if ( uart_rx_buffer[ check_buf_cnt ] == 0 ) 
                {
                    uart_rx_buffer[ check_buf_cnt ] = 13;
                }
            }
            log_printf( &logger, "%s", uart_rx_buffer );

            // Storages data in parser buffer
            rsp_cnt += rsp_size;
            if ( rsp_cnt < PROCESS_PARSER_BUFFER_SIZE )
            {
                strncat( current_parser_buf, uart_rx_buffer, rsp_size );
            }
            
            // Clear RX buffer
            memset( uart_rx_buffer, 0, PROCESS_RX_BUFFER_SIZE );
        } 
        else 
        {
            process_cnt--;
            
            // Process delay 
            Delay_ms( 100 );
        }
    }
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    gsm3_cfg_t cfg;

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    gsm3_cfg_setup( &cfg );
    GSM3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    gsm3_init( &gsm3, &cfg );

    gsm3_module_power( &gsm3 );

    gsm3_process(  );

    gsm3_send_command( &gsm3, GSM3_SINGLE_CMD_AT );
    gsm3_process(  );

    gsm3_send_command( &gsm3, GSM3_SINGLE_CMD_AT );
    gsm3_process(  );

    gsm3_send_command( &gsm3, GSM3_SINGLE_CMD_AT );
    gsm3_process(  );

    gsm3_send_command( &gsm3, GSM3_SINGLE_CMD_ATE0 );
    gsm3_process(  );

    gsm3_send_command( &gsm3, "AT+IFC=2,2" );
    gsm3_process(  );
    
    gsm3_send_command( &gsm3, "AT+CMGF=1" );
    gsm3_process(  );

    Delay_ms( 2000 );
}

void application_task ( void )
{
    gsm3_process(  );
}

void main ( void )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
