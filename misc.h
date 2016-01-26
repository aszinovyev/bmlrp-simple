#ifndef MISC_H
#define MISC_H

using namespace std;

extern default_random_engine Gen;

string Binary(Addr a, char n = sizeof(Addr) * 8, bool format = true);

#endif // MISC_H
