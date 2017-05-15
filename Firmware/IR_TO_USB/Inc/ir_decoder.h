/*
 * ir_decoder.h
 */

#ifndef IR_DECODER_H_
#define IR_DECODER_H_

#include "stdint.h"

typedef enum IR_COMMAND_T
{
	IR_NO_COMMAND = 0,
	IR_COMMAND_POWER_TOGGLE,
	IR_COMMAND_RETURN,
} IR_COMMAND_T;

typedef enum
{
	IR_REC_STATE_IDLE = 0,
	IR_REC_STATE_RECORDING,
	IR_REC_STATE_CAPTURED
} IR_REC_STATE_T;

IR_COMMAND_T ir_decode(void);
void ir_receiver_timeout(void);
void ir_receive_data(uint16_t cnt1, uint16_t cnt2);

#endif /* IR_DECODER_H_ */
