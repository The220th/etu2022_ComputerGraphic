#ifndef cacheBCR_H
#define cacheBCR_H

#include <cstdlib>

class CacheBCR
{
    private:
    const size_t N_MAX;
    const size_t K_MAX;

    size_t **bcr_cache;

    public:
    CacheBCR(std::size_t n_max, std::size_t k_max);
    ~CacheBCR();

    /* k               n!
      C = C(n, k) = ------
       n             k! (n-k)!
    */
    size_t get_bcr(std::size_t n, std::size_t k);
};

#endif // cacheBCR_H
