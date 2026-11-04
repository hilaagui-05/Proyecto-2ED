//Elaborado por : Hilary Aguilar y Arina Tarasova
//Proyecto Programado #3 - Estructuras de Datos
#include "pch.h"
#include "Ventanas.h"
#include <string>
#include <vector>

using namespace System;
using namespace System::Drawing;
using namespace System::IO;
using namespace System::Text;
using namespace System::Windows::Forms;
using namespace System::Runtime::InteropServices;

// Funciones nativas que estan al final de mainPrincipal.cpp
namespace servicios {
	std::string ejecutar(int tipo, int entidad, const std::vector<std::string>& campos);
}

namespace mainInterfaz {

	// ---------- conversion entre String^ (.NET) y std::string (UTF-8) ----------
	static std::string aStd(String^ s) {
		cli::array<Byte>^ b = Encoding::UTF8->GetBytes(s);
		std::string r(b->Length, '\0');
		if (b->Length > 0) {
			Marshal::Copy(b, 0, IntPtr(&r[0]), b->Length);
		}
		return r;
	}

	static String^ aNet(const std::string& s) {
		if (s.empty()) return String::Empty;
		cli::array<Byte>^ b = gcnew cli::array<Byte>((int)s.size());
		Marshal::Copy(IntPtr((void*)s.data()), b, 0, (int)s.size());
		return Encoding::UTF8->GetString(b);
	}

	// ---------- textos de las ventanas ----------
	// En cada campo: '#' = solo numeros, '~' = se puede dejar vacio, '$' = una sola palabra
	static const wchar_t* ENTIDADES[10] = { L"País", L"Ciudad", L"Paciente", L"Médico", L"Especialidad",
		L"Habitación", L"Cita", L"Hospitalización", L"Diagnóstico", L"Tratamiento" };

	static const wchar_t* INSERTAR[10] = {
		L"#CodPais;Nombre",
		L"#CodPais;#CodCiudad;Nombre",
		L"#IdPaciente;Nombre;Fecha de nacimiento (d/m/aaaa);Teléfono;#CodPais;#CodCiudad;Correo",
		L"#IdMédico;Nombre;Teléfono;Correo;#IdEspecialidad",
		L"#IdEspecialidad;Nombre;Descripción",
		L"#IdHabitación;#Número;Piso;#Tipo (1 individual, 2 compartida, 3 UCI);#Estado (0 disponible, 1 ocupada)",
		L"#IdCita;#IdPaciente;#IdMédico;#IdEspecialidad;Fecha (d/m/aaaa);Hora (hh:mm);Motivo;#Estado (0 pendiente, 1 confirmada)",
		L"#IdHospitalización;#IdPaciente;#IdHabitación;#IdMédico;Fecha de ingreso (d/m/aaaa);Fecha de salida (0 si sigue);Motivo",
		L"$CodDiagnóstico;Nombre;Descripción",
		L"#CodTratamiento;Nombre;Descripción;#Costo" };

	static const wchar_t* MODIFICAR[10] = {
		L"#CodPais;~Nuevo nombre",
		L"#CodPais;#CodCiudad;~Nuevo nombre",
		L"#CodPais;#CodCiudad;#IdPaciente;~Nuevo teléfono;~Nuevo correo",
		L"#IdEspecialidad;#IdMédico;~Nuevo teléfono;~Nuevo correo",
		L"#IdEspecialidad;~Nueva descripción",
		L"#IdHabitación;~Nuevo estado (0 disponible, 1 ocupada)",
		L"#IdPaciente;#IdMédico;#IdCita;~Nuevo motivo;~Nuevo estado (0 pendiente, 1 confirmada)",
		L"#IdPaciente;#IdHabitación;#IdHospitalización;~Nuevo motivo",
		L"$CodDiagnóstico;~Nueva descripción",
		L"#CodTratamiento;~Nuevo nombre;~Nueva descripción;~Nuevo costo" };

	static const wchar_t* CONSULTAR[10] = {
		L"#CodPais",
		L"#CodPais;#CodCiudad",
		L"#CodPais;#CodCiudad;#IdPaciente",
		L"#IdEspecialidad;#IdMédico",
		L"#IdEspecialidad",
		L"#IdHabitación",
		L"#IdPaciente;#IdMédico;#IdCita",
		L"#IdPaciente;#IdHabitación;#IdHospitalización",
		L"$CodDiagnóstico",
		L"#CodTratamiento" };

	static const wchar_t* TIPOS[3] = { L"Inserción", L"Modificación", L"Consulta" };

	// ======================= FormDatos =======================
	FormDatos::FormDatos(int tipo, int indice, String^ titulo, String^ spec)
	{
		this->tipo = tipo;
		this->indice = indice;
		cli::array<String^>^ partes = spec->Split(L';');
		int n = (spec->Length == 0) ? 0 : partes->Length;
		cajas = gcnew cli::array<TextBox^>(n);
		etiquetas = gcnew cli::array<String^>(n);
		numerico = gcnew cli::array<bool>(n);
		opcional = gcnew cli::array<bool>(n);
		unaPalabra = gcnew cli::array<bool>(n);

		this->Text = titulo;
		this->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.75F);
		this->BackColor = Color::FromArgb(238, 246, 247);
		this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
		this->MaximizeBox = false;
		this->MinimizeBox = false;
		this->StartPosition = FormStartPosition::CenterParent;

		Label^ lblTitulo = gcnew Label();
		lblTitulo->Text = titulo;
		lblTitulo->AutoSize = true;
		lblTitulo->Location = Point(20, 14);
		lblTitulo->ForeColor = Color::FromArgb(16, 52, 66);
		lblTitulo->Font = gcnew System::Drawing::Font(L"Segoe UI", 13.0F, FontStyle::Bold);
		this->Controls->Add(lblTitulo);

		for (int i = 0; i < n; i++) {
			String^ p = partes[i];
			numerico[i] = false; opcional[i] = false; unaPalabra[i] = false;
			while (p->Length > 0 && (p[0] == L'#' || p[0] == L'~' || p[0] == L'$')) {
				if (p[0] == L'#') numerico[i] = true;
				if (p[0] == L'~') opcional[i] = true;
				if (p[0] == L'$') unaPalabra[i] = true;
				p = p->Substring(1);
			}
			etiquetas[i] = p;

			Label^ etiqueta = gcnew Label();
			etiqueta->Text = p + L":";
			etiqueta->Location = Point(20, 62 + i * 36);
			etiqueta->Size = System::Drawing::Size(250, 22);
			etiqueta->AutoEllipsis = true;
			this->Controls->Add(etiqueta);

			cajas[i] = gcnew TextBox();
			cajas[i]->Location = Point(280, 59 + i * 36);
			cajas[i]->Size = System::Drawing::Size(250, 26);
			this->Controls->Add(cajas[i]);
		}

		int y = 62 + n * 36 + 8;
		btnAccion = gcnew Button();
		btnAccion->Text = (tipo == 0) ? L"Insertar" : (tipo == 1) ? L"Modificar" : L"Buscar";
		btnAccion->Location = Point(280, y);
		btnAccion->Size = System::Drawing::Size(120, 32);
		btnAccion->BackColor = Color::FromArgb(20, 110, 130);
		btnAccion->ForeColor = Color::White;
		btnAccion->FlatStyle = FlatStyle::Flat;
		btnAccion->Click += gcnew System::EventHandler(this, &FormDatos::Accion_Click);

		btnCerrar = gcnew Button();
		btnCerrar->Text = L"Cerrar";
		btnCerrar->Location = Point(410, y);
		btnCerrar->Size = System::Drawing::Size(120, 32);
		btnCerrar->Click += gcnew System::EventHandler(this, &FormDatos::Cerrar_Click);

		txtResultado = gcnew TextBox();
		txtResultado->Multiline = true;
		txtResultado->ReadOnly = true;
		txtResultado->ScrollBars = ScrollBars::Vertical;
		txtResultado->BackColor = Color::White;
		txtResultado->Font = gcnew System::Drawing::Font(L"Consolas", 10.0F);
		txtResultado->Location = Point(20, y + 46);
		txtResultado->Size = System::Drawing::Size(510, 150);

		this->Controls->Add(btnAccion);
		this->Controls->Add(btnCerrar);
		this->Controls->Add(txtResultado);
		this->ClientSize = System::Drawing::Size(550, y + 46 + 150 + 20);
		this->AcceptButton = btnAccion;
		this->CancelButton = btnCerrar;
	}

	void FormDatos::Accion_Click(System::Object^ sender, System::EventArgs^ e)
	{
		std::vector<std::string> campos;
		for (int i = 0; i < cajas->Length; i++) {
			String^ t = cajas[i]->Text->Replace(L"\r", L" ")->Replace(L"\n", L" ")->Trim();
			String^ problema = nullptr;
			if (t->Length == 0 && !opcional[i]) {
				problema = L"Falta completar el campo: " + etiquetas[i];
			}
			else if (t->Length > 0 && numerico[i] && !opcional[i]) {
				for (int k = 0; k < t->Length; k++) {
					if (t[k] < L'0' || t[k] > L'9') { problema = L"El campo " + etiquetas[i] + L" debe llevar solo números."; break; }
				}
				if (problema == nullptr && t->Length > 9) problema = L"El número del campo " + etiquetas[i] + L" es demasiado grande.";
			}
			else if (t->Length > 0 && unaPalabra[i] && t->IndexOf(L' ') >= 0) {
				problema = L"El campo " + etiquetas[i] + L" no puede llevar espacios.";
			}
			if (problema != nullptr) {
				MessageBox::Show(this, problema, L"Datos incompletos", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				cajas[i]->Focus();
				return;
			}
			campos.push_back(aStd(t));
		}

		this->Cursor = System::Windows::Forms::Cursors::WaitCursor;
		std::string r;
		try {
			r = servicios::ejecutar(tipo, indice, campos);
		}
		catch (...) {
			r = "Ocurrio un error inesperado.";
		}
		this->Cursor = System::Windows::Forms::Cursors::Default;

		String^ texto = aNet(r);
		if (tipo == 0 && texto->Contains(L"correctamente")) {
			for (int i = 0; i < cajas->Length; i++) cajas[i]->Clear();
			if (cajas->Length > 0) cajas[0]->Focus();
		}
		txtResultado->Text = texto->Replace(L"\r\n", L"\n")->Replace(L"\n", L"\r\n");
	}

	void FormDatos::Cerrar_Click(System::Object^ sender, System::EventArgs^ e)
	{
		this->Close();
	}

	// ======================= Ventanas =======================
	void Ventanas::Abrir(Form^ padre, int tipo, int indice)
	{
		const wchar_t** tabla = (tipo == 0) ? INSERTAR : (tipo == 1) ? MODIFICAR : CONSULTAR;
		String^ titulo = String::Concat(gcnew String(TIPOS[tipo]), L" de ", gcnew String(ENTIDADES[indice]));
		FormDatos^ f = gcnew FormDatos(tipo, indice, titulo, gcnew String(tabla[indice]));
		f->ShowDialog(padre);
	}
}