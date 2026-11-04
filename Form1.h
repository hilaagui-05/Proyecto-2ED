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
		~Form1() {
			if (components)
			{
				delete components;
			}
		}
		//Componentes del diseñador
	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	private: System::Windows::Forms::ToolStripLabel^ itemFecha;
	private: System::Windows::Forms::ToolStripLabel^ itemHora;
	private: System::Windows::Forms::StatusStrip^ statusStrip1;
	private: System::Windows::Forms::ToolStripStatusLabel^ lblUsuario;
	private: System::Windows::Forms::TableLayoutPanel^ tablaTarjetas;
	private: System::Windows::Forms::Timer^ timer1;
	private: System::ComponentModel::IContainer^ components;

#pragma region Windows Form Designer generated code
		   void InitializeComponent(void) {
			   this->components = (gcnew System::ComponentModel::Container());
			   this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			   this->itemFecha = (gcnew System::Windows::Forms::ToolStripLabel());
			   this->itemHora = (gcnew System::Windows::Forms::ToolStripLabel());
			   this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
			   this->lblUsuario = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			   this->tablaTarjetas = (gcnew System::Windows::Forms::TableLayoutPanel());
			   this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			   this->menuStrip1->SuspendLayout();
			   this->statusStrip1->SuspendLayout();
			   this->tablaTarjetas->SuspendLayout();
			   this->SuspendLayout();

			   //menuStrip1: menú, fecha y hora en la misma barra
			   this->menuStrip1->BackColor = System::Drawing::Color::FromArgb(244, 248, 250);
			   this->menuStrip1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10.5F));
			   this->menuStrip1->ImageScalingSize = System::Drawing::Size(22, 22);
			   this->menuStrip1->Items->Add(this->itemHora);
			   this->menuStrip1->Items->Add(this->itemFecha);
			   this->menuStrip1->Location = System::Drawing::Point(0, 0);
			   this->menuStrip1->Name = L"menuStrip1";
			   this->menuStrip1->Padding = System::Windows::Forms::Padding(8, 4, 12, 4);
			   this->menuStrip1->Size = System::Drawing::Size(1240, 36);
			   this->menuStrip1->TabIndex = 0;
			   this->menuStrip1->Text = L"menuStrip1";

			   //itemFecha
			   this->itemFecha->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
			   this->itemFecha->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10.5F, System::Drawing::FontStyle::Bold));
			   this->itemFecha->ForeColor = System::Drawing::Color::FromArgb(16, 52, 66);
			   this->itemFecha->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   this->itemFecha->Margin = System::Windows::Forms::Padding(0, 0, 18, 0);
			   this->itemFecha->Name = L"itemFecha";
			   this->itemFecha->Text = L"00/00/0000";

			   //itemHora
			   this->itemHora->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
			   this->itemHora->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10.5F, System::Drawing::FontStyle::Bold));
			   this->itemHora->ForeColor = System::Drawing::Color::FromArgb(16, 52, 66);
			   this->itemHora->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   this->itemHora->Name = L"itemHora";
			   this->itemHora->Text = L"00:00:00";

			   //statusStrip1: solo el usuario
			   this->statusStrip1->BackColor = System::Drawing::Color::FromArgb(3, 26, 36);
			   this->statusStrip1->Items->Add(this->lblUsuario);
			   this->statusStrip1->Location = System::Drawing::Point(0, 698);
			   this->statusStrip1->Name = L"statusStrip1";
			   this->statusStrip1->SizingGrip = false;
			   this->statusStrip1->Size = System::Drawing::Size(1240, 22);
			   this->statusStrip1->TabIndex = 1;
			   this->statusStrip1->Text = L"statusStrip1";

			   //lblUsuario
			   this->lblUsuario->ForeColor = System::Drawing::Color::FromArgb(200, 240, 230);
			   this->lblUsuario->Name = L"lblUsuario";
			   this->lblUsuario->Text = L"Usuario: Administrador";

			   //tablaTarjetas
			   this->tablaTarjetas->BackColor = System::Drawing::Color::Transparent;
			   this->tablaTarjetas->ColumnCount = 4;
			   this->tablaTarjetas->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 25)));
			   this->tablaTarjetas->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 25)));
			   this->tablaTarjetas->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 25)));
			   this->tablaTarjetas->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 25)));
			   this->tablaTarjetas->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->tablaTarjetas->Name = L"tablaTarjetas";
			   this->tablaTarjetas->Padding = System::Windows::Forms::Padding(30, 24, 30, 24);
			   this->tablaTarjetas->RowCount = 3;
			   this->tablaTarjetas->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, static_cast<float>(33.33333))));
			   this->tablaTarjetas->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, static_cast<float>(33.33333))));
			   this->tablaTarjetas->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, static_cast<float>(33.33333))));
			   this->tablaTarjetas->TabIndex = 2;

			   //timer1
			   this->timer1->Enabled = true;
			   this->timer1->Interval = 1000;
			   this->timer1->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);

			   //Form1
			   this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->BackColor = System::Drawing::Color::FromArgb(5, 38, 52);
			   this->ClientSize = System::Drawing::Size(1240, 720);
			   this->Controls->Add(this->tablaTarjetas);
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
			   this->tablaTarjetas->ResumeLayout(false);
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
		void LeerArchivos();

		//Eventos implementados en Form1.cpp
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e);
	private: System::Void opcion_Click(System::Object^ sender, System::EventArgs^ e);
	};
}
