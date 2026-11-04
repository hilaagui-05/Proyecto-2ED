#include "pch.h"
#include "Form1.h"

namespace mainInterfaz {

	void Form1::CrearMenu() {
		ToolStripMenuItem^ archivo = gcnew ToolStripMenuItem("Archivo");
		ToolStripMenuItem^ leer = gcnew ToolStripMenuItem("Leer archivos CSV y construir árboles");
		leer->Click += gcnew System::EventHandler(this, &Form1::leerArchivos_Click);
		ToolStripMenuItem^ salir = gcnew ToolStripMenuItem(L"Salir");
		salir->Click += gcnew System::EventHandler(this, &Form1::salir_Click);
		archivo->DropDownItems->Add(leer);
		archivo->DropDownItems->Add(gcnew ToolStripSeparator());
		archivo->DropDownItems->Add(salir);

		ToolStripMenuItem^ mantenimiento = gcnew ToolStripMenuItem(L"Mantenimiento");
		cli::array<String^>^ grupos = gcnew cli::array<String^>{ L"Inserción", L"Modificación", L"Consultas", L"De todos los árboles" };
		for each (String ^ grupo in grupos) {
			ToolStripMenuItem^ g = gcnew ToolStripMenuItem(grupo);
			for each (String ^ entidad in entidades) {
				ToolStripMenuItem^ op = gcnew ToolStripMenuItem(entidad);
				op->Tag = grupo;   // guarda de cuál grupo viene
				op->Click += gcnew System::EventHandler(this, &Form1::entidad_Click);
				g->DropDownItems->Add(op);
			}
			mantenimiento->DropDownItems->Add(g);
		}

		cli::array<String^>^ reportes = gcnew cli::array<String^>{
			L"Países", L"Ciudades de un país", L"Pacientes", L"Especialidades",
				L"Habitaciones disponibles", L"Habitaciones ocupadas", L"Hospitalizaciones",
				L"Hospitalizaciones de un médico", L"Médicos", L"Médicos de una especialidad",
				L"Citas por fecha", L"Citas por especialidad", L"Citas de un médico",
				L"Pacientes de un país", L"Pacientes de una ciudad", L"Citas de un paciente",
				L"Diagnósticos", L"Tratamientos" };
		ToolStripMenuItem^ menuReportes = gcnew ToolStripMenuItem(L"Reportes");
		for each (String ^ reporte in reportes)
		{
			ToolStripMenuItem^ op = gcnew ToolStripMenuItem(reporte);
			menuReportes->DropDownItems->Add(op);
		}
		ToolStripMenuItem^ acerca = gcnew ToolStripMenuItem(L"Acerca de");
		acerca->Click += gcnew System::EventHandler(this, &Form1::mnuAcercaDe_Click);

		this->menuStrip1->Items->Add(archivo);
		this->menuStrip1->Items->Add(mantenimiento);
		this->menuStrip1->Items->Add(menuReportes);
		this->menuStrip1->Items->Add(acerca);
	}

	void Form1::CrearTarjetas() {
		cli::array<String^>^ claves = gcnew cli::array<String^>{ L"Paises", L"Ciudades", L"Pacientes", L"Medicos",
			L"Especialidades", L"Citas", L"Habitaciones", L"Hospitalizaciones", L"Diagnosticos", L"Tratamientos", L"Datos" };
		cli::array<String^>^ textos = gcnew cli::array<String^>{ L"Países", L"Ciudades", L"Pacientes", L"Médicos",
			L"Especialidades", L"Citas", L"Habitaciones", L"Hospitalizaciones", L"Diagnósticos", L"Tratamientos", L"Cargar datos" };
		cli::array<String^>^ imagenes = gcnew cli::array<String^>{ L"icono_pais.png", L"icono_ciudad.png", L"icono_paciente.png",
			L"icono_medico.png", L"icono_especialidad.png", L"icono_cita.png", L"icono_habitacion.png", L"icono_hospital.png",
			L"icono_diagnostico.png", L"icono_tratamiento.png", L"icono_datos.png" };
		// colores de fondo (R, G, B) de cada tarjeta
		cli::array<int>^ rgb = gcnew cli::array<int>{ 255, 238, 200, 210, 230, 248, 214, 242, 232, 225, 225, 250,
			250, 222, 236, 255, 230, 208, 206, 236, 250, 232, 224, 250, 255, 246, 204, 255, 222, 222, 206, 244, 240 };

		for (int i = 0; i < claves->Length; i++) {
			Panel^ panel = gcnew Panel();
			PictureBox^ imagen = gcnew PictureBox();
			Label^ texto = gcnew Label();

			imagen->Name = String::Concat(L"pic", claves[i]);
			imagen->Dock = DockStyle::Fill;
			imagen->BackColor = System::Drawing::Color::Transparent;
			imagen->SizeMode = PictureBoxSizeMode::Zoom;
			imagen->Cursor = System::Windows::Forms::Cursors::Hand;
			imagen->Image = Cargar(imagenes[i]);
			imagen->Click += gcnew System::EventHandler(this, &Form1::tarjeta_Click);

			texto->Name = String::Concat(L"lbl", claves[i]);
			texto->Dock = DockStyle::Bottom;
			texto->Height = 34;
			texto->BackColor = System::Drawing::Color::White;
			texto->ForeColor = System::Drawing::Color::FromArgb(16, 52, 66);
			texto->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.75,System::Drawing::FontStyle::Bold);
			texto->TextAlign = ContentAlignment::MiddleCenter;
			texto->Text = textos[i];
			texto->Cursor = System::Windows::Forms::Cursors::Hand;
			texto->Click += gcnew System::EventHandler(this, &Form1::tarjeta_Click);

			panel->Name = String::Concat(L"pnl", claves[i]);
			panel->Dock = DockStyle::Fill;
			panel->Margin = System::Windows::Forms::Padding(8);
			panel->Padding = System::Windows::Forms::Padding(10, 12, 10, 10);
			panel->BackColor = System::Drawing::Color::FromArgb(rgb[i * 3], rgb[i * 3 + 1], rgb[i * 3 + 2]);
			panel->Cursor = System::Windows::Forms::Cursors::Hand;
			panel->Click += gcnew System::EventHandler(this, &Form1::tarjeta_Click);
			panel->Controls->Add(imagen);   // primero el que llena
			panel->Controls->Add(texto);    // despues el que va abajo

			this->tablaTarjetas->Controls->Add(panel, i % 4, i / 4);
		}
	}

	Image^ Form1::Cargar(String^ nombre) {
		cli::array<String^>^ rutas = gcnew cli::array<String^>{
			Path::Combine(Path::Combine(Environment::CurrentDirectory, "imagenes"), nombre),
				Path::Combine(Path::Combine(AppDomain::CurrentDomain->BaseDirectory, "imagenes"), nombre),
				Path::Combine(Path::Combine(AppDomain::CurrentDomain->BaseDirectory, "..\\imagenes"), nombre),
				Path::Combine(Path::Combine(AppDomain::CurrentDomain->BaseDirectory, "..\\..\\imagenes"), nombre) };
		for each (String ^ ruta in rutas) {
			if (File::Exists(ruta)) {
				cli::array<Byte>^ datos = File::ReadAllBytes(ruta);   // en memoria: no bloquea el archivo
				return Image::FromStream(gcnew MemoryStream(datos));
			}
		}
		return nullptr;
	}

	void Form1::CargarImagenes() {
		Image^ fondo = Cargar(L"fondo.png");
		if (fondo != nullptr) {
			this->BackgroundImage = fondo;
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
		}
		this->picLogoChico->Image = Cargar(L"icono_hospital.png");
		this->picLogoGrande->Image = Cargar(L"logo_grande.png");
		this->picFecha->Image = Cargar(L"icono_cita.png");
		this->picHora->Image = Cargar(L"icono_reloj.png");
	}

	void Form1::Mensaje(String^ texto)
	{
		this->lblMensaje->Text = texto;
	}

	void Form1::LeerArchivos() {
		if (archivosCargados) {
			Mensaje(L"Los archivos CSV ya fueron cargados.");
			return;
		}
		try {
			this->Cursor = System::Windows::Forms::Cursors::WaitCursor;
			cargarArchivos();   // funcion nativa del Proyecto #2
			archivosCargados = true;
			Mensaje(L"Archivos CSV leídos y árboles construidos correctamente.");
		}
		catch (...)
		{
			Mensaje(L"Ocurrió un error al leer los archivos CSV.");
		}
		this->Cursor = System::Windows::Forms::Cursors::Default;
	}

	System::Void Form1::timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		DateTime ahora = DateTime::Now;
		CultureInfo^ es = gcnew CultureInfo("es-CR");
		this->lblFecha->Text = ahora.ToString("ddd dd/MM/yyyy", es);
		this->lblHora->Text = ahora.ToString("hh:mm:ss tt", es);
	}

	System::Void Form1::leerArchivos_Click(System::Object^ sender, System::EventArgs^ e) {
		LeerArchivos();
	}

	System::Void Form1::salir_Click(System::Object^ sender, System::EventArgs^ e) {
		this->Close();
	}

	System::Void Form1::mnuAcercaDe_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ texto = String::Concat(L"Sistema de Gestión Hospitalaria\n", L"Hospital San Rafael\n\n",
			L"Proyecto Programado #3 - Avance 1 (interfaz gráfica)\n", L"Estructuras de Datos\n\n",
			L"Elaborado por:\n   Hilary Aguilar\n   Arina Tarasova\n\n",
			L"Continuación del Proyecto #2: los árboles ABB, B, AA, AVL y rojinegro\n",
			L"se mantienen y ahora se acceden desde esta ventana.");
		MessageBox::Show(this, texto, L"Acerca de", MessageBoxButtons::OK, MessageBoxIcon::Information);
	}

	// Clic en una tarjeta. Por ahora solo "Cargar datos" tiene funcion
	// Las otras aun no están implementadas.
	System::Void Form1::tarjeta_Click(System::Object^ sender, System::EventArgs^ e) {
		Control^ control = safe_cast<Control^>(sender);
		String^ clave = control->Name->Substring(3);
		if (clave == L"Datos")
		{
			LeerArchivos();
		}
	}

	System::Void Form1::entidad_Click(System::Object^ sender, System::EventArgs^ e) {
		ToolStripMenuItem^ op = safe_cast<ToolStripMenuItem^>(sender);
		String^ accion = safe_cast<String^>(op->Tag);   // Inserción, Modificación o Consultas
		String^ entidad = op->Text;                      // País, Ciudad, ...
		// Por ahora solo probamos que el clic llega bien.
		MessageBox::Show(this, accion + L" de " + entidad, L"Mantenimiento");
	}
}
