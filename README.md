# vecmath

[![CI](https://github.com/jaemin-cho04/vecmath/actions/workflows/ci.yml/badge.svg)](https://github.com/jaemin-cho04/vecmath/actions/workflows/ci.yml)

A from-scratch C++ linear algebra library (`linalg`), and the robotics/controls
projects built on top of it — forward kinematics, control theory, and (in
progress) ROS 2 and reinforcement learning. No Eigen, no external math libs;
every operation is implemented and tested by hand.

## Build & test

```bash
cmake -S . -B build          # configure (first run downloads GoogleTest)
cmake --build build -j        # compile
ctest --test-dir build --output-on-failure   # run the test suite
```

## Layout

```
include/linalg/   public headers (the API) — the library
src/              library implementations only
tests/            GoogleTest unit tests
.github/          CI: builds + tests on every push
```

`apps/` (demos/sims that use the library) will be added back once Phase 2
starts — removed for now to keep the repo focused on the library foundation.

## Roadmap

This started as a math library and is growing into a full robotics/controls
portfolio, built in stages on top of it.

**Phase 1 — `linalg` library (done):**
- [x] `Vec3` — add, subtract, scale, dot, cross, length, normalize, equality
- [x] `Mat3` / `Mat4` — multiply, transpose, identity, determinant, inverse
- [x] Rotations — rotation matrices, then quaternions
- [x] Quaternion-to-rotation-matrix, conjugate, slerp, Euler angle conversions
- [x] Homogeneous 4×4 transforms (translation + rotation)
- [x] `Transform3D` — quaternion + translation rigid-body transform (SE(3))
- [x] Generalized `Vec<T, N>` / `Mat<T, R, C>` templates

**Phase 2 — control systems in C++:**
- [ ] Inverted pendulum simulation + PID controller, using `linalg`
- [ ] LQR controller, compared against PID

**Phase 3 — ROS 2 + robot arm** (run via Docker)

**Phase 4 — MuJoCo + reinforcement learning** (trained policy demo, native
macOS, Python)

**Phase 5 — wrap-up** (this README gets a full rewrite once Phases 3-4 land,
with demo clips and links)
