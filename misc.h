#ifndef MISC_H
#define MISC_H

using namespace std;

typedef unsigned char uchar;

extern default_random_engine Gen;

string Binary(Addr a, uchar n = sizeof(Addr) * 8, bool format = true);

#endif // MISC_H
