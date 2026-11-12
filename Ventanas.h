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
		int tipo;     // 0 insertar, 1 modificar, 2 consultar, 3 eliminar, 4 reporte
		int indice;   // entidad (o número de reporte cuando tipo es 4)
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

	// Ventana pequeña que sale al tocar un icono: tiene los botones Insertar, Modificar y Buscar
	public ref class FormEntidad : public System::Windows::Forms::Form
	{
	public:
		FormEntidad(int indice, String^ nombre);
	private:
		int indice;   // entidad (0 = País ... 9 = Tratamiento)

		// Un solo evento para los tres botones: la etiqueta (Tag) dice cual se toco
		void Boton_Click(System::Object^ sender, System::EventArgs^ e);
		void Cerrar_Click(System::Object^ sender, System::EventArgs^ e);
	};

	// Punto de entrada que usa el menu
	public ref class Ventanas abstract sealed
	{
	public:
		// tipo: 0 inserción, 1 modificación, 2 consulta, 3 borrado
		static void Abrir(Form^ padre, int tipo, int indice);

		// Ventana con Insertar / Modificar / Buscar de una entidad (la que sale al tocar un icono)
		static void AbrirEntidad(Form^ padre, int indice);

		// Ventana que pide los datos de un reporte (0 a 17) y genera el PDF
		static void AbrirReporte(Form^ padre, int numero);

		// Ventana "Acerca de"
		static void AbrirAcercaDe(Form^ padre);
	};
}