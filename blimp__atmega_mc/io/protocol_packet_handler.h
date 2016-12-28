#ifndef __PROTOCOL_PACKET_HANDLER_H__
#define __PROTOCOL_PACKET_HANDLER_H__

#include "i2c.c"
#include "../../shared_source/uart_protocol_handler.c"

#include "../../shared_source/byte_order.c"

#include "../../shared_source/print_dtype.c"

uint8_t uartProtocolHandleRemoteRequest ();
uint8_t uartProtocolHandlePacket ();

extern 

#endif
