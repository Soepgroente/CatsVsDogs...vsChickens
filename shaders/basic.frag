#version 450

// Inputs from vertex shader
layout(location = 0) in vec3 fragNormal;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) in vec3 fragWorldPos;

// Output
layout(location = 0) out vec4 outColor;

// Simple lighting parameters
const vec3 lightDir = normalize(vec3(1.0, 1.0, -1.0));
const vec3 lightColor = vec3(1.0, 1.0, 0.9);
const vec3 ambientColor = vec3(0.3, 0.3, 0.35);

void main() {
    // Simple diffuse lighting
    vec3 normal = normalize(fragNormal);
    float diffuse = max(dot(normal, -lightDir), 0.0);
    
    // Base color (placeholder - would come from texture)
    vec3 baseColor = vec3(0.7, 0.7, 0.7);
    
    // Combine lighting
    vec3 color = baseColor * (ambientColor + diffuse * lightColor);
    
    outColor = vec4(color, 1.0);
}
