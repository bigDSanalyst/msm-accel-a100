#ifndef ZK_BLS_PUB_H
#define ZK_BLS_PUB_H

#include <stdint.h>

#if defined(_MSC_VER)
  #define ZK_EXPORT __declspec(dllexport)
#else
  #define ZK_EXPORT __attribute__((visibility("default")))
#endif

#ifdef __cplusplus
extern "C" {
#endif

struct Fp {
    uint64_t limbs[6];
};

struct FpPoint {
    Fp X;
    Fp Y;
    Fp Z;
};

struct Scalar381 {
    uint64_t limbs[6];
};

ZK_EXPORT void pippenger_msm_kernel(
    FpPoint *d_result_windows, 
    const FpPoint *d_points, 
    const Scalar381 *d_scalars, 
    int num_points,
    int window_bits,
    int total_windows
);

#ifdef __cplusplus
}
#endif

#endif // ZK_BLS_PUB_H
