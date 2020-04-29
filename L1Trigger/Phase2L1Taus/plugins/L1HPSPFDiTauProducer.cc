#include "L1Trigger/Phase2L1Taus/interface/L1HPSPFDiTauProducer.h"

#include "FWCore/Utilities/interface/InputTag.h"

#include <cmath> // std::fabs

L1HPSPFDiTauProducer::L1HPSPFDiTauProducer(const edm::ParameterSet& cfg) 
  : max_dz_(cfg.getParameter<double>("max_dz"))
  , debug_(cfg.getUntrackedParameter<bool>("debug", false))
{

  srcL1HPSPFTaus_   = cfg.getParameter<edm::InputTag>("srcL1HPSPFTaus");
  tokenL1HPSPFTaus_ = consumes<l1t::L1HPSPFTauCollection>(srcL1HPSPFTaus_);

  produces<l1t::L1HPSPFDiTauCollection>();
}

L1HPSPFDiTauProducer::~L1HPSPFDiTauProducer()
{}


void L1HPSPFDiTauProducer::produce(edm::Event& evt, const edm::EventSetup& es)
{
  std::unique_ptr<l1t::L1HPSPFDiTauCollection> l1HPSPFDiTauCollection(new l1t::L1HPSPFDiTauCollection());

  edm::Handle<l1t::L1HPSPFTauCollection>  l1HPSPFTaus;
  evt.getByToken(tokenL1HPSPFTaus_,     l1HPSPFTaus);
  
  if ( debug_ )
    {
      int nTaus = l1HPSPFTaus->size();
      std::cout << " Number of Taus " << nTaus << std::endl;
    }
  
  for( size_t idxTau1 = 0; idxTau1 < l1HPSPFTaus->size(); idxTau1++ )
    {
      for( size_t idxTau2 = idxTau1 + 1; idxTau2 < l1HPSPFTaus->size(); idxTau2++ )
	{
	  edm::Ref<l1t::L1HPSPFTauCollection> leadingTau(l1HPSPFTaus, idxTau1);
	  edm::Ref<l1t::L1HPSPFTauCollection> subleadingTau(l1HPSPFTaus, idxTau2);

	  if ( leadingTau->leadChargedPFCand().isNonnull() && leadingTau->leadChargedPFCand()->pfTrack().isNonnull() && subleadingTau->leadChargedPFCand().isNonnull() && subleadingTau->leadChargedPFCand()->pfTrack().isNonnull() ) 
	    {
	      float z1 = leadingTau->leadChargedPFCand()->pfTrack()->vertex().z();
	      float z2 = subleadingTau->leadChargedPFCand()->pfTrack()->vertex().z();   
	      float dz = z1 - z2;
	      if ( std::fabs(dz) < max_dz_ )
		{
		  l1t::L1HPSPFDiTau l1HPSPFDiTau(leadingTau, subleadingTau, dz);
		  l1HPSPFDiTauCollection->push_back(l1HPSPFDiTau);
		}
	    }
	}
    }

  if ( debug_ )
    {
      std::cout << "AFTER selection : " << std::endl;
      for ( size_t idx = 0; idx < l1HPSPFDiTauCollection->size(); ++idx )
	{
	  const l1t::L1HPSPFDiTau l1PFTau = l1HPSPFDiTauCollection->at(idx);
	  std::cout << "L1HPSPFTau # " << idx << " dz_ " << l1PFTau.dz_ << " leadingTau Pt " << l1PFTau.leadingL1HPSPFTau_->pt() << " subleadingTau Pt " << l1PFTau.subleadingL1HPSPFTau_->pt() << std::endl;
	}
    }
  
  evt.put(std::move(l1HPSPFDiTauCollection));
  
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(L1HPSPFDiTauProducer);
