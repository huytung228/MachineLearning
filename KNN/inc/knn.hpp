#pragma once
#ifndef __KNN__
#define __KNN__

#include <iostream>
#include <vector>
#include "Data.hpp"

class Knn
{
private:
	uint32_t k; // k nearest neighbors
	std::vector<data*>* neighbors;
	std::vector<data*>* training_data;
	std::vector<data*>* testing_data;
	std::vector<data*>* validation_data;

public:
	Knn();
	Knn(uint32_t);
	~Knn();

	void set_training_data(std::vector<data*>* vect);
	void set_testing_data(std::vector<data*>* vect);
	void set_validation_data(std::vector<data*>* vect);

	int predict();
	double calculate_distance(data* query_point, data* input);
	void find_k_nearest(data* query_point);
	double validation_performance();
	double test_performance();
	void set_k(uint32_t);
};

Knn::Knn()
{
}

Knn::~Knn()
{
}

#endif // !__KNN__

