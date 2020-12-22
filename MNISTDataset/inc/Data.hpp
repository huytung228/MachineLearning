#pragma once
#ifndef __DATA_H__
#define __DATA_H__

#include <vector>
#include <iostream>
#include <stdint.h>

class data
{
public:
	data();
	~data();
	void set_feature_vector(std::vector<uint8_t>*);
	void append_to_feature_vector(uint8_t);
	void set_label(uint8_t);
	void set_enumerate_label(int);

	int get_feature_vector_size();
	uint8_t get_label();
	uint8_t get_enumerate_label();

	std::vector<uint8_t> * get_feature_vector();

private:
	std::vector<uint8_t>* feature_vector;
	uint8_t label;
	int enum_label;
};

#endif // !__DATA_H__
