#include <gtest/gtest.h>
#include <string>
#include <07/07.cpp>

TEST(output, compare)
{
	string s = "00000001This is REEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEaly LOOOOOOOOOOOOOOOOOOOOAOOOO\n00000002OOAng string And some moreThis is REEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEaly \n00000003LOOOOOOOOOOOOOOOOOOOOAOOOOOOAng string And some moresmlstring\n";
	
	const char longstring[] = "This is REEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEaly LOOOOOOOOOOOOOOOOOOOOAOOOOOOAng string And some more";
	stringbuf basicbuffer;
	outbuff mybuff(&basicbuffer);
	ostream simplestream(&mybuff);
	simplestream << longstring << longstring << "smlstring";
	mybuff.sync();
	string mystr = basicbuffer.str();
	ASSERT_TRUE(s == mystr);

}


int main(int argc, char *argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}