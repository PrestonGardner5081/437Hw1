/**************************************************
* CMPEN 473, Spring 2022, Penn State University
* 
* Homework 1 
* On 01/15/2022
* By Preston Gardner
* 
***************************************************/

/* Homework 1 
 * Slow sequential LED blinking program in C for 
 * Raspberry Pi zero computer with 
 * red   LED on GPIO12 (with 500 ohm resistor in series)
 * green LED on GPIO13 (with 500 ohm resistor in series)
 * blue  LED on GPIO22 (with 500 ohm resistor in series)
 * yelow LED on GPIO23 (with 500 ohm resistor in series)
 * 
 * LED turn-on and LED turn-off in 2 second cycle, repeat, chanign LED color sequentially
 * 
 * IMPORTANT! This project is made for the raspberry pi zero. The base memory 
 * address in import_registers.c needs to be 0xFE000000 to run on rasp pi 4
 */

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <termios.h>
#include <fcntl.h>
#include <signal.h>
#include "import_registers.h"
#include "gpio.h"
#include "cm.h"
#include "pwm.h"
#include "spi.h"
#include "io_peripherals.h"
#include "enable_pwm_clock.h"

volatile struct io_peripherals *io;

void INThandler(int sig)
{
  GPIO_CLR(&(io->gpio), 12);
  GPIO_CLR(&(io->gpio), 13);
  GPIO_CLR(&(io->gpio), 22);
  GPIO_CLR(&(io->gpio), 23);
  exit(0);
}

int main(void)
{
  signal(SIGINT, INThandler);

  io = import_registers();
  if (io != NULL)
  {
    /* print where the I/O memory was actually mapped to */
    printf("mem at 0x%8.8X\n", (unsigned int)io);
    char usrInput;
    int pinSelect = -1;

    /* set the pin function to OUTPUT for GPIO */
    io->gpio.GPFSEL1.field.FSEL2 = GPFSEL_OUTPUT; //GPIO12 red
    io->gpio.GPFSEL1.field.FSEL3 = GPFSEL_OUTPUT; //GPIO13 green
    io->gpio.GPFSEL2.field.FSEL3 = GPFSEL_OUTPUT; //GPIO23 yellow
    io->gpio.GPFSEL2.field.FSEL2 = GPFSEL_OUTPUT; //GPIO22 blue

    printf("hit 'ctl c' to quit\n");

    while (1)
    {
      printf("\nSelect LED r,g,b,o\n");
      printf("Or q to quit\n");

      while ((usrInput = getchar()) == '\n')
        ;

      if (usrInput == 'r')
      {
        GPIO_CLR(&(io->gpio), pinSelect);
        pinSelect = 12;
      }
      else if (usrInput == 'g')
      {
        GPIO_CLR(&(io->gpio), pinSelect);
        pinSelect = 13;
      }
      else if (usrInput == 'b')
      {
        GPIO_CLR(&(io->gpio), pinSelect);
        pinSelect = 22;
      }
      else if (usrInput == 'o')
      {
        GPIO_CLR(&(io->gpio), pinSelect);
        pinSelect = 23;
      }
      else if (usrInput == 'q')
      {
        GPIO_CLR(&(io->gpio), 12);
        GPIO_CLR(&(io->gpio), 13);
        GPIO_CLR(&(io->gpio), 22);
        GPIO_CLR(&(io->gpio), 23);
        break;
      }
      else
      {
        continue;
      }

      GPIO_SET(&(io->gpio), pinSelect);
    }
  }
  else
  {
    ; /* warning message already issued */
  }

  return 0;
}
