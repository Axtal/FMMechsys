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

	private:
		String ^ filename;     //h5 file simple 
		String ^ filenameFP;

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

	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;

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
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(6, 26);
			this->label1->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(144, 17);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Open h5 Mechsys file";
			this->label1->Click += gcnew System::EventHandler(this, &Gui::label1_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(31, 105);
			this->label2->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(199, 17);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Created by Sergio Torres PhD";
			this->label2->Click += gcnew System::EventHandler(this, &Gui::label2_Click);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(34, 61);
			this->button1->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(138, 35);
			this->button1->TabIndex = 3;
			this->button1->Text = L"Generate";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Gui::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(167, 23);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 4;
			this->button2->Text = L"...";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Gui::button2_Click);
			// 
			// Gui
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(260, 131);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
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
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		//The user introduces the filename
		String ^ftemp = filenameFP;

		std::string fname = marshal_as<std::string>(ftemp);

		//Open the file and dataset containing the fractures
		hid_t file_id, dataset;
		
		file_id = H5Fopen(fname.c_str(), H5F_ACC_RDONLY, H5P_DEFAULT);

		if (file_id < 0)
		{
			Splash ^ splash = gcnew Splash;
			splash->ModifyL1("File not found");
			splash->ShowDialog();
			return;
		}
		
		


		dataset    = H5Dopen(file_id, "/Verts", H5P_DEFAULT);
		hid_t dspace   = H5Dget_space(dataset);
		hssize_t hsize = H5Sget_simple_extent_ndims(dspace);

		size_t ndims = hsize;
		hsize_t * dims;
		dims = new hsize_t[ndims]; 
		H5Sget_simple_extent_dims(dspace, dims, NULL);

		//Gettings number of fractures
		
		String ^ Nfractures = "Number of fractures ";
		Nfractures = Nfractures + System::Convert::ToString(dims[0]);

		Splash ^ splash = gcnew Splash;
		splash->ModifyL1(Nfractures);
		splash->ShowDialog();

	}
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
	OpenFileDialog ^ openFileDialog1 = gcnew OpenFileDialog();
	openFileDialog1->Filter = "h5 Files|*.h5";
	openFileDialog1->Title = "Select an h5 File";

	//if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	//{
		// Assign the cursor in the Stream to  
		// the Form's Cursor property.  
		//this->Cursor = gcnew
			//System::Windows::Forms::Cursor(
				//openFileDialog1->OpenFile());
	//}
	if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		//System::IO::StreamReader ^sr = gcnew	System::IO::StreamReader(openFileDialog1->FileName);
		//MessageBox.Show(sr->ReadToEnd());
		//sr.Close();
		filename   = System::IO::Path::GetFileName(openFileDialog1->FileName);
		filenameFP = System::IO::Path::GetFullPath(openFileDialog1->FileName);
	}
	//filename = openFileDialog1->FileName;
}
};
}
