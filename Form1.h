//Elaborado por : Hilary Aguilar y Arina Tarasova
//Proyecto Programado #3 - Estructuras de Datos
#pragma once

void cargarArchivos(); //lee los CSV y construye los arboles
namespace mainInterfaz {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Globalization;
	using namespace System::IO;

	/// <summary>
	/// Resumen de Form1: ventana principal del sistema
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			entidades = gcnew cli::array<String^>{ L"País", L"Ciudad", L"Paciente", L"Médico", L"Especialidad", L"Habitación", L"Cita", L"Hospitalización", L"Diagnóstico", L"Tratamiento" };
			archivosCargados = false;
			this->DoubleBuffered = true;
			CrearMenu();
			CrearTarjetas();
			CargarImagenes();
			timer1_Tick(nullptr, nullptr);
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1() {
			if (components)
			{
				delete components;
			}
		}
	//Componentes, declara y configura el diseñador
	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	private: System::Windows::Forms::StatusStrip^ statusStrip1;
	private: System::Windows::Forms::ToolStripStatusLabel^ lblUsuario;
	private: System::Windows::Forms::ToolStripStatusLabel^ lblMensaje;
	private: System::Windows::Forms::Panel^ panelSuperior;
	private: System::Windows::Forms::PictureBox^ picLogoChico;
	private: System::Windows::Forms::Label^ lblSistema;
	private: System::Windows::Forms::Label^ lblHospital;
	private: System::Windows::Forms::PictureBox^ picFecha;
	private: System::Windows::Forms::Label^ lblFecha;
	private: System::Windows::Forms::Label^ lblSeparador;
	private: System::Windows::Forms::PictureBox^ picHora;
	private: System::Windows::Forms::Label^ lblHora;
	private: System::Windows::Forms::TableLayoutPanel^ tablaPrincipal;
	private: System::Windows::Forms::TableLayoutPanel^ tablaTarjetas;
	private: System::Windows::Forms::Panel^ panelDerecho;
	private: System::Windows::Forms::PictureBox^ picLogoGrande;
	private: System::Windows::Forms::Label^ lblHospitalGrande;
	private: System::Windows::Forms::Label^ lblSistemaGrande;
	private: System::Windows::Forms::Label^ lblPie;
	private: System::Windows::Forms::Timer^ timer1;
	private: System::ComponentModel::IContainer^ components;

#pragma region Windows Form Designer generated code
		   /// <summary>
		   /// Método necesario para admitir el Diseñador. No se puede modificar
		   /// el contenido de este método con el editor de código.
		   /// </summary>
		   void InitializeComponent(void){
			   this->components = (gcnew System::ComponentModel::Container());
			   this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			   this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
			   this->lblUsuario = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			   this->lblMensaje = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			   this->panelSuperior = (gcnew System::Windows::Forms::Panel());
			   this->picLogoChico = (gcnew System::Windows::Forms::PictureBox());
			   this->lblSistema = (gcnew System::Windows::Forms::Label());
			   this->lblHospital = (gcnew System::Windows::Forms::Label());
			   this->picFecha = (gcnew System::Windows::Forms::PictureBox());
			   this->lblFecha = (gcnew System::Windows::Forms::Label());
			   this->lblSeparador = (gcnew System::Windows::Forms::Label());
			   this->picHora = (gcnew System::Windows::Forms::PictureBox());
			   this->lblHora = (gcnew System::Windows::Forms::Label());
			   this->tablaPrincipal = (gcnew System::Windows::Forms::TableLayoutPanel());
			   this->tablaTarjetas = (gcnew System::Windows::Forms::TableLayoutPanel());
			   this->panelDerecho = (gcnew System::Windows::Forms::Panel());
			   this->picLogoGrande = (gcnew System::Windows::Forms::PictureBox());
			   this->lblHospitalGrande = (gcnew System::Windows::Forms::Label());
			   this->lblSistemaGrande = (gcnew System::Windows::Forms::Label());
			   this->lblPie = (gcnew System::Windows::Forms::Label());
			   this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			   this->menuStrip1->SuspendLayout();
			   this->statusStrip1->SuspendLayout();
			   this->panelSuperior->SuspendLayout();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picLogoChico))->BeginInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picFecha))->BeginInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picHora))->BeginInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picLogoGrande))->BeginInit();
			   this->tablaPrincipal->SuspendLayout();
			   this->tablaTarjetas->SuspendLayout();
			   this->panelDerecho->SuspendLayout();
			   this->SuspendLayout();

			   //menuStrip1
			   this->menuStrip1->Location = System::Drawing::Point(0, 0);
			   this->menuStrip1->Name = L"menuStrip1";
			   this->menuStrip1->Size = System::Drawing::Size(1240, 24);
			   this->menuStrip1->TabIndex = 0;
			   this->menuStrip1->Text = L"menuStrip1";

			   //statusStrip1
			   this->statusStrip1->BackColor = System::Drawing::Color::FromArgb(3, 26, 36);
			   this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) { this->lblUsuario, this->lblMensaje });
			   this->statusStrip1->Location = System::Drawing::Point(0, 698);
			   this->statusStrip1->Name = L"statusStrip1";
			   this->statusStrip1->SizingGrip = false;
			   this->statusStrip1->Size = System::Drawing::Size(1240, 22);
			   this->statusStrip1->TabIndex = 1;
			   this->statusStrip1->Text = L"statusStrip1";

			   //lblUsuario
			   this->lblUsuario->ForeColor = System::Drawing::Color::FromArgb(200, 240, 230);
			   this->lblUsuario->Name = L"lblUsuario";
			   this->lblUsuario->Size = System::Drawing::Size(330, 17);
			   this->lblUsuario->Text = L"Usuario: Administrador     |     Sistema de Gestión Hospitalaria";

			   //lblMensaje
			   this->lblMensaje->ForeColor = System::Drawing::Color::FromArgb(255, 224, 140);
			   this->lblMensaje->Name = L"lblMensaje";
			   this->lblMensaje->Size = System::Drawing::Size(895, 17);
			   this->lblMensaje->Spring = true;
			   this->lblMensaje->Text = L"Listo.";
			   this->lblMensaje->TextAlign = System::Drawing::ContentAlignment::MiddleRight;

			   //Panel superior
			   this->panelSuperior->BackColor = System::Drawing::Color::FromArgb(170, 2, 22, 30);
			   this->panelSuperior->Controls->Add(this->picLogoChico);
			   this->panelSuperior->Controls->Add(this->lblSistema);
			   this->panelSuperior->Controls->Add(this->lblHospital);
			   this->panelSuperior->Controls->Add(this->picFecha);
			   this->panelSuperior->Controls->Add(this->lblFecha);
			   this->panelSuperior->Controls->Add(this->lblSeparador);
			   this->panelSuperior->Controls->Add(this->picHora);
			   this->panelSuperior->Controls->Add(this->lblHora);
			   this->panelSuperior->Dock = System::Windows::Forms::DockStyle::Top;
			   this->panelSuperior->Location = System::Drawing::Point(0, 24);
			   this->panelSuperior->Name = L"panelSuperior";
			   this->panelSuperior->Size = System::Drawing::Size(1240, 68);
			   this->panelSuperior->TabIndex = 2;

			   //LogoChico
			   this->picLogoChico->BackColor = System::Drawing::Color::Transparent;
			   this->picLogoChico->Location = System::Drawing::Point(20, 14);
			   this->picLogoChico->Name = L"picLogoChico";
			   this->picLogoChico->Size = System::Drawing::Size(40, 40);
			   this->picLogoChico->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			   this->picLogoChico->TabIndex = 0;
			   this->picLogoChico->TabStop = false;

			   // lblSistema
			   this->lblSistema->AutoSize = true;
			   this->lblSistema->BackColor = System::Drawing::Color::Transparent;
			   this->lblSistema->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14.25, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			   this->lblSistema->ForeColor = System::Drawing::Color::White;
			   this->lblSistema->Location = System::Drawing::Point(70, 10);
			   this->lblSistema->Name = L"lblSistema";
			   this->lblSistema->Size = System::Drawing::Size(300, 26);
			   this->lblSistema->TabIndex = 1;
			   this->lblSistema->Text = L"Sistema de Gestión Hospitalaria";

			   //lblHospital
			   this->lblHospital->AutoSize = true;
			   this->lblHospital->BackColor = System::Drawing::Color::Transparent;
			   this->lblHospital->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10.0, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			   this->lblHospital->ForeColor = System::Drawing::Color::FromArgb(150, 235, 215);
			   this->lblHospital->Location = System::Drawing::Point(72, 38);
			   this->lblHospital->Name = L"lblHospital";
			   this->lblHospital->Size = System::Drawing::Size(110, 19);
			   this->lblHospital->TabIndex = 1;
			   this->lblHospital->Text = L"Hospital San Rafael";

			   //fecha
			   this->picFecha->BackColor = System::Drawing::Color::Transparent;
			   this->picFecha->Location = System::Drawing::Point(796, 19);
			   this->picFecha->Name = L"picFecha";
			   this->picFecha->Size = System::Drawing::Size(30, 30);
			   this->picFecha->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			   this->picFecha->TabIndex = 0;
			   this->picFecha->TabStop = false;
			   this->picFecha->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right);

			   //lblSeparador
			   this->lblSeparador->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right);
			   this->lblSeparador->AutoSize = false;
			   this->lblSeparador->BackColor = System::Drawing::Color::Transparent;
			   this->lblSeparador->Font = (gcnew System::Drawing::Font(L"Segoe UI", static_cast<float>(12.75), System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			   this->lblSeparador->ForeColor = System::Drawing::Color::FromArgb(130, 255, 255, 255);
			   this->lblSeparador->Location = System::Drawing::Point(1004, 17);
			   this->lblSeparador->Name = L"lblSeparador";
			   this->lblSeparador->Size = System::Drawing::Size(16, 34);
			   this->lblSeparador->TabIndex = 1;
			   this->lblSeparador->Text = L"|";
			   this->lblSeparador->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;

			   //hora
			   this->picHora->BackColor = System::Drawing::Color::Transparent;
			   this->picHora->Location = System::Drawing::Point(1026, 19);
			   this->picHora->Name = L"picHora";
			   this->picHora->Size = System::Drawing::Size(30, 30);
			   this->picHora->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			   this->picHora->TabIndex = 0;
			   this->picHora->TabStop = false;
			   this->picHora->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right);

			   //lblHora
			   this->lblHora->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right);
			   this->lblHora->AutoSize = false;
			   this->lblHora->BackColor = System::Drawing::Color::Transparent;
			   this->lblHora->Font = (gcnew System::Drawing::Font(L"Segoe UI", static_cast<float>(12.75), System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			   this->lblHora->ForeColor = System::Drawing::Color::White;
			   this->lblHora->Location = System::Drawing::Point(1062, 17);
			   this->lblHora->Name = L"lblHora";
			   this->lblHora->Size = System::Drawing::Size(160, 34);
			   this->lblHora->TabIndex = 1;
			   this->lblHora->Text = L"00:00:00 a. m.";
			   this->lblHora->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;

			   //tablaPrincipal
			   this->tablaPrincipal->BackColor = System::Drawing::Color::Transparent;
			   this->tablaPrincipal->ColumnCount = 2;
			   this->tablaPrincipal->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 64)));
			   this->tablaPrincipal->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 36)));
			   this->tablaPrincipal->Controls->Add(this->tablaTarjetas, 0, 0);
			   this->tablaPrincipal->Controls->Add(this->panelDerecho, 1, 0);
			   this->tablaPrincipal->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->tablaPrincipal->Location = System::Drawing::Point(0, 92);
			   this->tablaPrincipal->Name = L"tablaPrincipal";
			   this->tablaPrincipal->Padding = System::Windows::Forms::Padding(24, 24, 28, 24);
			   this->tablaPrincipal->RowCount = 1;
			   this->tablaPrincipal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			   this->tablaPrincipal->Size = System::Drawing::Size(1240, 606);
			   this->tablaPrincipal->TabIndex = 3;

			   //tablaTarjetas
			   this->tablaTarjetas->BackColor = System::Drawing::Color::Transparent;
			   this->tablaTarjetas->ColumnCount = 4;
			   this->tablaTarjetas->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 25)));
			   this->tablaTarjetas->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 25)));
			   this->tablaTarjetas->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 25)));
			   this->tablaTarjetas->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 25)));
			   this->tablaTarjetas->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->tablaTarjetas->Location = System::Drawing::Point(24, 24);
			   this->tablaTarjetas->Margin = System::Windows::Forms::Padding(0);
			   this->tablaTarjetas->Name = L"tablaTarjetas";
			   this->tablaTarjetas->RowCount = 3;
			   this->tablaTarjetas->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, static_cast<float>(33.33333))));
			   this->tablaTarjetas->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, static_cast<float>(33.33333))));
			   this->tablaTarjetas->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, static_cast<float>(33.33333))));
			   this->tablaTarjetas->Size = System::Drawing::Size(600, 558);
			   this->tablaTarjetas->TabIndex = 0;

			   //panelDerecho
			   this->panelDerecho->BackColor = System::Drawing::Color::FromArgb(34, 255, 255, 255);
			   this->panelDerecho->Controls->Add(this->lblSistemaGrande);
			   this->panelDerecho->Controls->Add(this->lblHospitalGrande);
			   this->panelDerecho->Controls->Add(this->picLogoGrande);
			   this->panelDerecho->Controls->Add(this->lblPie);
			   this->panelDerecho->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->panelDerecho->Location = System::Drawing::Point(618, 28);
			   this->panelDerecho->Margin = System::Windows::Forms::Padding(14, 4, 0, 4);
			   this->panelDerecho->Name = L"panelDerecho";
			   this->panelDerecho->Size = System::Drawing::Size(380, 550);
			   this->panelDerecho->TabIndex = 1;

			   //logoGrande
			   this->picLogoGrande->BackColor = System::Drawing::Color::Transparent;
			   this->picLogoGrande->Dock = System::Windows::Forms::DockStyle::Top;
			   this->picLogoGrande->Name = L"picLogoGrande";
			   this->picLogoGrande->Size = System::Drawing::Size(380, 260);
			   this->picLogoGrande->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			   this->picLogoGrande->TabIndex = 0;
			   this->picLogoGrande->TabStop = false;

			   //lblHospitalGrande
			   this->lblHospitalGrande->AutoSize = false;
			   this->lblHospitalGrande->BackColor = System::Drawing::Color::Transparent;
			   this->lblHospitalGrande->Dock = System::Windows::Forms::DockStyle::Top;
			   this->lblHospitalGrande->Font = (gcnew System::Drawing::Font(L"Segoe UI", 24.0, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			   this->lblHospitalGrande->ForeColor = System::Drawing::Color::White;
			   this->lblHospitalGrande->Name = L"lblHospitalGrande";
			   this->lblHospitalGrande->Size = System::Drawing::Size(380, 56);
			   this->lblHospitalGrande->TabIndex = 1;
			   this->lblHospitalGrande->Text = L"Hospital San Rafael";
			   this->lblHospitalGrande->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;

			   //lblSistemaGrande
			   this->lblSistemaGrande->AutoSize = false;
			   this->lblSistemaGrande->BackColor = System::Drawing::Color::Transparent;
			   this->lblSistemaGrande->Dock = System::Windows::Forms::DockStyle::Top;
			   this->lblSistemaGrande->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11.25, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			   this->lblSistemaGrande->ForeColor = System::Drawing::Color::FromArgb(170, 240, 222);
			   this->lblSistemaGrande->Name = L"lblSistemaGrande";
			   this->lblSistemaGrande->Size = System::Drawing::Size(380, 30);
			   this->lblSistemaGrande->TabIndex = 1;
			   this->lblSistemaGrande->Text = L"Sistema de Gestión Hospitalaria";
			   this->lblSistemaGrande->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;

			   //lblPie
			   this->lblPie->AutoSize = false;
			   this->lblPie->BackColor = System::Drawing::Color::Transparent;
			   this->lblPie->Dock = System::Windows::Forms::DockStyle::Bottom;
			   this->lblPie->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			   this->lblPie->ForeColor = System::Drawing::Color::FromArgb(150, 215, 200);
			   this->lblPie->Name = L"lblPie";
			   this->lblPie->Size = System::Drawing::Size(380, 40);
			   this->lblPie->TabIndex = 1;
			   this->lblPie->Text = L"Estructuras de Datos  ·  Proyecto #3  ·  Avance 1";
			   this->lblPie->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;

			   //timer1
			   this->timer1->Enabled = true;
			   this->timer1->Interval = 1000;
			   this->timer1->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);

			   //Form1
			   this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->BackColor = System::Drawing::Color::FromArgb(5, 38, 52);
			   this->ClientSize = System::Drawing::Size(1240, 720);
			   this->Controls->Add(this->tablaPrincipal);
			   this->Controls->Add(this->panelSuperior);
			   this->Controls->Add(this->statusStrip1);
			   this->Controls->Add(this->menuStrip1);
			   this->MainMenuStrip = this->menuStrip1;
			   this->MinimumSize = System::Drawing::Size(1016, 700);
			   this->Name = L"Form1";
			   this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			   this->Text = L"Sistema de Gestión Hospitalaria - Hospital San Rafael";
			   this->menuStrip1->ResumeLayout(false);
			   this->menuStrip1->PerformLayout();
			   this->statusStrip1->ResumeLayout(false);
			   this->statusStrip1->PerformLayout();
			   this->panelSuperior->ResumeLayout(false);
			   this->panelSuperior->PerformLayout();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picLogoChico))->EndInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picFecha))->EndInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picHora))->EndInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picLogoGrande))->EndInit();
			   this->tablaPrincipal->ResumeLayout(false);
			   this->tablaTarjetas->ResumeLayout(false);
			   this->panelDerecho->ResumeLayout(false);
			   this->ResumeLayout(false);
			   this->PerformLayout();
		   }
#pragma endregion
	private:
		cli::array<String^>^ entidades; //nombre de cada entidad
		bool archivosCargados;

		//métodos que estan en Form1.cpp
		void CrearMenu();
		void CrearTarjetas();
		Image^ Cargar(String^ nombre);
		void CargarImagenes();
		void Mensaje(String^ texto);
		void LeerArchivos();

	//Eventos implementados en Form1.cpp
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e);
	private: System::Void leerArchivos_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void salir_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void mnuAcercaDe_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void tarjeta_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void entidad_Click(System::Object^ sender, System::EventArgs^ e);
	};
}
