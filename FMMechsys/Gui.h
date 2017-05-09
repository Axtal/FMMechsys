#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <fstream>
#include <hdf5.h>
#include <hdf5_hl.h>
#include <Eigen/Dense>
#include <msclr/marshal_cppstd.h>
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
		hid_t file_id;		
		file_id = H5Fopen(fname.c_str(), H5F_ACC_RDONLY, H5P_DEFAULT);
		if (file_id < 0)
		{
			Splash ^ splash = gcnew Splash;
			splash->ModifyL1("File not found");
			splash->ShowDialog();
			return;
		}
		
		hid_t dataset;
		dataset    = H5Dopen(file_id, "/Verts", H5P_DEFAULT);
		if (dataset < 0)
		{
			Splash ^ splash = gcnew Splash;
			splash->ModifyL1("No /Verts dataset in h5 file");
			splash->ShowDialog();
			return;
		}

		hid_t dspace   = H5Dget_space(dataset);
		hssize_t hsize = H5Sget_simple_extent_ndims(dspace);

		size_t ndims = hsize;
		hsize_t * dims;
		dims = new hsize_t[ndims]; 
		H5Sget_simple_extent_dims(dspace, dims, NULL);

		size_t nfrac = dims[0] / 15;

		

		//Gettings number of fractures		
		String ^ Nfractures = "Number of fractures ";
		Nfractures = Nfractures + System::Convert::ToString(nfrac);


		
		Splash ^ splash = gcnew Splash;
		splash->ModifyL1(Nfractures);
		splash->ShowDialog();


		// Getting fractures
		float * Vecs;
		Vecs = new float[dims[0]];
		H5LTread_dataset_float(file_id, "/Verts", Vecs);

		// Closing h5 file
		H5Fflush(file_id, H5F_SCOPE_GLOBAL);
		H5Fclose(file_id);

		Eigen::Vector3d * Verts;
		Verts = new Eigen::Vector3d[5 * nfrac];

		for (size_t nf = 0; nf < nfrac; nf++)
		{
			Verts[5 * nf + 0] = Eigen::Vector3d(Vecs[15 * nf + 0], Vecs[15 * nf + 1], Vecs[15 * nf + 2]);
			Verts[5 * nf + 1] = Eigen::Vector3d(Vecs[15 * nf + 3], Vecs[15 * nf + 4], Vecs[15 * nf + 5]);
			Verts[5 * nf + 2] = Eigen::Vector3d(Vecs[15 * nf + 6], Vecs[15 * nf + 7], Vecs[15 * nf + 8]);
			Verts[5 * nf + 3] = Eigen::Vector3d(Vecs[15 * nf + 9], Vecs[15 * nf + 10], Vecs[15 * nf + 11]);
			Verts[5 * nf + 4] = Eigen::Vector3d(Vecs[15 * nf + 12], Vecs[15 * nf + 13], Vecs[15 * nf + 14]);
		}
		delete[] dims;

		std::ofstream myfile("macro.fmf");
		// Writing Fractures to Fracman fracture file
		for (size_t nf = 0; nf < nfrac; nf++)
		{
			double x = Verts[5 * nf + 4](0);
			double y = Verts[5 * nf + 4](2);
			double z = Verts[5 * nf + 4](1);
			Eigen::Vector3d d1 = Verts[5 * nf + 1] - Verts[5 * nf + 0];
			Eigen::Vector3d d2 = Verts[5 * nf + 3] - Verts[5 * nf + 0];
			Eigen::Vector3d d3 = Verts[5 * nf + 3] - Verts[5 * nf + 1];
			Eigen::Vector3d d1xd2 = d1.cross(d2);
			Eigen::Vector3d nz(0, 0, 1);

			double theta = acos(d1xd2.dot(nz) / d1xd2.norm());
			double phi = 0.0;
			double lf = d3.norm();

			myfile << " BEGIN SingleFracture \n";
			myfile << "	Name = \"Single Fracture " << nf + 1 << "\" \n";
			myfile << "	Set = \"SF" << nf + 1 << "\" \n";
			myfile << "	Center = " << x << ", " << y << ", " << z << "\n";
			myfile << "	PoleTrPl trend = " << theta * 180 / M_PI << " plunge = " << phi * 180 / M_PI << "\n";
			myfile << "	Radius = " << lf << "\n";
			myfile << "	NumSides = 4 \n";
			myfile << "	MaxElementSize = 0 \n";
			myfile << "	Property Name = \"Aperture\" Type = \"CONSTANT\" \"Value\" = 0.001 \n";
			myfile << "	Property Name = \"Permeability\" Type = \"CONSTANT\" \"Value\" = 1.0e5 \n";
			myfile << "	Property Name = \"Compressibility\" Type = \"CONSTANT\" \"Value\" = 1.0e-7 \n";
			myfile << " END \n";
		}
		//myfile << " BEGIN CREATEREGION \n";
		//myfile << "   ObjectName = \"RegionBox_1\" \n";
		//myfile << "   Type = \"Box\" \n";
		//myfile << "   Center = 0.0, 0.0, 0.0 \n";
		//myfile << "   Size = " << L << ", " << L << ", " << L << "\n";
		//myfile << " END \n";
		//myfile << " BEGIN CLIPFRACTURES \n";
		//myfile << "   Object = \"RegionBox_1\" \n";
		//myfile << "   ClipToPositive = 1 \n";
		//myfile << " END \n";

		myfile.close();


	}
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
	OpenFileDialog ^ openFileDialog1 = gcnew OpenFileDialog();
	openFileDialog1->Filter = "h5 Files|*.h5";
	openFileDialog1->Title = "Select an h5 File";
	if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		filename   = System::IO::Path::GetFileName(openFileDialog1->FileName);
		filenameFP = System::IO::Path::GetFullPath(openFileDialog1->FileName);
	}
}
};
}
