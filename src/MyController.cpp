// -*- C++ -*-
/*!
 * @file  MyController.cpp
 * @brief My Controller
 * @date $Date$
 *
 * $Id$
 */

#include "MyController.h"

// Module specification
// <rtc-template block="module_spec">
static const char* mycontroller_spec[] =
  {
    "implementation_id", "MyController",
    "type_name",         "MyController",
    "description",       "My Controller",
    "version",           "1.0.0",
    "vendor",            "yumin05cim",
    "category",          "Test",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.velocity_x", "0.05",
    "conf.default.velocity_theta", "1.0",
    // Widget
    "conf.__widget__.velocity_x", "text",
    "conf.__widget__.velocity_theta", "text",
    // Constraints
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
MyController::MyController(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_poseIn("pose", m_pose),
    m_bumperIn("bumper", m_bumper),
    m_joystickIn("joystick", m_joystick),
    m_velocityOut("velocity", m_velocity)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
MyController::~MyController()
{
}



RTC::ReturnCode_t MyController::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("pose", m_poseIn);
  addInPort("bumper", m_bumperIn);
  addInPort("joystick", m_joystickIn);
  
  // Set OutPort buffer
  addOutPort("velocity", m_velocityOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("velocity_x", m_velocity_x, "0.05");
  bindParameter("velocity_theta", m_velocity_theta, "1.0");
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t MyController::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t MyController::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t MyController::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t MyController::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t MyController::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t MyController::onExecute(RTC::UniqueId ec_id)
{

	std::cout<< "Vx=" << m_velocity_x << std::endl;
	std::cout<< "Vtheta=" << m_velocity_theta << std::endl;

	m_velocity.data.vx = m_velocity_x;
	m_velocity.data.vy = 0;
	m_velocity.data.va = m_velocity_theta;

	m_velocityOut.write();

/*
	if(m_poseIn.isNew()){
		m_poseIn.read();
		std::cout << "X=" << m_pose.data.position.x << std::endl;
		std::cout << "Y=" << m_pose.data.position.y << std::endl;
		std::cout << "Z=" << m_pose.data.heading << std::endl;
	}
*/
/*
	if(m_bumperIn.isNew()){
		m_bumperIn.read();
		if(m_bumper.data[0] == true){
			std::cout << "Right Bumper Hit!!" << std::endl;
		}
		if(m_bumper.data[1] == true){
			std::cout << "Left Bumper Hit!!" << std::endl;
		}
	}
*/
	if(m_joystickIn.isNew()){
		m_joystickIn.read();
		std::cout << m_joystick.data[0];
		std::cout << m_joystick.data[1] << std::endl;

		if(m_joystick.data[0] == true){
			m_velocity.data.vx = m_velocity_x + m_joystick.data[0];
		}

		if(m_joystick.data[1] == true){
			m_velocity.data.va = m_velocity_theta + (m_joystick.data[1]/10);
		}
		m_velocityOut.write();

	}
	
	return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t MyController::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t MyController::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t MyController::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t MyController::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t MyController::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void MyControllerInit(RTC::Manager* manager)
  {
    coil::Properties profile(mycontroller_spec);
    manager->registerFactory(profile,
                             RTC::Create<MyController>,
                             RTC::Delete<MyController>);
  }
  
};


