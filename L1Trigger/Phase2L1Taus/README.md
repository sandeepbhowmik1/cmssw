# L1TauProducerPhase2



cmsrel CMSSW_11_1_2

cd CMSSW_11_1_2/src

cmsenv

git cms-init



# Modification To compile

git cms-addpkg DataFormats/L1TCorrelator

cp /home/sbhowmik/L1TauTrigger/L1TauProducerPhase2/CMSSW_11_1_2/src/DataFormats/L1TCorrelator/interface/TkPrimaryVertex.h $CMSSW_BASE/src/DataFormats/L1TCorrelator/interface

cp /home/sbhowmik/L1TauTrigger/L1TauProducerPhase2/CMSSW_11_1_2/src/DataFormats/L1TCorrelator/src/classes_def.xml $CMSSW_BASE/src/DataFormats/L1TCorrelator/src

git cms-addpkg DataFormats/L1Trigger

cp /home/sbhowmik/L1TauTrigger/L1TauProducerPhase2/CMSSW_11_1_2/src/DataFormats/L1Trigger/interface/Muon.h $CMSSW_BASE/src/DataFormats/L1Trigger/interface

cp /home/sbhowmik/L1TauTrigger/L1TauProducerPhase2/CMSSW_11_1_2/src/DataFormats/L1Trigger/src/classes_def.xml $CMSSW_BASE/src/DataFormats/L1Trigger/src



# To Reconstruct L1 HPS Tau


git clone https://github.com/sandeepbhowmik1/L1TauProducerPhase2 $CMSSW_BASE/src/L1Trigger/Phase2L1Taus 

git clone https://github.com/sandeepbhowmik1/L1TauProducerPhase2-DataFormats $CMSSW_BASE/src/DataFormats/Phase2L1Taus

scram b -j 8



