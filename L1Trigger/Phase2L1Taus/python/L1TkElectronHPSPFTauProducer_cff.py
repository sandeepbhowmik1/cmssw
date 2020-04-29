import FWCore.ParameterSet.Config as cms

L1TkElectronHPSPFTauProducer = cms.EDProducer("L1TkElectronHPSPFTauProducer",
  srcL1TkElectrons          = cms.InputTag("L1TkElectrons:EG"),
  srcL1HPSPFTaus            = cms.InputTag("L1HPSPFTauProducerWithStripsWithoutPreselectionPF"),
  debug                     = cms.untracked.bool(False),                                  
)
