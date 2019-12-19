#include <iostream>
#include <vector>

struct MyGuard {
	std::ostream& _x;
	std::ios_base::fmtflags oldflags;
	char oldfill;
	std::iostream::iostate oldexc;

	MyGuard(std::ostream& x) : _x(x) {
		oldflags = _x.flags();
		oldfill = _x.fill();
		oldexc = _x.exceptions();
	}

	~MyGuard() {
		_x.setf(oldflags);
		_x.fill(oldfill);
		_x.exceptions(oldexc);
	}
};

void print_hex(int i) {
	MyGuard g(std::cout);
	std::cout.setf(std::ios_base::hex, std::ios_base::basefield);
	std::cout << i << "\n";
	//или std::cout << std::hexstd::cout << i;4
}

template <typename T>
class Matrix {
public:
	std::vector<T> data;
	int rows;
	int cols;

	Matrix(std::vector<std::vector<T>> d) {
		rows = d.size();
		cols = d[0].size();
		data = std::vector<T>(rows*cols);
		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < cols; ++j)
			{
				data[i*cols + j] = d[i][j];
			}
		}
	}

	Matrix() {}
	Matrix(int r, int c) {
		data = std::vector<T>(r*c);
		rows = r;
		cols = c;
	}

	Matrix<T> abs() {
		Matrix<T> out(rows, cols);
		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < cols; ++j)
			{
				out.data[i*cols + j] = std::abs(data[i*cols + j]);
			}
		}
		return(out);
	}

	Matrix<T> transpose() {
		Matrix<T> out(cols, rows);
		for (int i = 0; i < cols; ++i)
		{
			for (int j = 0; j < rows; ++j)
			{
				out.data[i*rows + j] = data[j*cols + i];
			}
		}
		return(out);
	}

	bool all() {
		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < cols; ++j)
			{
				if(!data[i*cols + j]) return(false);
			}
		}
		return(true);
	}

	Matrix<bool> operator<(const Matrix& m) {
		Matrix<bool> out(rows, cols);
		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < cols; ++j)
			{
				out.data[i*cols + j] = data[i*cols + j] < m.data[i*cols + j];
			}
		}
		return(out);
	}

	Matrix<bool> operator<(const float& e) {
		Matrix<bool> out(rows, cols);
		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < cols; ++j)
			{
				out.data[i*cols + j] = data[i*cols + j] < e;
			}
		}
		return(out);
	}

	Matrix<bool> operator-(const Matrix& m) {
		Matrix<bool> out(rows, cols);
		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < cols; ++j)
			{
				out.data[i*cols + j] = data[i*cols + j] - m.data[i*cols + j];
			}
		}
		return(out);
	}

	void print() {
		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < cols; ++j)
			{
				std::cout << data[i * cols + j] << " ";
			}
			std::cout << "\n";
		}
	}

	bool is_symmetric(float eps) {
		return ((*this - this->transpose()).abs() < eps).all();
	}


};

template<typename T>
Matrix<T> where(Matrix<bool> out, const Matrix<T>& a, const Matrix<T>& b) {
	int rows = a.rows;
	int cols = a.cols;
	Matrix<T> prod(rows, cols);
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			if (out.data[i*cols + j]) prod.data[i*cols + j] = a.data[i*cols + j];
			else prod.data[i*cols + j] = b.data[i*cols + j];
		}
	}
	return(prod);
}


// int main() {
// 	typedef float T;

// 	std::vector<std::vector<T>> ad = {{1,2,3},{4,5,6},{7,8,9}};
// 	std::vector<std::vector<T>> bd = {{9,8,7},{6,5,4},{1,2,3}};
// 	Matrix<T> a(ad), b(bd);
// 	a.print();
// 	// c.print();
// 	// b.print();
// 	// // a < b;
// 	// // Matrix<bool> k = 
// 	Matrix<T> c = where(a < b, a, b);
// 	c.print();

// 	Matrix<T> d({{1, 2}, {2, 1}});
// 	std::cout << d.is_symmetric(0.001) << "\n";
// 	return(0);
// }