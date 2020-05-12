/*
 * bit_math.h
 *
 * Created: 4/10/2020 9:25:08 AM
 *  Author: User™
 */ 


#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SET_BIT(var,bit) var|=(1<<bit)
#define CLEAR_BIT(var,bit) var&=~(1<<bit)
#define GIT_BIT(var,bit) ((var>>bit)&1)


#endif /* BIT_MATH_H_ */