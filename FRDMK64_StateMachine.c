# FRDMK64F_StateMachine
Show in a bare metal project how to implement a state machine
#include "fsl_debug_console.h"
#include "fsl_port.h"
#include "fsl_gpio.h"
#include "fsl_common.h"
#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define BOARD_LED_GPIO BOARD_LED_RED_GPIO
#define BOARD_LED_GPIO_PIN BOARD_LED_RED_GPIO_PIN



#define BOARD_SW_GPIO BOARD_SW3_GPIO
#define BOARD_SW_PORT BOARD_SW3_PORT
#define BOARD_SW_GPIO_PIN BOARD_SW3_GPIO_PIN
#define BOARD_SW_IRQ BOARD_SW3_IRQ
#define BOARD_SW_IRQ_HANDLER BOARD_SW3_IRQ_HANDLER
#define BOARD_SW_NAME BOARD_SW3_NAME

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
/* Whether the SW button is pressed */
volatile bool g_ButtonPress = false;
volatile bool g_ButtonPresssw2 = false;

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Interrupt service fuction of switch.
 *
 * This function toggles the LED
 */
void BOARD_SW_IRQ_HANDLER(void)
{
    /* Clear external interrupt flag. */
    GPIO_ClearPinsInterruptFlags(BOARD_SW_GPIO, 1U << BOARD_SW_GPIO_PIN);
    /* Change state of button. */
    g_ButtonPress = true;
}

void BOARD_SW2_IRQ_HANDLER(void)
{
    /* Clear external interrupt flag. */
    GPIO_ClearPinsInterruptFlags(BOARD_SW2_GPIO, 1U << BOARD_SW2_GPIO_PIN);
    /* Change state of button. */
    g_ButtonPresssw2 = true;
}
/*!
 * @brief Main function
 */
int main(void)
{
    /* Define the init structure for the input switch pin */
    gpio_pin_config_t sw_config = {
        kGPIO_DigitalInput, 0,
    };

    /* Define the init structure for the output LED pin */
    gpio_pin_config_t led_config = {
        kGPIO_DigitalOutput, 0,
    };

    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole(); //configura uart en puerto B
    char state = 'i';
    /* Print a note to terminal. */
    PRINTF("\r\n State Machine sample\r\n");
    PRINTF("\r\n Press %s to turn on/off a LED \r\n", BOARD_SW_NAME);

    /* Init input switch GPIO. */
    PORT_SetPinInterruptConfig(BOARD_SW_PORT, BOARD_SW_GPIO_PIN, kPORT_InterruptFallingEdge);
    EnableIRQ(BOARD_SW_IRQ);
    GPIO_PinInit(BOARD_SW_GPIO, BOARD_SW_GPIO_PIN, &sw_config);

    /* Init input switch GPIO. */
    PORT_SetPinInterruptConfig(BOARD_SW2_PORT, BOARD_SW2_GPIO_PIN, kPORT_InterruptFallingEdge);
    EnableIRQ(BOARD_SW2_IRQ);
    GPIO_PinInit(BOARD_SW2_GPIO, BOARD_SW2_GPIO_PIN, &sw_config);

    /* Init output LED GPIO. */
    GPIO_PinInit(BOARD_LED_GPIO, BOARD_LED_GPIO_PIN, &led_config);
    GPIO_PinInit(BOARD_LED_BLUE_GPIO, BOARD_LED_BLUE_GPIO_PIN, &led_config);

    while (1)
    {
        //if (g_ButtonPress)
        //{
        //    PRINTF(" %s is pressed \r\n", BOARD_SW_NAME);
            /* Toggle LED. */
        //    GPIO_TogglePinsOutput(BOARD_LED_GPIO, 1U << BOARD_LED_GPIO_PIN);
            /* Reset state of button. */
        //    g_ButtonPress = false;
        //}

        //if (g_ButtonPresssw2)
        //        {
        //            PRINTF(" %s is pressed \r\n", BOARD_SW_NAME);
                    /* Toggle LED. */
        //            GPIO_TogglePinsOutput(BOARD_LED_BLUE_GPIO, 1U << BOARD_LED_BLUE_GPIO_PIN);
                    /* Reset state of button. */
        //            g_ButtonPresssw2 = false;
        //        }
    	switch(state)
    	      {
    	        case('i'):
    				{ if (g_ButtonPress)
    		        	{  	PRINTF(" %s is pressed \r\n", BOARD_SW_NAME);
    		            	/* Reset state of button. */
    		            	g_ButtonPress = false;
    		            	state = 'f';
    		            	break;
    		        	}
    				  else
    				    {	PRINTF("\r\n Initial State: waiting for the start signal.");
    				    	state = 'i';
    				    	break;
    					}
    				}

    	        case('f'):
    				{ if (g_ButtonPress)
    	        		{  	PRINTF(" %s is pressed \r\n", BOARD_SW_NAME);
    	            		/* Reset state of button. */
    	            		g_ButtonPress = false;
    	            		state = 's';
    	            		break;
    	        		}
    				  else
    				  	{	PRINTF("\r\n First State: waiting for the continue signal.");
    			    		state = 'f';
    			    		break;
    				  	}

    				}

    	        case('s'):
    	        	{ if (g_ButtonPress)
    	            	{  	PRINTF(" %s is pressed \r\n", BOARD_SW_NAME);
    	               		/* Reset state of button. */
    	               		g_ButtonPress = false;
    	               		state = 't';
    	               		break;
    	            	}
    	        	  else
    	        	  	{	PRINTF("\r\n Second State: waiting for the continue signal.");
    	        	   		state = 's';
    	        	   		break;
    	        	  	}
    	            }

    	        case('t'):
    	            { if (g_ButtonPress)
    	               	{  	PRINTF(" %s is pressed \r\n", BOARD_SW_NAME);
    	               		/* Reset state of button. */
    	               		g_ButtonPress = false;
    	               		state = 'q';
    	               		break;
    	               	}
    	              else
    	              	{	PRINTF("\r\n Third State: waiting for the continue signal.");
    	               		state = 't';
    	               		break;
    	              	}
    	            }

    	        case('q'):
    	            { if (g_ButtonPress)
    	               	{  	PRINTF(" %s is pressed \r\n", BOARD_SW_NAME);
    	              		/* Reset state of button. */
    	               		g_ButtonPress = false;
    	               		state = 'l';
    	               		break;
    	               	}
    	              else
    	              	{	PRINTF("\r\n Fourth State: waiting for the continue signal.");
    	               		state = 'q';
    	               		break;
    	              	}
    	            }

    	        case('l'):
    	            { if (g_ButtonPress)
    	                {  	PRINTF(" %s is pressed \r\n", BOARD_SW_NAME);
    	                	/* Reset state of button. */
    	                	g_ButtonPress = false;
    	                	state = 'i';
    	                	PRINTF("\r\n Last state Reached, going to initial state.");
    	                	break;
    	                }
    	               else
    	                {	PRINTF("\r\n Last State: waiting for the continue signal.");
    	                	state = 'l';
    	                	break;
    	                }
    	             }
    	      }

    }
}
