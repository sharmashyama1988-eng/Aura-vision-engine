#pragma once

#include "Aura/Camera/Camera.hpp"
#include <vector>

namespace aura::vision {

    struct FeaturePoint {
        float x, y;
        float confidence;
    };

    struct DetectionResult {
        std::string label;
        float confidence;
        float box[4]; // [x, y, w, h]
    };

    class ImageProcessor {
    public:
        // Real-time edge detection (Canny algorithm skeleton)
        static void DetectEdges(const camera::Frame& frame, std::vector<FeaturePoint>& outPoints);

        // Compute Image Histogram for Auto-Exposure
        static void ComputeHistogram(const camera::Frame& frame, uint32_t outHistogram[256]);

        // Integrate with Neural Network (NPU)
        static void RunInference(const camera::Frame& frame, std::vector<DetectionResult>& outResults);
    };

} // namespace aura::vision
