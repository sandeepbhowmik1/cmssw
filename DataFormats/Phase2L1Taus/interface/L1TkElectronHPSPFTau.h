#ifndef DataFormats_Phase2L1Taus_L1TkElectronHPSPFTau_H
#define DataFormats_Phase2L1Taus_L1TkElectronHPSPFTau_H

#include "DataFormats/Phase2L1Taus/interface/L1HPSPFTau.h" //l1t::L1HPSPFTau
#include "DataFormats/Phase2L1Taus/interface/L1HPSPFTauFwd.h" //l1t::L1HPSPFTauCollection 
#include "DataFormats/Common/interface/Ref.h" 
#include "DataFormats/L1TrackTrigger/interface/L1TkElectronParticle.h"
#include "DataFormats/L1TrackTrigger/interface/L1TkElectronParticleFwd.h"

// forward declation needed in order to declare L1TkElectronHPSPFTauProducer class as friend (that has access to private data-members) 
class L1TkElectronHPSPFTauProducer;

namespace l1t
{
  
  class L1TkElectronHPSPFTau : public reco::LeafCandidate
  {
  public:
    
    typedef edm::Ref<l1t::L1TkElectronParticleCollection > L1TkElectronParticleRef ;
    typedef edm::Ref<l1t::L1HPSPFTauCollection> L1HPSPFTauRef; 


    /// default constructor
    L1TkElectronHPSPFTau();

    L1TkElectronHPSPFTau(const L1TkElectronParticleRef & L1TkElectronParticle, const L1HPSPFTauRef & L1HPSPFTau)
      : L1TkElectronParticle_(L1TkElectronParticle)
      , L1HPSPFTau_(L1HPSPFTau)
    {}

    /// destructor
    ~L1TkElectronHPSPFTau();
    
    const L1TkElectronParticleRef & L1TkElectronParticle()    const { return L1TkElectronParticle_; }
    const L1HPSPFTauRef & L1HPSPFTau() const { return L1HPSPFTau_; }
    

    friend class ::L1TkElectronHPSPFTauProducer;
    
  private:
    L1TkElectronParticleRef L1TkElectronParticle_;
    L1HPSPFTauRef L1HPSPFTau_;
    
};

}

#endif 
