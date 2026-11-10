#include "pch.h"
#include "Form1.h"
#include "Ventanas.h"

namespace mainInterfaz
{

	void Form1::CrearMenu()
	{
		// Mantenimiento (Inserción / Modificación / Búsquedas / Borrados y Cargar archivos)
		ToolStripMenuItem ^ mantenimiento = gcnew ToolStripMenuItem(L"Mantenimiento");
		cli::array<String ^> ^ grupos = gcnew cli::array<String ^>{L"Inserción", L"Modificación", L"Búsquedas", L"Borrados"};
		for (int g = 0; g < grupos->Length; g++)
		{
			ToolStripMenuItem ^ grupo = gcnew ToolStripMenuItem(grupos[g]);
			for (int i = 0; i < entidades->Length; i++)
			{
				ToolStripMenuItem ^ op = gcnew ToolStripMenuItem(entidades[i]);
				op->Tag = String::Concat(Convert::ToString(g), L":", Convert::ToString(i)); // "tipo:indice"
				op->Click += gcnew System::EventHandler(this, &Form1::opcion_Click);
				grupo->DropDownItems->Add(op);
			}
			mantenimiento->DropDownItems->Add(grupo);
		}
		ToolStripMenuItem ^ cargar = gcnew ToolStripMenuItem(L"Cargar archivos");
		cargar->Tag = L"4:0";
		cargar->Click += gcnew System::EventHandler(this, &Form1::opcion_Click);
		mantenimiento->DropDownItems->Add(cargar);

		// Reportes todavía no se hace (solo se muestra el título)
		ToolStripMenuItem ^ menuReportes = gcnew ToolStripMenuItem(L"Reportes");
		// Acerca de abre la ventana con los datos del sistema y las autoras
		ToolStripMenuItem ^ acerca = gcnew ToolStripMenuItem(L"Acerca de");
		acerca->Click += gcnew System::EventHandler(this, &Form1::acerca_Click);

		this->menuStrip1->Items->Add(mantenimiento);
		this->menuStrip1->Items->Add(menuReportes);
		this->menuStrip1->Items->Add(acerca);
	}

	void Form1::CrearTarjetas()
	{
		cli::array<String ^> ^ claves = gcnew cli::array<String ^>{L"Paises", L"Ciudades", L"Pacientes", L"Medicos",
																   L"Especialidades", L"Citas", L"Habitaciones", L"Hospitalizaciones", L"Diagnosticos", L"Tratamientos"};
		cli::array<String ^> ^ textos = gcnew cli::array<String ^>{L"Países", L"Ciudades", L"Pacientes", L"Médicos",
																   L"Especialidades", L"Citas", L"Habitaciones", L"Hospitalizaciones", L"Diagnósticos", L"Tratamientos"};
		cli::array<String ^> ^ imagenes = gcnew cli::array<String ^>{L"icono_pais.png", L"icono_ciudad.png", L"icono_paciente.png",
																	 L"icono_medico.png", L"icono_especialidad.png", L"icono_cita.png", L"icono_habitacion.png", L"icono_hospital.png",
																	 L"icono_diagnostico.png", L"icono_tratamiento.png"};
		// colores de fondo (R, G, B) de cada tarjeta
		cli::array<int> ^ rgb = gcnew cli::array<int>{255, 238, 200, 210, 230, 248, 214, 242, 232, 225, 225, 250,
													  250, 222, 236, 255, 230, 208, 206, 236, 250, 232, 224, 250, 255, 246, 204, 255, 222, 222};

		// Las tarjetas tienen Citas antes que Habitaciones, pero las ventanas (Ventanas.cpp) las tienen
		// al revés. Esta lista convierte la posición de la tarjeta en el número de entidad correcto.
		cli::array<int> ^ entidadDeTarjeta = gcnew cli::array<int>{0, 1, 2, 3, 4, 6, 5, 7, 8, 9};

		for (int i = 0; i < claves->Length; i++)
		{
			Panel ^ panel = gcnew Panel();
			PictureBox ^ imagen = gcnew PictureBox();
			Label ^ texto = gcnew Label();

			imagen->Name = String::Concat(L"pic", claves[i]);
			imagen->Dock = DockStyle::Fill;
			imagen->BackColor = System::Drawing::Color::Transparent;
			imagen->SizeMode = PictureBoxSizeMode::Zoom;
			imagen->Cursor = System::Windows::Forms::Cursors::Hand;
			imagen->Image = Cargar(imagenes[i]);

			texto->Name = String::Concat(L"lbl", claves[i]);
			texto->Dock = DockStyle::Bottom;
			texto->Height = 34;
			texto->BackColor = System::Drawing::Color::White;
			texto->ForeColor = System::Drawing::Color::FromArgb(16, 52, 66);
			texto->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.75, System::Drawing::FontStyle::Bold);
			texto->TextAlign = ContentAlignment::MiddleCenter;
			texto->Text = textos[i];
			texto->Cursor = System::Windows::Forms::Cursors::Hand;

			panel->Name = String::Concat(L"pnl", claves[i]);
			panel->Dock = DockStyle::Fill;
			panel->Margin = System::Windows::Forms::Padding(8);
			panel->Padding = System::Windows::Forms::Padding(10, 12, 10, 10);
			panel->BackColor = System::Drawing::Color::FromArgb(rgb[i * 3], rgb[i * 3 + 1], rgb[i * 3 + 2]);
			panel->Cursor = System::Windows::Forms::Cursors::Hand;
			panel->Controls->Add(imagen); // primero el que llena
			panel->Controls->Add(texto);  // despues el que va abajo

			// El clic funciona sobre el panel, la imagen o el texto. El Tag guarda el número de entidad
			String ^ numeroEntidad = Convert::ToString(entidadDeTarjeta[i]);
			panel->Tag = numeroEntidad;
			imagen->Tag = numeroEntidad;
			texto->Tag = numeroEntidad;
			panel->Click += gcnew System::EventHandler(this, &Form1::tarjeta_Click);
			imagen->Click += gcnew System::EventHandler(this, &Form1::tarjeta_Click);
			texto->Click += gcnew System::EventHandler(this, &Form1::tarjeta_Click);

			this->tablaTarjetas->Controls->Add(panel, i % 4, i / 4);
		}
	}

	Image ^ Form1::Cargar(String ^ nombre)
	{
		cli::array<String ^> ^ rutas = gcnew cli::array<String ^>{
			Path::Combine(Path::Combine(Environment::CurrentDirectory, "imagenes"), nombre),
			Path::Combine(Path::Combine(AppDomain::CurrentDomain->BaseDirectory, "imagenes"), nombre),
			Path::Combine(Path::Combine(AppDomain::CurrentDomain->BaseDirectory, "..\\imagenes"), nombre),
			Path::Combine(Path::Combine(AppDomain::CurrentDomain->BaseDirectory, "..\\..\\imagenes"), nombre)};
		for each (String ^ ruta in rutas)
		{
			if (File::Exists(ruta))
			{
				cli::array<Byte> ^ datos = File::ReadAllBytes(ruta); // en memoria: no bloquea el archivo
				return Image::FromStream(gcnew MemoryStream(datos));
			}
		}
		return nullptr;
	}

	void Form1::CargarImagenes()
	{
		Image ^ fondo = Cargar(L"fondo.png");
		if (fondo != nullptr)
		{
			this->BackgroundImage = fondo;
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
		}
		this->itemFecha->Image = Cargar(L"icono_cita.png");
		this->itemHora->Image = Cargar(L"icono_reloj.png");
	}

	void Form1::LeerArchivos()
	{
		if (archivosCargados)
		{
			MessageBox::Show(this, L"Los archivos ya fueron cargados.", L"Cargar archivos", MessageBoxButtons::OK, MessageBoxIcon::Information);
			return;
		}
		try
		{
			this->Cursor = System::Windows::Forms::Cursors::WaitCursor;
			cargarArchivos(); // funcion nativa del Proyecto #2
			archivosCargados = true;
			this->Cursor = System::Windows::Forms::Cursors::Default;
			MessageBox::Show(this, L"Archivos cargados correctamente.", L"Cargar archivos", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}
		catch (...)
		{
			this->Cursor = System::Windows::Forms::Cursors::Default;
			MessageBox::Show(this, L"Ocurrió un error al leer los archivos.", L"Cargar archivos", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

	System::Void Form1::timer1_Tick(System::Object ^ sender, System::EventArgs ^ e)
	{
		DateTime ahora = DateTime::Now;
		CultureInfo ^ es = gcnew CultureInfo("es-CR");
		this->itemFecha->Text = ahora.ToString("dd/MM/yyyy", es);
		this->itemHora->Text = ahora.ToString("hh:mm:ss tt", es);
	}

	// Clic en una opción del menú: la etiqueta (Tag) trae "tipo:indice"
	// tipo: 0 inserción, 1 modificación, 2 consulta, 3 borrado, 4 cargar archivos
	System::Void Form1::opcion_Click(System::Object ^ sender, System::EventArgs ^ e)
	{
		ToolStripMenuItem ^ item = safe_cast<ToolStripMenuItem ^>(sender);
		String ^ tag = safe_cast<String ^>(item->Tag);
		cli::array<String ^> ^ partes = tag->Split(L':');
		int tipo = Int32::Parse(partes[0]);
		int indice = Int32::Parse(partes[1]);
		if (tipo == 4)
		{
			LeerArchivos();
			return;
		}
		Ventanas::Abrir(this, tipo, indice);
	}

	// Clic en un icono: abre la ventana con Insertar, Modificar, Buscar y Eliminar de esa entidad.
	// El Tag del control tocado trae el número de entidad.
	System::Void Form1::tarjeta_Click(System::Object ^ sender, System::EventArgs ^ e)
	{
		Control ^ control = safe_cast<Control ^>(sender);
		int indice = Int32::Parse(safe_cast<String ^>(control->Tag));
		Ventanas::AbrirEntidad(this, indice);
	}

	// Clic en el menú Acerca de
	System::Void Form1::acerca_Click(System::Object ^ sender, System::EventArgs ^ e)
	{
		Ventanas::AbrirAcercaDe(this);
	}
}
