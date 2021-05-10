#include "DataFormats/Phase2HLTPFTaus/interface/PFTauPair.h"

#include "DataFormats/Math/interface/deltaR.h" // reco::deltaR

namespace reco {

PFTauPair::PFTauPair()
{}

PFTauPair::PFTauPair(const reco::PFTauRef& leadPFTau, double leadPFTau_sumChargedIso, const reco::PFTauRef& subleadPFTau, double subleadPFTau_sumChargedIso, double dz)
  : LeafCandidate(leadPFTau->charge() + subleadPFTau->charge(), 
                  leadPFTau->p4() + subleadPFTau->p4(), 
                  reco::LeafCandidate::Point(0.5*(leadPFTau->vertex().x() + subleadPFTau->vertex().x()), 
                                             0.5*(leadPFTau->vertex().y() + subleadPFTau->vertex().y()), 
                                             0.5*(leadPFTau->vertex().z() + subleadPFTau->vertex().z())))
   , leadPFTau_(leadPFTau)
   , leadPFTau_sumChargedIso_(leadPFTau_sumChargedIso)
   , subleadPFTau_(subleadPFTau)
   , subleadPFTau_sumChargedIso_(subleadPFTau_sumChargedIso)
   , dz_(dz)
{
  assert(leadPFTau_->pt() >= subleadPFTau_->pt());
  assert(reco::deltaR(leadPFTau_->p4(), subleadPFTau_->p4()) > 1.e-3);
}

PFTauPair::~PFTauPair()
{}

const reco::PFTauRef& 
PFTauPair::leadPFTau() const 
{ 
  return leadPFTau_; 
}

double 
PFTauPair::leadPFTau_sumChargedIso() const 
{ 
  return leadPFTau_sumChargedIso_; 
}

const reco::PFTauRef& 
PFTauPair::subleadPFTau() const 
{ 
  return subleadPFTau_; 
}

double 
PFTauPair::subleadPFTau_sumChargedIso() const 
{ 
  return subleadPFTau_sumChargedIso_; 
}

double 
PFTauPair::dz() const 
{ 
  return dz_; 
}

std::ostream& operator<<(std::ostream& out, const PFTauPair& pfTauPair)
{
  //out << "PFTauPair:"
  //    << " pT = " << pfTauPair.pt() << "," 
  out << "pT = " << pfTauPair.pt() << "," 
      << " eta = " << pfTauPair.eta() << "," 
      << " phi = " << pfTauPair.phi() << "," 
      << " charge = " << pfTauPair.charge() << "," 
      << " mass = " << pfTauPair.mass() << std::endl;
  out << " vertex: x = " << pfTauPair.vertex().x() << ", y = " << pfTauPair.vertex().y() << ", z = " << pfTauPair.vertex().z() << std::endl;

  const reco::PFTauRef& leadPFTau = pfTauPair.leadPFTau();
  out << "leadingPFTau:" 
      << " pT = " << leadPFTau->pt() << "," 
      << " eta = " << leadPFTau->eta() << "," 
      << " phi = " << leadPFTau->phi() << "," 
      << " decayMode = " << leadPFTau->decayMode() << "," 
      << " mass = " << leadPFTau->mass() << std::endl;
  out << " vertex: x = " << leadPFTau->vertex().x() << ", y = " << leadPFTau->vertex().y() << ", z = " << leadPFTau->vertex().z() << std::endl;
  const reco::PFCandidatePtr leadPFTau_leadPFChargedHadrCand = leadPFTau->leadPFChargedHadrCand();  
  out << " leadChargedHadrCand:";
  if ( leadPFTau_leadPFChargedHadrCand.isNonnull() && leadPFTau_leadPFChargedHadrCand.isAvailable() )
  {
    out << " pT = " << leadPFTau_leadPFChargedHadrCand->pt() << "," 
        << " eta = " << leadPFTau_leadPFChargedHadrCand->eta() << "," 
        << " phi = " << leadPFTau_leadPFChargedHadrCand->phi() << "," 
        << " pdgId = " << leadPFTau_leadPFChargedHadrCand->pdgId() << std::endl;
    out << "  vertex:";
    const reco::Track* leadPFTau_leadTrack = leadPFTau_leadPFChargedHadrCand->bestTrack();
    if ( leadPFTau_leadTrack )
    {
      out << " x = " << leadPFTau_leadTrack->vertex().x() << ", y = " << leadPFTau_leadTrack->vertex().y() << ", z = " << leadPFTau_leadTrack->vertex().z() 
          << " (dz = " << leadPFTau_leadTrack->dz(pfTauPair.vertex()) << ")" << std::endl;
    } 
    else 
    {
      out << " N/A" << std::endl;
    }
  } 
  else
  {
    out << " N/A" << std::endl;
  }
  out << " sumChargedIso = " << pfTauPair.leadPFTau_sumChargedIso() << std::endl;

  const reco::PFTauRef& subleadPFTau = pfTauPair.subleadPFTau();
  out << "subleadingPFTau:" 
      << " pT = " << subleadPFTau->pt() << "," 
      << " eta = " << subleadPFTau->eta() << "," 
      << " phi = " << subleadPFTau->phi() << "," 
      << " decayMode = " << subleadPFTau->decayMode() << "," 
      << " mass = " << subleadPFTau->mass() << std::endl;
  out << " vertex: x = " << subleadPFTau->vertex().x() << ", y = " << subleadPFTau->vertex().y() << ", z = " << subleadPFTau->vertex().z() << std::endl;
  const reco::PFCandidatePtr subleadPFTau_leadPFChargedHadrCand = subleadPFTau->leadPFChargedHadrCand();  
  out << " leadChargedHadrCand:";
  if ( subleadPFTau_leadPFChargedHadrCand.isNonnull() && subleadPFTau_leadPFChargedHadrCand.isAvailable() )
  {
    out << " pT = " << subleadPFTau_leadPFChargedHadrCand->pt() << "," 
        << " eta = " << subleadPFTau_leadPFChargedHadrCand->eta() << "," 
        << " phi = " << subleadPFTau_leadPFChargedHadrCand->phi() << "," 
        << " pdgId = " << subleadPFTau_leadPFChargedHadrCand->pdgId() << std::endl;
    out << "  vertex:";
    const reco::Track* subleadPFTau_leadTrack = subleadPFTau_leadPFChargedHadrCand->bestTrack();
    if ( subleadPFTau_leadTrack )
    {
      out << " x = " << subleadPFTau_leadTrack->vertex().x() << ", y = " << subleadPFTau_leadTrack->vertex().y() << ", z = " << subleadPFTau_leadTrack->vertex().z() 
          << " (dz = " << subleadPFTau_leadTrack->dz(pfTauPair.vertex()) << ")" << std::endl;
    } 
    else 
    {
      out << " N/A" << std::endl;
    }
  } 
  else
  {
    out << " N/A" << std::endl;
  }
  out << " sumChargedIso = " << pfTauPair.subleadPFTau_sumChargedIso() << std::endl;

  out << "dz = " << pfTauPair.dz() << std::endl;

  return out;
}

}
