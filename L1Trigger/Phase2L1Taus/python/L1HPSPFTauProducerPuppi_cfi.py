import FWCore.ParameterSet.Config as cms

L1HPSPFTauProducerPuppi = cms.EDProducer("L1HPSPFTauProducer",
  srcL1PFCands              = cms.InputTag("l1pfCandidates:Puppi"),                                      
  srcL1Jets               = cms.InputTag("Phase1L1TJetProducer:UncalibratedPhase1L1TJetFromPfCandidates"),
  srcL1Vertices             = cms.InputTag("L1TkPrimaryVertex"),
  useChargedPFCandSeeds     = cms.bool(True),                          
  min_seedChargedPFCand_pt  = cms.double(5.),
  max_seedChargedPFCand_eta = cms.double(2.4),
  max_seedChargedPFCand_dz  = cms.double(1.e+3),
  useJetSeeds             = cms.bool(True),                          
  min_seedJet_pt          = cms.double(30.),
  max_seedJet_eta         = cms.double(2.4),
  signalConeSize            = cms.string("2.8/max(1., pt)"),
  min_signalConeSize        = cms.double(0.05),
  max_signalConeSize        = cms.double(0.10),
  useStrips                 = cms.bool(True),                                           
  stripSize_eta             = cms.double(0.05),
  stripSize_phi             = cms.double(0.20),
  isolationConeSize         = cms.double(0.4),
  min_PFTau_pt              = cms.double(20.),
  max_PFTau_eta             = cms.double(2.4),                                       
  min_leadChargedPFCand_pt  = cms.double(1.),
  max_leadChargedPFCand_eta = cms.double(2.4),
  max_leadChargedPFCand_dz  = cms.double(1.e+3),
  max_chargedIso            = cms.double(1.e+3),
  max_chargedRelIso         = cms.double(1.0),
  inputFileName_rhoCorr     = cms.string(""),
  histogramName_rhoCorr     = cms.string(""),               
  deltaR_cleaning           = cms.double(0.4),
  signalQualityCuts = cms.PSet(
    chargedHadron = cms.PSet(
      min_pt = cms.double(0.),
      max_dz = cms.double(1.e+3),                                          
    ),
    neutralHadron = cms.PSet(
      min_pt = cms.double(0.)
    ),                                        
    muon = cms.PSet(
      min_pt = cms.double(0.),
      max_dz = cms.double(1.e+3),                                          
    ),
    electron = cms.PSet(
      min_pt = cms.double(0.),
      max_dz = cms.double(1.e+3),                                          
    ),                                            
    photon = cms.PSet(
      min_pt = cms.double(0.)
    )                                      
  ),
  isolationQualityCuts = cms.PSet(
    chargedHadron = cms.PSet(
      min_pt = cms.double(0.),
      max_dz = cms.double(1.e+3),                                          
    ),
    neutralHadron = cms.PSet(
      min_pt = cms.double(0.)
    ),                                        
    muon = cms.PSet(
      min_pt = cms.double(0.),
      max_dz = cms.double(1.e+3),                                          
    ),
    electron = cms.PSet(
      min_pt = cms.double(0.),
      max_dz = cms.double(1.e+3),                                          
    ),                                            
    photon = cms.PSet(
      min_pt = cms.double(0.)
    )              
  ),
  applyPreselection = cms.bool(False),                                             
  debug = cms.untracked.bool(False)                                  
)
