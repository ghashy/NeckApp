/**
 * @file Chord.hpp.
 * @brief Contains declaration for two classes: TargetChord and
 * HearableChord.
 *
 * Created by Ghashy.
 */

#ifndef CHORD_HPP
#define CHORD_HPP

#include <algorithm>
#include <vector>

#include "godot_cpp/classes/ref_counted.hpp"
#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/core/binder_common.hpp>
#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/variant/string_name.hpp>

#include "ChordDetector.h"

class HearableChord;

enum class MusKey { C, Cis, D, Dis, E, F, Fis, G, Gis, A, B, H };

class TargetChord : public godot::RefCounted {
    private:
        GDCLASS(TargetChord, godot::RefCounted);
    public:
        struct Desc {
                int root;
                int quality;
                int intervals;
        };
        enum class Degree { _1 = 1, _2, _3, _4, _5, _6, _7 };
        enum class ChordList {
            maj,
            min,
            min_7,
            _7,
            maj_7,
            sus2,
            sus4,
            add9_narrow,
            add9_wide,
            m_add9_narrow,
            m_add9_wide,
            _9,
            m_9,
            dim
        };

        TargetChord() = default;
        TargetChord& init(MusKey key, MusKey root, ChordList chord, bool is_modern_naming);
        TargetChord& init(const TargetChord& target_chord);

        godot::String get_chord_name() const { return chord_name; }
        void set_chord_name(const godot::String& name) {};
        friend bool operator==(const TargetChord& a, const TargetChord& b);
        void push(int root, int quality, int intervals);
        bool compare(const TargetChord& heared) const;
    protected:
        static void _bind_methods();
    private:
        godot::String init_chord_name() const;
        std::vector<Desc> desc_vec {};
        static godot::String get_key(MusKey key, MusKey root, ChordList chord);
        static godot::String get_amature_key(MusKey key, MusKey root, ChordList chord);
        ChordList chord;
        godot::String chord_key {};
        godot::String chord_name;
};

inline MusKey operator+=(MusKey& a, const int& b) {
    int temp = int(a) + b;
    if (temp > 11) temp -= 12;
    a = MusKey(temp);
    return a;
}

inline MusKey operator+(const MusKey& a, const int& b) {
    int temp = int(a) + b;
    if (temp > 11) temp -= 12;
    return MusKey(temp);
}

inline bool operator==(const TargetChord::Desc& a, const TargetChord::Desc& b) {
    return a.root == b.root and a.quality == b.quality and a.intervals == b.intervals;
}

inline bool operator==(const TargetChord& a, const TargetChord& b) {
    for (TargetChord::Desc element : a.desc_vec) {
        if (std::find(b.desc_vec.begin(), b.desc_vec.end(), element) != b.desc_vec.end()) {
            return true;
        }
    }
    return false;
}

#endif // CHORD_HPP