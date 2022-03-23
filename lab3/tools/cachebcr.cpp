
#include <string>
#include <cstdlib>

#include "../include/cachebcr.h"

using namespace std;

CacheBCR::CacheBCR(size_t n_max, size_t k_max) : N_MAX(n_max), K_MAX(k_max)
{
    bcr_cache = new size_t*[N_MAX];
    for(size_t i = 0; i < N_MAX; ++i)
        bcr_cache[i] = new size_t[K_MAX];
    for(size_t i = 0; i < N_MAX; ++i)
        for(size_t j = 0; j < K_MAX; ++j)
            bcr_cache[i][j] = 0;
}

CacheBCR::~CacheBCR()
{
    for(size_t i = 0; i < N_MAX; ++i)
        delete bcr_cache[i];
    delete bcr_cache;
}


size_t CacheBCR::get_bcr(size_t n, size_t k)
{
    // https://habr.com/ru/post/274689/comments/#comment_8730359
    // https://www.wolframalpha.com/input?i=Binomial%5B15%2C+05%5D

    if(n >= N_MAX)
        throw string("") + "n=" + std::to_string(n) + " more or equals, than N_MAX=" + std::to_string(N_MAX) + ". ";
    if(k >= K_MAX)
        throw string("") + "k=" + std::to_string(k) + " more or equals, than K_MAX=" + std::to_string(K_MAX) + ". ";

    /*if(k == 1)
        return n;
    if(k == 0) // WTF. Always FALSE?!
        return 1;
    if(n == 0)
        return 0;
    if(k > n/2)
        k = n - k;*/
	if (k>n/2) k=n-k;
	if (k==1)  return n;
	if (k==0)  return 1;

    if (bcr_cache[n][k] == 0)
        bcr_cache[n][k] = get_bcr(n-1, k) + get_bcr(n-1, k-1);
    return bcr_cache[n][k];
}
