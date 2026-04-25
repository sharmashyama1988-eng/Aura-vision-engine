#include "Aura/Renderer/VisualEngine.hpp"
#include "Aura/Core/TaskScheduler.hpp"
#include <iostream>
#include <thread>

int main() {
    using namespace aura;

    std::cout << "--- Starting Aura Vision Engine ---" << std::endl;

    // 1. Initialize Multi-threaded Task Scheduler
    auto scheduler = CreateScope<core::TaskScheduler>(4);
    std::cout << "[Main] Task Scheduler initialized with 4 workers." << std::endl;

    // 2. Initialize Visual Engine
    auto engine = CreateScope<renderer::VisualEngine>();
    engine->Initialize();

    // 3. Configure Render State
    renderer::RenderState state;
    state.enableHDR = true;
    state.enableNoiseReduction = true;
    state.sharpness = 1.2f;
    engine->SetRenderState(state);

    std::cout << "[Main] Engine configuration complete." << std::endl;

    // Simulation: Processing 10 frames in a loop
    for (int i = 0; i < 10; ++i) {
        // In a real app, this would come from the CameraProvider callback
        auto dummyFrame = CreateRef<camera::Frame>();
        dummyFrame->metadata.width = 1920;
        dummyFrame->metadata.height = 1080;
        dummyFrame->metadata.timestamp = i * 33; // ~30fps

        // Offload frame processing to a worker thread
        scheduler->Enqueue([&engine, dummyFrame]() {
            engine->ProcessFrame(dummyFrame);
        });

        std::this_thread::sleep_for(std::chrono::milliseconds(33));
    }

    std::cout << "[Main] Shutting down..." << std::endl;
    engine->Shutdown();

    return 0;
}
