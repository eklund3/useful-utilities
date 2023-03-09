#ifndef ALGLIBADAPTER_H
#define ALGLIBADAPTER_H

#include "alglib/interpolation.h"

class AlglibAdapter
{
public:
    AlglibAdapter(alglib::spline1dinterpolant s) : m_s(s) {};
    const alglib::spline1dinterpolant m_s;
    double operator() (double x) const {
        return alglib::spline1dcalc(m_s, (double)x);
    }
};

#endif // ALGLIBADAPTER_H
