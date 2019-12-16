#include <sstream>
#include <fstream>
#include <iostream>
#include <streambuf>
#include <cctype>

using namespace std;

class wcstream : public streambuf {
    public:
    wcstream(streambuf *_old) : old(_old){}
    long int nchar=0, nline=0, nword=0;
    char prev = -1;

    int underflow() {
        int result = EOF;
        if ( gptr() < egptr() ) { // do not call ever in fact
            result = *gptr();
        }
        else {
            result = old->sbumpc();
            if( result != EOF ) {
                ++nchar;
                if(result == '\n') ++nline;
                if(isalnum(result) && (prev == -1 || isblank(prev) || prev == '\n')) ++nword;
                buf = result;
                setg( &buf , &buf , &buf + 1 );
                prev = result;
            }
        }
        return result;
    }

    private:
    char buf;
    streambuf *old;
};

int main() {
    wcstream mybuf(cin.rdbuf());
    cin.rdbuf(&mybuf);
    std::string line;
    while (std::getline(std::cin, line)){
    }
    cout << mybuf.nline << " " << mybuf.nword << " " << mybuf.nchar;
    return(0);
}