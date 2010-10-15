#include <gsl/gsl_errno.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_roots.h>

#include "RootFinder.hh"

RootData::RootData(bool cvg, double rt, double fnv) :
    converged(cvg), root(rt), fnvalue(fnv) 
{ }

RootFinder::RootFinder(double (* const helper)(double, void *), 
    void * const params, const double guess, const double min, 
    const double max, const double tolerance) : 
    myHelper(helper), myParams(params), myGuess(guess), myMin(min), myMax(max), 
    myTolerance(tolerance) 
{ }

// Lots of code cribbed from GSL documentation
// http://www.gnu.org/software/gsl/manual/html_node/Root-Finding-Examples.html

const RootData& RootFinder::findRoot() {
    int status;
    int iter = 0, max_iter = RF_MAX_ITER;
    bool converged = true;
    const gsl_root_fsolver_type *T;
    gsl_root_fsolver *s;
    double r = myGuess;
    double x_lo = myMin, x_hi = myMax;
    gsl_function F;
    
    F.function = myHelper;
    F.params = myParams;

    T = gsl_root_fsolver_brent;
    s = gsl_root_fsolver_alloc(T);
    gsl_root_fsolver_set(s, &F, x_lo, x_hi);

    do {
        iter++;
        status = gsl_root_fsolver_iterate(s);
        r = gsl_root_fsolver_root(s);
        x_lo = gsl_root_fsolver_x_lower(s);
        x_hi = gsl_root_fsolver_x_upper(s);
        status = gsl_root_test_interval(x_lo, x_hi, 0.0, myTolerance);
    } while (status == GSL_CONTINUE && iter < max_iter);

    gsl_root_fsolver_free(s);    
    
    if (iter > max_iter || status != GSL_SUCCESS) {
        converged = false;
    }

    RootData const *rdata = new RootData(converged, r, myHelper(r, myParams));
    return (const RootData&)(*rdata);
}
