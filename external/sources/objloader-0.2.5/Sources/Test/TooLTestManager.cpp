/*
 *  TooLTestManager.cpp
 *  ToolSDL
 *
 *  Created by Seb on 06/01/06.
 *  Copyright 2006 The Old Game Factory. All rights reserved.
 *
 */
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>

#include "TooLTestManager.hpp"


//
CTooLTestManager& CTooLTestManager::getInstance()
{
	static CTooLTestManager theTooLTestManager;
	return theTooLTestManager;
}


//
CTooLTestManager::CTooLTestManager()
{
}


//
int CTooLTestManager::run()
{
	CLogger::get() << "\n  ---- TooL: running unit tests...\n";

	bool bLogger = CLogger::get().m_isOn;
	CLogger::get().m_isOn = false;

	// Create the event manager and test controller
	CPPUNIT_NS::TestResult controller;
	
	// Add a listener that colllects test result
	CPPUNIT_NS::TestResultCollector result;
	controller.addListener( &result );        
	
	// Add a listener that print dots as test run.
	CPPUNIT_NS::BriefTestProgressListener progress;
	controller.addListener( &progress );      
	
	// Add the top suite to the test runner
	CPPUNIT_NS::TestRunner runner;
	runner.addTest( CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest() );
	runner.run( controller );
	
	// Print test in a compiler compatible format.
	CPPUNIT_NS::CompilerOutputter outputter( &result, std::cerr );
	outputter.write(); 
	
	CLogger::get().m_isOn = bLogger;
	CLogger::get() << "  ---- TooL: unit tests finished.\n\n";

	return result.wasSuccessful() ? 0 : 1;
}
