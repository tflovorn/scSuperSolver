/*
  Copyright (c) 2010 Timothy Lovorn

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/

#include "BZone.hh"

// Would be nice to have a single function handle transforming one BZone point
// into another instead of duplicating the traversal

double BZone::minimum(const State& st, bzFunction func) {
    double kx = -M_PI, ky = -M_PI, min = DBL_MAX, val;
    int N = st.env.gridLen;
    double step = 2 * M_PI / N;
    while (ky < M_PI) {
        while (kx < M_PI) {
            val = func(st, kx, ky);
            if (val < min) {
                min = val;
            }      
            kx += step;      
        }
        ky += step;
        kx = -M_PI;
    }
    return min;
}

double BZone::average(const State& st, bzFunction func) {
    double kx = -M_PI, ky = -M_PI, min = DBL_MAX, sum = 0.0;
    int N = st.env.gridLen;
    double step = 2 * M_PI / N;
    while (ky < M_PI) {
        while (kx < M_PI) {
            sum += func(st, kx, ky);
            kx += step;      
        }
        ky += step;
        kx = -M_PI;
    }
    return sum / (N * N);
}
