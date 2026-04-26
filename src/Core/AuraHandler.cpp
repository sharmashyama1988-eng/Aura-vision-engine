#include "Aura/Core/AuraHandler.hpp"
#include <android/log.h>
#include <thread>

#define LOG_TAG "AuraHandler"
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

namespace aura::core {

    struct ThermalPolicy { float threshold; bool disableProVisual; bool disableAI; int cpuFreqLimit; };
    static const ThermalPolicy POLICIES[4] = {
        { 35.0f, false, false, 0 }, { 42.0f, true, false, 80 }, { 48.0f, true, true, 50 }, { 55.0f, true, true, 20 }
    };

    AuraHandler::AuraHandler() : m_CurrentLevel(ComputeLevel::MEDIUM) { this->EvaluateCapacity(); }
    AuraHandler::~AuraHandler() {}

    ComputeLevel AuraHandler::EvaluateCapacity() {
        unsigned int nThreads = std::thread::hardware_concurrency();
        long ramMB = this->DetectAvailableRAM();
        if (nThreads <= 4 || ramMB < 1024) m_CurrentLevel = ComputeLevel::LOW;
        else if (nThreads <= 8) m_CurrentLevel = ComputeLevel::MEDIUM;
        else m_CurrentLevel = ComputeLevel::ULTRA;
        return m_CurrentLevel;
    }

    long AuraHandler::DetectAvailableRAM() { return 6144; }

    void AuraHandler::GuardSystem() {
        SystemHealth health = this->GetCurrentHealth();
        if (health.availableRam < 256 * 1024 * 1024) this->EmergencyMemoryCleanup();
    }

    bool AuraHandler::IsSupercomputingSafe() {
        SystemHealth health = GetCurrentHealth();
        return (m_CurrentLevel >= ComputeLevel::HIGH) && (health.temperature < 48.0f);
    }

    SystemHealth AuraHandler::GetCurrentHealth() { return { 0.45f, 2048 * 1024 * 1024, true, 38.0f }; }
    void AuraHandler::EmergencyMemoryCleanup() { LOGE("AuraHandler: LOW MEMORY!"); }

} // namespace aura::core
