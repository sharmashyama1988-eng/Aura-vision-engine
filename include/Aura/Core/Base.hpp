#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

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

} // namespace aura
