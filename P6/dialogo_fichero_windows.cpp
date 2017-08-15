#include "dialogo_fichero_windows.h"
#include <windows.h>
#include <atlstr.h>

#include <iostream>

#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
bool lee_nombre_fichero(std::string& fichero_tsp)
{
    OPENFILENAME ofn ;
    char szFile[200] ;
    ZeroMemory( &ofn, sizeof( ofn));
    ofn.lStructSize = sizeof ( ofn );
    ofn.hwndOwner = NULL  ;
    ofn.lpstrFile = (LPWSTR)szFile;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = sizeof( szFile );
	//ofn.lpstrFilter = CString("Ficheros_TSP\0*.tsp\0");
    ofn.nFilterIndex =1;
    ofn.lpstrFileTitle = NULL ;
    ofn.nMaxFileTitle = 0 ;
    //ofn.lpstrInitialDir= LPWSTR("Ficheros_TSP");
    ofn.Flags = OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST;
    if (GetOpenFileName(&ofn))  // displays open file dialog box
    {
        fichero_tsp = CW2A(ofn.lpstrFile);
        fichero_tsp.c_str();
        return true;
    }
    return false;
}