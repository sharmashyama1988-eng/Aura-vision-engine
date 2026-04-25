#pragma once

#include "Aura/Core/Base.hpp"

namespace aura::gpu {

    enum class BufferType {
        Vertex,
        Index,
        Uniform,
        Storage
    };

    class IBuffer {
    public:
        virtual ~IBuffer() = default;
        virtual void UploadData(const void* data, size_t size) = 0;
        virtual void Bind(uint32_t bindingPoint) = 0;
    };

    class IComputePipeline {
    public:
        virtual ~IComputePipeline() = default;
        virtual bool Compile(const std::string& source) = 0;
        virtual void Dispatch(uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) = 0;
    };

    class IDevice {
    public:
        virtual ~IDevice() = default;
        virtual Ref<IBuffer> CreateBuffer(BufferType type, size_t size) = 0;
        virtual Ref<IComputePipeline> CreateComputePipeline() = 0;
        virtual void WaitForIdle() = 0;
    };

} // namespace aura::gpu
