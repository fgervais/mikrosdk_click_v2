\mainpage Main Page

---
# Multi Stepper TB62261 click

> Multi Stepper Click is a compact add-on board that contains a bipolar stepper motor driver. This board features the TB62261FTG, a PHASE-in controlled bipolar stepping motor driver from Toshiba Semiconductor. It supports a PWM constant-current control drive and full-, half-, and quarter-step operation for less motor noise and smoother control. It has a wide operating voltage range of 10V to 38V with an output current capacity of 1.2A in addition to several built-in error detection circuits.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/multisteppertb62261_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/multi-stepper-click-tb62261)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2022.
- **Type**          : I2C type


# Software Support

We provide a library for the Multi Stepper TB62261 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Multi Stepper TB62261 Click driver.

#### Standard key functions :

- `multisteppertb62261_cfg_setup` Config Object Initialization function.
```c
void multisteppertb62261_cfg_setup ( multisteppertb62261_cfg_t *cfg );
```

- `multisteppertb62261_init` Initialization function.
```c
err_t multisteppertb62261_init ( multisteppertb62261_t *ctx, multisteppertb62261_cfg_t *cfg );
```

- `multisteppertb62261_default_cfg` Click Default Configuration function.
```c
err_t multisteppertb62261_default_cfg ( multisteppertb62261_t *ctx );
```

#### Example key functions :

- `multisteppertb62261_set_step_mode` This function sets the step mode resolution settings in ctx->step_mode.
```c
void multisteppertb62261_set_step_mode ( multisteppertb62261_t *ctx, uint8_t mode );
```

- `multisteppertb62261_drive_motor` This function drives the motor for the specific number of steps at the selected speed.
```c
err_t multisteppertb62261_drive_motor ( multisteppertb62261_t *ctx, uint32_t steps, uint8_t speed );
```

- `multisteppertb62261_set_direction` This function sets the motor direction to clockwise or counter-clockwise in ctx->direction.
```c
void multisteppertb62261_set_direction ( multisteppertb62261_t *ctx, uint8_t dir );
```

## Example Description

> This example demonstrates the use of the Multi Stepper TB62261 click board by driving the motor in both directions for a desired number of steps.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    multisteppertb62261_cfg_t multisteppertb62261_cfg;  /**< Click config object. */

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
    multisteppertb62261_cfg_setup( &multisteppertb62261_cfg );
    MULTISTEPPERTB62261_MAP_MIKROBUS( multisteppertb62261_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == multisteppertb62261_init( &multisteppertb62261, &multisteppertb62261_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( MULTISTEPPERTB62261_ERROR == multisteppertb62261_default_cfg ( &multisteppertb62261 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Drives the motor clockwise for 200 steps and then counter-clockiwse for 100 steps with 2 seconds delay before changing the direction.
Each step will be logged on the USB UART where you can track the program flow.

```c
void application_task ( void )
{
    multisteppertb62261_set_direction ( &multisteppertb62261, MULTISTEPPERTB62261_DIR_CW );
    if ( MULTISTEPPERTB62261_OK == multisteppertb62261_drive_motor ( &multisteppertb62261, 200, 
                                                                     MULTISTEPPERTB62261_SPEED_FAST ) )
    {
        log_printf ( &logger, " Move 200 steps clockwise \r\n\n" );
        Delay_ms ( 2000 );
    }
    
    multisteppertb62261_set_direction ( &multisteppertb62261, MULTISTEPPERTB62261_DIR_CCW );
    if ( MULTISTEPPERTB62261_OK == multisteppertb62261_drive_motor ( &multisteppertb62261, 100,
                                                                     MULTISTEPPERTB62261_SPEED_FAST ) )
    {
        log_printf ( &logger, " Move 100 steps counter-clockwise \r\n\n" );
        Delay_ms ( 2000 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.MultiStepperTB62261

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---