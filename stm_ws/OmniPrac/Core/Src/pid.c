/*
 * pid.c
 *
 *  Created on: 2020/02/29
 *      Author: nabeya11
 */

#include "pid.h"

void PID_Ctrl_Reset(PID_StructTypedef* params){
	params->integral = 0;
	params->prev_value = 0;
}

float PID_Ctrl(PID_StructTypedef* params, float value){
	float diff;

	//積算
	params->integral += value;
	//差分
	diff=value - params->prev_value;
	params->prev_value  = value;

	return (value*params->kp + params->integral * params->ki - diff * params->kd);
}
