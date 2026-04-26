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

        // --- NEW ENGINES ---
        
        // Motion Detection Engine
        static bool DetectMotion(const camera::Frame& current, const camera::Frame& previous);

        // Object Tracking Engine
        static void TrackObject(const camera::Frame& frame, const DetectionResult& target, float outPos[2]);

        // Facial Recognition Engine
        static void RecognizeFace(const camera::Frame& frame, std::vector<std::string>& outNames);

        // OCR Engine (Optical Character Recognition)
        static void ExtractText(const camera::Frame& frame, std::string& outText);
    };

} // namespace aura::vision
