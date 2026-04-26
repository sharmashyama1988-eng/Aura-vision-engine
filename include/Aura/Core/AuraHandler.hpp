#pragma once

#include <string>

namespace aura::core {

    enum class ComputeLevel { LOW, MEDIUM, HIGH, ULTRA };

    struct SystemHealth { float cpuLoad; long availableRam; bool isNpuPresent; float temperature; };

    class AuraHandler {
    public:
        AuraHandler();
        ~AuraHandler();
        ComputeLevel EvaluateCapacity();
        void GuardSystem();
        bool IsSupercomputingSafe();
        SystemHealth GetCurrentHealth();

    private:
        ComputeLevel m_CurrentLevel;
        long DetectAvailableRAM();
        void ApplyThermalThrottling(struct ThermalPolicy policy);
        void EmergencyMemoryCleanup();
    };

} // namespace aura::core
