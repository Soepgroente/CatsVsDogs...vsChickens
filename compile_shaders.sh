#!/bin/bash
# Compile GLSL shaders to SPIR-V

SHADER_DIR="shaders"

echo "Compiling shaders..."

# Check if glslc is available
if ! command -v glslc &> /dev/null; then
    echo "Error: glslc not found. Please install Vulkan SDK."
    exit 1
fi

# Compile all .vert and .frag files
for shader in "$SHADER_DIR"/*.vert "$SHADER_DIR"/*.frag; do
    if [ -f "$shader" ]; then
        output="${shader}.spv"
        echo "  $shader -> $output"
        glslc "$shader" -o "$output"
        
        if [ $? -ne 0 ]; then
            echo "Error compiling $shader"
            exit 1
        fi
    fi
done

echo "Shader compilation complete!"
