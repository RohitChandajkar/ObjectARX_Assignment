// Project7.cpp : Defines the initialization routines for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "arxHeaders.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void addLineCommand()
{
    // Prompt the user to specify the start point of the line
    ads_point startPoint;
    int result = acedGetPoint(NULL, L"\nSpecify start point of line: ", startPoint);
    if (result != RTNORM)
    {
        acutPrintf(L"\nError or user cancelled.");
        return;
    }

    // Prompt the user to specify the end point of the line
    ads_point endPoint;
    result = acedGetPoint(startPoint, L"\nSpecify end point of line: ", endPoint);
    if (result != RTNORM)
    {
        acutPrintf(L"\nError or user cancelled.");
        return;
    }

    // Open the current space for writing
    AcDbBlockTable* pBlockTable;
    acdbHostApplicationServices()->workingDatabase()->getSymbolTable(pBlockTable, AcDb::kForRead);
    AcDbBlockTableRecord* pSpaceRecord;
    pBlockTable->getAt(ACDB_MODEL_SPACE, pSpaceRecord, AcDb::kForWrite);
    pBlockTable->close();

    // Create a new line entity
    AcDbLine* pLine = new AcDbLine(asPnt3d(startPoint), asPnt3d(endPoint));
    pSpaceRecord->appendAcDbEntity(pLine);
    pLine->close();

    pSpaceRecord->close();

    acedUpdateDisplay();
    acutPrintf(L"\nLine added successfully.");
}


extern "C" AcRx::AppRetCode acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt)
{
    switch (msg)
    {
    case AcRx::kInitAppMsg:
        acrxDynamicLinker->unlockApplication(pkt);
        acrxDynamicLinker->registerAppMDIAware(pkt);
        acutPrintf(L"\nLoading project...\n");
        // Commands to add
        acedRegCmds->addCommand(_T("XYZ"), _T("userInfo"),
            _T("rohit"), ACRX_CMD_MODAL, addLineCommand);//addLine  makeLayer
        break;
    case AcRx::kUnloadAppMsg:
        acutPrintf(_T("\nUnloading createLine project...\n"));
        // Command Groups to remove
        acedRegCmds->removeGroup(_T("AUCommnds"));
        break;
    default:
        break;
    }
    return AcRx::kRetOK;
}
