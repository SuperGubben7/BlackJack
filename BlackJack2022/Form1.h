#pragma once
#include "player.h"
#include "game.h"
#include "windowManager.h"
#include <string>

// 1: Man väljer hur många spelare ska vara med (1-5)
// 2: Alla väljer sina namn (om någon väljer samma namn som en annan får den välja nytt namn)
// 3: 
//
//
//
//
//
//
//
//
//
//
//
//


namespace BlackJack {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class Form1 : public System::Windows::Forms::Form
	{
	public: System::Windows::Forms::Timer^ timer_NameError;

	private: System::Windows::Forms::Button^ button_Hit;
	private: System::Windows::Forms::Button^ button_Stand;
	private: System::Windows::Forms::Button^ button_DoubleDown;
	private: System::Windows::Forms::Button^ button_Split;
	private: System::Windows::Forms::Button^ button_Surrender;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::TrackBar^ trackBar_Bet;
	private: System::Windows::Forms::NumericUpDown^ numericUpDown_Bet;
	private: System::Windows::Forms::Label^ label_BetName;
	private: System::Windows::Forms::Button^ button_ConfirmBet;

	private:
		WindowManager^ windowManager;
	private: System::Windows::Forms::Button^ button_ShowCardsContinue;
		   Game^ game;

	public:
		Form1(void)
		{
			InitializeComponent();

			if (System::ComponentModel::LicenseManager::UsageMode != System::ComponentModel::LicenseUsageMode::Designtime) {
				this->windowManager = gcnew WindowManager(this);
				this->ManageWindow();
			}
		}




		// ------------------------------ ↓ Funktioner ↓ ------------------------------ // 

		// Funktion som kallar allt från windowManager som ska kallas vid varje uppdatering
		void ManageWindow() {
			if (windowManager != nullptr) {
				this->windowManager->AlignAll();
				this->windowManager->SetAllVisibility();
			}
		}

		// 
		void CreateGame(int playerAmount) {
			this->game = gcnew Game(playerAmount, this, windowManager, timer_NameError);

			this->game->GameStart(5000);
		}

		// 
		Control^ GetControl(String^ controlName) {
			return this->Controls->Find(controlName, true)[0];
		}

		// ------------------------------ ↑ Funktioner ↑ ------------------------------ //

	protected: ~Form1() { if (components) { delete components; } }
	private: System::Windows::Forms::Button^ button_PlayerAmountOne;
	private: System::Windows::Forms::Button^ button_PlayerAmountTwo;
	private: System::Windows::Forms::Button^ button_PlayerAmountThree;
	private: System::Windows::Forms::Button^ button_PlayerAmountFour;
	private: System::Windows::Forms::Button^ button_PlayerAmountFive;
	private: System::Windows::Forms::TextBox^ textBox_Name;
	private: System::Windows::Forms::Label^ label_NameInfo;
	private: System::Windows::Forms::Button^ button_NameConfirm;
	private: System::Windows::Forms::Label^ label_NameError;
	private: System::ComponentModel::IContainer^ components;
	protected:





	protected:

	protected:




#pragma region Windows Form Designer generated code
		   void InitializeComponent(void)
		   {
			   this->components = (gcnew System::ComponentModel::Container());
			   this->button_PlayerAmountOne = (gcnew System::Windows::Forms::Button());
			   this->button_PlayerAmountTwo = (gcnew System::Windows::Forms::Button());
			   this->button_PlayerAmountThree = (gcnew System::Windows::Forms::Button());
			   this->button_PlayerAmountFour = (gcnew System::Windows::Forms::Button());
			   this->button_PlayerAmountFive = (gcnew System::Windows::Forms::Button());
			   this->textBox_Name = (gcnew System::Windows::Forms::TextBox());
			   this->label_NameInfo = (gcnew System::Windows::Forms::Label());
			   this->button_NameConfirm = (gcnew System::Windows::Forms::Button());
			   this->label_NameError = (gcnew System::Windows::Forms::Label());
			   this->timer_NameError = (gcnew System::Windows::Forms::Timer(this->components));
			   this->button_Hit = (gcnew System::Windows::Forms::Button());
			   this->button_Stand = (gcnew System::Windows::Forms::Button());
			   this->button_DoubleDown = (gcnew System::Windows::Forms::Button());
			   this->button_Split = (gcnew System::Windows::Forms::Button());
			   this->button_Surrender = (gcnew System::Windows::Forms::Button());
			   this->button1 = (gcnew System::Windows::Forms::Button());
			   this->trackBar_Bet = (gcnew System::Windows::Forms::TrackBar());
			   this->numericUpDown_Bet = (gcnew System::Windows::Forms::NumericUpDown());
			   this->label_BetName = (gcnew System::Windows::Forms::Label());
			   this->button_ConfirmBet = (gcnew System::Windows::Forms::Button());
			   this->button_ShowCardsContinue = (gcnew System::Windows::Forms::Button());
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar_Bet))->BeginInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown_Bet))->BeginInit();
			   this->SuspendLayout();
			   // 
			   // button_PlayerAmountOne
			   // 
			   this->button_PlayerAmountOne->Location = System::Drawing::Point(0, 0);
			   this->button_PlayerAmountOne->Name = L"button_PlayerAmountOne";
			   this->button_PlayerAmountOne->Size = System::Drawing::Size(80, 50);
			   this->button_PlayerAmountOne->TabIndex = 0;
			   this->button_PlayerAmountOne->Text = L"1 Spelare";
			   this->button_PlayerAmountOne->UseVisualStyleBackColor = true;
			   this->button_PlayerAmountOne->Click += gcnew System::EventHandler(this, &Form1::button_PlayerAmountOne_Click);
			   // 
			   // button_PlayerAmountTwo
			   // 
			   this->button_PlayerAmountTwo->Location = System::Drawing::Point(29, -1);
			   this->button_PlayerAmountTwo->Name = L"button_PlayerAmountTwo";
			   this->button_PlayerAmountTwo->Size = System::Drawing::Size(80, 50);
			   this->button_PlayerAmountTwo->TabIndex = 1;
			   this->button_PlayerAmountTwo->Text = L"2 Spelare";
			   this->button_PlayerAmountTwo->UseVisualStyleBackColor = true;
			   this->button_PlayerAmountTwo->Click += gcnew System::EventHandler(this, &Form1::button_PlayerAmountTwo_Click);
			   // 
			   // button_PlayerAmountThree
			   // 
			   this->button_PlayerAmountThree->Location = System::Drawing::Point(62, -1);
			   this->button_PlayerAmountThree->Name = L"button_PlayerAmountThree";
			   this->button_PlayerAmountThree->Size = System::Drawing::Size(80, 50);
			   this->button_PlayerAmountThree->TabIndex = 2;
			   this->button_PlayerAmountThree->Text = L"3 Spelare";
			   this->button_PlayerAmountThree->UseVisualStyleBackColor = true;
			   this->button_PlayerAmountThree->Click += gcnew System::EventHandler(this, &Form1::button_PlayerAmountThree_Click);
			   // 
			   // button_PlayerAmountFour
			   // 
			   this->button_PlayerAmountFour->Location = System::Drawing::Point(97, -1);
			   this->button_PlayerAmountFour->Name = L"button_PlayerAmountFour";
			   this->button_PlayerAmountFour->Size = System::Drawing::Size(80, 50);
			   this->button_PlayerAmountFour->TabIndex = 3;
			   this->button_PlayerAmountFour->Text = L"4 Spelare";
			   this->button_PlayerAmountFour->UseVisualStyleBackColor = true;
			   this->button_PlayerAmountFour->Click += gcnew System::EventHandler(this, &Form1::button_PlayerAmountFour_Click);
			   // 
			   // button_PlayerAmountFive
			   // 
			   this->button_PlayerAmountFive->Location = System::Drawing::Point(130, -1);
			   this->button_PlayerAmountFive->Name = L"button_PlayerAmountFive";
			   this->button_PlayerAmountFive->Size = System::Drawing::Size(80, 50);
			   this->button_PlayerAmountFive->TabIndex = 4;
			   this->button_PlayerAmountFive->Text = L"5 Spelare";
			   this->button_PlayerAmountFive->UseVisualStyleBackColor = true;
			   this->button_PlayerAmountFive->Click += gcnew System::EventHandler(this, &Form1::button_PlayerAmountFive_Click);
			   // 
			   // textBox_Name
			   // 
			   this->textBox_Name->Location = System::Drawing::Point(0, 55);
			   this->textBox_Name->Name = L"textBox_Name";
			   this->textBox_Name->Size = System::Drawing::Size(111, 20);
			   this->textBox_Name->TabIndex = 5;
			   this->textBox_Name->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			   // 
			   // label_NameInfo
			   // 
			   this->label_NameInfo->AutoSize = true;
			   this->label_NameInfo->Location = System::Drawing::Point(149, 59);
			   this->label_NameInfo->Name = L"label_NameInfo";
			   this->label_NameInfo->Size = System::Drawing::Size(91, 13);
			   this->label_NameInfo->TabIndex = 6;
			   this->label_NameInfo->Text = L"Spelare 1\'s namn:";
			   this->label_NameInfo->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			   this->label_NameInfo->Visible = false;
			   // 
			   // button_NameConfirm
			   // 
			   this->button_NameConfirm->AutoSize = true;
			   this->button_NameConfirm->Location = System::Drawing::Point(87, 53);
			   this->button_NameConfirm->Name = L"button_NameConfirm";
			   this->button_NameConfirm->Size = System::Drawing::Size(75, 23);
			   this->button_NameConfirm->TabIndex = 7;
			   this->button_NameConfirm->Text = L"Confirm";
			   this->button_NameConfirm->UseVisualStyleBackColor = true;
			   this->button_NameConfirm->Click += gcnew System::EventHandler(this, &Form1::button_NameConfirm_Click);
			   // 
			   // label_NameError
			   // 
			   this->label_NameError->AutoSize = true;
			   this->label_NameError->ForeColor = System::Drawing::Color::Red;
			   this->label_NameError->Location = System::Drawing::Point(218, 59);
			   this->label_NameError->Name = L"label_NameError";
			   this->label_NameError->Size = System::Drawing::Size(86, 13);
			   this->label_NameError->TabIndex = 8;
			   this->label_NameError->Text = L"error placeholder";
			   this->label_NameError->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			   this->label_NameError->Visible = false;
			   // 
			   // timer_NameError
			   // 
			   this->timer_NameError->Interval = 3000;
			   this->timer_NameError->Tick += gcnew System::EventHandler(this, &Form1::timer_NameError_Tick);
			   // 
			   // button_Hit
			   // 
			   this->button_Hit->AutoSize = true;
			   this->button_Hit->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			   this->button_Hit->Enabled = false;
			   this->button_Hit->Location = System::Drawing::Point(9, 90);
			   this->button_Hit->Margin = System::Windows::Forms::Padding(2);
			   this->button_Hit->Name = L"button_Hit";
			   this->button_Hit->Size = System::Drawing::Size(35, 23);
			   this->button_Hit->TabIndex = 9;
			   this->button_Hit->Text = L"HIT";
			   this->button_Hit->UseVisualStyleBackColor = true;
			   // 
			   // button_Stand
			   // 
			   this->button_Stand->AutoSize = true;
			   this->button_Stand->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			   this->button_Stand->Enabled = false;
			   this->button_Stand->Location = System::Drawing::Point(31, 90);
			   this->button_Stand->Margin = System::Windows::Forms::Padding(2);
			   this->button_Stand->Name = L"button_Stand";
			   this->button_Stand->Size = System::Drawing::Size(54, 23);
			   this->button_Stand->TabIndex = 10;
			   this->button_Stand->Text = L"STAND";
			   this->button_Stand->UseVisualStyleBackColor = true;
			   // 
			   // button_DoubleDown
			   // 
			   this->button_DoubleDown->AutoSize = true;
			   this->button_DoubleDown->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			   this->button_DoubleDown->Enabled = false;
			   this->button_DoubleDown->Location = System::Drawing::Point(69, 90);
			   this->button_DoubleDown->Margin = System::Windows::Forms::Padding(2);
			   this->button_DoubleDown->Name = L"button_DoubleDown";
			   this->button_DoubleDown->Size = System::Drawing::Size(99, 23);
			   this->button_DoubleDown->TabIndex = 11;
			   this->button_DoubleDown->Text = L"DOUBLE DOWN";
			   this->button_DoubleDown->UseVisualStyleBackColor = true;
			   // 
			   // button_Split
			   // 
			   this->button_Split->AutoSize = true;
			   this->button_Split->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			   this->button_Split->Enabled = false;
			   this->button_Split->Location = System::Drawing::Point(144, 90);
			   this->button_Split->Margin = System::Windows::Forms::Padding(2);
			   this->button_Split->Name = L"button_Split";
			   this->button_Split->Size = System::Drawing::Size(47, 23);
			   this->button_Split->TabIndex = 12;
			   this->button_Split->Text = L"SPLIT";
			   this->button_Split->UseVisualStyleBackColor = true;
			   // 
			   // button_Surrender
			   // 
			   this->button_Surrender->AutoSize = true;
			   this->button_Surrender->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			   this->button_Surrender->Enabled = false;
			   this->button_Surrender->Location = System::Drawing::Point(174, 90);
			   this->button_Surrender->Margin = System::Windows::Forms::Padding(2);
			   this->button_Surrender->Name = L"button_Surrender";
			   this->button_Surrender->Size = System::Drawing::Size(86, 23);
			   this->button_Surrender->TabIndex = 13;
			   this->button_Surrender->Text = L"SURRENDER";
			   this->button_Surrender->UseVisualStyleBackColor = true;
			   // 
			   // button1
			   // 
			   this->button1->Location = System::Drawing::Point(0, 0);
			   this->button1->Margin = System::Windows::Forms::Padding(2);
			   this->button1->Name = L"button1";
			   this->button1->Size = System::Drawing::Size(58, 31);
			   this->button1->TabIndex = 14;
			   this->button1->Text = L"DEBUG";
			   this->button1->UseVisualStyleBackColor = true;
			   this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			   // 
			   // trackBar_Bet
			   // 
			   this->trackBar_Bet->AutoSize = false;
			   this->trackBar_Bet->Location = System::Drawing::Point(9, 132);
			   this->trackBar_Bet->Margin = System::Windows::Forms::Padding(2);
			   this->trackBar_Bet->Maximum = 1000;
			   this->trackBar_Bet->Name = L"trackBar_Bet";
			   this->trackBar_Bet->Size = System::Drawing::Size(166, 23);
			   this->trackBar_Bet->TabIndex = 15;
			   this->trackBar_Bet->Scroll += gcnew System::EventHandler(this, &Form1::trackBar_Bet_Scroll);
			   // 
			   // numericUpDown_Bet
			   // 
			   this->numericUpDown_Bet->Location = System::Drawing::Point(182, 135);
			   this->numericUpDown_Bet->Margin = System::Windows::Forms::Padding(2);
			   this->numericUpDown_Bet->Name = L"numericUpDown_Bet";
			   this->numericUpDown_Bet->Size = System::Drawing::Size(58, 20);
			   this->numericUpDown_Bet->TabIndex = 16;
			   this->numericUpDown_Bet->ValueChanged += gcnew System::EventHandler(this, &Form1::numericUpDown_Bet_ValueChanged);
			   // 
			   // label_BetName
			   // 
			   this->label_BetName->AutoSize = true;
			   this->label_BetName->Location = System::Drawing::Point(256, 137);
			   this->label_BetName->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			   this->label_BetName->Name = L"label_BetName";
			   this->label_BetName->Size = System::Drawing::Size(35, 13);
			   this->label_BetName->TabIndex = 17;
			   this->label_BetName->Text = L"\'s bet:";
			   // 
			   // button_ConfirmBet
			   // 
			   this->button_ConfirmBet->AutoSize = true;
			   this->button_ConfirmBet->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			   this->button_ConfirmBet->Location = System::Drawing::Point(297, 131);
			   this->button_ConfirmBet->Name = L"button_ConfirmBet";
			   this->button_ConfirmBet->Size = System::Drawing::Size(52, 23);
			   this->button_ConfirmBet->TabIndex = 18;
			   this->button_ConfirmBet->Text = L"Confirm";
			   this->button_ConfirmBet->UseVisualStyleBackColor = true;
			   this->button_ConfirmBet->Click += gcnew System::EventHandler(this, &Form1::button_ConfirmBet_Click);
			   // 
			   // button_ShowCardsContinue
			   // 
			   this->button_ShowCardsContinue->Location = System::Drawing::Point(297, 188);
			   this->button_ShowCardsContinue->Name = L"button_ShowCardsContinue";
			   this->button_ShowCardsContinue->Size = System::Drawing::Size(75, 23);
			   this->button_ShowCardsContinue->TabIndex = 19;
			   this->button_ShowCardsContinue->Text = L"Continue";
			   this->button_ShowCardsContinue->UseVisualStyleBackColor = true;
			   // 
			   // Form1
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			   this->ClientSize = System::Drawing::Size(789, 430);
			   this->Controls->Add(this->button_ShowCardsContinue);
			   this->Controls->Add(this->button_ConfirmBet);
			   this->Controls->Add(this->label_BetName);
			   this->Controls->Add(this->numericUpDown_Bet);
			   this->Controls->Add(this->trackBar_Bet);
			   this->Controls->Add(this->button1);
			   this->Controls->Add(this->button_Surrender);
			   this->Controls->Add(this->button_Split);
			   this->Controls->Add(this->button_DoubleDown);
			   this->Controls->Add(this->button_Stand);
			   this->Controls->Add(this->button_Hit);
			   this->Controls->Add(this->button_NameConfirm);
			   this->Controls->Add(this->label_NameInfo);
			   this->Controls->Add(this->textBox_Name);
			   this->Controls->Add(this->button_PlayerAmountFive);
			   this->Controls->Add(this->button_PlayerAmountFour);
			   this->Controls->Add(this->button_PlayerAmountThree);
			   this->Controls->Add(this->button_PlayerAmountTwo);
			   this->Controls->Add(this->button_PlayerAmountOne);
			   this->Controls->Add(this->label_NameError);
			   this->MinimumSize = System::Drawing::Size(805, 469);
			   this->Name = L"Form1";
			   this->Text = L"BlackJack";
			   this->Resize += gcnew System::EventHandler(this, &Form1::Form1_Resize);
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar_Bet))->EndInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown_Bet))->EndInit();
			   this->ResumeLayout(false);
			   this->PerformLayout();

		   }
#pragma endregion


	private: System::Void button_PlayerAmountOne_Click(System::Object^ sender, System::EventArgs^ e) {
		this->CreateGame(1);
	}
	private: System::Void button_PlayerAmountTwo_Click(System::Object^ sender, System::EventArgs^ e) {
		this->CreateGame(2);
	}
	private: System::Void button_PlayerAmountThree_Click(System::Object^ sender, System::EventArgs^ e) {
		this->CreateGame(3);
	}
	private: System::Void button_PlayerAmountFour_Click(System::Object^ sender, System::EventArgs^ e) {
		this->CreateGame(4);
	}
	private: System::Void button_PlayerAmountFive_Click(System::Object^ sender, System::EventArgs^ e) {
		this->CreateGame(5);
	}

	private: System::Void button_NameConfirm_Click(System::Object^ sender, System::EventArgs^ e) {
		this->game->SetName();
	}

	private: System::Void Form1_Resize(System::Object^ sender, System::EventArgs^ e) {
		ManageWindow();
	}

	private: System::Void timer_NameError_Tick(System::Object^ sender, System::EventArgs^ e) {
		this->label_NameError->Text = "";
		this->label_NameError->Visible = false;
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		windowManager->AddDealerCard(game->GetCard());
		ManageWindow();
	}
	private: System::Void trackBar_Bet_Scroll(System::Object^ sender, System::EventArgs^ e) {
		this->numericUpDown_Bet->Value = (Decimal)this->trackBar_Bet->Value;
	}

	private: System::Void numericUpDown_Bet_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
		this->trackBar_Bet->Value = (int)(this->numericUpDown_Bet->Value);
	}

	private: System::Void button_ConfirmBet_Click(System::Object^ sender, System::EventArgs^ e) {
		this->game->SetBet();
	}
};
}