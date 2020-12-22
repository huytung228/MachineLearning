#pragma once
#ifndef __DATA_HANDLER__
#define __DATA_HANDLER__

#include <iostream>
#include "Data.hpp"
#include <vector>
#include <map>
#include <cstdio>

class data_handler {
	std::vector<data*>* data_array;
	std::vector<data*>* traninng_array;
	std::vector<data*>* validation_array;
	std::vector<data*>* test_array;

	uint8_t num_classes;
	int feature_vector_size;
	std::map<uint8_t, int> class_map;

	int data_size; // number of images
	const double TRAINING_SET_PERCENT = 0.8;
	const double TETS_SET_PERCENT = 0.15;
	const double VALIDATION_SET_PERCENT = 0.05;

public:
	data_handler();
	~data_handler();

	void read_feature_vector(std::string path);
	void read_feature_label(std::string path);

	void split_data();
	void count_classes();

	uint32_t convert_to_little_endian(const uint8_t* bytes);
	std::vector<data*>* get_training_data();
	std::vector<data*>* get_testing_data();
	std::vector<data*>* get_validation_data();
};

#endif // !__DATA_HANDLER__

