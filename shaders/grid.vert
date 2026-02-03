#version 450

// Vertex attributes
layout(location = 0) in vec3 inPosition;

// Uniforms
layout(binding = 0) uniform UniformBufferObject {
    mat4 view;
    mat4 proj;
} ubo;

// Push constants for grid color
layout(push_constant) uniform PushConstants {
    vec4 color;
} pushConstants;

// Outputs to fragment shader
layout(location = 0) out vec4 fragColor;

void main() {
    gl_Position = ubo.proj * ubo.view * vec4(inPosition, 1.0);
    fragColor = pushConstants.color;
}
