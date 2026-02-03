# Assets

Game assets including models, textures, and sounds.

## Directory Structure

- **models/**: 3D models for units, buildings, terrain
- **textures/**: Texture files (diffuse, normal, specular maps)
- **sounds/**: Audio files for sound effects and music

## Asset Guidelines

### Models
- Format: GLTF/GLB or OBJ
- Triangle count: Keep optimized for RTS gameplay (LOD system planned)
- Scale: Use consistent world scale

### Textures
- Format: PNG or KTX2 (for Vulkan)
- Resolutions: Power of 2 (e.g., 512x512, 1024x1024)
- Compression: Consider BC7/ASTC for runtime

### Sounds
- Format: OGG Vorbis (music), WAV (sound effects)
- Sample rate: 44.1kHz or 48kHz
- Bit depth: 16-bit minimum

## Factions

### Cats
- Units: Scout Cat, Warrior Cat, Archer Cat, etc.
- Buildings: Cat House, Fish Farm, etc.

### Dogs
- Units: Hound, Guard Dog, Retriever, etc.
- Buildings: Dog House, Bone Pit, etc.

### Chickens
- Units: Chicken Scout, Rooster Warrior, Hen Mage, etc.
- Buildings: Coop, Grain Silo, etc.
