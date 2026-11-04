//Elaborado por : Hilary Aguilar y Arina Tarasova
//Proyecto Programado #3 - Estructuras de Datos
#include "pch.h"
#include "Form1.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Windows::Forms;

// Cierra la ventana negra de consola (el proyecto se enlaza como Console para que
// el arranque de C++ inicialice bien los arboles y variables globales del Proyecto #2)
ref class Consola
{
public:
	[DllImport("kernel32.dll")]
		static bool FreeConsole();
};

[STAThreadAttribute]
int main(array<System::String^>^ args)
{
	Consola::FreeConsole();

	// Habilitar los efectos visuales de Windows antes de crear cualquier control
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	// Crear la ventana principal y ejecutarla
	// (mainInterfaz es el namespace que esta en Form1.h)
	Application::Run(gcnew mainInterfaz::Form1());
	return 0;
}