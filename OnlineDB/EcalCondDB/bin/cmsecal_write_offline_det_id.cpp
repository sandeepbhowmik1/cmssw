/**
 *   cmsecal_write_offline_det_id.cpp
 *
 *   Reads the ECAL CondDB 'channelview' table a list of crystal IDs
 *   (logic_id) and writes back a mapping of EBDetId.rawId() to
 *   logic_id as well as a mapping of ieta, iphi to logic_id
 *   
 *   Author: Ricky Egeland, with help by Zhen Xie!
 */

#include "DataFormats/EcalDetId/interface/EBDetId.h"
#include "RelationalAccess/IAuthenticationService.h"
#include "RelationalAccess/IRelationalService.h"
#include "RelationalAccess/IRelationalDomain.h"
#include "RelationalAccess/ISession.h"
#include "RelationalAccess/ITransaction.h"
#include "RelationalAccess/ISchema.h"
#include "RelationalAccess/ITable.h"
#include "RelationalAccess/IQuery.h"
#include "RelationalAccess/ICursor.h"
#include "RelationalAccess/ITableDataEditor.h"
#include "RelationalAccess/IBulkOperation.h"
#include "RelationalAccess/SchemaException.h"
#include "CoralBase/AttributeList.h"
#include "CoralBase/Attribute.h"
#include "CoralBase/AttributeSpecification.h"
#include "CoralBase/Exception.h"
#include "SealKernel/Exception.h"
#include "SealKernel/Context.h"
#include "SealKernel/ComponentLoader.h"
#include "SealKernel/IMessageService.h"
#include "PluginManager/PluginManager.h"

#include <iostream>
#include <string>
#include <vector>
#include <time.h>


class CondDBApp {
public:

  /**
   *   App constructor; Makes the database connection
   */
  CondDBApp(std::string connect, std::string user, std::string pass) :
    m_context( new seal::Context)
  {
    std::cout << "Loading services..." << std::flush;
    seal::PluginManager::get()->initialise();
    seal::Handle<seal::ComponentLoader> loader = new seal::ComponentLoader( m_context );
    loader->load( "CORAL/Services/RelationalService" );

    loader->load( "CORAL/Services/EnvironmentAuthenticationService" );

    loader->load( "SEAL/Services/MessageService" );
    std::vector< seal::Handle<seal::IMessageService> > v_msgSvc;
    m_context->query( v_msgSvc );
    seal::Handle<seal::IMessageService> msgSvc;
    if ( ! v_msgSvc.empty() ) {
      msgSvc = v_msgSvc.front();
      msgSvc->setOutputStream( std::cerr, seal::Msg::Nil );
      msgSvc->setOutputStream( std::cerr, seal::Msg::Verbose );
      msgSvc->setOutputStream( std::cerr, seal::Msg::Debug );
      msgSvc->setOutputStream( std::cerr, seal::Msg::Info );
      msgSvc->setOutputStream( std::cerr, seal::Msg::Fatal );
      msgSvc->setOutputStream( std::cerr, seal::Msg::Error );
      msgSvc->setOutputStream( std::cerr, seal::Msg::Warning );
    }
    if (!::getenv( "POOL_OUTMSG_LEVEL" )){ //if not set, default to warning
      msgSvc->setOutputLevel( seal::Msg::Debug);
    } else {
      msgSvc->setOutputLevel( seal::Msg::Debug );
    }
    seal::IHandle<coral::IRelationalService> serviceHandle = m_context->query<coral::IRelationalService>( "CORAL/Services/RelationalService" );
    if ( ! serviceHandle ) {
      std::cerr << "[Error] Could not retrieve the relational service" << std::endl;
      exit(-1);
    }

    coral::IRelationalDomain& m_domain = serviceHandle->domainForConnection( connect );
    std::cout << "m_domain is " << m_domain.flavorName() << std::endl;
    m_session = std::auto_ptr<coral::ISession>(m_domain.newSession( connect ));
    m_session->connect();
    std::cout << "Done." << std::endl;
  }

  /**
   *  App destructor
   */
  ~CondDBApp() 
  {
    m_session->disconnect();
    delete m_context;
  }

  void writeMapping()
  {
    std::cout << "Starting session..." << std::flush;
    m_session->startUserSession();
    std::cout << "Starting transaction..." << std::flush;
    m_session->transaction().start();

    std::cout << "Setting query..." << std::flush;
    coral::IQuery* cvQuery = m_session->nominalSchema().tableHandle("CHANNELVIEW").newQuery();
    cvQuery->addToOutputList("ID1");
    cvQuery->addToOutputList("ID2");
    cvQuery->addToOutputList("LOGIC_ID");
    cvQuery->defineOutputType("ID1", "int");
    cvQuery->defineOutputType("ID2", "int");
    cvQuery->defineOutputType("LOGIC_ID", "int");

    cvQuery->addToOrderList("ID1");
    cvQuery->addToOrderList("ID2");

    std::string where = "NAME = :name AND MAPS_TO = :maps_to";
    coral::AttributeList whereData;
    whereData.extend<std::string>( "NAME" );
    whereData.extend<std::string>( "MAPS_TO" );
    whereData[0].data<std::string>() = "EB_crystal_number";
    whereData[1].data<std::string>() = "EB_crystal_number";
    cvQuery->setCondition( where, whereData );
    cvQuery->setRowCacheSize(61200); // number of crystals in barrel

    std::cout << "Getting editor for CHANNELVIEW..." << std::flush;
    coral::ITableDataEditor& cvEditor = m_session->nominalSchema().tableHandle("CHANNELVIEW").dataEditor();
    
    std::cout << "Setting up buffers..." << std::flush;
    coral::AttributeList rowBuffer;
    rowBuffer.extend<std::string>( "NAME" );
    rowBuffer.extend<int>( "ID1" );
    rowBuffer.extend<int>( "ID2" );
    rowBuffer.extend<int>( "ID3" );
    rowBuffer.extend<std::string>("MAPS_TO");
    rowBuffer.extend<int>( "LOGIC_ID" );

    std::string& name = rowBuffer[0].data<std::string>();
    int& id1 = rowBuffer[1].data<int>();
    int& id2 = rowBuffer[2].data<int>();
    int& id3 = rowBuffer[3].data<int>();
    std::string& mapsTo = rowBuffer[4].data<std::string>();
    int& logicId = rowBuffer[5].data<int>();
    
    coral::IBulkOperation* bulkInserter = cvEditor.bulkInsert(rowBuffer, 37*1700*2); // number of crystals in barrel * number of mappings
    std::cout << "Done." << std::endl;
    
    std::cout << "Looping over supermodule" << std::endl;
    EBDetId ebid;
    int SM = 0;
    int offSM = 0; // SM slot in the offline
    int xtal = 0;
    int detId = 0;
    int ieta = 0;
    int iphi = 0;
    id1 = id2 = id3 = 0;
    coral::ICursor& cvCursor = cvQuery->execute();
    while (cvCursor.next()) {
      SM = cvCursor.currentRow()["ID1"].data<int>();
      xtal = cvCursor.currentRow()["ID2"].data<int>();
      logicId = cvCursor.currentRow()["LOGIC_ID"].data<int>();

      // Both construction SM 0 and 36 are mapped to
      // ECAL slot 36 in the offline
      if (SM != 0) {
	offSM = SM;
      } else {
	offSM = 36;
      }

      ebid = EBDetId(offSM, xtal, EBDetId::SMCRYSTALMODE);
      detId = ebid.rawId();
      ieta = ebid.ieta();
      iphi = ebid.iphi();

      std::cout << "SM " << SM
		<< " xtal " << xtal
		<< " logic_id " << logicId
	        << " ieta " << ieta
	        << " iphi " << iphi
		<< " det_id " << detId << std::endl;
      name = "Offline_det_id";
      mapsTo = "EB_crystal_number";
      id1 = detId;
      rowBuffer[ "ID2" ].setNull( true );
      rowBuffer[ "ID3" ].setNull( true );
      bulkInserter->processNextIteration();

      name = "EB_crystal_angle";
      mapsTo = "EB_crystal_number";
      id1 = ieta;
      rowBuffer[ "ID2" ].setNull( false );
      id2 = iphi;
      rowBuffer[ "ID3" ].setNull( true );
      bulkInserter->processNextIteration();
    }
    bulkInserter->flush();
    delete bulkInserter;
    std::cout << "Done." << std::endl;

    std::cout << "Getting editor for VIEWDESCRIPTION..." << std::flush;
    coral::ITableDataEditor& vdEditor = m_session->nominalSchema().tableHandle("VIEWDESCRIPTION").dataEditor();
    
    std::cout << "Setting up buffers..." << std::flush;
    coral::AttributeList rowBuffer2;
    rowBuffer2.extend<std::string>( "NAME" );
    rowBuffer2.extend<std::string>( "ID1NAME" );
    rowBuffer2.extend<std::string>( "ID2NAME" );
    rowBuffer2.extend<std::string>( "ID3NAME" );
    rowBuffer2.extend<std::string>( "DESCRIPTION" );

    std::string& vdname = rowBuffer2["NAME"].data<std::string>();
    std::string& id1name = rowBuffer2["ID1NAME"].data<std::string>();
    std::string& id2name = rowBuffer2["ID2NAME"].data<std::string>();
    std::string& id3name = rowBuffer2["ID3NAME"].data<std::string>();
    std::string& description = rowBuffer2["DESCRIPTION"].data<std::string>();

    id3name = "";  // Always null; using to get rid of warning

    vdname = "Offline_det_id";
    id1name = "det_id";
    rowBuffer2[ "ID2NAME" ].setNull( true );
    rowBuffer2[ "ID3NAME" ].setNull( true );
    description = "DetID rawid() as used in CMSSW";
    vdEditor.insertRow(rowBuffer2);

    vdname = "EB_crystal_angles";
    id1name = "ieta";
    rowBuffer2[ "ID2NAME" ].setNull( false );
    id2name = "iphi";
    rowBuffer2[ "ID3NAME" ].setNull( true );
    description = "Crystals in ECAL barrel super-modules by angle index";
    vdEditor.insertRow(rowBuffer2);
    

    std::cout << "Committing..." << std::flush;
    m_session->transaction().commit();
    std::cout << "Done." << std::endl;    

  }


private:
  seal::Context* m_context;
  std::auto_ptr<coral::ISession> m_session;
};



int main (int argc, char* argv[])
{
  std::string connect;
  std::string user;
  std::string pass;

  if (argc != 4) {
    std::cout << "Usage:" << std::endl;
    std::cout << "  " << argv[0] << " <connect string> <user> <pass>" << std::endl;
    exit(-1);
  }

  connect = argv[1];
  user = argv[2];
  pass = argv[3];

  std::string userenv("CORAL_AUTH_USER=");
  userenv += user;
  ::putenv(const_cast<char*>(userenv.c_str()));
  std::string passenv("CORAL_AUTH_PASSWORD=");
  passenv += pass;
  ::putenv(const_cast<char*>(passenv.c_str()));

  try {
    CondDBApp app(connect, user, pass);
    app.writeMapping();
  } catch (coral::Exception &e) {
    std::cerr << "coral::Exception:  " << e.what() << std::endl;
//   } catch (seal::Exception &e) {
//     std::cerr << "seal::Exception:  " << e.what() << std::endl;
  } catch (std::exception &e) {
    std::cerr << "ERROR:  " << e.what() << std::endl;
  } catch (...) {
    std::cerr << "Unknown error caught" << std::endl;
  }

  std::cout << "All Done." << std::endl;

  return 0;
}
