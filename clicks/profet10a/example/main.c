/*!
 * @file main.c
 * @brief PROFET 10A Click Example.
 *
 * # Description
 * This example showcases the ability of the PROFET 10A Click board.
 * It configures Host MCU for communication and then enables 
 * and disables output channel. Besides that, it reads the voltage 
 * of IS pin and calculates current on output.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of the communication modules(ADC and UART) 
 * and additional pins for controlling the device.
 *
 * ## Application Task
 * On every iteration of the task device switches between 
 * DIAGNOSTIC and OFF mode while it reads the voltage of IS pin 
 * and with that calculates current on output.
 * 
 * @note
 * Formula for calculating current on load: 
 * I_load = voltage(IS) x kILIS / 1.2 kΩ
 *
 * Click board won't work properly on the PIC18F97J94 MCU card.
 * 
 * @author Luka FIlipovic
 *
 */

#include "board.h"
#include "log.h"
#include "profet10a.h"

static profet10a_t profet10a;   /**< PROFET 10A Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    profet10a_cfg_t profet10a_cfg;  /**< Click config object. */

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
    log_info( &logger, " Application Init " );

    // Click initialization.
    profet10a_cfg_setup( &profet10a_cfg );
    PROFET10A_MAP_MIKROBUS( profet10a_cfg, MIKROBUS_1 );
    if ( profet10a_init( &profet10a, &profet10a_cfg ) == ADC_ERROR )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    
    profet10a_set_mode( &profet10a, PROFET10A_DIAGNOSTIC_ON );
    Delay_ms( 1000 );
}

void application_task ( void )
{
    static uint8_t mode = PROFET10A_DIAGNOSTIC_ON;
    float profet10a_an_voltage = 0;
    
    profet10a_set_mode( &profet10a, mode );
    
    if ( PROFET10A_DIAGNOSTIC_ON == profet10a.mode )
    {
        mode = PROFET10A_MODE_OFF;
        log_printf( &logger, " > Output ON diagnostic mode\r\n" );
        Delay_ms( 2000 );
    }
    else
    {
        mode = PROFET10A_DIAGNOSTIC_ON;
        log_printf( &logger, " > Output OFF\r\n" );
    }

    if ( profet10a_read_an_pin_voltage ( &profet10a, &profet10a_an_voltage ) != ADC_ERROR )
    {
        log_printf( &logger, " > IS Voltage \t~ %.3f[V]\r\n", profet10a_an_voltage );
        
        float current = profet10a_an_voltage * profet10a.kilis / profet10a.rsens;
        log_printf( &logger, " > OUT Current \t~ %.3f[A]\r\n", current );
    }  
    
    log_printf( &logger, "*******************************************\r\n" );
    
    Delay_ms( 2000 );
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
