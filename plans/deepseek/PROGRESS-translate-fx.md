# PROGRESS: translate-fx

## Status
Territory reviewed: `src/game/fx_particle_system_bulk.cpp` and `src/game/fx_particle_system.cpp` still contain 301 `__declspec(naked)` asm blocks (297 in bulk, 4 in fx_particle_system.cpp).

## Skipped (all)
The remaining blocks are hard MSVC-scheduling / vtable / allocator assembly (ConcreteModuleClass/ConcreteModuleTemplate constructors, getInstance singletons, createTemplate factories, copy ctors, dtors, operator=, createModule). Per the plan's guidance to "SKIP freely, never spin", no blocks were converted in this pass.

Next pass would need to pick off tractable stragglers one at a time, restoring any failed attempt to the original naked block.
