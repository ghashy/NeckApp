/**
 * @file ChordInfo.cpp.
 * @brief Implementation file for ChordInfo class.
 *
 * Created by Ghashy.
 */

#include "ChordInfo.hpp"
#include <Chord.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

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

    // We skip if silence
    int size = 0;
    for (int i = 0; i < samples_count; i++) {
        if (buffer[i].x == 0.0) continue;
        size++;
    }
    if (size < samples_count-5000) return false;
    // Hearing
    for (int j = 0; j < samples_count; j += frame_size) {
        for (int i = 0; i < frame_size; i++) {
            if (i + j >= samples_count) break;
            frame[i] = buffer[i + j].x;
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