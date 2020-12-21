#pragma warning (disable : 4996)
#include "data_handler.hpp"
#include <unordered_set>

data_handler::data_handler()
{
	data_array = new std::vector<data*>;
	traninng_array = new std::vector<data*>;
	test_array = new std::vector<data*>;
	validation_array = new std::vector<data*>;
};
void data_handler::read_feature_vector(std::string path)
{
	uint32_t header[4];
	uint8_t bytes[4];
	FILE* f = fopen(path.c_str(), "r");
	if (f)
	{
		for (size_t i = 0; i < 4; i++)
		{
			if (fread(bytes, sizeof(bytes), 1, f))
			{
				header[i] = convert_to_little_endian(bytes);
 			}
		}
		printf("Done getting header data \n");
		int image_size = header[2] * header[3];

		// Loop through each image
		for (size_t i = 0; i < header[1]; i++)
		{
			data *d = new data();
			uint8_t element[1];
			// Read each bytes of an image
			for (size_t j = 0; j < image_size; j++)
			{
				if (fread(element, sizeof(element), 1, f))
				{
					d->append_to_feature_vector(element[0]);
				}
				else
				{
					printf("Error in reading from file\n");
					exit(1);
				}
			}
			data_array->push_back(d);
		}
		data_size = data_array->size();
		printf("Successfully read and stored %lu feature vectors.\n", data_array->size());
	}
	else
	{
		printf("File dose not exist! %d %s\n", __LINE__, __func__);
		exit(1);
	}
};
void data_handler::read_feature_label(std::string path)
{
	uint32_t header[2];
	uint8_t bytes[4];
	FILE* f = fopen(path.c_str(), "r");
	if(f)
	{
		for (size_t i = 0; i < 2; i++)
		{
			if (fread(bytes, sizeof(bytes), 1, f))
			{
				header[i] = convert_to_little_endian(bytes);
			}
		}
		printf("Done getting header label \n");

		// Loop through number of images
		uint8_t element[1];

		for (size_t i = 0; i < header[1]; i++)
		{
			if (fread(element, sizeof(element), 1, f))
			{
				data_array->at(i)->set_label(element[0]);
			}
			else
			{
				printf("Error in reading from file\n");
			}
		}

		printf("Done read and stored label\n");
	}
	else
	{
		printf("File dose not exist \n");
	}

};

void data_handler::split_data()
{
	int training_size = data_size * TRAINING_SET_PERCENT;
	int test_size = data_size * TETS_SET_PERCENT;
	int valid_size = data_size * VALIDATION_SET_PERCENT;

	std::unordered_set<int> used_indexes; // use un ordered set for shuffle

	// Training data
	int count = 0;
	while (count < training_size)
	{
		int rand_index = rand() % data_size; // rand_index from 0 to data_size -1
		if (used_indexes.find(rand_index) == used_indexes.end()) // Cant find rand_index in used_indexes
		{
			traninng_array->push_back(data_array->at(rand_index));
			used_indexes.insert(rand_index);
		}
		count++;
	}

	// Test data
	count = 0;
	while (count < test_size)
	{
		int rand_index = rand() % data_size; // rand_index from 0 to data_size -1
		if (used_indexes.find(rand_index) == used_indexes.end()) // Cant find rand_index in used_indexes
		{
			test_array->push_back(data_array->at(rand_index));
			used_indexes.insert(rand_index);
		}
		count++;
	}

	// validation data
	count = 0;
	while (count < valid_size)
	{
		int rand_index = rand() % data_size; // rand_index from 0 to data_size -1
		if (used_indexes.find(rand_index) == used_indexes.end()) // Cant find rand_index in used_indexes
		{
			validation_array->push_back(data_array->at(rand_index));
			used_indexes.insert(rand_index);
		}
		count++;
	}

	printf("Training size:%d, Testing size:%d, Valid size:%d \n", traninng_array->size(), test_array->size(), validation_array->size());
};
void data_handler::count_classes()
{
	int count = 0;
	for (size_t i = 0; i < data_size; i++)
	{
		if (class_map.find(data_array->at(i)->get_label()) == class_map.end()) // Khong tim thay
		{
			class_map[data_array->at(i)->get_label()] = count;
			data_array->at(i)->set_enumerate_label(count);
			count++;
		}
	}
	num_classes = count;
	printf("Successfully extracted %u classes \n", num_classes);
};

uint32_t data_handler::convert_to_little_endian(const uint8_t* bytes)
{
	return (uint32_t)(bytes[0] << 24 | bytes[1] << 16 | bytes[2] << 8 | bytes[3]);
};
std::vector<data*>* data_handler::get_training_data()
{
	return traninng_array;
};
std::vector<data*>* data_handler::get_testing_data()
{
	return test_array;
};
std::vector<data*>* data_handler::get_validation_data()
{
	return validation_array;
};