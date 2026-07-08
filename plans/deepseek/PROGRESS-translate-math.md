# Progress: translate-math (Agent 15)

## Attempted / Skipped

| File | Line | Symbol / Function | Status | Notes |
|------|------|-------------------|--------|-------|
| `src/math/matrix4d.cpp` | 2893 | `??0Matrix4D@@QAE@ABVCoord3D@@@Z` | SKIPPED | Tried 3 C++ shapes; compiler insists on keeping the `1.0f` constant in `ecx` instead of `edx`, producing a 4-byte different instruction sequence. Restored original naked block. |
| `src/math/coord3d.cpp` | 701 | `?CrossProduct@Coord3D@@QAEAAV1@ABUCoord3DBase@@0@Z` | SKIPPED | Tried 3 C++ shapes; x87 operand scheduling for the `y` component could not be coaxed to match original (`fld right.x; fmul left.z; fld left.x; fmul right.z`). Compiler loads `right.z` before `left.x`. Restored original naked block. |
| `src/math/coord3d.cpp` | 272 | `Coord3D::GetLengthEstimate` | SKIPPED | x87 + 5 branches; high scheduling risk, no CSV row. |
| `src/math/coord3d.cpp` | 398 | `Coord3D::lengthEstimate` | SKIPPED | Duplicate of above; x87 + 5 branches. |
| `src/math/coord2d.cpp` | 236 | `Coord2D::toAngle` | SKIPPED | x87 atan2-style logic + 4 branches + 2 calls. |
| `src/math/coord2d.cpp` | 390 | `Coord2D::Rotate(float)` | SKIPPED | x87 sin/cos + branches. |
| `src/math/coord2d.cpp` | 472 | `Coord2D::Rotate(const Coord2D &, float)` | SKIPPED | x87 sin/cos + branches. |
| `src/math/region.cpp` | 334 | `operator<<(Debug &, const Region2D &)` | SKIPPED | Debug stream + vtable calls + string literals. |
| `src/math/region.cpp` | 484 | `operator<<(Debug &, const IRegion2D &)` | SKIPPED | Debug stream + vtable calls + string literals. |
| `src/math/region.cpp` | 634 | `operator<<(Debug &, const RealRange &)` | SKIPPED | Debug stream + vtable calls + string literals. |

## Result

No translations landed in this pass. The remaining math-library naked blocks are all
x87-scheduling, branch-heavy, or Debug-stream/virtual-call heavy and fall into the
"skip freely, never spin" category per `plans/deepseek/15-translate-math.md`.

All owned files were left byte-verified green:
- `src/math/matrix4d.cpp`: 26/26 matched
- `src/math/coord3d.cpp`: 71/71 matched
