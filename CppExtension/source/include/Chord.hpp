/**
 * @file Chord.hpp.
 * @brief Contains declaration for two classes: TargetChord and
 * HearableChord.
 *
 * Created by Ghashy.
 */

#ifndef CHORD_HPP
#define CHORD_HPP

#include "ChordDetector.h"

#include <algorithm>

#include "godot_cpp/classes/ref_counted.hpp"
#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/core/binder_common.hpp>
#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/variant/string_name.hpp>
#include <vector>

class HearableChord;

//------------------------------------------------------------------------------

enum class Key { C, Cis, D, Dis, E, F, Fis, G, Gis, A, B, H };

//------------------------------------------------------------------------------

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

        //----------------------------------------------------------------------

        TargetChord() = default;
        TargetChord& init(Key key, Key root, ChordList chord, bool is_modern_naming);
        TargetChord& init(const TargetChord& target_chord);

        //----------------------------------------------------------------------

        godot::String get_chord_name() const;
        friend bool operator==(const TargetChord& a, const TargetChord& b);
        void push(int root, int quality, int intervals);
        bool compare(const TargetChord& heared) const;
    protected:
        static void _bind_methods();
    private:
        std::vector<Desc> desc_vec {};
        static godot::String get_key(Key key, Key root, ChordList chord);
        static godot::String get_amature_key(Key key, Key root, ChordList chord);
        ChordList chord;
        godot::String chord_key {};
};

//------------------------------------------------------------------------------

inline Key operator+=(Key& a, const int& b)
{
    int temp = int(a) + b;
    if (temp > 11) temp -= 12;
    a = Key(temp);
    return a;
}

//------------------------------------------------------------------------------

inline Key operator+(const Key& a,
                                      const int& b)
{
    int temp = int(a) + b;
    if (temp > 11) temp -= 12;
    return Key(temp);
}

//------------------------------------------------------------------------------

inline bool operator==(const TargetChord::Desc& a, const TargetChord::Desc& b)
{
    return a.root == b.root and a.quality == b.quality and a.intervals == b.intervals;
}

//------------------------------------------------------------------------------

inline bool operator==(const TargetChord& a, const TargetChord& b)
{
    for (TargetChord::Desc element : a.desc_vec) {
        if (std::find(b.desc_vec.begin(), b.desc_vec.end(), element)
            != b.desc_vec.end()) {
            return true;
        }
    }
    return false;
}

#endif // CHORD_HPP