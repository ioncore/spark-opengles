/*
 *  main.cpp
 *  The OpenGL Obj Loader
 *
 *  Created by Seb on 07/12/05.
 *  Copyright 2005 The Old Game Factory. All rights reserved.
 *
 */
#ifdef TOOL_NO_PREFIX_HEADER
	#include "stable.pch"
#endif

#include "Exception.hpp"
#include "Mesh.hpp"
#include "ObjMeshParser.hpp"
#include "WindowManager.hpp"
#include "MeshViewer.hpp"
#include "Texture.hpp"

#ifdef TOOL_UNIT_TESTING
	#include "Test/TooLTestManager.hpp"
#endif //TOOL_UNIT_TESTING


//
int main (int argc, char* argv[])
{
#ifdef TOOL_UNIT_TESTING
	const int nRet = CTooLTestManager::getInstance().run();
	if (0 != nRet)
		return nRet;
#endif //TOOL_UNIT_TESTING

	CLogger::get() << "  ---- TooL: application running...\n";
	string strFileName = (2 > argc) ? "Data/Cube.obj" : argv[1];	//	Remove me: default file for dev. phase. 

	// Loads a Mesh from a file
	shared_ptr<CMesh> pMesh(new CMesh());
	try {
		CObjMeshParser::parse(pMesh, strFileName);
		pMesh->generateFlatNormals();
	}
	catch (CException& e) { CLogger::get() << "Error: " << e.getMessage() << ".\n"; return 1; }
	catch (std::bad_alloc) { CLogger::get() << "Error: memory allocation failed.\n"; return 1; }
	catch (std::exception) { CLogger::get() << "Error: exception caught.\n"; return 1; }
	//	Remove me: dev.info.
	pMesh->dumpBounds();

	//	setup the viewer
	//	and start it
	try {
		//  init and create the viewer window
		CWindowManager::get().createWindow(10, 100, 400, 300, "The OpenGL Obj Loader - Mesh Viewer");
		CMeshViewer::getInstance().setMesh(pMesh);
		//	start main loop (loops untill the user stops it)
		CWindowManager::get().startLoop();
	}
	catch (CException& e) { CLogger::get() << "Error: " << e.getMessage() << ".\n"; return 1; }
	catch (std::bad_alloc) { CLogger::get() << "Error: memory allocation failed.\n"; return 1; }
	catch (std::exception) { CLogger::get() << "Error: exception caught.\n"; return 1; }

	CLogger::get() << "Everything done, quitting.\n";
	CLogger::get() << "  ---- TooL: application ended.\n";	//	Some clean up (dtors et al.) occurs after this point though.
    return 0;
}
