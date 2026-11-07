// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (c) 2026 add000
// Part of Shinon (深音)
#pragma once
#include <cstdint>
#include <string>
#include <vector>

namespace shinon {

constexpr uint32_t kApiVersion = 1;  // bump on breaking changes

struct AudioBuffer {
    float** channels = nullptr;  // channels[ch][frame]
    uint32_t numChannels = 0;
    uint32_t numFrames = 0;
};

struct ParamInfo {
    uint32_t id;
    std::string name;
    std::string unit;
    float minValue, maxValue, defaultValue;
};

// Every feature (PEQ, FIR, SOFA, calibration, limiter...) is a Node.
class INode {
public:
    virtual ~INode() = default;
    virtual void prepare(double sampleRate, uint32_t maxBlockSize, uint32_t channels) = 0;
    // Real-time safe: no allocation, locks, I/O.
    virtual void process(AudioBuffer& buf) = 0;
    // Called from the audio thread after draining the lock-free param queue.
    virtual void setParam(uint32_t id, float value) = 0;
    virtual std::vector<ParamInfo> paramInfo() const = 0;
    virtual uint32_t latencySamples() const { return 0; }
    virtual std::string saveState() const = 0;          // JSON
    virtual bool loadState(const std::string& json) = 0;
};

}  // namespace shinon
