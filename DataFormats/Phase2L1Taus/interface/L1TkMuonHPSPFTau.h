#ifndef DataFormats_Phase2L1Taus_L1TkMuonHPSPFTau_H
#define DataFormats_Phase2L1Taus_L1TkMuonHPSPFTau_H

#include "DataFormats/Phase2L1Taus/interface/L1HPSPFTau.h" //l1t::L1HPSPFTau
#include "DataFormats/Phase2L1Taus/interface/L1HPSPFTauFwd.h" //l1t::L1HPSPFTauCollection 
#include "DataFormats/Common/interface/Ref.h" 
#include "DataFormats/L1TrackTrigger/interface/L1TkMuonParticle.h"
#include "DataFormats/L1TrackTrigger/interface/L1TkMuonParticleFwd.h"

// forward declation needed in order to declare L1TkMuonHPSPFTauProducer class as friend (that has access to private data-members) 
class L1TkMuonHPSPFTauProducer;

namespace l1t
{
  
  class L1TkMuonHPSPFTau : public reco::LeafCandidate
  {
  public:

    typedef edm::Ref<l1t::L1TkMuonParticleCollection > L1TkMuonParticleRef ;
    typedef edm::Ref<l1t::L1HPSPFTauCollection> L1HPSPFTauRef; 


    /// default constructor
    L1TkMuonHPSPFTau();

    L1TkMuonHPSPFTau(const L1TkMuonParticleRef & L1TkMuonParticle, const L1HPSPFTauRef & L1HPSPFTau)
      : L1TkMuonParticle_(L1TkMuonParticle)
      , L1HPSPFTau_(L1HPSPFTau)
    {}

    /// destructor
    ~L1TkMuonHPSPFTau();
    
    const L1TkMuonParticleRef & L1TkMuonParticle()    const { return L1TkMuonParticle_; }
    const L1HPSPFTauRef & L1HPSPFTau() const { return L1HPSPFTau_; }
    

    friend class ::L1TkMuonHPSPFTauProducer;
    
  private:
    L1TkMuonParticleRef L1TkMuonParticle_;
    L1HPSPFTauRef L1HPSPFTau_;
    
};

}

#endif 
