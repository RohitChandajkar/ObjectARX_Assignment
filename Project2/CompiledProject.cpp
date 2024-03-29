// CompiledProject.cpp : Defines the initialization routines for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "arxHeaders.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



extern "C" AcRx::AppRetCode acrxEntryPoint(AcRx::AppMsgCode msg, void* appId)
{
	switch (msg) {
	case AcRx::kInitAppMsg:
		acrxDynamicLinker->unlockApplication(appId);
		acrxDynamicLinker->registerAppMDIAware(appId);
		// Add tasks here that should happen when loading the ARX file
		break;
	case AcRx::kUnloadAppMsg:
		// Add tasks here that should happen when unloading the ARX file
		break;
	}
	return AcRx::kRetOK;
}