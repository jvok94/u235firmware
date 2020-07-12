#ifndef INC_UTIL_H_
#define INC_UTIL_H_

void util_assertFail(void);

#define UTIL_ASSERT(x) if (!(x)) util_assertFail();

#endif /* INC_UTIL_H_ */
