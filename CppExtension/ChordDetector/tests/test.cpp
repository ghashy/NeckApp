#include <catch2/catch_test_macros.hpp>
#include "Chromagram.h"
#include "ChordDetector.h"
#include "Test_Signals.h"

TEST_CASE( "C_Major_44_1") {
    int frameSize = 1024;
    
    Chromagram c(frameSize,44100);
    
    std::vector<double> frame(frameSize);
    
    for (int i = 0;i < 8192;i = i + frameSize)
    {
        for (int k = 0;k < frameSize;k++)
        {
            frame[k] = C_Major_44_1[i+k];
        }
        
        c.processAudioFrame(frame);
        
        if (c.isReady())
        {
            std::vector<double> chroma = c.getChromagram();
            
            REQUIRE(chroma[0] > chroma[1]);
            REQUIRE(chroma[0] > chroma[2]);
            REQUIRE(chroma[0] > chroma[3]);
            REQUIRE(chroma[0] > chroma[5]);
            REQUIRE(chroma[0] > chroma[6]);
            REQUIRE(chroma[0] > chroma[8]);
            REQUIRE(chroma[0] > chroma[9]);
            REQUIRE(chroma[0] > chroma[10]);
            REQUIRE(chroma[0] > chroma[11]);
            
            REQUIRE(chroma[4] > chroma[1]);
            REQUIRE(chroma[4] > chroma[2]);
            REQUIRE(chroma[4] > chroma[3]);
            REQUIRE(chroma[4] > chroma[5]);
            REQUIRE(chroma[4] > chroma[6]);
            REQUIRE(chroma[4] > chroma[8]);
            REQUIRE(chroma[4] > chroma[9]);
            REQUIRE(chroma[4] > chroma[10]);
            REQUIRE(chroma[4] > chroma[11]);
            
            REQUIRE(chroma[7] > chroma[1]);
            REQUIRE(chroma[7] > chroma[2]);
            REQUIRE(chroma[7] > chroma[3]);
            REQUIRE(chroma[7] > chroma[5]);
            REQUIRE(chroma[7] > chroma[6]);
            REQUIRE(chroma[7] > chroma[8]);
            REQUIRE(chroma[7] > chroma[9]);
            REQUIRE(chroma[7] > chroma[10]);
            REQUIRE(chroma[7] > chroma[11]);
        }
    }
}

TEST_CASE("CMajor48kHz")
{
    int frameSize = 1024;
    
    Chromagram c(frameSize,48000);
    
    double frame[frameSize];
    
    for (int i = 0;i < 8192;i = i + frameSize)
    {
        for (int k = 0;k < frameSize;k++)
        {
            frame[k] = C_Major_48[i+k];
        }
        
        c.processAudioFrame(frame);
        
        if (c.isReady())
        {
            std::vector<double> chroma = c.getChromagram();
            
            REQUIRE(chroma[0] > chroma[1]);
            REQUIRE(chroma[0] > chroma[2]);
            REQUIRE(chroma[0] > chroma[3]);
            REQUIRE(chroma[0] > chroma[5]);
            REQUIRE(chroma[0] > chroma[6]);
            REQUIRE(chroma[0] > chroma[8]);
            REQUIRE(chroma[0] > chroma[9]);
            REQUIRE(chroma[0] > chroma[10]);
            REQUIRE(chroma[0] > chroma[11]);
            
            REQUIRE(chroma[4] > chroma[1]);
            REQUIRE(chroma[4] > chroma[2]);
            REQUIRE(chroma[4] > chroma[3]);
            REQUIRE(chroma[4] > chroma[5]);
            REQUIRE(chroma[4] > chroma[6]);
            REQUIRE(chroma[4] > chroma[8]);
            REQUIRE(chroma[4] > chroma[9]);
            REQUIRE(chroma[4] > chroma[10]);
            REQUIRE(chroma[4] > chroma[11]);
            
            REQUIRE(chroma[7] > chroma[1]);
            REQUIRE(chroma[7] > chroma[2]);
            REQUIRE(chroma[7] > chroma[3]);
            REQUIRE(chroma[7] > chroma[5]);
            REQUIRE(chroma[7] > chroma[6]);
            REQUIRE(chroma[7] > chroma[8]);
            REQUIRE(chroma[7] > chroma[9]);
            REQUIRE(chroma[7] > chroma[10]);
            REQUIRE(chroma[7] > chroma[11]);
        }
    }

}

TEST_CASE("CMajor")
{
    ChordDetector chordDetector;
    
    double chroma[12] = {1,0,0,0,1,0,0,1,0,0,0,0};
    
    chordDetector.detectChord(chroma);
    
    REQUIRE(chordDetector.rootNote == 0);
    REQUIRE(chordDetector.quality == ChordDetector::Major);
    REQUIRE(chordDetector.intervals == 0);
}

//======================================================================
TEST_CASE("CMinor")
{
    ChordDetector chordDetector;
    
    double chroma[12] = {1,0,0,1,0,0,0,1,0,0,0,0};
    
    chordDetector.detectChord(chroma);
    
    REQUIRE(chordDetector.rootNote == 0);
    REQUIRE(chordDetector.quality == ChordDetector::Minor);
    REQUIRE(chordDetector.intervals == 0);
}