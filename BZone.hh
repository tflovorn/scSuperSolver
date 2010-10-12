#ifndef __MFTS__BZONE_H
#define __MFTS__BZONE_H

#include "State.hh"

typedef double (*bzFunction)(const State&, double, double);

class BZone {
public:
    static double average(const State& st, bzFunction func);
    static double minimum(const State& st, bzFunction func);
};

#endif
