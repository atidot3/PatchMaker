#pragma once

#include <Patcher.h>
#include <DirectoryManager.h>

#include <thread>
#include <msclr\marshal_cppstd.h>

namespace DeltaPatcher
{

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Text;
	using namespace System::IO;

	/// <summary>
	/// Description résumée de MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: ajoutez ici le code du constructeur
			//
		}

	protected:
		/// <summary>
		/// Nettoyage des ressources utilisées.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ Start;
	protected:

	private: System::Windows::Forms::TextBox^ srcPath;


	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::TextBox^ destPath;

	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::ProgressBar^ progressBar1;
	private: System::Windows::Forms::RichTextBox^ richTextBox1;

	protected:

	private:
		/// <summary>
		/// Validator
		/// </summary>
		bool src = false;
		bool dest = false;
		bool out = false;
		DirectoryManager::DirectoryCompared* directoryParsed;
		std::string* newFilesPath;
		std::string* oldFilesPath;

	private: System::ComponentModel::BackgroundWorker^ backgroundWorker1;
	private: System::Windows::Forms::Button^ Generate;
	private: System::Windows::Forms::TextBox^ output;
	private: System::Windows::Forms::Button^ outputButton;


		/// <summary>
		/// Variable nécessaire au concepteur.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Méthode requise pour la prise en charge du concepteur - ne modifiez pas
		/// le contenu de cette méthode avec l'éditeur de code.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->Start = (gcnew System::Windows::Forms::Button());
			this->srcPath = (gcnew System::Windows::Forms::TextBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->destPath = (gcnew System::Windows::Forms::TextBox());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->Generate = (gcnew System::Windows::Forms::Button());
			this->output = (gcnew System::Windows::Forms::TextBox());
			this->outputButton = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// Start
			// 
			this->Start->BackColor = System::Drawing::Color::LightGreen;
			this->Start->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->Start->Location = System::Drawing::Point(48, 182);
			this->Start->Name = L"Start";
			this->Start->Size = System::Drawing::Size(126, 34);
			this->Start->TabIndex = 0;
			this->Start->Text = L"Parse Directory";
			this->Start->UseVisualStyleBackColor = false;
			this->Start->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// srcPath
			// 
			this->srcPath->Location = System::Drawing::Point(12, 34);
			this->srcPath->Name = L"srcPath";
			this->srcPath->Size = System::Drawing::Size(359, 20);
			this->srcPath->TabIndex = 1;
			this->srcPath->Text = L"New path folder";
			// 
			// button2
			// 
			this->button2->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button2.BackgroundImage")));
			this->button2->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->button2->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->button2->Location = System::Drawing::Point(389, 34);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 2;
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// destPath
			// 
			this->destPath->Location = System::Drawing::Point(12, 83);
			this->destPath->Name = L"destPath";
			this->destPath->Size = System::Drawing::Size(359, 20);
			this->destPath->TabIndex = 3;
			this->destPath->Text = L"Old path folder";
			// 
			// button3
			// 
			this->button3->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button3.BackgroundImage")));
			this->button3->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->button3->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->button3->Location = System::Drawing::Point(389, 83);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(75, 23);
			this->button3->TabIndex = 4;
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// progressBar1
			// 
			this->progressBar1->Location = System::Drawing::Point(12, 238);
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(846, 23);
			this->progressBar1->TabIndex = 5;
			// 
			// richTextBox1
			// 
			this->richTextBox1->Location = System::Drawing::Point(499, 12);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(359, 218);
			this->richTextBox1->TabIndex = 6;
			this->richTextBox1->Text = L"";
			// 
			// Generate
			// 
			this->Generate->BackColor = System::Drawing::Color::LightGreen;
			this->Generate->Enabled = false;
			this->Generate->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->Generate->Location = System::Drawing::Point(202, 182);
			this->Generate->Name = L"Generate";
			this->Generate->Size = System::Drawing::Size(126, 34);
			this->Generate->TabIndex = 7;
			this->Generate->Text = L"Generate Patch";
			this->Generate->UseVisualStyleBackColor = false;
			this->Generate->Click += gcnew System::EventHandler(this, &MyForm::Generate_Click);
			// 
			// output
			// 
			this->output->Location = System::Drawing::Point(12, 135);
			this->output->Name = L"output";
			this->output->Size = System::Drawing::Size(359, 20);
			this->output->TabIndex = 8;
			this->output->Text = L"Output directory";
			// 
			// outputButton
			// 
			this->outputButton->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"outputButton.BackgroundImage")));
			this->outputButton->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->outputButton->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->outputButton->Location = System::Drawing::Point(389, 135);
			this->outputButton->Name = L"outputButton";
			this->outputButton->Size = System::Drawing::Size(75, 23);
			this->outputButton->TabIndex = 9;
			this->outputButton->UseVisualStyleBackColor = true;
			this->outputButton->Click += gcnew System::EventHandler(this, &MyForm::outputButton_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(885, 273);
			this->Controls->Add(this->outputButton);
			this->Controls->Add(this->output);
			this->Controls->Add(this->Generate);
			this->Controls->Add(this->richTextBox1);
			this->Controls->Add(this->progressBar1);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->destPath);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->srcPath);
			this->Controls->Add(this->Start);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	// -- File processing
	private: System::Void onAllFilesDone(Object^ sender, RunWorkerCompletedEventArgs^ e)
	{
		
	}
	private: System::Void onFileProgress(Object^ sender, ProgressChangedEventArgs^ e)
	{
		progressBar1->Value += e->ProgressPercentage;
	}
	private: System::Void doFile(Object^ sender, DoWorkEventArgs^ e)
	{

	}
	
	// -- Directory and file parsing
	private: System::Void onDirectoryParsed(Object^ sender, RunWorkerCompletedEventArgs^ e)
	{
		// -- turn off all old ui
		{
			destPath->Enabled = false;
			srcPath->Enabled = false;
			button2->Enabled = false;
			button3->Enabled = false;
		}
		// -- turn new ui on
		{
			this->Generate->Enabled = true;
		}

		progressBar1->Value = 0;
		richTextBox1->Text += "file to delete: " + gcnew String(std::to_string(directoryParsed->deleteFiles.size()).c_str()) + "\n";
		richTextBox1->Text += "file to adde: " + gcnew String(std::to_string(directoryParsed->newFiles.size()).c_str()) + "\n";
		richTextBox1->Text += "file to compare: " + gcnew String(std::to_string(directoryParsed->compareFiles.size()).c_str()) + "\n";
	}
	private: System::Void onDirectoryLoadProgress(Object^ sender, ProgressChangedEventArgs^ e)
	{
		progressBar1->Value += e->ProgressPercentage;
	}
	private: System::Void doLoadDir(Object^ sender, DoWorkEventArgs^ e)
	{
		msclr::interop::marshal_context context;
		auto toto = context.marshal_as<std::string>(srcPath->Text);;
		newFilesPath = new std::string(toto);
		toto = context.marshal_as<std::string>(destPath->Text);
		oldFilesPath = new std::string(toto);

		DirectoryManager newFolder(*newFilesPath);
		DirectoryManager oldFolder(*oldFilesPath);
		backgroundWorker1->ReportProgress(5);

		auto newFilesSrc = newFolder.Parse(*newFilesPath);
		auto oldFilesDest = oldFolder.Parse(*oldFilesPath);
		backgroundWorker1->ReportProgress(5);

		directoryParsed->compareFiles = DirectoryManager::GetSameFile(newFilesSrc, oldFilesDest, *newFilesPath, *oldFilesPath);
		backgroundWorker1->ReportProgress(25);

		directoryParsed->deleteFiles = DirectoryManager::GetOldFile(newFilesSrc, oldFilesDest, *newFilesPath, *oldFilesPath);
		backgroundWorker1->ReportProgress(30);

		directoryParsed->newFiles = DirectoryManager::GetNewFile(newFilesSrc, oldFilesDest, *newFilesPath, *oldFilesPath);
		backgroundWorker1->ReportProgress(35);

		newFilesSrc.clear();
		oldFilesDest.clear();
	}
	private: System::Void Generate_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (!out)
		{
			MessageBox::Show("Output folder must be set");
			return;
		}

		/*backgroundWorker1->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &MyForm::doFile);
		backgroundWorker1->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &MyForm::onFileProgress);
		backgroundWorker1->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &MyForm::onAllFilesDone);*/
		richTextBox1->Text = "";
		for (auto& t : directoryParsed->compareFiles)
		{
			auto str = Patcher::Compare(*newFilesPath + t, *oldFilesPath + t);
			richTextBox1->Text += gcnew String((char*)str.data());
		}
	}

	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (!dest || !src)
		{
			MessageBox::Show("Old source and New source folder must be set");
			return;
		}

		Start->Enabled = false;
		backgroundWorker1->WorkerReportsProgress = true;
		backgroundWorker1->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &MyForm::doLoadDir);
		backgroundWorker1->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &MyForm::onDirectoryLoadProgress);
		backgroundWorker1->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &MyForm::onDirectoryParsed);

		directoryParsed = new DirectoryManager::DirectoryCompared;

		backgroundWorker1->RunWorkerAsync();
	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e)
	{
		FolderBrowserDialog fbd;
		fbd.Description = "Choose new source folder";
		if (fbd.ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			src = true;
			srcPath->Text = fbd.SelectedPath;
		}
	}
	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e)
	{
		FolderBrowserDialog fbd;
		fbd.Description = "Choose old source folder";
		if (fbd.ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			dest = true;
			destPath->Text = fbd.SelectedPath;
		}
	}
	private: System::Void outputButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		FolderBrowserDialog fbd;
		fbd.Description = "Choose output folder";
		if (fbd.ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			out = true;
			output->Text = fbd.SelectedPath;
		}
	}
};
}
