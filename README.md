# Cats vs Dogs... vs Chickens

A 2.5D Real-Time Strategy (RTS) game built with C++ and Vulkan, featuring three animal factions in a visual style similar to StarCraft 2.

## Project Status

This is the foundational structure of the game. Currently implemented:
- ✅ Project folder structure
- ✅ Camera system with pan, zoom, and rotation
- ✅ Input handling via GLFW
- ✅ Basic game loop
- ✅ Placeholder math library (vec2/vec3/vec4, mat3/mat4)
- ✅ Build system (Makefile)

**TODO**: Integrate Vulkan rendering pipeline (placeholder structure ready)

## Features

### Camera System (2.5D)
- **Pan**: WASD or Arrow keys to move across the world
- **Zoom**: Mouse wheel to zoom in/out
- **Rotate**: Q/E keys to rotate around Z-axis
- Smooth isometric-style perspective suitable for RTS gameplay

### Input Handler
- Keyboard state tracking with press/release detection
- Mouse position and button tracking
- Mouse scroll/wheel support
- Extensible callback system

## Project Structure

```
.
├── src/                  # Source files (.cpp)
│   ├── main.cpp         # Application entry point and game loop
│   ├── Camera.cpp       # Camera system implementation
│   └── InputHandler.cpp # Input handling implementation
│
├── include/             # Header files (.h/.hpp)
│   ├── Camera.h         # Camera system
│   └── InputHandler.h   # Input handler
│
├── lib/                 # Third-party libraries
│   └── math/           # Custom math library (vec2/3/4, mat3/4)
│       ├── vec2.h
│       ├── vec3.h
│       ├── vec4.h
│       ├── mat3.h
│       └── mat4.h
│
├── shaders/            # Vulkan shader files (GLSL/SPIR-V)
│
├── assets/             # Game assets
│   ├── models/        # 3D models
│   ├── textures/      # Textures
│   └── sounds/        # Audio files
│
├── build/              # Build artifacts (gitignored)
│
├── Makefile            # Build system
└── README.md           # This file
```

## Building

### Prerequisites

- C++17 or later compiler (g++, clang++)
- GLFW 3.x
- Vulkan SDK
- Make

#### Ubuntu/Debian
```bash
make install-deps
```

Or manually:
```bash
sudo apt-get update
sudo apt-get install -y build-essential libglfw3-dev libvulkan-dev vulkan-tools
```

#### Arch Linux
```bash
sudo pacman -S base-devel glfw-x11 vulkan-devel
```

#### macOS
```bash
brew install glfw vulkan-sdk molten-vk
```

### Compilation

```bash
# Debug build
make debug

# Release build (optimized)
make release

# Default build
make
```

### Running

```bash
make run
# Or directly:
./build/rts_game
```

### Cleaning

```bash
make clean
```

## Shaders

The project includes example GLSL shaders in the `shaders/` directory:
- `basic.vert/frag`: Basic 3D rendering with simple lighting
- `grid.vert/frag`: Ground grid rendering for spatial reference

### Compiling Shaders

Shaders must be compiled to SPIR-V before use:

```bash
./compile_shaders.sh
```

Or manually:
```bash
glslc shaders/basic.vert -o shaders/basic.vert.spv
glslc shaders/basic.frag -o shaders/basic.frag.spv
```

Note: `glslc` comes with the Vulkan SDK.

## Controls

| Input | Action |
|-------|--------|
| **WASD** or **Arrow Keys** | Pan camera across the world |
| **Q** | Rotate camera counter-clockwise |
| **E** | Rotate camera clockwise |
| **Mouse Wheel** | Zoom in/out |
| **ESC** | Exit application |

## Technical Details

### Graphics API
- **Vulkan**: Modern graphics API for high-performance rendering
- **GLFW**: Cross-platform window and input management
- **Custom Math Library**: User-provided vec2/vec3/vec4 and mat3/mat4 (placeholder included)

### Rendering
- 2.5D perspective (3D rendering with isometric camera)
- Suitable for RTS gameplay with clear unit visibility
- Ready for integration of custom Vulkan rendering pipeline

## Next Steps / TODO

### High Priority
- [ ] Integrate Vulkan rendering pipeline
  - [ ] Instance and device creation
  - [ ] Swapchain setup
  - [ ] Render pass and framebuffers
  - [ ] Command buffers
  - [ ] Shader loading
- [ ] Implement basic grid rendering (ground plane)
- [ ] Add simple cube/placeholder mesh rendering
- [ ] Replace placeholder math library with user's implementation

### Future Features
- [ ] Entity Component System (ECS) for game objects
- [ ] Unit selection and control
- [ ] Pathfinding (A* or similar)
- [ ] Three factions: Cats, Dogs, Chickens
  - [ ] Unique units per faction
  - [ ] Faction-specific abilities
- [ ] Resource gathering system
- [ ] Building placement and construction
- [ ] Combat system
- [ ] UI/HUD rendering
- [ ] Audio system
- [ ] Multiplayer networking

## Architecture Notes

### Separation of Concerns
- **Camera**: Handles view/projection matrices and camera controls
- **InputHandler**: Centralizes all input state management
- **Application**: Main game loop and system coordination
- **Rendering**: Placeholder for Vulkan pipeline integration (user-provided)

### Math Library
The included math library in `lib/math/` is a **placeholder**. Replace these files with your existing vec2/vec3/vec4 and mat3/mat4 implementations from your previous project.

### Extensibility
The codebase is designed to be extended with:
- Entity Component System (ECS) for managing game entities
- Resource management system
- AI and pathfinding
- Networking layer for multiplayer
- Audio system

## License

[Add your license here]

## Credits

- Project structure and foundation: GitHub Copilot
- Game concept: Cats vs Dogs... vs Chickens
