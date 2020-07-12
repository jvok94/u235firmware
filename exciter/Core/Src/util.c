void util_assertFail(void)
{
#ifdef DEBUG
	__asm__("bkpt"); //Throw breakpoint if in debug mode
#endif

	while (1) ; //Loop forever
}
