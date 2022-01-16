#pragma once

#include <iostream>
#include <utility>
#include <random>
#include <memory>
#include <functional>
#include <fstream>
#include <sstream>
#include <chrono>
#include <string>
#include <array>
#include <vector>
#include <math.h>
#include <unordered_map>
#include <iomanip>
#include "utils/StringUtils.h"

//GLEW and GLFW
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//STB Image for loading PNGs
#include "stb_image/stb_image.h"

//Math
#define PI 3.14159265f
#include "math/Mat4f.h"
#include "math/Vector.h"
#include "math/Random.h"

//Engine
#include "engine/Log.h"
#include "engine/Texture.h"
#include "engine/SpriteSheet.h"
#include "engine/Image.h"
#include "engine/Line.h"
#include "engine/Rectangle.h"
#include "engine/Circle.h"
#include "engine/Animation.h"
#include "engine/Text.h"
#include "engine/Input.h"
#include "engine/Renderer.h"
#include "engine/VertexBuffer.h"
#include "engine/VertexBufferLayout.h"
#include "engine/VertexArray.h"
#include "engine/IndexBuffer.h"
#include "engine/Shader.h"

//TowerDefense Base
#include "core/Clock.h"
#include "core/Entity.h"
#include "core/StaticImage.h"
#include "core/Button.h"
#include "core/AnimationEffect.h"