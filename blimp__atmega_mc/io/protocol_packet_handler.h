#ifndef __PROTOCOL_PACKET_HANDLER_H__
#define __PROTOCOL_PACKET_HANDLER_H__

#include <inttypes.h>
#include <stdlib.h>

#include "../../shared_source/uart_protocol_handler.h"
#include "../../shared_source/byte_order.h"
#include "../../shared_source/print_dtype.h"
#include "../../shared_source/debug.h"

#include "i2c.h"

extern int16_t iEngineRight;
extern int16_t iEngineLeft;

uint8_t uartProtocolHandleRemoteRequest (struct strUartProtocol *strpProtocolLink);
uint8_t uartProtocolHandlePacket (struct strUartProtocol *strpProtocolLink);

/*struct stepper;
void setStepperOffsetAngle (struct stepper* cStepperToSet, const int16_t iAngle);*/

#endif
