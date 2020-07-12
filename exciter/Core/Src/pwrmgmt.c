#include "stm32l0xx_hal.h"
#include "hwconfig.h"
#include "util.h"

void pwrmgmt_useCrystal(void)
{
	HAL_StatusTypeDef status;
	RCC_OscInitTypeDef oscParams;
	RCC_PLLInitTypeDef pllParams;
	RCC_ClkInitTypeDef clkParams;

	/*
	 * Step 1: switch on the 12MHz crystal oscillator (set OSCEN high)
	 */
	HAL_GPIO_WritePin(HWCONFIG_OSCEN_PORT, HWCONFIG_OSCEN_PIN, GPIO_PIN_SET);

	/*
	 * Step 2: enable 12MHz external oscillator (HSE bypass) multiplied up to 32MHz using PLL
	 */
	pllParams.PLLSource = RCC_PLLSOURCE_HSE;
	pllParams.PLLMUL = RCC_PLL_MUL4; //Multiply 12MHz input by 4 to get 48MHz
	pllParams.PLLDIV = RCC_PLL_DIV3; //Divide 48MHz by 3 to get 16MHz output
	pllParams.PLLState = RCC_PLL_ON;
	oscParams.PLL = pllParams;
	oscParams.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	oscParams.HSEState = RCC_HSE_BYPASS; //External oscillator
	status = HAL_RCC_OscConfig(&oscParams);
	UTIL_ASSERT(status == HAL_OK);

	/*
	 * Step 3: select PLL as clock source
	 */
	clkParams.ClockType = RCC_CLOCKTYPE_SYSCLK;
	clkParams.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	status = HAL_RCC_ClockConfig(&clkParams, FLASH_LATENCY_0);
	UTIL_ASSERT(status == HAL_OK);
	UTIL_ASSERT(SystemCoreClock == 16000000UL); //Clock should now be 16MHz

	/*
	 * Step 4: disable HSI (16MHz internal RC) oscillator
	 */
	pllParams.PLLState = RCC_PLL_NONE; //No change to PLL configuration
	oscParams.PLL = pllParams;
	oscParams.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	oscParams.HSIState = RCC_HSI_OFF;
	status = HAL_RCC_OscConfig(&oscParams);
	UTIL_ASSERT(status == HAL_OK);
}

void pwrmgmt_useRC(void)
{
	HAL_StatusTypeDef status;
	RCC_OscInitTypeDef oscParams;
	RCC_PLLInitTypeDef pllParams;
	RCC_ClkInitTypeDef clkParams;

	/*
	 * Step 1: enable HSI (16MHz internal RC) oscillator
	 */
	pllParams.PLLState = RCC_PLL_NONE; //No change to PLL configuration (yet)
	oscParams.PLL = pllParams;
	oscParams.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	oscParams.HSIState = RCC_HSI_ON;
	status = HAL_RCC_OscConfig(&oscParams);
	UTIL_ASSERT(status == HAL_OK);

	/*
	 * Step 2: select HSI as clock source
	 */
	clkParams.ClockType = RCC_CLOCKTYPE_SYSCLK;
	clkParams.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
	status = HAL_RCC_ClockConfig(&clkParams, FLASH_LATENCY_0);
	UTIL_ASSERT(status == HAL_OK);
	UTIL_ASSERT(SystemCoreClock == 16000000UL); //Clock should now be 16MHz

	/*
	 * Step 3: disable external (HSE) oscillator and PLL
	 */
	pllParams.PLLState = RCC_PLL_OFF;
	oscParams.PLL = pllParams;
	oscParams.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	oscParams.HSEState = RCC_HSE_OFF;
	status = HAL_RCC_OscConfig(&oscParams);
	UTIL_ASSERT(status == HAL_OK);

	/*
	 * Step 4: switch off the 12MHz crystal oscillator (set OSCEN pin low)
	 */
	HAL_GPIO_WritePin(HWCONFIG_OSCEN_PORT, HWCONFIG_OSCEN_PIN, GPIO_PIN_RESET);
}
