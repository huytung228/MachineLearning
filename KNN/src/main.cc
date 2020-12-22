#include "knn.hpp"
#include "data_handler.hpp"

int main()
{
	data_handler* dh = new data_handler();
	dh->read_feature_vector("../../MNISTDataset/Data/train-images.idx3-ubyte");
	dh->read_feature_label("../../MNISTDataset/Data/train-labels.idx1-ubyte");
	dh->split_data();

	Knn* knn = new Knn(3);
	knn->set_training_data(dh->get_training_data());
	knn->set_testing_data(dh->get_testing_data());
	knn->set_validation_data(dh->get_validation_data());
	knn->set_k(3);
	double performance = knn->validation_performance();
	printf("FINAL PERFORMANCCE : %.3f \n", performance);
}