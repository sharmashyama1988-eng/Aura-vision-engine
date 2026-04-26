#pragma once

#include <string>

namespace aura::camera {

    class CameraEngineer {
    public:
        CameraEngineer();
        ~CameraEngineer();
        void AutoTuneHardware();
        void OptimizeOptics();
        void DigitalCalibration();
        void ApplySceneProfile(const std::string& profileName);

    private:
        bool m_IsHardwareOptimized;
    };

} // namespace aura::camera
