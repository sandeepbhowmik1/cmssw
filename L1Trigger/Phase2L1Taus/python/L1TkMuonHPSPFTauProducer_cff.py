import FWCore.ParameterSet.Config as cms

L1TkMuonHPSPFTauProducer = cms.EDProducer("L1TkMuonHPSPFTauProducer",
  srcL1TkMuons          = cms.InputTag("L1TkMuons"),
  srcL1HPSPFTaus            = cms.InputTag("L1HPSPFTauProducerWithStripsWithoutPreselectionPF"),
  debug                     = cms.untracked.bool(False),                                  
)
