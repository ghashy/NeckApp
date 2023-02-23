/**
 * @file ChordInfo.hpp.
 * @brief Interface file for ChordInfo class.
 *
 * Created by Ghashy.
 */

#ifndef CHORD_INFO_HPP
#define CHORD_INFO_HPP

#include "godot_cpp/classes/audio_effect_capture.hpp"
#include "godot_cpp/classes/audio_server.hpp"
#include "godot_cpp/core/class_db.hpp"
#include "godot_cpp/variant/packed_vector2_array.hpp"
#include "godot_cpp/variant/packed_vector3_array.hpp"
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/core/binder_common.hpp>
#include <godot_cpp/variant/vector3.hpp>

#include "ChordDetector.h"
#include "Chromagram.h"

#include "Chord.hpp"

class ChordInfo : public godot::RefCounted {
    private:
        GDCLASS(ChordInfo, godot::RefCounted);
    public:
        ChordInfo();
        ~ChordInfo();

        /**
         * `brief:` Function for calculate if chosen chord is same as chord,
         *  played on guitar and given in `buffer` parameter.
         *
         * `buffer:` audio signal.
         * `return:` Is audio signal conforms to given `TargetChord`
         */
        bool calculate_result(godot::PackedVector2Array buffer,
                              int samples_count, int frame_size,
                              int sample_rate, godot::Ref<TargetChord> chord,
                              int calculation_interval = 8192);
    protected:
        static void _bind_methods();
    private:
        // Instance of AudioEffectCapture
        godot::Ref<godot::AudioEffectCapture> effect;
        godot::AudioServer* server = godot::AudioServer::get_singleton();
};

#endif // CHORD_INFO_HPP