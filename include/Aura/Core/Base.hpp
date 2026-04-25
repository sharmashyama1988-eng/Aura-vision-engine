#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <vector>
#include <csignal>
#include <iostream>

namespace aura {

    // Engine Version
    constexpr uint32_t VERSION_MAJOR = 1;
    constexpr uint32_t VERSION_MINOR = 0;
    constexpr uint32_t VERSION_PATCH = 0;

    // Core Types
    using byte = uint8_t;
    using uint = uint32_t;
    using uint64 = uint64_t;
    using int64 = int64_t;

    // Alignment for SIMD
    #define AURA_ALIGN_16 alignas(16)
    #define AURA_ALIGN_32 alignas(32)

    // Resource Management
    template<typename T>
    using Ref = std::shared_ptr<T>;

    template<typename T, typename... Args>
    constexpr Ref<T> CreateRef(Args&&... args) {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    using Scope = std::unique_ptr<T>;

    template<typename T, typename... Args>
    constexpr Scope<T> CreateScope(Args&&... args) {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    // --- Zero-Crash Stability Layer ---

    class SignalHandler {
    public:
        static void Setup() {
            std::signal(SIGSEGV, HandleCrash);
            std::signal(SIGABRT, HandleCrash);
            std::signal(SIGFPE,  HandleCrash);
        }

    private:
        static void HandleCrash(int signal) {
            std::cerr << "[CRITICAL] Aura Engine caught system signal: " << signal << std::endl;
            std::cerr << "[CRITICAL] Attempting emergency shutdown of Trinity Core..." << std::endl;
            // Here we would safely release locks and save logs before exiting
            std::exit(signal);
        }
    };

} // namespace aura
