#include "L1Trigger/Phase2L1Taus/interface/L1TkElectronHPSPFTauProducer.h"

#include "FWCore/Utilities/interface/InputTag.h"

#include <cmath> // std::fabs

L1TkElectronHPSPFTauProducer::L1TkElectronHPSPFTauProducer(const edm::ParameterSet& cfg) 
  : debug_(cfg.getUntrackedParameter<bool>("debug", false))
{

  srcL1TkElectrons_   = cfg.getParameter<edm::InputTag>("srcL1TkElectrons");
  tokenL1TkElectrons_ = consumes<l1t::L1TkElectronParticleCollection>(srcL1TkElectrons_);

  srcL1HPSPFTaus_   = cfg.getParameter<edm::InputTag>("srcL1HPSPFTaus");
  tokenL1HPSPFTaus_ = consumes<l1t::L1HPSPFTauCollection>(srcL1HPSPFTaus_);

  produces<l1t::L1TkElectronHPSPFTauCollection>();
}

L1TkElectronHPSPFTauProducer::~L1TkElectronHPSPFTauProducer()
{}


void L1TkElectronHPSPFTauProducer::produce(edm::Event& evt, const edm::EventSetup& es)
{
  std::unique_ptr<l1t::L1TkElectronHPSPFTauCollection> l1TkElectronHPSPFTauCollection(new l1t::L1TkElectronHPSPFTauCollection());

  edm::Handle<l1t::L1TkElectronParticleCollection>  l1TkElectrons;
  evt.getByToken(tokenL1TkElectrons_,     l1TkElectrons);

  edm::Handle<l1t::L1HPSPFTauCollection>  l1HPSPFTaus;
  evt.getByToken(tokenL1HPSPFTaus_,     l1HPSPFTaus);
  
  if ( debug_ )
    {
      int nTaus = l1HPSPFTaus->size();
      std::cout << " Number of Taus " << nTaus << std::endl;
    }
  
  for( size_t idxElectron = 0; idxElectron < l1TkElectrons->size(); idxElectron++ )
    {
      for( size_t idxTau = 0; idxTau < l1HPSPFTaus->size(); idxTau++ )
	{
	  edm::Ref<l1t::L1TkElectronParticleCollection> electron(l1TkElectrons, idxElectron);
	  edm::Ref<l1t::L1HPSPFTauCollection> Tau(l1HPSPFTaus, idxTau);

	  if ( electron->getTrkPtr().isNonnull() && Tau->leadChargedPFCand().isNonnull() && Tau->leadChargedPFCand()->pfTrack().isNonnull() ) 
	    {
	      l1t::L1TkElectronHPSPFTau l1TkElectronHPSPFTau(electron, Tau);

	      l1TkElectronHPSPFTauCollection->push_back(l1TkElectronHPSPFTau);
	    }
	}
    }

  if ( debug_ )
    {
      std::cout << "AFTER selection : " << std::endl;
      for ( size_t idx = 0; idx < l1TkElectronHPSPFTauCollection->size(); ++idx )
	{
	  const l1t::L1TkElectronHPSPFTau l1PFTau = l1TkElectronHPSPFTauCollection->at(idx);
	  std::cout << "L1ElectronHPSPFTau # " << idx << " Electron Pt " << l1PFTau.L1TkElectronParticle_->pt() << " Tau Pt " << l1PFTau.L1HPSPFTau_->pt() << std::endl;
	}
    }

  evt.put(std::move(l1TkElectronHPSPFTauCollection));
  
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(L1TkElectronHPSPFTauProducer);
