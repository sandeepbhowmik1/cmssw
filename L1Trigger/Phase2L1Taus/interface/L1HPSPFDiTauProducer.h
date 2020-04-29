#ifndef L1Trigger_Phase2L1Taus_L1HPSPFDiTauProducer_h
#define L1Trigger_Phase2L1Taus_L1HPSPFDiTauProducer_h

#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"

#include "DataFormats/Phase2L1Taus/interface/L1HPSPFDiTau.h"        // l1t::L1HPSPFDiTau
#include "DataFormats/Phase2L1Taus/interface/L1HPSPFDiTauFwd.h"     // l1t::L1HPSPFDiTauCollection
#include "DataFormats/Phase2L1Taus/interface/L1HPSPFTau.h"          // l1t::L1HPSPFTau
#include "DataFormats/Phase2L1Taus/interface/L1HPSPFTauFwd.h"       // l1t::L1HPSPFTauCollection  
//#include "L1Trigger/Phase2L1Taus/interface/L1HPSPFTauProducer.h"    // l1t::L1HPSPFTauCollection 

#include <string>
#include <vector>

class L1HPSPFDiTauProducer : public edm::EDProducer 
{
 public:
  explicit L1HPSPFDiTauProducer(const edm::ParameterSet& cfg);
  ~L1HPSPFDiTauProducer();

 private:
  void produce(edm::Event& evt, const edm::EventSetup& es);
  
  edm::InputTag srcL1HPSPFTaus_;
  edm::EDGetTokenT<l1t::L1HPSPFTauCollection>  tokenL1HPSPFTaus_;
  
  float max_dz_;
  
  bool debug_;
};

#endif
