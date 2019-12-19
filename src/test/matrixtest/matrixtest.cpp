#include <gtest/gtest.h>
#include <string>
#include <matrix/matrix.cpp>


struct sym_param {
	std::vector<std::vector<float>> input;
	bool expected;
};

class matrix_test : public ::testing::TestWithParam<sym_param> {};

TEST_P(matrix_test, _) {
	const sym_param& param = GetParam();
	EXPECT_EQ(param.expected, Matrix<float>(param.input).is_symmetric(0.001));
}

INSTANTIATE_TEST_CASE_P(_, matrix_test, ::testing::Values(
	sym_param{{{1,2},{2,1}}, 1}
));

struct where_param {
	std::vector<std::vector<float>> inputA;
	std::vector<std::vector<float>> inputB;
	std::vector<std::vector<float>> expected;
};

class where_test : public ::testing::TestWithParam<where_param> {};

TEST_P(where_test, _) {
	const where_param& param = GetParam();
	Matrix<float> out = where((Matrix<float>(param.inputA) < Matrix<float>(param.inputB)), Matrix<float>(param.inputA), Matrix<float>(param.inputB));
	for (int i = 0; i < out.rows; ++i)
	{
		for (int j = 0; j < out.cols; ++j)
		{
			float t = out.data[i*out.cols + j];
			float tt = param.expected[i][j];
			EXPECT_EQ(tt, t);
		}
	}
}

INSTANTIATE_TEST_CASE_P(_, where_test, ::testing::Values(
	where_param{ {{1,2},{2,1}}, {{2,1},{1,2}}, {{1,1},{1,1}} }
));

int main(int argc, char *argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

