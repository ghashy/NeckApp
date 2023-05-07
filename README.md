# NeckApp

Neck is an app created for guitarists to learn notes, intervals and chords
on the 6-string guitar’s neck.

- This app made in the [Godot engine](https://github.com/godotengine/godot), with using a custom c++ extension.

- C++ extension uses the [Chromagram Estimation & Chord Detection](https://github.com/adamstark/Chord-Detector-and-Chromagram), and the [KISS FFT](https://github.com/mborgerding/kissfft) library.

- C++ extension is disabled in Simplified version branch.

## Principle

The basics of the program are two randomly generated numbers. The number on
the LEFT is the number of the scale degree (from 1 to 7). The number on the
RIGHT is the number of the guitar's string (from 2 to 6). Why not from 1 to 6?
Because the first string is the same as the sixth, so there is no need to learn
the notes on it. And there is no chords or intervals you can play from the first
string down to the next (because the first string is the last high string).

You can choose up to 12 minor keys to practice with various amount of
switching between them. For instance: you've chosen 4 keys - E, F#, G# and B;
now you can select how often they will change one another (after 3-5 generated
number, after 5-10 etc.); or you can choose only one key and practice in it as
long as you want.

After you found the reqired scale degree on the required string, you should
play all the intervals from this note. Here is a list of all intervals from all
degrees:

- I. Major second, minor third, perfect fourth, perfect fifth, minor sixth, minor seventh
- II. Minor second, minor third, perfect fourth, diminished fifth, minor sixth, minor seventh
- III. Major second, major third, perfect fourth, perfect fifth, major sixth, major seventh
- IV. Major second, minor third, perfect fourth, perfect fifth, major sixth, minor seventh
- V. Minor second, minor third, perfect fourth, perfect fifth, minor sixth, minor seventh
- VI. Major second, major third, augmented fourth, perfect fifth, major sixth, major seventh
- VII. Major second, major third, perfect fourth, perfect fifth, major sixth, minor seventh

### Here are all cords from all degrees that I practice for now:

        I. m, m7, sus2, sus4, m add9 narrow, m add9 wide, m9
        II. dim
        III. maj, maj7, sus2, sus4, add9 narrow, add9 wide, 9
        IV. m, m7, sus2, sus4, m add9 narrow, m add9 wide, m9
        V. m, m7, sus4
        VI. maj, maj7, sus2, add9 narrow, add9 wide, 9
        VII. maj, 7, sus2, sus4, add9 narrow, add9 wide, 9

### Some explanations are required. Since it's impossible to play all chords on all strings, there are some exceptions due to the current string:

        6th & 5th string - all chords are playable
        4th string - add9 wide & m add9 wide aren't playable
        3d string - sus4, all add9 and all 9 chords aren't playable
        2nd string - none of them are playable
        
Also, I must specify what do I mean by 'narrow' and 'wide' add9 chords. The
'narrow' one is the chord + second above the octave (for instance E-G-B-F#) and
the 'wide' one is sus2 + third above the octave (E-B-F#-G). There is, as well,
a rule which determines whether the cord is played or not. If the second is
minor - the sound of sus2, (m)add9 and (m)9 chords aren't nice to the ear.
It's not forbidden, of course, to play them, but the result sounds not quite
harmoniously, so I evade it. Also, if there is triton - sus4 chord will sound
unharmoniously as well.

### How do I recomend to practice using this app (including examples in brackets):

1. Chose the key/keys, alternation and press 'START' (E)
2. Find needed degree and string according to generated numbers and play it (4 : 5)
3. Play intervals from second to seventh with the string below (The root note of each interval is A on the fifth string, and the second note of each interval is on the fourth string; intervals are as follows: major second, minor third, perfect fourth, perfect fifth, major sixth, minor seventh)
4. Play chords with the given root note (The cords are: Am, Am7, Asus2, Asus4, Am add9 narrow, Am add9 wide, Am9)
5. Press 'NEXT' and move to the next pair of generated numbers. Or press 'FINISH' to stop practicing.
