#ifndef _LINKER_H_
#define _LINKER_H_

#include <charstring.h>

/**
 * This file is intended to test the proper construction of objects inside the
 * char string header. There is an easy to make mistake where structs are
 * assigned within a header file, as a result, this will prompt a  _multiple
 * definition_ compile error. The proper design to create an object is to
 * define an `extern struct` inside the header, and to provide a macro function
 * which will assign it. It is up to the end user to assign the object using
 * said macro function.
 */
void VerifyLinking(void);

#endif /* _LINKER_H_ */