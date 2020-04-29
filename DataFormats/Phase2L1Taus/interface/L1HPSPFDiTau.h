#ifndef DataFormats_Phase2L1Taus_L1HPSPFDiTau_H
#define DataFormats_Phase2L1Taus_L1HPSPFDiTau_H

#include "DataFormats/Phase2L1Taus/interface/L1HPSPFTau.h" //l1t::L1HPSPFTau
#include "DataFormats/Phase2L1Taus/interface/L1HPSPFTauFwd.h" //l1t::L1HPSPFTauCollection 
#include "DataFormats/Common/interface/Ref.h" 

// forward declation needed in order to declare L1HPSPFDiTauProducer class as friend (that has access to private data-members) 
class L1HPSPFDiTauProducer;

namespace l1t
{
  
  class L1HPSPFDiTau : public reco::LeafCandidate
  {
  public:
    
    typedef edm::Ref<l1t::L1HPSPFTauCollection> L1HPSPFTauRef; 


    /// default constructor
    L1HPSPFDiTau();

    L1HPSPFDiTau(const L1HPSPFTauRef & leadingL1HPSPFTau, const L1HPSPFTauRef & subleadingL1HPSPFTau, float dz)
      : leadingL1HPSPFTau_(leadingL1HPSPFTau)
      , subleadingL1HPSPFTau_(subleadingL1HPSPFTau)
      , dz_(dz)
    {}

    /// destructor
    ~L1HPSPFDiTau();
    
    const L1HPSPFTauRef & leadingL1HPSPFTau()    const { return leadingL1HPSPFTau_; }
    const L1HPSPFTauRef & subleadingL1HPSPFTau() const { return subleadingL1HPSPFTau_; }
    
    float dz()                       const { return dz_; }
    
    friend class ::L1HPSPFDiTauProducer;
    
  private:
    L1HPSPFTauRef leadingL1HPSPFTau_;
    L1HPSPFTauRef subleadingL1HPSPFTau_;
    
    float dz_;
};

}

#endif 
