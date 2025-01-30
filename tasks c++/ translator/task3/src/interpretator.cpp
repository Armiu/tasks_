#include "interpretator.hpp"

void Interpretator::interpretation() {
    pars.analyze();
    Exec.execute(pars.prog, pars.recs);
}