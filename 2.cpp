#include <iostream>
#include <string>
template <class T_Vector>
class Vector2D
{
public:
	T_Vector x_, y_;

	Vector2D(const T_Vector& x_input, const T_Vector& y_input)
		: x_(x_input), y_(y_input)
	{}

	void print() {
		std::cout << x_ << " " << y_ << std::endl;
	}

};
int main()
{
	Vector2D<int> int_vector(1, 1);
	int_vector.print();

	Vector2D<float> float_vector(1.6f, 3.8f);
	float_vector.print();

	Vector2D<double> double_vector(3.1, 2.2);
	double_vector.print();


	return 0;
}