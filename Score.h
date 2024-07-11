/*
  Yucong Jiang, June 2021
*/

#ifndef SCORE_H
#define SCORE_H

#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

#include "Templates.h"


struct Fraction // Simplest form using GCD.
{
    int numerator;
    int denominator;

    Fraction() : numerator{0}, denominator{1} { }
    Fraction(int n, int d) {
        int div = gcd(n, d);
        numerator = n/div;
        denominator = d/div;
    }

    static int gcd(int p, int q) {
        if (q == 0) {
            return p;
        } else {
            return gcd(q, p % q);
        }
    }

    static Fraction fromString(const std::string &s) {
        std::string n, d;
        std::istringstream iss(s);
        getline(iss, n, '/');
        getline(iss, d, '/');
        return Fraction(stoi(n), stoi(d));
    }

    double getValue() const {
        if (denominator == 0) {
            std::cerr<<"denominator is zero in Fraction::getValue()."<<"\n";
            return 0;
        }
        return (double)numerator / (double)denominator;
    }

    bool operator==(const Fraction &other) const { // default c++20
        if (numerator == other.numerator && denominator == other.denominator)
            return true;
        return false;
    }

    Fraction(const Fraction&) = default;

    Fraction& operator=(const Fraction&) = default;

    bool operator<(const Fraction& other) const {
        int n = numerator;
    	int d = denominator;
    	int nn = other.numerator;
    	int dd = other.denominator;
    	return (n * dd < nn * d);
    }

    Fraction operator-(const Fraction& other) const {
        int n = numerator;
    	int d = denominator;
    	int nn = other.numerator;
    	int dd = other.denominator;
    	return (Fraction(n*dd - d*nn, d*dd));
    }
};

std::ostream& operator<<(std::ostream &strm, const Fraction &f);

class Score
{
public:
    Score();
    ~Score();

    struct MeasureInfo
    {
        int measureNumber;
        Fraction measurePosition; // position within the measure
        Fraction measureFraction; // cumulative fraction in the entire piece

        MeasureInfo(int mn, Fraction mp, Fraction mf): measureNumber{mn},
         measurePosition{mp}, measureFraction{mf} { }
        
        bool operator==(const MeasureInfo &other) const { // default c++20
            if (measureNumber == other.measureNumber &&
             measurePosition == other.measurePosition)
                return true;
            return false;
        }

        bool operator<(const MeasureInfo& other) const { // ignore measureFraction
            if (measureNumber < other.measureNumber) return true;
            else if(measureNumber > other.measureNumber) return false;
            else return measurePosition < other.measurePosition;
        }

        bool operator>=(const MeasureInfo& other) const { // ignore measureFraction
            return (*this == other) || (other < *this);
        }

        std::string toLabel() const {
            return std::to_string(measureNumber) + "+"
                + std::to_string(measurePosition.numerator) + "/"
                + std::to_string(measurePosition.denominator);
        }
    };

    struct Note
    {
        bool isNewNote; // is an emerging note as opposed to a continuing note
        int midiNumber;
        std::string noteId; // from MEI

        Note(bool nn, int mn, std::string ni) : isNewNote{nn}, midiNumber{mn}, noteId{ni} { }
    };

    struct MusicalEvent
    {
        MeasureInfo measureInfo;
        std::vector<Note> notes;
        Template eventTemplate;
        Fraction duration;
        float tempo { 120. }; // e.g., Quarter note = 120.0
        int meterNumer; // e.g., 3
        int meterDenom; // e.g., 4

        MusicalEvent(MeasureInfo mi) : measureInfo{mi} { }
    };

    struct TempoChange
    {
        // Example on scores: quarter note = 120 bpm
        MeasureInfo measureInfo;
        float newTempo;
        float noteLength; // Quarter note = 1.0, eighth note = 0.5, etc.

        TempoChange(MeasureInfo mi, float t, float n) : measureInfo{mi},
         newTempo{t}, noteLength{n} { }
    };

    struct MeterChange
    {
        int measureNumber;
        int numer;
        int denom;

        MeterChange(int mn, int n, int d): measureNumber{mn}, numer{n}, denom{d} { }
    };

    typedef std::vector<MusicalEvent> MusicalEventList;
    typedef std::vector<TempoChange> TempoChangeList;
    typedef std::vector<MeterChange> MeterChangeList;

    bool initialize(std::string scoreFilePath);
    bool readTempo(std::string tempoFilePath);
    bool readMeter(std::string meterFilePath);

    const MusicalEventList& getMusicalEvents() const;

    void setEventTemplates(NoteTemplates& t);

private:
    MusicalEventList m_musicalEvents;
    TempoChangeList m_tempoChanges;
    MeterChangeList m_meterChanges;
};

#endif
