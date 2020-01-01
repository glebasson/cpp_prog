#include <gtest/gtest.h>
#include <10/rotate.cpp>
#include <utility>

template<typename T> using P = std::pair<T, T>;
template<typename T>
::testing::AssertionResult EQ_Pair(P<T> v1, P<T> v2)
{
	if (v1.first == v2.first && v1.second == v2.second)
		return ::testing::AssertionSuccess();
	else
		return ::testing::AssertionFailure() << v1.first << " " << v1.second 
			<< " != " << v2.first << " " << v2.second;
}

// typedef std::pair<int, int> P;

TEST(rotate, coverage)
{
	// EXPECT_TRUE(d[i] == q[i]);
	P<int> v(1,2);
	EXPECT_TRUE(EQ_Pair(rotate(v, 360), P<int>(1, 2)));
	EXPECT_TRUE(EQ_Pair(rotate(v, 180), P<int>(-1, -2)));
	EXPECT_TRUE(EQ_Pair(rotate(v, 90), P<int>(-2, 1)));
	EXPECT_TRUE(EQ_Pair(rotate(v, -90), P<int>(2, -1)));
	v = P<int>(-1, 2);
	EXPECT_TRUE(EQ_Pair(rotate(v, 90), P<int>(-2, -1)));
	EXPECT_TRUE(EQ_Pair(rotate(v, -90), P<int>(2, 1)));
	v = P<int>(-1, 2);
	EXPECT_TRUE(EQ_Pair(rotate(v, -90), P<int>(2, 1)));
	EXPECT_TRUE(EQ_Pair(rotate(v, 90), P<int>(-2, -1)));
	v = P<int>(1, 0);
	EXPECT_TRUE(EQ_Pair(rotate(v, 90), P<int>(0, 1)));
	EXPECT_TRUE(EQ_Pair(rotate(v, -90), P<int>(0, -1)));
	v = P<int>(0, 1);
	EXPECT_TRUE(EQ_Pair(rotate(v, 90), P<int>(-1, 0)));
	EXPECT_TRUE(EQ_Pair(rotate(v, -90), P<int>(1, 0)));

}

int main(int argc, char *argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}