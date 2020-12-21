#include "Data.hpp"
#include "data_handler.hpp"

int main()
{
	data_handler* dh = new data_handler();
	dh->read_feature_vector("./Data/train-images.idx3-ubyte");
	dh->count_classes();
}