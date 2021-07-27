\mainpage Main Page
 
---
# RS485 5 click

The RS485 5 Click is a Click board™ equipped with the MAX485, low-power, slew-rate-limited transceiver for RS-485 and RS-422 communication, from Maxim Integrated. This device supports half-duplex RS-485 communication and can be used as an interface between the TTL level UART and the RS485 communication bus. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/rs4855_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/rs485-5-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : UART type


# Software Support

We provide a library for the Rs4855 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Rs4855 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void rs4855_cfg_setup ( rs4855_cfg_t *cfg ); 
 
- Initialization function.
> RS4855_RETVAL rs4855_init ( rs4855_t *ctx, rs4855_cfg_t *cfg );

#### Example key functions :

- Generic write function.
> void rs4855_generic_write ( rs4855_t *ctx, char *data_buf, uint16_t len );
 
- Sets DE pin to high or low state
> void rs4855_set_de_state( rs4855_t *ctx, uint8_t state );

- Sets RE pin to high or low state
> void rs4855_set_re_state( rs4855_t *ctx, uint8_t state );

## Examples Description

> This example reads and processes data from RS485 5 clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver and enables the selected mode.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    rs4855_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    rs4855_cfg_setup( &cfg );
    RS4855_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rs4855_init( &rs4855, &cfg );

    Delay_ms( 100 );

#ifdef DEMO_APP_RECEIVER
    rs4855_set_re_state( &rs4855, RS4855_PIN_STATE_LOW );
    rs4855_set_de_state( &rs4855, RS4855_PIN_STATE_LOW );
    log_info( &logger, "---- Receiver mode ----" );
#endif    
#ifdef DEMO_APP_TRANSMITTER
    rs4855_set_re_state( &rs4855, RS4855_PIN_STATE_HIGH );
    rs4855_set_de_state( &rs4855, RS4855_PIN_STATE_HIGH );
    log_info( &logger, "---- Transmitter mode ----" );
#endif    
}
  
```

### Application Task

> Depending on the selected mode, it reads all the received data or sends the desired message every 2 seconds.

```c

void application_task ( void )
{
#ifdef DEMO_APP_RECEIVER
    rs4855_process( );
#endif    
    
#ifdef DEMO_APP_TRANSMITTER
    rs4855_generic_write( &rs4855, TEXT_TO_SEND, 8 );
    log_info( &logger, "---- Data sent ----" );
    Delay_ms( 2000 );
#endif  
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Rs4855

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---