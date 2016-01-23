#include <string>
#include <vector>
#include <set>
#include "bmlrp.h"
#include "misc.h"

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
