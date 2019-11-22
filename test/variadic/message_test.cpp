#include <gtest/gtest.h>
#include <string>
#include <variadic/variadic.cpp>

// int main() {
// 	std::stringstream ss;
// 	message(ss, "My name is %, Age = %, and this is just percents %%%%%", "Gleb", 21);
// 	EXPECT_EQ("My name is Gleb, Age = 21, and this is just percents %%%%%", ss.str());
// }

TEST(message, compare)
{
	std::stringstream ss;
	message(ss, "My name is %, Age = %, and this is just percents %%%%%", "Gleb", 21);
	EXPECT_EQ("My name is Gleb, Age = 21, and this is just percents %%%%%", ss.str());
}

TEST(cat, compare)
{
	std::array<int, 3> a = { 1, 2, 3};
	std::array<int, 3> b = { 1, 2, 3};
	std::array<int, 3> c = { 5, 6, 8};
	std::array<int, 9> d = cat(a, b, c);
	std::array<int, 9> q = {1, 2, 3, 1, 2, 3, 5, 6, 8};
	for(int i=0; i<d.size(); i++) {
		EXPECT_TRUE(d[i] == q[i]);
	}
}

TEST(tie, compare)
{
	std::array<int, 3> q = { 1, 2, 3};
	std::array<int, 3> w = { 1, 2, 3};
	std::array<int, 3> e = { 5, 6, 8};
	std::array<int, 3> a = { 1, 2, 3};
	std::array<int, 3> b = { 1, 2, 3};
	std::array<int, 3> c = { 5, 6, 8};
	tie(q, w, e) = cat(a, b, c);
	for(int i=0; i<q.size(); ++i) {
		EXPECT_TRUE(a[i] == q[i]);
	}
	for(int i=0; i<w.size(); ++i) {
		EXPECT_TRUE(b[i] == w[i]);
	}
	for(int i=0; i<e.size(); ++i) {
		EXPECT_TRUE(c[i] == e[i]);
	}
}

int main(int argc, char *argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}