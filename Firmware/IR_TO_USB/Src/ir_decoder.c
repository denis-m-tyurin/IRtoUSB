/*
 * ir_decoder.c
 */
#include "ir_decoder.h"

#define IR_DEBUG

#ifdef IR_DEBUG
#include "keyboard.h"
#endif

static volatile IR_REC_STATE_T recState = IR_REC_STATE_IDLE;

#define MAX_CAPT_COUNT 255
static volatile uint8_t captCount = 0;
static volatile uint16_t captArray[MAX_CAPT_COUNT];

#define checkVal(var,val,tol) (var>(val*(100-tol)/100) && var<(val*(100+tol)/100))
#define IR_NEC_START_PULSE      9000
#define IR_NEC_START_WIDTH      13500
#define IR_NEC_0_PULSE          562
#define IR_NEC_0_WIDTH          1125
#define IR_NEC_1_PULSE          562
#define IR_NEC_1_WIDTH          2250
#define IR_NEC_TOL              20

IR_COMMAND_T ir_decode(void)
{
	uint32_t frame;
	uint8_t i;
	uint8_t buf[15];

	if (recState == IR_REC_STATE_CAPTURED)
	{
		frame=0;

		if (captCount==0)
		{
			recState = IR_REC_STATE_IDLE;
			return IR_NO_COMMAND;
		}

		if (captCount<33)
		{
			recState = IR_REC_STATE_IDLE;
			return IR_NO_COMMAND;
		}

		// check start bit
		if (!checkVal(captArray[0], IR_NEC_START_WIDTH, IR_NEC_TOL))
		{
			recState = IR_REC_STATE_IDLE;
			return IR_NO_COMMAND;
		}

		if (!checkVal(captArray[1], IR_NEC_START_PULSE, IR_NEC_TOL))
		{
			recState = IR_REC_STATE_IDLE;
			return IR_NO_COMMAND;
		}

		for(i=0; i<32; i++)
		{
			  if (checkVal(captArray[(i+1)*2], IR_NEC_0_WIDTH, IR_NEC_TOL)
					  && checkVal(captArray[(i+1)*2+1], IR_NEC_0_PULSE, IR_NEC_TOL))
			  {
				  frame = frame >> 1;
		          continue;
		      }

		      if (checkVal(captArray[(i+1)*2], IR_NEC_1_WIDTH, IR_NEC_TOL)
		    		  && checkVal(captArray[(i+1)*2+1], IR_NEC_1_PULSE, IR_NEC_TOL))
		      {
		    	  frame = (frame >> 1) | 0x80000000;
		          continue;
		      }

		      recState = IR_REC_STATE_IDLE;
		      return IR_NO_COMMAND;
		}

		switch(frame)
		{
		case 0xED127984:	// Power button
			recState = IR_REC_STATE_IDLE;
			return IR_COMMAND_POWER_TOGGLE;
		break;

		case 0xf9067984:	// HOME button
			recState = IR_REC_STATE_IDLE;
			return IR_COMMAND_RETURN;
		break;

		default:
#ifdef IR_DEBUG
			keyboardPutString("Unknown: 0x");
			memset(buf,0,15);
			utoa(frame, buf, 16);
			keyboardPutString(buf);
			keyboardPutString("\r\n");
#endif
			recState = IR_REC_STATE_IDLE;
			return IR_NO_COMMAND;
		}


	}
	return IR_NO_COMMAND;
}

void ir_receiver_timeout(void)
{
	if (recState == IR_REC_STATE_RECORDING)
	{
		recState = IR_REC_STATE_CAPTURED;
	}
}

void ir_receive_data(uint16_t cnt1, uint16_t cnt2)
{
	if (recState == IR_REC_STATE_RECORDING)
	{
	            	if (captCount < MAX_CAPT_COUNT)
	            	{
	            		captArray[captCount*2] = cnt1; //width
	                    captArray[captCount*2+1] = cnt2; //pulse
	                    captCount++;
	                }
	}
	else if (recState == IR_REC_STATE_IDLE)
	{
		recState = IR_REC_STATE_RECORDING;
	    captCount = 0;
	}
}

