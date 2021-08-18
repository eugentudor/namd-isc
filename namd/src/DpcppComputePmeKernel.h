#ifdef NAMD_DPCPP
#include <CL/sycl.hpp>
#include <dpct/dpct.hpp>

#ifndef CL_SYCL_LANGUAGE_VERSION
#undef __align__
#define __align__(X)
#endif

void dpcpp_init_bspline_coeffs(float **c, float **dc, int order, sycl::queue &queue);

#define DPCPP_PME_CHARGES_PROTOTYPE                                             \
template <int order>                                                            \
void dpcpp_pme_charges(const float *coeffs, float *const *q_arr, int *f_arr,    \
    int *fz_arr, float *a_data, int n_atoms, int K1, int K2,                    \
    int K3, sycl::queue& queue)

DPCPP_PME_CHARGES_PROTOTYPE;

#define DPCPP_PME_CHARGES_BATCHED_PROTOTYPE                                     \
void dpcpp_pme_charges_batched(                                                 \
    const float *coeffs, float *const *q_arr, int *f_arr, int *fz_arr,          \
    float **a_data_ptr, int *n_atoms_ptr, int *K1_ptr, int *K2_ptr,             \
    int *K3_ptr, int order, int numPatches, int n_max_atoms,                    \
    sycl::queue& queue)

DPCPP_PME_CHARGES_BATCHED_PROTOTYPE;

#define DPCPP_PME_FORCES_PROTOTYPE                                              \
template <int order>                                                            \
void dpcpp_pme_forces(                                                          \
    const float *coeffs, float *const *q_arr, float *const *afn, int dimy,      \
    int maxn, int K1, int K2, int K3, sycl::queue& queue)

DPCPP_PME_FORCES_PROTOTYPE;

#endif // NAMD_DPCPP

