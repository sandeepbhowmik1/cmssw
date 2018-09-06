#ifndef L1TTRACKERPLUSBARRELSTUBSMATCHER_H
#define L1TTRACKERPLUSBARRELSTUBSMATCHER_H

#include "DataFormats/L1TMuon/interface/L1MuKBMTCombinedStub.h"
#include "DataFormats/L1TMuon/interface/RegionalMuonCandFwd.h"
#include "DataFormats/L1TrackTrigger/interface/L1TkMuonParticle.h"
#include "DataFormats/L1TrackTrigger/interface/L1TkMuonParticleFwd.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "L1Trigger/L1TTrackMatch/interface/L1TTrackerPlusBarrelStubsSectorProcessor.h"
class L1TTrackerPlusBarrelStubsMatcher {
 public:
  typedef std::vector<edm::Ptr< l1t::L1TkMuonParticle::L1TTTrackType > > TrackPtrVector;

  L1TTrackerPlusBarrelStubsMatcher(const edm::ParameterSet&);
  ~L1TTrackerPlusBarrelStubsMatcher();

  std::vector<l1t::L1TkMuonParticle> process(const TrackPtrVector& ,const L1MuKBMTCombinedStubRefVector& stub);
 private:
  int verbose_;
  std::vector<L1TTrackerPlusBarrelStubsSectorProcessor> sectors_;
  std::vector<l1t::L1TkMuonParticle> overlapClean(const std::vector<l1t::L1TkMuonParticle>&);
  int deltaPhi_(double p1,double p2);
  int phiProp_(int muPhi,int k,int sc,int st);
  bool muonCheck_(l1t::L1TkMuonParticle muon1, l1t::L1TkMuonParticle muon2);

};



#endif
