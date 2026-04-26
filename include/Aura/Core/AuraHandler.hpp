#pragma once

#include <string>

namespace aura::core {

    enum class ComputeLevel {
        LOW,      // Basic processing only
        MEDIUM,   // Standard Vision engines enabled
        HIGH,     // ProVisual enabled
        ULTRA     // Supercomputing/NPU full power
    };

    struct SystemHealth {
        float cpuLoad;
        long availableRam;
        bool isNpuPresent;
        float temperature;
    };

    /**
     * @brief THERMAL THROTTLING POLICIES
     */
    struct ThermalPolicy {
        float threshold;
        bool disableProVisual;
        bool disableAI;
        int cpuFreqLimit;
    };

    class AuraHandler {
    public:
        AuraHandler();
        ~AuraHandler();

        // Evaluates device power to prevent crashes
        ComputeLevel EvaluateCapacity();

        // Dynamic Governor: Throttles engine if system is overheating or low on RAM
        void GuardSystem();

        // Returns true if it's safe to run heavy "ProVisual" tasks
        bool IsSupercomputingSafe();

        SystemHealth GetCurrentHealth();

    private:
        long DetectAvailableRAM();
        void ApplyThermalThrottling(const ThermalPolicy& policy);
        void EmergencyMemoryCleanup();

        ComputeLevel m_CurrentLevel;
    };

} // namespace aura::core
