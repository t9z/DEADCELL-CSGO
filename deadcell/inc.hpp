#pragma once

#pragma warning( disable : 4307 ) // warning C4307: '*': integral constant overflow
#pragma warning( disable : 4244 ) // warning C4244: '=': conversion possible loss of data

using ulong_t = unsigned long;

#define WIN32_LEAN_AND_MEAN
#define NOCOMM
#define NOMINMAX

#include <windows.h>
#include <cstdint>
#include <string>
#include <sstream>
#include <cctype>
#include <random>
#include <array>
#include <utility>
#include <intrin.h>
#include <chrono>

// oshgui.
#include "../oshgui/OSHGui.hpp"
#include "../oshgui/Drawing/Direct3D9/Direct3D9Renderer.hpp"
#include "../oshgui/Drawing/RenderTarget.hpp"
#include "../oshgui/Input/Input.hpp"

#include "hash/hash.hpp"
#include "pe/types.hpp"
#include "util/misc/misc.hpp"
#include "pe/module/module.hpp"
#include "pe/pe.hpp"
#include "util/pattern/pattern.hpp"
#include "math/math.hpp"
#include "console/console.hpp"
#include "input/input.hpp"

// renderer.
#include "oshgui/renderer.hpp"