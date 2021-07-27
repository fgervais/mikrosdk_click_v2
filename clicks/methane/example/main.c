/*!
 * @file main.c
 * @brief Methane Click Example.
 *
 * # Description
 * The demo application shows the reading of the adc 
 * values given by the sensors.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Configuring clicks and log objects.
 * 
 * ## Application Task  
 * Reads the adc value and prints in two forms adc value and voltage.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "methane.h"

static methane_t methane;   /**< Methane Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    methane_cfg_t methane_cfg;  /**< Click config object. */

    // Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );

    // Click initialization.

    methane_cfg_setup( &methane_cfg );
    METHANE_MAP_MIKROBUS( methane_cfg, MIKROBUS_1 );
    if ( methane_init( &methane, &methane_cfg ) == ADC_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}

void application_task ( void ) {
    uint16_t methane_an_value = 0;

    if ( methane_read_an_pin_value ( &methane, &methane_an_value ) != ADC_ERROR ) {
        log_printf( &logger, " ADC Value : %u\r\n", methane_an_value );
    }

    float methane_an_voltage = 0;

    if ( methane_read_an_pin_voltage ( &methane, &methane_an_voltage ) != ADC_ERROR ) {
        log_printf( &logger, " AN Voltage : %.3f[V]\r\n\n", methane_an_voltage );
    }

    Delay_ms( 1000 );
}

void main ( void ) {
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END