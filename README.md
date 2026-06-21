# linalg

A from-scratch C++ linear algebra and 3D geometry library — built by hand to
learn the language and the math, not just call into Eigen. Foundation for
robotics (transforms, kinematics) and aerospace (attitude, orbits) work.

> Built without AI code generation. Every operation is implemented and tested
> by hand so I can explain the *why* behind each design choice.

## Build & test

```bash
cmake -S . -B build          # configure (first run downloads GoogleTest)
cmake --build build -j        # compile
ctest --test-dir build --output-on-failure   # run the test suite
```

## Layout

```
include/linalg/   public headers (the API)
src/              implementations
tests/            GoogleTest unit tests
.github/          CI: builds + tests on every push
```

## Roadmap

- [x] `Vec3` — add, subtract, scale, dot, cross, length, normalize, equality
- [x] `Mat3` / `Mat4` — multiply, transpose, identity, determinant, inverse
- [x] Rotations — rotation matrices, then quaternions
- [ ] Homogeneous 4×4 transforms (translation + rotation)
- [ ] Demo: forward kinematics of a 2–3 link arm, printing the end-effector position
- [ ] Generalize concrete types to templates: `Vec<N>`, `Mat<R, C>`
