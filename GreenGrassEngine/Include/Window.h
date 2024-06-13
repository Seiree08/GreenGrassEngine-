//Esta clase crea la ventana como un recurso 
#pragma once
#include "PreRequisites.h"

class Window
{
public:
	Window() = default;
	~Window() = default;

	HRESULT init(HINSTANCE hInstance, int nCmdShow, WNDPROC wndproc);
	//wndproc detecta inputs del teclado o mouse

	void update();

	void render();

	void destroy();

public:
	HWND m_hWnd = nullptr;
	//Ahora en lugar de ser global es miembro de la clase
	unsigned int m_width;
	unsigned int m_height;
	//Variables para el ancho y alto, el unsigned en general sirve pa' decir que esté en valores positivos o negativos
private:
	HINSTANCE m_hInst = nullptr;
	//Ahora en lugar de ser global es miembro de la clase
	RECT m_rect;
	//Determina el ancho y alto de la ventana, el tamaño
	std::string m_windowName = "GreenGrass Engine";
};
