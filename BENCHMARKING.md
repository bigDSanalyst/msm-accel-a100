# Reproducibility and Benchmarking Methodology

This document outlines the exact methodology used to benchmark the `libzk_bls_accel` multi-scalar multiplication (MSM) kernel against Ingonyama's ICICLE (v2.x) library.

## Hardware and Environment
* **GPU:** NVIDIA A100 80GB SXM4
* **CUDA Version:** 12.x
* **Host Environment:** Ubuntu Linux (Google Colab / Dedicated instance)

## Methodology
To ensure a rigorous and scientifically valid head-to-head comparison, all benchmarks adhere to the following constraints:
1. **Deterministic Inputs:** Both libraries operate on identical pseudo-randomly generated scalars and BLS12-381 curve points, seeded via `numpy.random.seed()`.
2. **Isolated Timing:** Measurements are captured using high-resolution CUDA events. The recorded latencies represent **pure kernel execution time** and strictly exclude Host-to-Device (H2D) and Device-to-Host (D2H) memory transfer overhead.
3. **Consistent Window Sizing:** Both implementations utilize a 4-bit Pippenger window parameter.
4. **Statistical Smoothing:** Reported latencies and throughput metrics represent the median over 10 consecutive iterations to eliminate system jitter.

## Execution
To reproduce the scaling suite and head-to-head metrics locally, execute the provided Python test harness:

```bash
cd benchmarks/
python compare_icicle.py
```

## Compilation Flags
The `libzk_bls_accel.so` shared library was compiled using `nvcc` with the following baseline optimizations:
`-O3 -arch=sm_80 --use_fast_math -Xptxas -O3,-v`