# Shaders

This directory will contain Vulkan shader files (GLSL source and compiled SPIR-V).

## Planned Shaders

- **vertex.vert**: Basic vertex shader for 3D geometry
- **fragment.frag**: Basic fragment shader with lighting
- **grid.vert/frag**: Shader for ground grid rendering
- **ui.vert/frag**: Shaders for UI rendering

## Compilation

Shaders should be compiled using `glslc` or `glslangValidator`:

```bash
glslc shader.vert -o shader.vert.spv
glslc shader.frag -o shader.frag.spv
```
