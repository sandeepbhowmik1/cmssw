#ifndef L1Trigger_Phase2L1Taus_L1TkElectronHPSPFTauProducer_h
#define L1Trigger_Phase2L1Taus_L1TkElectronHPSPFTauProducer_h

#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"

#include "DataFormats/Phase2L1Taus/interface/L1TkElectronHPSPFTau.h"        // l1t::L1TkElectronHPSPFTau
#include "DataFormats/Phase2L1Taus/interface/L1TkElectronHPSPFTauFwd.h"     // l1t::L1TkElectronHPSPFTauCollection
#include "DataFormats/Phase2L1Taus/interface/L1HPSPFTau.h"          // l1t::L1HPSPFTau
#include "DataFormats/Phase2L1Taus/interface/L1HPSPFTauFwd.h"       // l1t::L1HPSPFTauCollection  
#include "DataFormats/L1TrackTrigger/interface/L1TkElectronParticle.h" 
#include "DataFormats/L1TrackTrigger/interface/L1TkElectronParticleFwd.h"

#include <string>
#include <vector>

class L1TkElectronHPSPFTauProducer : public edm::EDProducer 
{
 public:
  explicit L1TkElectronHPSPFTauProducer(const edm::ParameterSet& cfg);
  ~L1TkElectronHPSPFTauProducer();

 private:
  void produce(edm::Event& evt, const edm::EventSetup& es);

  edm::InputTag srcL1TkElectrons_;
  edm::EDGetTokenT<l1t::L1TkElectronParticleCollection>  tokenL1TkElectrons_;

  edm::InputTag srcL1HPSPFTaus_;
  edm::EDGetTokenT<l1t::L1HPSPFTauCollection>  tokenL1HPSPFTaus_;

  bool debug_;
};

#endif
