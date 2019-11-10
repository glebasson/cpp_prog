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

int main(int argc, char *argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}