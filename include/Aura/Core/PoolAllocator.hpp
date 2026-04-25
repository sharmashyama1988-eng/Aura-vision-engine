#pragma once

#include "Aura/Core/Base.hpp"
#include <vector>
#include <mutex>

namespace aura::core {

    /**
     * @brief A high-performance Pool Allocator for fixed-size objects.
     * Essential for high-frequency frame data objects in a visual engine.
     */
    class PoolAllocator {
    public:
        PoolAllocator(size_t objectSize, size_t objectsPerBlock = 1024);
        ~PoolAllocator();

        void* Allocate();
        void Deallocate(void* ptr);

    private:
        struct Block {
            std::vector<byte> data;
            Block(size_t size) : data(size) {}
        };

        struct FreeNode {
            FreeNode* next;
        };

        size_t m_ObjectSize;
        size_t m_ObjectsPerBlock;
        FreeNode* m_FreeList = nullptr;
        std::vector<Scope<Block>> m_Blocks;
        std::mutex m_Mutex;

        void AllocateBlock();
    };

} // namespace aura::core
