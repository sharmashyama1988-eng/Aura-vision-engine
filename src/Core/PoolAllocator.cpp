#include "Aura/Core/PoolAllocator.hpp"

namespace aura::core {

    PoolAllocator::PoolAllocator(size_t objectSize, size_t objectsPerBlock)
        : m_ObjectSize(objectSize < sizeof(FreeNode) ? sizeof(FreeNode) : objectSize),
          m_ObjectsPerBlock(objectsPerBlock) {
        AllocateBlock();
    }

    PoolAllocator::~PoolAllocator() {
        // Blocks are managed by unique_ptr, so they'll be cleaned up automatically.
    }

    void* PoolAllocator::Allocate() {
        std::lock_guard<std::mutex> lock(m_Mutex);
        if (!m_FreeList) {
            AllocateBlock();
        }

        void* ptr = m_FreeList;
        m_FreeList = m_FreeList->next;
        return ptr;
    }

    void PoolAllocator::Deallocate(void* ptr) {
        if (!ptr) return;
        std::lock_guard<std::mutex> lock(m_Mutex);
        FreeNode* node = static_cast<FreeNode*>(ptr);
        node->next = m_FreeList;
        m_FreeList = node;
    }

    void PoolAllocator::AllocateBlock() {
        size_t blockSize = m_ObjectSize * m_ObjectsPerBlock;
        auto block = CreateScope<Block>(blockSize);
        
        // Link all objects in the new block into the free list
        byte* data = block->data.data();
        for (size_t i = 0; i < m_ObjectsPerBlock; ++i) {
            FreeNode* node = reinterpret_cast<FreeNode*>(data + (i * m_ObjectSize));
            node->next = m_FreeList;
            m_FreeList = node;
        }

        m_Blocks.push_back(std::move(block));
    }

} // namespace aura::core
