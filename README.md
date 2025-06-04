# 2D Game Engine

A lightweight 2D game engine written in C++ featuring an Entity-Component-System (ECS) architecture with Lua scripting support. Includes a complete helicopter combat demo game showcasing the engine's capabilities.

## Features

### Core Engine
- **Entity-Component-System (ECS)** architecture for flexible game object management
- **SDL2** integration for graphics, input, and audio
- **Lua scripting** with Sol2 for game logic and level definition
- **Asset management** system for textures, fonts, and resources
- **Event-driven** architecture with custom event bus
- **ImGui** integration for debug interface and development tools

### Game Systems
- **Rendering System** with z-index sorting and camera culling
- **Physics & Movement** with rigidbody components and collision detection
- **Animation System** supporting sprite sheet animations
- **Collision Detection** with AABB collision system
- **Health & Damage** system with visual health bars
- **Projectile System** with emitters and lifecycle management
- **Camera System** with smooth following and boundary constraints
- **Keyboard Input** handling with customizable controls

### Scripting & Content
- **Lua-based level definition** for easy content creation
- **Dynamic entity scripting** with runtime behavior modification
- **Asset loading** from configuration files
- **Day/night cycle** support with dynamic texture swapping

## Demo Game

The included demo is a top-down helicopter combat game featuring:

- **Player-controlled helicopter** with directional movement and shooting
- **Enemy AI** including tanks, fighter jets, and SAM sites
- **Dynamic environments** with obstacles, vegetation, and military installations
- **Combat mechanics** with different weapon types and damage systems
- **Multiple enemy types** with unique behaviors and attack patterns

## Build Requirements

- **C++17** compiler
- **CMake 3.14+**
- **SDL2** development libraries
- **SDL2_image, SDL2_ttf, SDL2_mixer**
- **Lua 5.4**
- **GLM** (OpenGL Mathematics)
- **ImGui** (included)
- **Sol2** (Lua binding library)

## Building

```bash
mkdir build
cd build
cmake ..
make
```

## Running

```bash
./Engine.app
```

### Controls
- **Arrow Keys**: Move helicopter
- **Space**: Shoot
- **D**: Toggle debug mode
- **ESC**: Quit

## Project Structure

```
src/
├── ECS/              # Entity-Component-System implementation
├── Components/       # Game components (Transform, Sprite, etc.)
├── Systems/          # Game systems (Render, Movement, etc.)
├── Game/            # Main game loop and level loading
├── AssetManager/    # Resource management
├── EventBus/        # Event system
├── Events/          # Event definitions
└── Logger/          # Debug logging system

assets/
├── scripts/         # Lua level definitions
├── images/          # Game textures and sprites
├── fonts/           # Font files
└── tilemaps/        # Tile-based level maps
```

## Architecture Highlights

### ECS System
The engine uses a data-oriented ECS architecture where:
- **Entities** are lightweight IDs
- **Components** store data (Transform, Sprite, Health, etc.)
- **Systems** process entities with specific component combinations

### Lua Integration
Game content is defined in Lua scripts, allowing for:
- Easy level creation and modification
- Runtime entity behavior scripting
- Dynamic asset loading and configuration

### Event-Driven Design
Systems communicate through events:
- Collision events trigger damage calculations
- Input events drive movement and actions
- Modular system interactions

## License

Copyright (c) 2025 Jakub Kurc
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
