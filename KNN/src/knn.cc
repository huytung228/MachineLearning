#include "knn.hpp"
#include <cmath>
#include <utility>      // std::pair, std::make_pair
#include <algorithm>    // std::sort
#include <map>

Knn::Knn()
{
	// DO NOTHING
};
Knn::Knn(uint32_t val) 
{
	k = val;
};

Knn::~Knn()
{
	//DO NOTHING
};

void Knn::set_k(uint32_t val)
{
	k = val;
}

void Knn::set_training_data(std::vector<data*> *vect)
{
	training_data = vect;
};

void Knn::set_testing_data(std::vector<data*>* vect)
{
	testing_data = vect;
};
void Knn::set_validation_data(std::vector<data*> *vect)
{
	validation_data = vect;
};

double Knn::calculate_distance(data* query_point, data* input)
{
	double distance = 0.0;
	uint32_t query_point_size = query_point->get_feature_vector_size();
	uint32_t input_size = input->get_feature_vector_size();

	if (query_point_size != input_size)
	{
		printf("[%s][%d] Error length of 2 vector diff: %d vs %d \n", __func__, __LINE__, query_point_size, input_size);
	}
	else
	{
		for (size_t i = 0; i < query_point_size; i++)
		{
			distance += pow(query_point->get_feature_vector()->at(i) - input->get_feature_vector()->at(i), 2);
		}
		distance = sqrt(distance);
	}
	return distance;
};
void Knn::find_k_nearest(data* query_point)
{
	std::vector<std::pair<double, uint32_t>> distances; // list include distances from current node to all rest nodes
	neighbors = new std::vector<data*>; // list of k nearest neighbors

	double dis = 0.0; // dis between 2 point

	for (size_t i = 0; i < training_data->size(); i++)
	{
		dis = calculate_distance(query_point, training_data->at(i));
		distances.push_back(std::make_pair(dis, i));
	}

	std::sort(distances.begin(), distances.end());

	for (size_t i = 0; i < k; i++)
	{
		neighbors->push_back(training_data->at(distances[i].second));
	}
	printf("[%s][%d] Successfully find k:%u nearest neighbors\n", __func__, __LINE__, neighbors->size());
};
int Knn::predict()
{
	std::map<uint8_t, uint8_t> class_freq;
	uint8_t label;
	for (size_t i = 0; i < neighbors->size(); i++)
	{
		label = neighbors->at(i)->get_label();
		if (class_freq.find(label) == class_freq.end())
		{
			class_freq[label] = 1;
		}
		else
		{
			class_freq[label] ++;
		}
	}
	
	int best = 0;
	int max = 0;

	for (auto kv : class_freq)
	{
		if (kv.second > max)
		{
			max = kv.second;
			best = kv.first;
		}
	}
	return best;
};

double Knn::validation_performance()
{
	uint8_t label_predict;
	uint32_t count_accuracy;
	for (data* query_point : * validation_data)
	{
		find_k_nearest(query_point);
		label_predict = predict();
		if (label_predict == query_point->get_label())
		{
			count_accuracy++;
		}
	}
	printf("[%s][%d] Validation accuray k:%u %.3f \n", k, ((double)(count_accuracy*100)) / validation_data->size());
	return ((double)(count_accuracy * 100)) / validation_data->size();
};
double Knn::test_performance()
{
	uint8_t label_predict;
	uint32_t count_accuracy;
	for (data* query_point : *testing_data)
	{
		find_k_nearest(query_point);
		label_predict = predict();
		if (label_predict == query_point->get_label())
		{
			count_accuracy++;
		}
	}
	printf("[%s][%d] Test accuray k:%u %.3f \n", k, ((double)(count_accuracy * 100)) / testing_data->size());
	return ((double)(count_accuracy * 100)) / testing_data->size();
};