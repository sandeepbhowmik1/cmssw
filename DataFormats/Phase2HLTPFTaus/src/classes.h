#include "Rtypes.h"

#include "DataFormats/TrackReco/interface/TrackBase.h"

#include "DataFormats/Phase2HLTPFTaus/interface/PFTauPair.h"    // reco::PFTauPair
#include "DataFormats/Phase2HLTPFTaus/interface/PFTauPairFwd.h" // reco::PFTauPairCollection

namespace DataFormats_Phase2HLTPFTaus
{
  struct dictionary 
  {
    //reco::TrackBase::Point point;
    edm::Wrapper<reco::TrackBase::Point> pointWrapper;

    reco::PFTauPair pfTauPair;
    reco::PFTauPairCollection pfTauPairCollection;
    edm::Wrapper<reco::PFTauPairCollection> pfTauPairCWrapper;
  };
}
