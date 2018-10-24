/**
 * \file
 *
 * \brief User board initialization template
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <asf.h>
#include <board.h>
#include <conf_board.h>

#if defined(__GNUC__)
void board_init(void) WEAK __attribute__((alias("system_board_init")));
#elif defined(__ICCARM__)
void board_init(void);
#  pragma weak board_init=system_board_init
#endif



void system_board_init(void)
{
	/* This function is meant to contain board-specific initialization code
	 * for, e.g., the I/O pins. The initialization can rely on application-
	 * specific board configuration, found in conf_board.h.
	 */
	
	struct port_config config_port_pin;
	
	port_get_config_defaults(&config_port_pin);
	
	//init SW0
	config_port_pin.direction  = PORT_PIN_DIR_INPUT;
	config_port_pin.input_pull = PORT_PIN_PULL_UP;
	port_pin_set_config(SW0, &config_port_pin);

	//init LED0 and LED1
	config_port_pin.direction  = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(LED0, &config_port_pin);
	port_pin_set_config(LED1, &config_port_pin);
	port_pin_set_output_level(LED0, LED_OFF);
	port_pin_set_output_level(LED1, LED_OFF);

}