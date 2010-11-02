#include <gsl/gsl_errno.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_min.h>

#include "Minimizer.hh"

MinimumData::MinimumData(bool cvg, double min, double fnv) :
    converged(cvg), x_min(min), fnvalue(fnv) 
{ }

Minimizer::Minimizer(double (* const helper)(double, void *), 
    void * const params, const double guess, const double range_min, 
    const double range_max, const double tolerance) : 
    myHelper(helper), myParams(params), myGuess(guess), myRangeMin(range_min), 
    myRangeMax(range_max), myTolerance(tolerance) 
{ }

// Lots of code cribbed from GSL documentation
// http://www.gnu.org/software/gsl/manual/html_node/Root-Finding-Examples.html

const MinimumData& Minimizer::findMinimum() {
    int status;
    int iter = 0, max_iter = MINIMIZER_MAX_ITER;
    bool converged = true;
    const gsl_min_fminimizer_type *T;
    gsl_min_fminimizer *s;
    double m = myGuess;
    double x_lo = myRangeMin, x_hi = myRangeMax;
    gsl_function F;
    
    F.function = myHelper;
    F.params = myParams;

    T = gsl_min_fminimizer_brent;
    s = gsl_min_fminimizer_alloc(T);
    gsl_min_fminimizer_set(s, &F, m, x_lo, x_hi);

    do {
        iter++;
        status = gsl_min_fminimizer_iterate(s);
        m = gsl_min_fminimizer_minimum(s);
        x_lo = gsl_min_fminimizer_x_lower(s);
        x_hi = gsl_min_fminimizer_x_upper(s);
        status = gsl_min_test_interval(x_lo, x_hi, 0.0, myTolerance);
    } while (status == GSL_CONTINUE && iter < max_iter);

    gsl_min_fminimizer_free(s);
    
    if (iter >= max_iter || status != GSL_SUCCESS) {
        converged = false;
    }

    MinimumData const *mdata = new MinimumData(converged, m, 
                                               myHelper(m, myParams));
    return (const MinimumData&)(*mdata);
}
