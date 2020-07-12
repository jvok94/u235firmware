#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "stm32l0xx.h"
#include "util.h"

#define M_TXBUF_LENGTH 32 //bytes
uint8_t m_txBuf0[M_TXBUF_LENGTH];
uint8_t m_txBuf1[M_TXBUF_LENGTH];
uint8_t *m_activeTxBuf = m_txBuf0;
volatile bool m_txDone = true;

void DMA1_Channel4_5_IRQHandler(void)
{
	if (DMA1->ISR & DMA_ISR_TCIF4)
	{
		DMA1->IFCR = DMA_IFCR_CTCIF4;
		DMA1_Channel4->CCR &= ~DMA_CCR_EN;
		USART2->CR1 &= ~USART_CR1_TE;
		m_txDone = true;
	}
}

void uart_init(void)
{
	/*
	 * Clocks configuration
	 */
	RCC->AHBENR			|=	RCC_AHBENR_DMAEN;				//Enable AHB bus clock to DMA peripheral
	RCC->APB1ENR		|= 	RCC_APB1ENR_USART2EN;			//Enable APB1 bus clock to USART2 peripheral

	/*
	 * Tx DMA configuration:
	 */
	DMA1_Channel4->CCR	= 	DMA_CCR_MINC				|	//Increment memory address
							DMA_CCR_DIR					|	//Memory to peripheral
							DMA_CCR_TCIE;					//Interrupt when transfer complete
	DMA1_Channel4->CPAR =	(uint32_t)&(USART2->TDR);		//Transfer to USART2_TDR (transmit data) register
	DMA1_CSELR->CSELR 	|=	(4U << DMA_CSELR_C4S_Pos);		//Map channel 4 to USART2_TX
	NVIC_EnableIRQ(DMA1_Channel4_5_IRQn);

	/*
	 * USART configuration
	 */
	USART2->BRR 		= 	139U;							//115.2kBaud divided from 16MHz clock (actually gives 115.107kBaud, 0.08% error)
	USART2->CR3			=	USART_CR3_DMAT;					//Enable DMA for transmission
	USART2->CR1 		= 	USART_CR1_UE;					//Enable peripheral
}

void uart_transmit(const uint8_t *buffer, uint16_t length)
{
	uint16_t txCount;
	for (txCount = 0; txCount < length; txCount += M_TXBUF_LENGTH)
	{
		uint16_t nextTransferLength = length - txCount;
		if (nextTransferLength > M_TXBUF_LENGTH)
		{
			nextTransferLength = M_TXBUF_LENGTH;
		}

		uint8_t *nextTxBuf;
		if (m_activeTxBuf == m_txBuf0)
		{
			nextTxBuf = m_txBuf1;
		}
		else
		{
			nextTxBuf = m_txBuf0;
		}

		memcpy(nextTxBuf, buffer + txCount, nextTransferLength);
		while (!m_txDone)
		{
			__WFI(); //Wait for last transfer to complete
		}

		DMA1_Channel4->CMAR = (uint32_t)nextTxBuf;
		DMA1_Channel4->CNDTR = nextTransferLength;
		m_activeTxBuf = nextTxBuf;
		m_txDone = false;
		__DSB(); //Memory barrier - ensure DMA is not enable until AFTER buffers are set up
		DMA1_Channel4->CCR |= DMA_CCR_EN;
		USART2->CR1 |= USART_CR1_TE;
	}
}
