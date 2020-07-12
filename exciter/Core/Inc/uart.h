#ifndef INC_UART_H_
#define INC_UART_H_

void uart_init(void);
void uart_transmit(const uint8_t *buffer, uint16_t length);

#endif /* INC_UART_H_ */
