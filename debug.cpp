#include "stable.h"
#include "misc.h"
#include "graph.h"
#include "bmlrp.h"
#include "debug.h"

string Binary(Addr a, uchar n, bool format) {
    myassert(n <= sizeof(a)*8);

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

void PrintGraph(const Graph& g) {
    cout << g.n << " vertices:  ";

    for (auto it = g.edges.cbegin(); it != g.edges.cend(); ++it) {
        cout << it->first << "-" << it->second << " ";
    }

    cout << endl;
}
