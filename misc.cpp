#include "stable.h"
#include "myassert.h"
#include "graph.h"
#include "bmlrp.h"
#include "misc.h"

default_random_engine Gen(0xABCD2345);

string Binary(Addr a, char n, bool format) {
    string res;
    for (char i = 0; i < n; ++i) {
        if (format && (i != 0) && (i % 4 == 0)) {
            res += ' ';
        }
        if (a & FirstBit) {
            res += '1';
        } else {
            res += '0';
        }

        a <<= 1;
    }

    return res;
}
