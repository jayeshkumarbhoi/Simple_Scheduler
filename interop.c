/**
 * Copyright (c) 2018, Tiny Mesh AS - https://tiny-mesh.com
 * All rights reserved.
 */

#include "event-queue.h"
#include "debug.h"

#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>



#define CMD_LINE_LENGTH 128
static unsigned char cmdBuffer[CMD_LINE_LENGTH];
static int cmdBufferIndex = 0;
static event inputEvent;
#define MIN_VALID_PRINT_CHAR 32
#define MAX_VALID_PRINT_CHAR 126

int recv_byte(unsigned char c)
{
	//check range for printable character (32-126)
	if(c >= MIN_VALID_PRINT_CHAR && c <= MAX_VALID_PRINT_CHAR)
	{
	  if(cmdBufferIndex < 128)
	  {
		 // Adds a single character to the command buffer
		  cmdBuffer[cmdBufferIndex++] = c;
	  }
	}
	  //Execute the command if <CR> is received
	else if((c == '\r') ||(c == '\n'))
	{
		  inputEvent.type = event_input;
		  inputEvent.data = &cmdBuffer[0];
		  inputEvent.size = cmdBufferIndex;
		  queue_insert(inputEvent);
	}

  return 0;
}

void reset_input(void)
{
	memset(cmdBuffer, 0, CMD_LINE_LENGTH);
	memset(&inputEvent, 0, sizeof(event));
	cmdBufferIndex = 0;
}

int write_byte(char c) {
  return putchar(c);
}



void set_term_raw(void) {
  struct termios raw;

  tcgetattr(STDIN_FILENO, &raw);

  raw.c_lflag &= ~(ICANON);
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}
