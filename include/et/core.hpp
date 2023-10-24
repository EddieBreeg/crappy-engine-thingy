#pragma once

#include <utility>
#include <memory>
#include <cassert>
#include <string_view>

#if defined(_WIN32)
#define ET_WINDOWS
#elif defined(__linux__)
#define ET_LINUX
#elif defined(__APPLE__)
#define ET_MAC
#endif

#if defined(ET_WINDOWS) && defined(ET_BUILD_SHARED)

#if defined(ET_BUILD)

#ifdef _MSC_VER
#define ET_API __declspec(dllexport)
#else
#define ET_API __attribute__((dllexport))
#endif

#else

#ifdef _MSC_VER
#define ET_API __declspec(dllimport)
#else
#define ET_API __attribute__((dllimport))
#endif

#endif

#else

#define ET_API

#endif

#ifndef NDEBUG
#define ET_DEBUG
#endif

#include <chrono>

namespace EngineThingy {
	namespace chrono = std::chrono;
	using Clock = chrono::steady_clock;
	using Timing = chrono::duration<double>;
	using TimePoint = Clock::time_point;

} // namespace EngineThingy
