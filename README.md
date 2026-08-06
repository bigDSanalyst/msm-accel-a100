# msm-accel-a100

A hardware-accelerated C++/CUDA implementation of Pippenger's algorithm for multi-scalar multiplication (MSM) over the BLS12-381 elliptic curve. This library is optimized specifically to maximize L2 cache residency and memory bandwidth saturation on NVIDIA A100 GPUs.

**Maintainer:** Nicholas Clifford Maino ([maiknown@gmail.com](mailto:maiknown@gmail.com)
(doi10.5281/zenodo.21822506))
---

## ⚖️ Important Licensing Notice

This public repository provides the **compiled shared library** (`libzk_bls_accel.so`), benchmarking harness, and accompanying LaTeX manuscript. 

The **full source code** of the optimized CUDA kernel (including Montgomery multiplication and zero‑conflict shared memory patterns) is **not** included in this open-source distribution.

The core kernel source is available under a **commercial license** for enterprises and researchers who require:
- Full source code auditability.
- Custom integration support.
- Multi‑curve extensions (BN254, etc.).
- Multi‑backend support (Metal, Vulkan).

**To acquire the source code or a commercial license, please contact:**  
📧 [maiknown@gmail.com](mailto:maiknown@gmail.com)

---

## Requirements

* **Hardware:** NVIDIA GPU with Compute Capability 8.0 (Ampere / A100 80GB SXM4) or higher.
* **CUDA Toolkit:** Version 11.8 or later (`nvcc`) – required only if you have the source license.
* **Host Compiler:** GCC/G++ 9 or later.
* **Python Runtime:** Python 3.8+ with `numpy`.

---

## Repository Structure

* `zk_bls_pub.h` – Public C++ API header to interface with the shared library.
* `build/libzk_bls_accel.so` – Pre‑compiled shared library (binary distribution).
* `benchmarks/` – Python test harness (`compare_icicle.py`) for deterministic input scaling and isolated CUDA event timing.
* `BENCHMARKING.md` – Methodology and execution specifications for empirical reproducibility.
* `epaper/` – LaTeX manuscript (`main.tex`) detailing the hardware architecture and performance analysis.

---

## Empirical Performance

The kernel maintains linear throughput scaling up to \( N = 2^{22} \) points, holding a stable throughput of **11.55 M pts/s**. At \( N = 2^{23} \) points (exceeding 1.5 GB in total point/scalar memory footprint), the memory bandwidth bounds result in a minor latency increase while sustaining **10.90 M pts/s**.

### Scaling Suite (NVIDIA A100 80GB SXM4, 4‑bit window)

| Points (N) | Latency (ms) | Throughput (M pts/s) |
| :--- | :--- | :--- |
| \( 2^{16} \) (65,536)   | 5.673   | **11.55** |
| \( 2^{18} \) (262,144)  | 22.690  | **11.55** |
| \( 2^{20} \) (1,048,576)| 90.761  | **11.55** |
| \( 2^{22} \) (4,194,304)| 363.044 | **11.55** |
| \( 2^{23} \) (8,388,608)| 769.654 | **10.90** |

### Head‑to‑Head Comparison (\( N = 1,048,576 \))

| Library | Latency (ms) | Throughput (M pts/s) |
| :--- | :--- | :--- |
| ICICLE (v2.x) | 98.500 | 10.65 |
| **This library (`libzk_bls`)** | **90.761** | **11.55** |

---

## Usage (Without Source)

1. Load the shared library `build/libzk_bls_accel.so` in your C++ or Python application.
2. Include `zk_bls_pub.h` for the function definitions.
3. Execute the benchmark harness to verify performance:

```bash
python benchmarks/compare_icicle.py
