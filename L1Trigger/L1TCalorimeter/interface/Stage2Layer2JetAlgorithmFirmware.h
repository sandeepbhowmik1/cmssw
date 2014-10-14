///
/// Description: Firmware headers
///
/// Implementation:
///    Concrete firmware implementations
///
/// \author: Jim Brooke - University of Bristol
/// Modified: Adam Elwood - ICL

//
//

#ifndef Stage2Layer2JetAlgorithmFirmware_H
#define Stage2Layer2JetAlgorithmFirmware_H

#include "L1Trigger/L1TCalorimeter/interface/Stage2Layer2JetAlgorithm.h"
#include "CondFormats/L1TObjects/interface/CaloParams.h"

namespace l1t {

  // Imp1 is for v1 and v2
  class Stage2Layer2JetAlgorithmFirmwareImp1 : public Stage2Layer2JetAlgorithm {
  public:
    Stage2Layer2JetAlgorithmFirmwareImp1(CaloParams* params);
    virtual ~Stage2Layer2JetAlgorithmFirmwareImp1();
    virtual void processEvent(const std::vector<CaloTower> & towers,
			      std::vector<Jet> & jets);

    void create(const std::vector<CaloTower> & towers,
		std::vector<Jet> & jets, std::string PUSubMethod);
    
    void sort(std::vector<Jet> & jets);

    int donutPUEstimate(int jetEta, int jetPhi, int size, 
                       const std::vector<l1t::CaloTower> & towers);

  private:

    CaloParams* const params_;

  };

}

#endif
