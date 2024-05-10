#include "Header.h"

void initialize_array(int n, vector<double>& a, vector<double>& b, vector<double>& c_result)
{
	for (int i = 0; i < n; i++) {
		a[i] = 1.2;
		b[i] = 2.8;
		c_result[i] = a[i] + b[i];
	}
}

void vector_add(sycl::queue& Q, int n, vector<double>& a, vector<double>& b, vector<double>& c)
{
	sycl::buffer a_buffer(a);
	sycl::buffer b_buffer(b);
	sycl::buffer c_buffer(c);
	auto task_add = Q.submit([&](sycl::handler& cgh) 
	{
		sycl::accessor a_accessor(a_buffer, cgh, sycl::read_only);
		sycl::accessor b_accessor(b_buffer, cgh, sycl::read_only);
		sycl::accessor c_accessor(c_buffer, cgh, sycl::write_only, sycl::no_init);
		cgh.parallel_for(sycl::range<1>(n), [=](sycl::id<1> idx) 
			{
			for(int j = 0; j < 36; j++)
				c_accessor[idx] = a_accessor[idx] + b_accessor[idx];
			});
		});
	task_add.wait();
}

int Test()
{
	sycl::queue Q;
	int n = 10000000;
	vector<double> a(n);
	vector<double> b(n);
	vector<double> c_result(n);
	vector<double> c(n);

	initialize_array(n, a, b, c_result);
	vector_add(Q, n, a, b, c);

	return 0;
}

int main(int argc, char* argv[])
{
	//Example();
	//Task();
	Task2();
	Task3();

	//Test();

	return 0;
}