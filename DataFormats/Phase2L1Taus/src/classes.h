#include "Rtypes.h"

#include "DataFormats/Common/interface/Wrapper.h"  
#include "DataFormats/Phase2L1Taus/interface/L1HPSPFTau.h"
#include "DataFormats/Phase2L1Taus/interface/L1HPSPFTauFwd.h"
#include "DataFormats/Phase2L1Taus/interface/L1HPSPFDiTau.h"
#include "DataFormats/Phase2L1Taus/interface/L1HPSPFDiTauFwd.h"
#include "DataFormats/Phase2L1Taus/interface/L1TkElectronHPSPFTau.h"
#include "DataFormats/Phase2L1Taus/interface/L1TkElectronHPSPFTauFwd.h"
#include "DataFormats/Phase2L1Taus/interface/L1TkMuonHPSPFTau.h"
#include "DataFormats/Phase2L1Taus/interface/L1TkMuonHPSPFTauFwd.h"

namespace DataFormats_Phase2L1Taus
{
  struct dictionary 
  {
    l1t::L1HPSPFTau l1hpspftau;
    l1t::L1HPSPFTauCollection l1hpspftauCollection;
    edm::Wrapper<l1t::L1HPSPFTauCollection> l1hpspftauCWrapper;
    edm::Ref<l1t::L1HPSPFTauCollection> l1hpspftauCRef;
    edm::RefVector<l1t::L1HPSPFTauCollection> l1hpspftauCRefVector;

    l1t::L1HPSPFDiTau l1hpspfditau;
    l1t::L1HPSPFDiTauCollection l1hpspfditauCollection;
    edm::Wrapper<l1t::L1HPSPFDiTauCollection> l1hpspfditauCWrapper;
    edm::Ref<l1t::L1HPSPFDiTauCollection> l1hpspfditauCRef;
    edm::RefVector<l1t::L1HPSPFDiTauCollection> l1hpspfditauCRefVector;

    l1t::L1TkElectronHPSPFTau l1tkelectronhpspftau;
    l1t::L1TkElectronHPSPFTauCollection l1tkelectronhpspftauCollection;
    edm::Wrapper<l1t::L1TkElectronHPSPFTauCollection> l1tkelectronhpspftauCWrapper;
    edm::Ref<l1t::L1TkElectronHPSPFTauCollection> l1tkelectronhpspftauCRef;
    edm::RefVector<l1t::L1TkElectronHPSPFTauCollection> l1tkelectronhpspftauCRefVector;

    l1t::L1TkMuonHPSPFTau l1tkmuonhpspftau;
    l1t::L1TkMuonHPSPFTauCollection l1tkmuonhpspftauCollection;
    edm::Wrapper<l1t::L1TkMuonHPSPFTauCollection> l1tkmuonhpspftauCWrapper;
    edm::Ref<l1t::L1TkMuonHPSPFTauCollection> l1tkmuonhpspftauCRef;
    edm::RefVector<l1t::L1TkMuonHPSPFTauCollection> l1tkmuonhpspftauCRefVector;
  };
}
