//      samples.c
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


#include "samples.h"

struct fsm * fsm_alloc(int size) {
	struct fsm * _fsm;
	
	if (size <= 0) {
		std::string err = "Trying to allocate sample with 0 size";
		throw std::runtime_error(err);
	} else {
		_fsm = new fsm;
		_fsm->data = new float[size];
		_fsm->size = size;
		return _fsm;
	}
		
}
	
void fsm_free(struct fsm * _fsm) {
	if (_fsm != NULL) {
		if (_fsm->data != NULL)
			delete _fsm->data;
		else {
			std::string err = "fsm->data already freed";
			throw std::runtime_error(err);
		}
		delete _fsm;
	} else {
		std::string err = "fsm already freed";
		throw std::runtime_error(err);
	}
}
