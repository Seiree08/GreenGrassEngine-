                                                                                          
//--------------------------------------------------------------------------------------                                                     
// File: GreenGrassEngine.cpp
//
// Esta aplicaci�n mustra un modelo prestablecido sobre una malla 
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------
 
#include "BaseApp.h"

//Maneja los mensajes que se proprcionen y relacionen con la biblioteca IMGUI
extern IMGUI_IMPL_API LRESULT 
  ImGui_ImplWin32_WndProcHandler(HWND hWnd,                                                                                                  
                                 UINT msg, 
                                 WPARAM wParam, 
                                 LPARAM lParam);

/// <summary>
///   Maneja los mensajes que se mandan a la ventana principal del programa
/// </summary>
/// <param name="hWnd">: Recibe el mensaje y permite a WndProc saber a qu� ventana 
///   se refiere el mensaje.</param>
/// <param name="message">: Indica qu� tipo de mensaje es, WndProc usa este 
///   mensaje para decidir c�mo procesar el mensaje</param>
/// <param name="wParam">: Contiene info adicional del mensaje (Valor, identificador o puntero)</param>
/// <param name="lParam">: Contiene info adicional del mensaje, muestra info m�s detallada que wParam</param>
/// <returns></returns>
LRESULT CALLBACK 
  WndProc(HWND hWnd, 
          UINT message, 
          WPARAM wParam, 
          LPARAM lParam )
{
    //Verifica si IMGUI maneja los mensajes
    if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
    return true;

    PAINTSTRUCT ps;
    HDC hdc;

    //Cambia para manejar los distintos mensajes
    switch( message )
    {
        //Mensaje de repintar la pantalla
        case WM_PAINT:
            hdc = BeginPaint( hWnd, &ps );
            EndPaint( hWnd, &ps );
            break;
        //Mensaje de destruir la pantalla
        case WM_DESTROY:
            PostQuitMessage( 0 );
            break;
        //Porcesa los mensajes predeterminados
        default:
            return DefWindowProc( hWnd, message, wParam, lParam );
    }
    return 0;
}

/// <summary>
///   Aqu� se configura e inicia la aplicaci�n
/// </summary>
/// <param name="hInstance">: Se usa principalmente para cargar recursos c�mo �conos, 
///   men�s, crear ventanas</param>
/// <param name="hPrevInstance">: Verifica si hay otra instancia de la app
///   ejecut�ndose</param>
/// <param name="lpCmdLine">: Es un puntero a una cadena de caracteres 
///   (se pasa como una s�la cadena de texto)</param>
/// <param name="nCmdShow">: Indica c�mo se va a mostrar la pantalla al iniciar la app</param>
/// <returns></returns>
int WINAPI 
  wWinMain(HINSTANCE hInstance, 
           HINSTANCE hPrevInstance, 
           LPWSTR lpCmdLine, 
           int nCmdShow)
{
  //Se crea una instancia de BaseApp
  BaseApp app; 
  //Se inicializa la app
  return app.run(hInstance, hPrevInstance, lpCmdLine, nCmdShow, WndProc);
}