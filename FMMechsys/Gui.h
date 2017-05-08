#pragma once
#include <iostream>
#include <fstream>
#include <hdf5.h>
#include <hdf5_hl.h>
#include <msclr/marshal_cppstd.h>

#define _USE_MATH_DEFINES
#include <cmath>

#include "Splash.h"

using namespace msclr::interop;

namespace FMMechsys {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Gui
	/// </summary>
	public ref class Gui : public System::Windows::Forms::Form
	{
	public:
		Gui(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Gui()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Label^  label3;
	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(12, 50);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(371, 31);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Name of h5 file from Mechsys";
			this->label1->Click += gcnew System::EventHandler(this, &Gui::label1_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(152, 211);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(378, 31);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Created by Sergio Torres PhD";
			this->label2->Click += gcnew System::EventHandler(this, &Gui::label2_Click);
			// 
			// textBox1
			// 
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.125F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox1->Location = System::Drawing::Point(430, 53);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(276, 38);
			this->textBox1->TabIndex = 2;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &Gui::textBox1_TextChanged);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(67, 118);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(275, 67);
			this->button1->TabIndex = 3;
			this->button1->Text = L"Generate";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Gui::button1_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.125F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(497, 133);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(86, 31);
			this->label3->TabIndex = 4;
			this->label3->Text = L"";
			this->label3->Click += gcnew System::EventHandler(this, &Gui::label3_Click);
			// 
			// Gui
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(12, 25);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(734, 251);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Name = L"Gui";
			this->Text = L"Fracman+Mechsys";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void label2_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		//The user introduces the filename
		String ^filename = textBox1->Text;
		std::string fname = marshal_as<std::string>(filename);
		fname = fname + ".h5";

		//Oopen the file and dataset containing the fractures
		hid_t file_id, dset;
		file_id = H5Fopen(fname.c_str(), H5F_ACC_RDONLY, H5P_DEFAULT);
		dset    = H5Dopen(file_id, "/Verts", H5P_DEFAULT);

		//Gettings number of fractures
		hid_t  dspace = H5Dget_space(dset);
		hsize_t dims[1];
		H5Sget_simple_extent_dims(dspace, dims, NULL);


		//Application::EnableVisualStyles();
		//Application::SetCompatibleTextRenderingDefault(false);
		//Splash splash;
		//Application::Run(%splash);

		Splash ^ splash = gcnew Splash;
		



		String ^Miu = "miu";
		splash->ModifyL1(Miu);

		splash->ShowDialog();

	}
private: System::Void label3_Click(System::Object^  sender, System::EventArgs^  e) {
}
};
}
