//Elaborado por : Hilary Aguilar y Arina Tarasova
//Proyecto Programado #3 - Estructuras de Datos
#pragma once

namespace mainInterfaz {
	using namespace System;
	using namespace System::Windows::Forms;

	// Formulario con inserción, modificación o consulta
	public ref class FormDatos : public System::Windows::Forms::Form
	{
	public:
		FormDatos(int tipo, int indice, String^ titulo, String^ spec);
	private:
		int tipo;     // 0 insertar, 1 modificar, 2 consultar
		int indice;   // entidad
		cli::array<TextBox^>^ cajas;
		cli::array<String^>^ etiquetas;
		cli::array<bool>^ numerico;   // solo digitos
		cli::array<bool>^ opcional;   // se puede dejar vacio
		cli::array<bool>^ unaPalabra; // sin espacios
		TextBox^ txtResultado;
		Button^ btnAccion;
		Button^ btnCerrar;

		void Accion_Click(System::Object^ sender, System::EventArgs^ e);
		void Cerrar_Click(System::Object^ sender, System::EventArgs^ e);
	};

	// Punto de entrada que usa el menu
	public ref class Ventanas abstract sealed
	{
	public:
		// tipo: 0 inserción, 1 modificación, 2 consulta
		static void Abrir(Form^ padre, int tipo, int indice);
	};
}