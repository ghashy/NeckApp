/**
 * @file Neck.cpp.
 * @brief Implementation file for Neck class.
 *
 * Created by Ghashy.
 */

#include <stdexcept>
#include <vector>

#include "godot_cpp/core/class_db.hpp"
#include "godot_cpp/variant/dictionary.hpp"
#include "godot_cpp/variant/utility_functions.hpp"
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/variant/typed_array.hpp>

#include "Neck.hpp"
#include <Chord.hpp>

godot::Ref<TargetChord> make_ref(TargetChord);

void Neck::_bind_methods() {
    godot::ClassDB::bind_method(godot::D_METHOD("get_values"), &Neck::get_values);
    godot::ClassDB::bind_method(godot::D_METHOD("get_chords", "key", "is_modern_naming"),
                                &Neck::get_chords);
}

// SORRY FOR THIS FUNCTION :)
godot::Array Neck::get_chords(int key_p, bool is_modern_naming) {
    // No chords on second string
    if (current_str == GuitarString::_2) { return godot::Array(); }

    godot::Array array {};
    MusKey key {key_p};
    switch (current_deg) {
        case TargetChord::Degree::_1:
            array.push_back(make_ref(
                TargetChord().init(key, key, TargetChord::ChordList::min, is_modern_naming)));
            array.push_back(make_ref(
                TargetChord().init(key, key, TargetChord::ChordList::min_7, is_modern_naming)));
            array.push_back(make_ref(
                TargetChord().init(key, key, TargetChord::ChordList::sus2, is_modern_naming)));

            if (current_str != GuitarString::_3) {
                array.push_back(make_ref(TargetChord().init(
                    key, key, TargetChord::ChordList::sus4, is_modern_naming)));
                array.push_back(make_ref(TargetChord().init(
                    key, key, TargetChord::ChordList::m_9, is_modern_naming)));
                array.push_back(make_ref(TargetChord().init(
                    key, key, TargetChord::ChordList::m_add9_narrow, is_modern_naming)));
            }

            if (current_str != GuitarString::_3 and current_str != GuitarString::_4) {
                array.push_back(make_ref(TargetChord().init(
                    key, key, TargetChord::ChordList::m_add9_wide, is_modern_naming)));
            }

            break;
        case TargetChord::Degree::_2:
            array.push_back(make_ref(TargetChord().init(
                key, key + 2, TargetChord::ChordList::dim, is_modern_naming)));
            break;
        case TargetChord::Degree::_3:
            array.push_back(make_ref(TargetChord().init(
                key, key + 3, TargetChord::ChordList::maj, is_modern_naming)));
            array.push_back(make_ref(TargetChord().init(
                key, key + 3, TargetChord::ChordList::maj_7, is_modern_naming)));
            array.push_back(make_ref(TargetChord().init(
                key, key + 3, TargetChord::ChordList::sus2, is_modern_naming)));

            if (current_str != GuitarString::_3) {
                array.push_back(make_ref(TargetChord().init(
                    key, key + 3, TargetChord::ChordList::sus4, is_modern_naming)));
                array.push_back(make_ref(TargetChord().init(
                    key, key + 3, TargetChord::ChordList::add9_narrow, is_modern_naming)));
                array.push_back(make_ref(TargetChord().init(
                    key, key + 3, TargetChord::ChordList::_9, is_modern_naming)));
            }

            if (current_str != GuitarString::_3 and current_str != GuitarString::_4) {
                array.push_back(make_ref(TargetChord().init(
                    key, key + 3, TargetChord::ChordList::add9_wide, is_modern_naming)));
            }

            break;
        case TargetChord::Degree::_4:
            array.push_back(make_ref(TargetChord().init(
                key, key + 5, TargetChord::ChordList::min, is_modern_naming)));
            array.push_back(make_ref(TargetChord().init(
                key, key + 5, TargetChord::ChordList::min_7, is_modern_naming)));
            array.push_back(make_ref(TargetChord().init(
                key, key + 5, TargetChord::ChordList::sus2, is_modern_naming)));

            if (current_str != GuitarString::_3) {
                array.push_back(make_ref(TargetChord().init(
                    key, key + 5, TargetChord::ChordList::sus4, is_modern_naming)));
                array.push_back(make_ref(TargetChord().init(
                    key, key + 5, TargetChord::ChordList::m_9, is_modern_naming)));
                array.push_back(make_ref(TargetChord().init(
                    key, key + 5, TargetChord::ChordList::m_add9_narrow, is_modern_naming)));
            }

            if (current_str != GuitarString::_3 and current_str != GuitarString::_4) {
                array.push_back(make_ref(TargetChord().init(
                    key, key + 5, TargetChord::ChordList::m_add9_wide, is_modern_naming)));
            }

            break;
        case TargetChord::Degree::_5:
            array.push_back(make_ref(TargetChord().init(
                key, key + 7, TargetChord::ChordList::min, is_modern_naming)));
            array.push_back(make_ref(TargetChord().init(
                key, key + 7, TargetChord::ChordList::min_7, is_modern_naming)));

            if (current_str != GuitarString::_3) {
                array.push_back(make_ref(TargetChord().init(
                    key, key + 7, TargetChord::ChordList::sus4, is_modern_naming)));
            }

            break;
        case TargetChord::Degree::_6:
            array.push_back(make_ref(TargetChord().init(
                key, key + 8, TargetChord::ChordList::maj, is_modern_naming)));
            array.push_back(make_ref(TargetChord().init(
                key, key + 8, TargetChord::ChordList::maj_7, is_modern_naming)));
            array.push_back(make_ref(TargetChord().init(
                key, key + 8, TargetChord::ChordList::sus2, is_modern_naming)));

            if (current_str != GuitarString::_3) {
                array.push_back(make_ref(TargetChord().init(
                    key, key + 8, TargetChord::ChordList::add9_narrow, is_modern_naming)));
                array.push_back(make_ref(TargetChord().init(
                    key, key + 8, TargetChord::ChordList::_9, is_modern_naming)));
            }

            if (current_str != GuitarString::_3 and current_str != GuitarString::_4) {
                array.push_back(make_ref(TargetChord().init(
                    key, key + 8, TargetChord::ChordList::add9_wide, is_modern_naming)));
            }

            break;
        case TargetChord::Degree::_7:
            array.push_back(make_ref(TargetChord().init(
                key, key + 10, TargetChord::ChordList::maj, is_modern_naming)));
            array.push_back(make_ref(TargetChord().init(
                key, key + 10, TargetChord::ChordList::_7, is_modern_naming)));
            array.push_back(make_ref(TargetChord().init(
                key, key + 10, TargetChord::ChordList::sus2, is_modern_naming)));

            if (current_str != GuitarString::_3) {
                array.push_back(make_ref(TargetChord().init(
                    key, key + 10, TargetChord::ChordList::sus4, is_modern_naming)));
                array.push_back(make_ref(TargetChord().init(
                    key, key + 10, TargetChord::ChordList::add9_narrow, is_modern_naming)));
                array.push_back(make_ref(TargetChord().init(
                    key, key + 10, TargetChord::ChordList::_9, is_modern_naming)));
            }

            if (current_str != GuitarString::_3 and current_str != GuitarString::_4) {
                array.push_back(make_ref(TargetChord().init(
                    key, key + 10, TargetChord::ChordList::add9_wide, is_modern_naming)));
            }

            break;
        default: throw std::runtime_error("Error: undefined chord");
    }
    return array;
}

godot::Ref<TargetChord> make_ref(TargetChord chord) {
    godot::Ref<TargetChord> result {};
    result.instantiate();
    result->init(chord);
    return result;
}

godot::Dictionary Neck::get_values() {
    using namespace std;
    static vector<std::string> pairs(25);
    static int idx = 0;
    static int last_r {};

    // First step generation.
    int s = get_s_value();
    int d = get_d_value();

    // Fix duplicated pairs.
    fix(pairs, s, d, last_r, idx);

    // Add to vector.
    pairs[idx] = std::to_string(s) + "-" + std::to_string(d);

    last_r = d;
    if (idx < 24) idx++;
    else
        idx = 0;

    godot::Dictionary result {};
    result["string"] = s; // s
    result["degree"] = d; // d
    current_str = GuitarString(s);
    current_deg = TargetChord::Degree(d);
    return result;
}

void Neck::fix(std::vector<std::string>& pairs, int& s, int& d, int last, int idx) {
    std::string key = std::to_string(s) + "-" + std::to_string(d);

    while (std::find(pairs.begin(), pairs.end(), key) != pairs.end() or d == last
           or is_duplicated_two_times(pairs, s, idx)) {
        s = get_s_value();
        d = get_d_value();
        key = std::to_string(s) + "-" + std::to_string(d);
    }
}

bool Neck::is_duplicated_two_times(std::vector<std::string>& str, int s, int idx) {
    for (int i = 1; i < 3; i++) {
        std::stringstream stream {str[idx]};
        int temp;
        stream >> temp;
        if (temp == s) { return true; }
        idx -= i;
    }
    return false;
}

int Neck::get_d_value() {
    std::default_random_engine generator;
    generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> distribution(1, 7);
    auto dice = std::bind(distribution, generator);
    int value = dice();
    return value;
}

int Neck::get_s_value() {
    std::default_random_engine generator;
    generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> distribution(2, 6);
    auto dice = std::bind(distribution, generator);
    int value = dice();
    return value;
}