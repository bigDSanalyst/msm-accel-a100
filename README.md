# msm-accel-a100

A hardware-accelerated C++/CUDA implementation of Pippenger's algorithm for multi-scalar multiplication (MSM) over the BLS12-381 elliptic curve. This library is optimized specifically to maximize L2 cache residency and memory bandwidth saturation on NVIDIA A100 GPUs.

---

## Requirements

* **Hardware:** NVIDIA GPU with Compute Capability 8.0 (Ampere / A100 80GB SXM4) or higher.
* **CUDA Toolkit:** Version 11.8 or later (`nvcc`).
* **Host Compiler:** GCC/G++ 9 or later.
* **Python Runtime:** Python 3.8+ with `numpy`.

---

## Repository Structure

* `bls12_381_master.cu` / `bls12_381_common.h`: Core CUDA kernels and internal struct definitions.
* `zk_bls_pub.h`: Public C++ API header.
* `build/libzk_bls_accel.so`: Compiled shared library for C++ and Python bindings.
* `benchmarks/`: Python test harness (`compare_icicle.py`) for deterministic input scaling and isolated CUDA event timing.
* `BENCHMARKING.md`: Methodology and execution specifications for empirical reproducibility.
* `epaper/`: LaTeX manuscript (`main.tex`) detailing the hardware architecture and performance analysis.

---

## Empirical Performance

The kernel maintains linear throughput scaling up to $N = 2^{22}$ points, holding a stable throughput of **11.55 M pts/s**. At $N = 2^{23}$ points (exceeding 1.5 GB in total point/scalar memory footprint), the memory bandwidth bounds result in a minor latency increase while sustaining **10.90 M pts/s**.

### Scaling Suite (NVIDIA A100 80GB SXM4, 4-bit window)

| Points (N) | Latency (ms) | Throughput (M pts/s) |
| :--- | :--- | :--- |
| $2^{16}$ (65,536) | 5.673 | **11.55** |
| $2^{18}$ (262,144) | 22.690 | **11.55** |
| $2^{20}$ (1,048,576) | 90.761 | **11.55** |
| $2^{22}$ (4,194,304) | 363.044 | **11.55** |
| $2^{23}$ (8,388,608) | 769.654 | **10.90** |

### Head-to-Head Comparison ($N = 1,048,576$)

| Library | Latency (ms) | Throughput (M pts/s) |
| :--- | :--- | :--- |
| ICICLE (v2.x) | 98.500 | 10.65 |
| **This library (`libzk_bls`)** | **90.761** | **11.55** |

---

## Build & Execution

### 1. Compile Shared Library

To compile the CUDA shared object manually using `nvcc`:

```bash
mkdir -p build
nvcc -O3 -shared -std=c++17 -Xcompiler -fPIC -arch=sm_80 bls12_381_master.cu -o build/libzk_bls_accel.so
