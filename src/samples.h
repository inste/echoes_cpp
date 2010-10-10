//      samples.h
//      
//      Copyright 2010 Ilya <ilya@laptop>
//      
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; either version 2 of the License, or
//      (at your option) any later version.
//      
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//      
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//      MA 02110-1301, USA.


#ifndef _SAMPLES_H_
#define _SAMPLES_H_

#include <iostream>
#include <string>
#include <stdexcept>

struct fsm {  // Float mono sample
	int size; // count of elements
	float * data; // pointer to actual data
};

struct fsm * fsm_alloc(int size);
void fsm_free(struct fsm * _fsm);

struct ssm { // Short (16 bit) mono sample
	int size;
	short * data;
};

struct ssm * ssm_alloc(int size);
void ssm_free(struct ssm * _ssm);


#endif /* _SAMPLES_H_ */
