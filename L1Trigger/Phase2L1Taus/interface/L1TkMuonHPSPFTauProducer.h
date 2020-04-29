#ifndef L1Trigger_Phase2L1Taus_L1TkMuonHPSPFTauProducer_h
#define L1Trigger_Phase2L1Taus_L1TkMuonHPSPFTauProducer_h

#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"

#include "DataFormats/Phase2L1Taus/interface/L1TkMuonHPSPFTau.h"        // l1t::L1TkMuonHPSPFTau
#include "DataFormats/Phase2L1Taus/interface/L1TkMuonHPSPFTauFwd.h"     // l1t::L1TkMuonHPSPFTauCollection
#include "DataFormats/Phase2L1Taus/interface/L1HPSPFTau.h"          // l1t::L1HPSPFTau
#include "DataFormats/Phase2L1Taus/interface/L1HPSPFTauFwd.h"       // l1t::L1HPSPFTauCollection  
#include "DataFormats/L1TrackTrigger/interface/L1TkMuonParticle.h" 
#include "DataFormats/L1TrackTrigger/interface/L1TkMuonParticleFwd.h"

#include <string>
#include <vector>

class L1TkMuonHPSPFTauProducer : public edm::EDProducer 
{
 public:
  explicit L1TkMuonHPSPFTauProducer(const edm::ParameterSet& cfg);
  ~L1TkMuonHPSPFTauProducer();

 private:
  void produce(edm::Event& evt, const edm::EventSetup& es);

  edm::InputTag srcL1TkMuons_;
  edm::EDGetTokenT<l1t::L1TkMuonParticleCollection>  tokenL1TkMuons_;

  edm::InputTag srcL1HPSPFTaus_;
  edm::EDGetTokenT<l1t::L1HPSPFTauCollection>  tokenL1HPSPFTaus_;

  bool debug_;
};

#endif
