#include <iostream>
#include <streambuf>
#include <sstream>
#include <locale>
#include <cstdio>
#include <memory.h>

using namespace std;

class outbuff : public streambuf {
  private:
  streambuf* destbuf;
  int lc;
  char buff[81];

  public:
  int overflow(int ch) override {
    ++lc;
    ostringstream temp;
    temp.width(8);
    temp.fill('0');
    temp << lc;
    memcpy(buff, string(temp.str()).data(), 8);
    buff[79] = ch;
    destbuf->sputn(buff, 81);
    pbump(-71);
    return(ch);
  }

  int sync() override {
    if (pptr() == pbase()) return 0;
    ptrdiff_t sz = pptr() - pbase();
    ++lc;
    ostringstream temp;
    temp.width(8);
    temp.fill('0');
    temp << lc;
    memcpy(buff, string(temp.str()).data(), 8);
    destbuf->sputn(buff, 8 + sz);
    destbuf->sputc('\n');
    pbump(-sz);
    return 0;
  }

  outbuff(streambuf* _destbuf): destbuf(_destbuf){
    lc = 0;
    buff[80] = '\n';
    setp(&buff[8], &buff[79]);
  }
  
};

// int main() {
//   const char longstring[] = "This is REEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEaly LOOOOOOOOOOOOOOOOOOOOAOOOOOOAng string And some more";
//   stringbuf basicbuffer;
//   outbuff mybuff(&basicbuffer);
//   ostream simplestream(&mybuff);
//   simplestream << longstring << longstring << "smlstring";
//   mybuff.sync();
//   string s = basicbuffer.str();
//   cout << s;
  
// }