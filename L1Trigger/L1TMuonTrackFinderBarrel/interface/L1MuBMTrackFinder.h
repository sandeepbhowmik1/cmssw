//-------------------------------------------------
//
/**  \class L1MuBMTrackFinder
 *
 *   L1 barrel Muon Trigger Track Finder (MTTF)
 *
 *   The barrel MTTF consists of:
 *      - 72 Sector Processors (SP),
 *      - 12 Eta Processors,
 *      - 12 Wedge Sorters (WS) and
 *      -  1 BM Muon Sorter (MS)
 *
 *
 *
 *   N. Neumeister            CERN EP
 *   J. Troconiz              UAM Madrid
 */
//
//--------------------------------------------------
#ifndef L1MUBM_TRACK_FINDER_H
#define L1MUBM_TRACK_FINDER_H

//---------------
// C++ Headers --
//---------------

#include <vector>
#include <iostream>
//----------------------
// Base Class Headers --
//----------------------

#include <map>

//------------------------------------
// Collaborating Class Declarations --
//------------------------------------

#include <FWCore/Framework/interface/Event.h>
#include <FWCore/ParameterSet/interface/ParameterSet.h>
#include "FWCore/Framework/interface/ConsumesCollector.h"
#include "L1Trigger/L1TMuonBarrel/interface/L1MuBMTrack.h"

#include "DataFormats/L1TMuon/interface/RegionalMuonCand.h"

class L1MuBMTFConfig;
class L1MuBMSecProcMap;
class L1MuBMSecProcId;
class L1MuBMSectorProcessor;
class L1MuBMEtaProcessor;
class L1MuBMWedgeSorter;
class L1MuBMMuonSorter;
class BMTrackCand;
class L1MuRegionalCand;

//              ---------------------
//              -- Class Interface --
//              ---------------------


class L1MuBMTrackFinder {

  public:

    /// container for muon candidates
    typedef l1t::RegionalMuonCandBxCollection::const_iterator TFtracks_const_iter;
    typedef l1t::RegionalMuonCandBxCollection::iterator       TFtracks_iter;

    /// constructor
    L1MuBMTrackFinder(const edm::ParameterSet & ps, edm::ConsumesCollector && iC);

    /// destructor
    virtual ~L1MuBMTrackFinder();

    /// build the structure of the barrel MTTF
    void setup();

    /// run the barrel MTTF
    void run(const edm::Event& e, const edm::EventSetup& c);

    /// reset the barrel MTTF
    void reset();

    inline int setAdd(int ust, int rel_add);

    /// get a pointer to a Sector Processor
    const L1MuBMSectorProcessor* sp(const L1MuBMSecProcId&) const;

    /// get a pointer to an Eta Processor, index [0-11]
    inline const L1MuBMEtaProcessor* ep(int id) const { return m_epvec[id]; }

    /// get a pointer to a Wedge Sorter, index [0-11]
    inline const L1MuBMWedgeSorter* ws(int id) const { return m_wsvec[id]; }

    /// get a pointer to the BM Muon Sorter
    inline const L1MuBMMuonSorter* ms() const { return m_ms; }

    /// get number of muon candidates found by the barrel MTTF
    int numberOfTracks();

    TFtracks_const_iter begin(int bx);

    TFtracks_const_iter end(int bx);

    void clear();

    /// get number of muon candidates found by the barrel MTTF at a given bx
    int numberOfTracks(int bx);

    /// return configuration
    static L1MuBMTFConfig* config() { return m_config; }

    std::vector<BMTrackCand>& getcache0() { return _cache0; }

    l1t::RegionalMuonCandBxCollection& getcache() { return _cache; }

  private:

    /// run Track Finder and store candidates in cache
    virtual void reconstruct(const edm::Event& e, const edm::EventSetup& c) { reset(); run(e,c); }

  private:

    std::vector<BMTrackCand>     _cache0;
    l1t::RegionalMuonCandBxCollection _cache;
    L1MuBMSecProcMap*                m_spmap;        ///< Sector Processors
    std::vector<L1MuBMEtaProcessor*> m_epvec;        ///< Eta Processors
    std::vector<L1MuBMWedgeSorter*>  m_wsvec;        ///< Wedge Sorters
    L1MuBMMuonSorter*                m_ms;           ///< BM Muon Sorter

    static L1MuBMTFConfig*           m_config;       ///< Track Finder configuration

    std::map<int,int> eta_map ={
    { -32,  -119},{ -31,  -115},{ -30,  -111},{ -29,  -107},{ -28,  -104},{ -27,  -100},{ -26,   -96},{ -25,   -92},{ -24,   -89},{ -23,   -85},
    { -22,   -81},{ -21,   -77},{ -20,   -74},{ -19,   -70},{ -18,   -66},{ -17,   -62},{ -16,   -59},{ -15,   -55},{ -14,   -51},{ -13,   -47},
    { -12,   -44},{ -11,   -40},{ -10,   -36},{  -9,   -32},{  -8,   -29},{  -7,   -25},{  -6,   -21},{  -5,   -17},{  -4,   -14},{  -3,   -10},
    {  -2,    -6},{  -1,    -2},{   0,     1},{   1,     5},{   2,     9},{   3,    13},{   4,    16},{   5,    20},{   6,    24},{   7,    28},
    {   8,    31},{   9,    35},{  10,    39},{  11,    43},{  12,    46},{  13,    50},{  14,    54},{  15,    58},{  16,    61},{  17,    65},
    {  18,    69},{  19,    73},{  20,    76},{  21,    80},{  22,    84},{  23,    88},{  24,    91},{  25,    95},{  26,    99},{  27,   103},
    {  28,   106},{  29,   110},{  30,   114},{  31,   118}};


};

#endif
