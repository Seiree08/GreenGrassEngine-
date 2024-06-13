#pragma once
#include "PreRequisites.h" /*Usa las librerías */
#include "window.h"

class BaseApp
{
public:
    BaseApp() = default;
    ~BaseApp() = default;

    HRESULT init();
    //void init(); Los recursos se inicializan

    void update();
    //void update(); Toda la lógica matemática se actualiza
    //Todo lo que tenga valores va en el update
    void render();
    //void render(); Toda la lógica gráfica o visual se actualiza
    //Todo lo que tenga ClearRedner o de Set va en render

    void destroy();
    //void destroy(); Toda la lógica  se libera de memoria, todas las clases que tengan info o punteros se liberan de memoria

    int run(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow);
    
    //Se define la función de WndProc
    LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam  );

private:

    Window m_window;
};