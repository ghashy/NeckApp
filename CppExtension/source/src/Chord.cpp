/*
 File: Chord.cpp.
 Description: Contains implementation for two classes: TargetChord and
 HearableChord

 Created by Ghashy, 2023.
*/


#include "Chord.hpp"
#include <ChordInfo.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/string.hpp>
#include <stdexcept>
#include <string>

void TargetChord::_bind_methods()
{
    godot::ClassDB::bind_method(godot::D_METHOD("get_chord_name"),
                                &TargetChord::get_chord_name);
}

//------------------------------------------------------------------------------

TargetChord& TargetChord::init(Key key, Key root, ChordList chord_p, bool is_modern_naming)
{
    // For define chord's name.
    chord_key = is_modern_naming ? get_amature_key(key, root, chord_p) : get_key(key, root, chord_p);
    chord = chord_p;
    Desc d1{};
    Desc d2{};
    d1.root = int(root);
    switch (chord_p) {
        case ChordList::min:
            d1.quality = 0;
            d1.intervals = 0;
            d2.root = int(root);
            d2.quality = 0;
            d2.intervals = 7;
            break;
        case ChordList::maj:
            d1.quality = 1;
            d1.intervals = 0;
            d2.root = int(root);
            d2.quality = 1;
            d2.intervals = 7;
            break;
        case ChordList::min_7:
            d1.quality = 0;
            d1.intervals = 7;
            d2 = d1;
            break;
        case ChordList::_7:
            d1.quality = 3;
            d1.intervals = 7;
            d2 = d1;
            break;
        case ChordList::maj_7:
            d1.quality = 1;
            d1.intervals = 7;
            d2 = d1;
            break;
        case ChordList::sus2:
            d1.quality = 2;
            d1.intervals = 2;
            d2 = d1;
            break;
        case ChordList::sus4:
            d1.root = int(root + 5);
            d1.quality = 2;
            d1.intervals = 2;
            d2 = d1;
            break;
        case ChordList::add9_narrow:
            d1.quality = 1;
            d1.intervals = 0;
            d2.root = d1.root;
            d2.quality = 2;
            d2.intervals = 2;
            break;
        case ChordList::add9_wide:
            d1.quality = 2;
            d1.intervals = 2;
            d2 = d1;
        case ChordList::m_add9_narrow:
            d1.quality = 0;
            d1.intervals = 7;
            d2.root = d1.root;
            d2.quality = 0;
            d2.intervals = 0;
            break;
        case ChordList::m_add9_wide:
            d1.quality = 2;
            d1.intervals = 2;
            d2 = d1;
            break;
        case ChordList::_9:
            d1.quality = 1;
            d1.intervals = 7;
            d2.root = d1.root;
            d2.quality = 3;
            d2.intervals = 7;
            break;
        case ChordList::m_9:
            d1.quality = 0;
            d1.intervals = 7;
            d2 = d1;
            break;
        case ChordList::dim:
            d1.quality = 4;
            d1.intervals = 0;
            d2 = d1;
            break;
        default: throw std::runtime_error("Error: unknown chord");
    }
    desc_vec.push_back(d1);
    desc_vec.push_back(d2);
    return *this;
}

//------------------------------------------------------------------------------

TargetChord& TargetChord::init(const TargetChord& target_chord)
{
    this->chord_key = target_chord.chord_key;
    this->chord = target_chord.chord;
    this->desc_vec = target_chord.desc_vec;
    return *this;
}

//------------------------------------------------------------------------------

godot::String set_letters_case(godot::String result, TargetChord::ChordList chord)
{
    switch (chord) {
        case TargetChord::ChordList::maj:
        case TargetChord::ChordList::_7:
        case TargetChord::ChordList::maj_7:
        case TargetChord::ChordList::sus2:
        case TargetChord::ChordList::sus4:
        case TargetChord::ChordList::add9_narrow:
        case TargetChord::ChordList::add9_wide:
        case TargetChord::ChordList::_9: break;
        default:
            result.to_lower();
    }
    return result;
}

//------------------------------------------------------------------------------

godot::String TargetChord::get_key(Key key, Key root, ChordList chord)
{
    using godot::String;

    String result {};
    switch (root) {
        case Key::A: result = String("A "); break;
        case Key::B: result = String("B "); break;
        case Key::H: result = String("H "); break;
        case Key::C: result = String("C "); break;
        case Key::Cis:
            if (key == Key::F or key == Key::B) { result = String("Des "); }
            else {
                result = String("Cis ");
            }
            break;
        case Key::D: result = String("D "); break;
        case Key::Dis:
            if (key == Key::C or key == Key::F or key == Key::G
                or key == Key::B) {
                result = String("Es ");
            }
            else {
                result = String("Dis ");
            }
            break;
        case Key::E: result = String("E "); break;
        case Key::F:
            if (key == Key::Dis) { result = String("Eis "); }
            else {
                result = String("F ");
            }
            break;
        case Key::Fis:
            if (key == Key::B) { result = String("Ges "); }
            else {
                result = String("Fis ");
            }
            break;
        case Key::G: result = String("G "); break;
        case Key::Gis:
            if (key == Key::C or key == Key::F or key == Key::B) {
                result = String("As ");
            }
            else {
                result = String("Gis ");
            }
            break;
        default: throw std::runtime_error("Error: unknown key");
    }
    return set_letters_case(result, chord);
}

//------------------------------------------------------------------------------

// Amature tonalities: C, C♯, D, D♯, E, F, F♯, G, G♯, A, B♭, B

godot::String TargetChord::get_amature_key(Key key, Key root, ChordList chord)
{
    using godot::String;
    String result{};
    switch (root) {
        case Key::A: result = String(L"A "); break;
        case Key::B: result = String(L"B♭ "); break;
        case Key::H: result = String(L"B "); break;
        case Key::C: result = String(L"C "); break;
        case Key::Cis:
            if (key == Key::F or key == Key::B) {
                result = String(L"D♭ ");
            }
            else {
                result = String(L"C♯ ");
            }
            break;
        case Key::D: result = String(L"D "); break;
        case Key::Dis:
            if (key == Key::C or key == Key::F or key == Key::G or key == Key::B) {
                result = String(L"E♭ ");
            }
            else {
                result = String(L"D♯ ");
            }
            break;
        case Key::E: result = String(L"E "); break;
        case Key::F:
            if (key == Key::Dis) {
                result = String(L"E♯ ");
            }
            else {
                result = String(L"F ");
            }
            break;
        case Key::Fis:
            if (key == Key::B) {
                result = String(L"G♭ ");
            }
            else {
                result = String(L"F♯ ");
            }
            break;
        case Key::G: result = String(L"G "); break;
        case Key::Gis:
            if (key == Key::C or key == Key::F or key == Key::B) {
                result = String(L"A♭ ");
            }
            else {
                result = String(L"G♯ ");
            }
            break;
        default: throw std::runtime_error("Error: unknown key");
    }
    return set_letters_case(result, chord);;
}

//------------------------------------------------------------------------------

godot::String TargetChord::get_chord_name() const
{
    using godot::String;
    String result = chord_key;
    switch (chord) {
        case ChordList::maj: break;
        case ChordList::min: result += String{"m"}; break;
        case ChordList::min_7: result += String{"m7"}; break;
        case ChordList::_7: result += String{"7"}; break;
        case ChordList::maj_7: result += String{"maj7"}; break;
        case ChordList::sus2: result += String{"sus2"}; break;
        case ChordList::sus4: result += String{"sus4"}; break;
        case ChordList::add9_narrow: result += String{"add9(n)"}; break;
        case ChordList::add9_wide: result += String{"add9(w)"}; break;
        case ChordList::m_add9_narrow: result += String{"madd9(n)"}; break;
        case ChordList::m_add9_wide: result += String{"madd9(w)"}; break;
        case ChordList::_9: result += String{"9"}; break;
        case ChordList::m_9: result += String{"m9"}; break;
        case ChordList::dim: result += String{"dim"}; break;
    }
    return result;
}

//------------------------------------------------------------------------------


void TargetChord::push(int root, int quality, int intervals)
{
    desc_vec.push_back(Desc{root, quality, intervals});
}

//------------------------------------------------------------------------------

bool TargetChord::compare(const TargetChord& heared) const
{
    return *this == heared;
}