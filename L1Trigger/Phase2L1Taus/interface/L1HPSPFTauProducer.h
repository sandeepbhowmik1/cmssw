#ifndef L1Trigger_Phase2L1Taus_L1HPSPFTauProducer_h
#define L1Trigger_Phase2L1Taus_L1HPSPFTauProducer_h

#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"

#include "L1Trigger/Phase2L1Taus/interface/L1HPSPFTauQualityCut.h" // L1HPSPFTauQualityCut
#include "L1Trigger/Phase2L1Taus/interface/L1HPSPFTauBuilder.h"    // L1HPSPFTauBuilder
#include "DataFormats/Phase2L1Taus/interface/L1HPSPFTau.h"         // l1t::L1HPSPFTau
#include "DataFormats/Phase2L1Taus/interface/L1HPSPFTauFwd.h"      // l1t::L1HPSPFTauCollection
#include "DataFormats/L1TParticleFlow/interface/PFCandidate.h"       // l1t::PFCandidate, l1t::PFCandidateCollection, l1t::PFCandidateRef 
#include "DataFormats/JetReco/interface/CaloJet.h"                 
#include "DataFormats/L1TCorrelator/interface/TkPrimaryVertex.h"

#include <string>
#include <vector>

class L1HPSPFTauProducer : public edm::EDProducer 
{
 public:
  explicit L1HPSPFTauProducer(const edm::ParameterSet& cfg);
  ~L1HPSPFTauProducer();

 private:
  void produce(edm::Event& evt, const edm::EventSetup& es);

  std::string moduleLabel_;

  L1HPSPFTauBuilder* tauBuilder_;
  
  edm::InputTag srcL1PFCands_;
  edm::EDGetTokenT<l1t::PFCandidateCollection> tokenL1PFCands_;
  edm::InputTag srcL1Jets_;
  edm::EDGetTokenT<std::vector<reco::CaloJet>> tokenL1Jets_;
  edm::InputTag srcL1Vertices_;
  edm::EDGetTokenT<std::vector<l1t::TkPrimaryVertex>> tokenL1Vertices_;
  edm::InputTag srcRho_;
  edm::EDGetTokenT<double> tokenRho_;

  std::vector<L1HPSPFTauQualityCut> signalQualityCuts_dzCut_disabled_;
  std::vector<L1HPSPFTauQualityCut> isolationQualityCuts_dzCut_disabled_;

  bool useChargedPFCandSeeds_;
  double min_seedChargedPFCand_pt_;
  double max_seedChargedPFCand_eta_;
  double max_seedChargedPFCand_dz_;

  bool useJetSeeds_;
  double min_seedJet_pt_;
  double max_seedJet_eta_;

  double min_PFTau_pt_;
  double max_PFTau_eta_;
  double min_leadChargedPFCand_pt_;
  double max_leadChargedPFCand_eta_;
  double max_leadChargedPFCand_dz_;
  double max_chargedIso_;
  double max_chargedRelIso_;

  double deltaR_cleaning_;
  double deltaR2_cleaning_;

  bool applyPreselection_;

  bool debug_;
};

#endif
