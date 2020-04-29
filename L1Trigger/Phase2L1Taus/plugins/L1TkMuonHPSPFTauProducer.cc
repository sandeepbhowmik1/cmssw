#include "L1Trigger/Phase2L1Taus/interface/L1TkMuonHPSPFTauProducer.h"

#include "FWCore/Utilities/interface/InputTag.h"

#include <cmath> // std::fabs

L1TkMuonHPSPFTauProducer::L1TkMuonHPSPFTauProducer(const edm::ParameterSet& cfg) 
  : debug_(cfg.getUntrackedParameter<bool>("debug", false))
{

  srcL1TkMuons_   = cfg.getParameter<edm::InputTag>("srcL1TkMuons");
  tokenL1TkMuons_ = consumes<l1t::L1TkMuonParticleCollection>(srcL1TkMuons_);

  srcL1HPSPFTaus_   = cfg.getParameter<edm::InputTag>("srcL1HPSPFTaus");
  tokenL1HPSPFTaus_ = consumes<l1t::L1HPSPFTauCollection>(srcL1HPSPFTaus_);

  produces<l1t::L1TkMuonHPSPFTauCollection>();
}

L1TkMuonHPSPFTauProducer::~L1TkMuonHPSPFTauProducer()
{}


void L1TkMuonHPSPFTauProducer::produce(edm::Event& evt, const edm::EventSetup& es)
{
  std::unique_ptr<l1t::L1TkMuonHPSPFTauCollection> l1TkMuonHPSPFTauCollection(new l1t::L1TkMuonHPSPFTauCollection());

  edm::Handle<l1t::L1TkMuonParticleCollection>  l1TkMuons;
  evt.getByToken(tokenL1TkMuons_,     l1TkMuons);

  edm::Handle<l1t::L1HPSPFTauCollection>  l1HPSPFTaus;
  evt.getByToken(tokenL1HPSPFTaus_,     l1HPSPFTaus);
  
  if ( debug_ )
    {
      int nTaus = l1HPSPFTaus->size();
      std::cout << " Number of Taus " << nTaus << std::endl;
    }
  
  for( size_t idxMuon = 0; idxMuon < l1TkMuons->size(); idxMuon++ )
    {
      for( size_t idxTau = 0; idxTau < l1HPSPFTaus->size(); idxTau++ )
	{
	  edm::Ref<l1t::L1TkMuonParticleCollection> electron(l1TkMuons, idxMuon);
	  edm::Ref<l1t::L1HPSPFTauCollection> Tau(l1HPSPFTaus, idxTau);

	  if ( electron->getTrkPtr().isNonnull() && Tau->leadChargedPFCand().isNonnull() && Tau->leadChargedPFCand()->pfTrack().isNonnull() ) 
	    {
	      l1t::L1TkMuonHPSPFTau l1TkMuonHPSPFTau(electron, Tau);

	      l1TkMuonHPSPFTauCollection->push_back(l1TkMuonHPSPFTau);
	    }
	}
    }

  if ( debug_ )
    {
      std::cout << "AFTER selection : " << std::endl;
      for ( size_t idx = 0; idx < l1TkMuonHPSPFTauCollection->size(); ++idx )
	{
	  const l1t::L1TkMuonHPSPFTau l1PFTau = l1TkMuonHPSPFTauCollection->at(idx);
	  std::cout << "L1MuonHPSPFTau # " << idx << " Muon Pt " << l1PFTau.L1TkMuonParticle_->pt() << " Tau Pt " << l1PFTau.L1HPSPFTau_->pt() << std::endl;
	}
    }

  evt.put(std::move(l1TkMuonHPSPFTauCollection));
  
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(L1TkMuonHPSPFTauProducer);
