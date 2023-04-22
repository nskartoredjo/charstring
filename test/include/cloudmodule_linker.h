#ifndef CLOUDMODULE_LINKER_H_
#define CLOUDMODULE_LINKER_H_

/**
 * @file cloudmodule_linker.h
 * @author DotRobot
 * @brief The cloud module linker verification file
 * @version 1.0
 * @date 2022-09-09
 *
 * @copyright Copyright (c) 2022
 *
 * This file is intended to test the proper construction of objects inside the
 * cloudmodule API. There is an easy to make mistake where structs are assigned
 * within a header file, as a result, this will prompt a  _multiple definition_
 * compile error. The proper design to create an API object is to define an
 * `extern struct` inside the header, and to provide a macro function which will
 * assign it. It is up to the end user to assign the object using said macro
 * function.
 *
 * ```c
 * typedef struct {
 *   uint8_t value;
 * } Type;
 *
 * extern Type type;
 *
 * #define Type() {69}
 *
 * // The end user now must assign the object inside a end_user.c source file
 * Type type = Type();
 * ```
 */

#include <cloudmodule.h>

void verifyLinking(void);

#endif /* CLOUDMODULE_LINKER_H_ */