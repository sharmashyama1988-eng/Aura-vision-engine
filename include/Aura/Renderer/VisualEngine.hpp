#pragma once

#include "Aura/Camera/Camera.hpp"
#include "Aura/Math/Matrix4.hpp"

namespace aura::renderer {

    struct RenderState {
        bool enableHDR = true;
        bool enableNoiseReduction = true;
        float sharpness = 1.0f;
        float bloomIntensity = 0.5f;
    };

    class VisualEngine {
    public:
        VisualEngine();
        ~VisualEngine();

        void Initialize();
        void Shutdown();

        // Process a camera frame using GPU compute pipelines
        void ProcessFrame(Ref<camera::Frame> frame);

        // Update engine state (delta time in seconds)
        void Update(float dt);

        // Render the processed frame to the display buffer
        void Render();

        void SetRenderState(const RenderState& state) { m_State = state; }

    private:
        RenderState m_State;
        math::Matrix4 m_ProjectionMatrix;
        math::Matrix4 m_ViewMatrix;

        // Internal GPU Context (Vulkan/Metal handles would go here)
        void* m_GPUContext = nullptr;

        void ApplyToneMapping();
        void ApplyTemporalAntiAliasing();
    };

} // namespace aura::renderer
