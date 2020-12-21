#include "Data.hpp"
#include "data_handler.hpp"

int main()
{
	srand(time(NULL));
	data_handler* dh = new data_handler();
	dh->read_feature_vector("./Data/train-images.idx3-ubyte");
	dh->read_feature_label("./Data/train-labels.idx1-ubyte");
	dh->split_data();
	dh->get_testing_data();
	dh->get_training_data();
	dh->get_validation_data();
	dh->count_classes();
}