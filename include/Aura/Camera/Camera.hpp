#pragma once

#include "Aura/Core/Base.hpp"
#include <vector>

namespace aura::camera {

    enum class PixelFormat {
        YUV420,
        RGBA8,
        BGRA8,
        Depth16
    };

    struct FrameMetadata {
        uint32_t width;
        uint32_t height;
        uint64_t timestamp;
        float focalLength;
        float exposureTime;
        float iso;
    };

    struct Frame {
        PixelFormat format;
        FrameMetadata metadata;
        std::vector<byte> data; // Raw frame data

        // In a "heavy" engine, we would use a GPU texture or a shared memory buffer here
        // to avoid copying from CPU to GPU every frame.
    };

    class ICameraProvider {
    public:
        virtual ~ICameraProvider() = default;

        virtual bool Initialize() = 0;
        virtual void StartCapture() = 0;
        virtual void StopCapture() = 0;
        
        virtual Ref<Frame> GetLatestFrame() = 0;
        
        virtual void SetResolution(uint32_t width, uint32_t height) = 0;
    };

} // namespace aura::camera
