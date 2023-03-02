/**
 * @file ChordInfo.cpp.
 * @brief Implementation file for ChordInfo class.
 *
 * Created by Ghashy.
 */

#include <godot_cpp/variant/utility_functions.hpp>

#include "ChordInfo.hpp"
#include <Chord.hpp>

using namespace godot;

ChordInfo::ChordInfo() {
    int bus_idx = server->get_bus_index("InputBus");
    effect = server->get_bus_effect(bus_idx, 0);
}

ChordInfo::~ChordInfo() {}

void ChordInfo::_bind_methods() {
    ClassDB::bind_method(D_METHOD("calculate_result", "buffer", "samples_count", "frame_size",
                                  "sample_rate", "chord", "calculation_interval"),
                         &ChordInfo::calculate_result, DEFVAL(8192));
}

bool ChordInfo::calculate_result(godot::PackedVector2Array buffer, int samples_count,
                                 int frame_size, int sample_rate, godot::Ref<TargetChord> chord,
                                 int calculation_interval) {
    using namespace std;

    Chromagram chroma {frame_size, sample_rate};
    chroma.setChromaCalculationInterval(calculation_interval);
    chroma.setSamplingFrequency(sample_rate);

    ChordDetector detector {};

    vector<double> frame(frame_size);
    TargetChord heared {};

    // Skip all 0.0 values in buffer
    vector<double> std_buffer;
    for (godot::Vector2 element : buffer) {
        if (std_buffer.size() == 0.0 and element.x == 0.0) continue;
        std_buffer.push_back(element.x);
    }

    //Hearing
    for (int j = 0; j < std_buffer.size(); j += frame_size) {
        for (int i = 0; i < frame_size; i++) {
            if (i + j >= std_buffer.size()) break;
            frame[i] = std_buffer[i + j];
        }
        chroma.processAudioFrame(frame);
        if (chroma.isReady()) {
            detector.detectChord(chroma.getChromagram());
            heared.push(detector.rootNote, detector.quality, detector.intervals);
            godot::UtilityFunctions::print(detector.rootNote, " ", detector.quality, " ",
                                           detector.intervals);
        }
    }
    bool result = chord->compare(heared);
    if (result) godot::UtilityFunctions::print("SUCCESS");
    return result;
}