//Elaborado por : Hilary Aguilar y Arina Tarasova
//Proyecto Programado #3 - Estructuras de Datos
#include "pch.h"
#include "Form1.h"

using namespace System;
using namespace System::Windows::Forms;

int main(array<System::String^>^ args)
{
	// Habilitar los efectos visuales de Windows antes de crear cualquier control
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	// Crear la ventana principal y ejecutarla
	// (mainInterfaz es el namespace que esta en Form1.h)
	Application::Run(gcnew mainInterfaz::Form1());
	return 0;
}
