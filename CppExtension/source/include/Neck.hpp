/**
 * @file Neck.hpp.
 * @brief Interface file for Neck class.
 *
 * Created by Ghashy.
 */

#ifndef NECK_HPP
#define NECK_HPP

#include "Chord.hpp"

#include <algorithm>
#include <chrono>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/variant/packed_int32_array.hpp>
#include <godot_cpp/variant/typed_array.hpp>
#include <random>
#include <sstream>
#include <string>
#include <vector>

#include "godot_cpp/variant/dictionary.hpp"
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/core/binder_common.hpp>

class Neck : public godot::RefCounted {
    private:
        GDCLASS(Neck, godot::RefCounted);
    public:

        enum class GuitarString { _2 = 2, _3, _4, _5, _6 };

        //----------------------------------------------------------------------

        godot::Dictionary get_values();
        /**
         * `brief:` Function for internal initialization of vector of Chords.
         *
         * `return:` size of vector (amount of available chords).
         */
        godot::Array get_chords(int key_p, bool is_modern_naming);
        Neck() {};
        ~Neck() {};
    protected:
        static void _bind_methods();
    private:
        GuitarString current_str {GuitarString::_2};
        TargetChord::Degree current_deg {TargetChord::Degree::_1};
        int get_d_value();
        int get_s_value();
        bool is_duplicated_two_times(std::vector<std::string>& str, int s,
                                     int idx);
        void fix(std::vector<std::string>& pairs, int& s, int& d, int last,
                 int idx);
};

#endif // NECK_HPP