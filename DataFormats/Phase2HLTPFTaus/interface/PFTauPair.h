#ifndef DataFormats_Phase2HLTPFTaus_PFTauPair_h
#define DataFormats_Phase2HLTPFTaus_PFTauPair_h

#include "DataFormats/Candidate/interface/LeafCandidate.h" // reco::LeafCandidate
#include "DataFormats/TauReco/interface/PFTau.h"           // reco::PFTau
#include "DataFormats/TauReco/interface/PFTauFwd.h"        // reco::PFTauRef

namespace reco
{
  class PFTauPair : public reco::LeafCandidate
  {
   public:
    PFTauPair();
    PFTauPair(const reco::PFTauRef& leadPFTau, double leadPFTau_sumChargedIso, const reco::PFTauRef& subleadPFTau, double subleadPFTau_sumChargedIso, double dz);
    ~PFTauPair();

    const reco::PFTauRef& leadPFTau() const;
    double leadPFTau_sumChargedIso() const;

    const reco::PFTauRef& subleadPFTau() const;
    double subleadPFTau_sumChargedIso() const;

    double dz() const;

   private:
    reco::PFTauRef leadPFTau_;
    double leadPFTau_sumChargedIso_;

    reco::PFTauRef subleadPFTau_;
    double subleadPFTau_sumChargedIso_;
 
    double dz_;
  };

  std::ostream& operator<<(std::ostream& out, const PFTauPair& pfTauPair);

} // end namespace reco

#endif
