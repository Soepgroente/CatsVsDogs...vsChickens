# Shaders

This directory will contain Vulkan shader files (GLSL source and compiled SPIR-V).

## Planned Shaders

- **basic.vert/frag**: Basic vertex and fragment shaders for 3D geometry with lighting
- **grid.vert/frag**: Shaders for ground grid rendering
- **ui.vert/frag**: Shaders for UI rendering (to be added)

## Compilation

Shaders should be compiled using `glslc` or `glslangValidator`:

```bash
glslc shader.vert -o shader.vert.spv
glslc shader.frag -o shader.frag.spv
```
