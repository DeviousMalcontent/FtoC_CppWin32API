/* 
 * Program: FtoC_WinAPi
 * Purpose: Converts a temperature to Celsius or Fahrenheit
 * Author: Mark Albanese 
 * Date: 25 March 2013
 * Version: 1.0
 * Release: 1
 * Language: C++ WinAPI
 * Compiler: Visual Studios 2010
 */

#include <windows.h>
#include <cstdio>
#include "resource.h"

/*
Code to enable visual styles; since I am using Microsoft Visual C++ 2010 express
I can add the following compiler directive to the source code instead of manually 
creating a manifest. 

For readability, the directive is broken into several lines here.
*/

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"") 

using namespace std;

//---------------------------------------------------------------------------
HWND hWnd;
HINSTANCE hInst;
LRESULT CALLBACK DlgProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

//---------------------------------------------------------------------------
int APIENTRY WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
                      LPSTR lpCmdLine, int nCmdShow )
{
        DialogBox(hInstance, MAKEINTRESOURCE(IDD_MAIN),
                  hWnd, reinterpret_cast<DLGPROC>(DlgProc));
        hInst = hInstance;

  return 0;
}

//---------------------------------------------------------------------------
LRESULT CALLBACK DlgProc(HWND hWndDlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    UINT ToCelsiusState, ToFahrenheitState;

    char strTemperatureInput[10], strResultOutput[10];

    HWND hwndTemperatureInput, hwndResultOutput;

    double TemperatureInput, ResultOutput;
    
    hwndTemperatureInput = GetDlgItem(hWndDlg, IDC_TEMPERATURE);
    hwndResultOutput     = GetDlgItem(hWndDlg, IDC_RESULT);

    switch(Msg)
      {
      case WM_INITDIALOG:
           CheckDlgButton(hWndDlg, IDC_CELSIUS, BST_CHECKED);
           
           SetWindowText(hwndTemperatureInput, "0");
           SetWindowText(hwndResultOutput, "");

       return TRUE;

      case WM_COMMAND:

              switch(wParam)
                {
                case IDC_CLEAR:
                        SetWindowText(hwndTemperatureInput, "0");
                        SetWindowText(hwndResultOutput, "");

                        TemperatureInput = NULL;
                        *strTemperatureInput = NULL;

                        ResultOutput = NULL;
                        *strResultOutput = NULL;

                    return TRUE;
                case IDC_CONVERT:
                        GetWindowText(hwndTemperatureInput, strTemperatureInput, 10);

                        TemperatureInput = atof(strTemperatureInput);

                        ToCelsiusState = IsDlgButtonChecked(hWndDlg, IDC_CELSIUS);
                        ToFahrenheitState = IsDlgButtonChecked(hWndDlg, IDC_FAHRENHEIT);

                        if(ToCelsiusState == BST_CHECKED && ToFahrenheitState == BST_UNCHECKED)
                        {
                            ResultOutput = (TemperatureInput - 32) * 5 / 9;
                        
                            sprintf_s(strResultOutput, "%2.f", ResultOutput);
                            SetWindowText(hwndResultOutput, strResultOutput);
                        }
                        else if (ToFahrenheitState == BST_CHECKED && ToCelsiusState == BST_UNCHECKED)
                        {
                            ResultOutput = TemperatureInput * 9 / 5 + 32;

                            sprintf_s(strResultOutput, "%2.f", ResultOutput);
                            SetWindowText(hwndResultOutput, strResultOutput);
                        }
                            TemperatureInput = NULL;
                            ResultOutput = NULL;
                            *strResultOutput = NULL;
                            *strTemperatureInput = NULL;

                        return TRUE;
                case IDC_EXIT:
                        EndDialog(hWndDlg, 0);
                        
                        return TRUE;
                case IDCANCEL:
                        EndDialog(hWndDlg, 0);
                        
                        return TRUE;
                }
                break;
        }
        return FALSE;
}
//---------------------------------------------------------------------------