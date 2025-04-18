#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

//
Control^ GetControl(String^ controlName, Form^ form) {
	return form->Controls->Find(controlName, true)[0];
}

// F� st�rsta font-storleken man kan ha i en label eller knapp utan att den sk�r sig
private ref class GetMaxFontSize {
private:
	Form^ form;
	float maxFontSize;

	int textWidth;
	int textHeight;

	void GetStringSize(System::String^ text) {
		// Anv�nd MeasureString f�r att r�kna ut bredden och l�ngden
		System::Drawing::Font^ font = gcnew System::Drawing::Font("Arial", maxFontSize);
		Size size = TextRenderer::MeasureText(text, font);

		// S�tt storleken
		textWidth = static_cast<int>(size.Width);
		textHeight = static_cast<int>(size.Height);
	}

public:
	// Initialization
	GetMaxFontSize(Form^ form) {
		this->form = form;
	}

	// Den functionen som man anv�nder utanf�r
	float Get(int width, int height, String^ text) {
		this->maxFontSize = 1;

		GetStringSize(text);
		while (textWidth < width && textHeight < height) {
			GetStringSize(text);
			maxFontSize += 1;
		}

		return maxFontSize - 4;
	}
};

private ref class PlayerChoiceScreenManager {
private:
	Form^ form;
	GetMaxFontSize^ getMaxFontSize;

	// Alla knappar som variabler
	Button^ buttonPlayerAmountOne;
	Button^ buttonPlayerAmountTwo;
	Button^ buttonPlayerAmountThree;
	Button^ buttonPlayerAmountFour;
	Button^ buttonPlayerAmountFive;

	// Funktionen som kallar allt annat, kallas fr�n public void AlignAll f�r varje knapp
	void Align(Button^ button, double xRelative, double yRelative) {
		SetRelativeButtonPosition(button, xRelative, yRelative);
		SetRelativeButtonSize(button, 0.15, 0.11);
		SetRelativeButtonTextSize(button);
	}

	// S�tt en relativ position (x=0-1, y=0-1)
	void SetRelativeButtonPosition(Button^ button, double xRelative, double yRelative) {
		int xAbsolute = (int)(this->form->ClientSize.Width * xRelative);
		int yAbsolute = (int)(this->form->ClientSize.Height * yRelative);

		// G�r s� den s�tter mitten av knappen d�r och inte h�rnet
		xAbsolute -= button->Width / 2;
		yAbsolute -= button->Height / 2;

		PlaceButton(button, xAbsolute, yAbsolute);
	}

	// �ndra storleken p� en knapp
	void SetRelativeButtonSize(Button^ button, double widthRelative, double heightRelative) {
		int widthAbsolute = (int)(this->form->ClientSize.Width * widthRelative);
		int heightAbsolute = (int)(this->form->ClientSize.Height * heightRelative);

		ResizeButton(button, widthAbsolute, heightAbsolute);
	}

	// G�r s� texten passas bra med h�jden och l�ngden av knappen
	void SetRelativeButtonTextSize(Button^ button) {
		int buttonWidth = button->Width;
		int buttonHeight = button->Height;


		float largestFontSize = this->getMaxFontSize->Get(button->Width, button->Height, button->Text);

		ResizeButtonText(button, largestFontSize);
	}

	// S�tt en knapp vid en viss coordinat
	void PlaceButton(Button^ button, int x, int y) {
		button->Location = System::Drawing::Point(x, y);
	}

	// �ndra storleken p� en knapp
	void ResizeButton(Button^ button, int width, int height) {
		button->Width = width;
		button->Height = height;
	}

	// �ndra storleken 
	void ResizeButtonText(Button^ button, float fontSize) {
		button->Font = gcnew Drawing::Font("Arial", fontSize);
		button->TextAlign = ContentAlignment::MiddleCenter;
	}


public:
	// Initialization
	PlayerChoiceScreenManager(Form^ form) {
		this->form = form;
		this->getMaxFontSize = gcnew GetMaxFontSize(form);

		// Variablar till alla knappar
		array<Control^>^ controls = form->Controls->Find("button_PlayerAmountOne", true);
		if (controls->Length > 0) {
			this->buttonPlayerAmountOne = (Button^)controls[0];
		}

		controls = form->Controls->Find("button_PlayerAmountTwo", true);
		if (controls->Length > 0) {
			this->buttonPlayerAmountTwo = (Button^)controls[0];
		}

		controls = form->Controls->Find("button_PlayerAmountThree", true);
		if (controls->Length > 0) {
			this->buttonPlayerAmountThree = (Button^)controls[0];
		}

		controls = form->Controls->Find("button_PlayerAmountFour", true);
		if (controls->Length > 0) {
			this->buttonPlayerAmountFour = (Button^)controls[0];
		}

		controls = form->Controls->Find("button_PlayerAmountFive", true);
		if (controls->Length > 0) {
			this->buttonPlayerAmountFive = (Button^)controls[0];
		}
	}

	// Funtion som man kallar varje g�ng alla player choice ska s�ttas p� r�tt plats
	void AlignAll() {
		Align(buttonPlayerAmountOne, 0.16, 0.5);
		Align(buttonPlayerAmountTwo, 0.33, 0.5);
		Align(buttonPlayerAmountThree, 0.5, 0.5);
		Align(buttonPlayerAmountFour, 0.66, 0.5);
		Align(buttonPlayerAmountFive, 0.82, 0.5);
	}

	// G�r s� alla knappar visas eller inte visas, beroende p� om denna sk�rm visas
	void SetVisibility(String^ currentScreen) {
		bool value = true;

		if (currentScreen != "playerChoice") { value = false; }

		this->buttonPlayerAmountOne->Visible = value;
		this->buttonPlayerAmountTwo->Visible = value;
		this->buttonPlayerAmountThree->Visible = value;
		this->buttonPlayerAmountFour->Visible = value;
		this->buttonPlayerAmountFive->Visible = value;
	}
};

private ref class PlayerNameChoiceManager {
private:
	Form^ form;

	TextBox^ textBox;
	Button^ button;
	Label^ infoLabel;
	Label^ errorLabel;

	// S�tt TextBoxen d�r man skriver sitt namn p� r�tt st�lle
	void AlignTextBox(TextBox^ textBox) {
		textBox->Width = form->ClientSize.Width / 3;
		textBox->Font = gcnew Font("Arial", (float)(form->ClientSize.Height / 20));

		int width = textBox->Width;
		int height = textBox->Height;

		int x = (form->ClientSize.Width / 2) - (width / 2);
		int y = (form->ClientSize.Height / 2) - (height / 2);

		textBox->Location = System::Drawing::Point(x, y);
	}

	// S�tt confirm-knappen r�tt
	void AlignButton(Button^ button, TextBox^ textBox) {
		button->Font = gcnew Font("Arial", (float)(form->ClientSize.Height / 20));

		int x = (form->ClientSize.Width / 2) - (button->Width / 2);
		int y = (textBox->Height) + (textBox->Top) + (10);

		button->Location = Point(x, y);
	}

	// S�tt labeln d�r det st�r vem som v�ljer namn p� r�tt plats
	void AlignInfoLabel(Label^ label) {
		label->Font = textBox->Font;

		int x = (this->form->Width / 2) - (label->Width / 2);
		int y = (this->textBox->Top) - (label->Height) - 10;

		label->Location = Point(x, y);
	}

	// S�tt labeln som visar om man har skrivit ett ogiltigt namn
	void AlignErrorLabel(Label^ label) {
		label->Font = gcnew Font(this->textBox->Font->FontFamily, this->textBox->Font->Size * (float)(0.8));

		int x = (this->form->Width / 2) + (this->textBox->Width / 2) + 10;
		int y = (this->form->ClientSize.Height / 2) - (label->Height / 2);

		label->Location = Point(x, y);
	}

public:
	PlayerNameChoiceManager(Form^ form) {
		this->form = form;

		array<Control^>^ controls = form->Controls->Find("textBox_Name", true);
		this->textBox = (TextBox^)controls[0];
		
		controls = form->Controls->Find("button_NameConfirm", true);
		this->button = (Button^)controls[0];
		
		controls = form->Controls->Find("label_NameInfo", true);
		this->infoLabel = (Label^)controls[0];
		
		controls = form->Controls->Find("label_NameError", true);
		this->errorLabel = (Label^)controls[0];
	}

	void AlignAll() {
		AlignTextBox(this->textBox);
		AlignButton(this->button, this->textBox);
		AlignInfoLabel(this->infoLabel);
		AlignErrorLabel(this->errorLabel);
	}

	void SetVisibility(String^ currentScreen) {
		bool value = true;

		if (currentScreen != "nameChoice") { value = false; }

		this->textBox->Visible = value;
		this->button->Visible = value;
		this->infoLabel->Visible = value;
		// this->infoLabel->Visible sk�ts av timern
	}
};

private ref class PlayingScreenManager {
private:
	Form^ form;

	GetMaxFontSize^ getMaxFontSize;

	Button^ buttonHit;
	Button^ buttonStand;
	Button^ buttonDoubleDown;
	Button^ buttonSplit;
	Button^ buttonSurrender;

	List<PictureBox^>^ dealerCards;

	void AlignChoiceButtons() {
		// Bredden som alla knappar ska ta upp
		double buttonLayoutWidth = form->ClientSize.Width * 0.65;

		ResizeButtons(100.0); // F�r att f� ett mer exakt v�rde
		// Totala bredden av alla knapparna
		int totalButtonWidth =
			this->buttonHit->Width +
			this->buttonStand->Width +
			this->buttonDoubleDown->Width +
			this->buttonSplit->Width +
			this->buttonSurrender->Width;

		// F� fonten p� alla knappar genom att f� vilken font buttonHit ska ha
		double hitButtonWidthPart = (double)(this->buttonHit->Width) / (double)totalButtonWidth;
		float fontSize = this->getMaxFontSize->Get(hitButtonWidthPart * buttonLayoutWidth, this->form->Height, buttonHit->Text);

		// S�tt allas font size
		ResizeButtons(fontSize);

		// 10px �ver botten
		int y = this->form->ClientSize.Height - 10 - buttonHit->Size.Height;

		// Mellanrum mellan knapparna
		int padding = 10;
		int totalPadding = padding * 4;

		this->buttonHit->Location = Point((this->form->ClientSize.Width - (int)buttonLayoutWidth)/2 - totalPadding, y);
		this->buttonStand->Location = Point(this->buttonHit->Left + this->buttonHit->Width + padding, y);
		this->buttonDoubleDown->Location = Point(this->buttonStand->Left + this->buttonStand->Width + padding, y);
		this->buttonSplit->Location = Point(this->buttonDoubleDown->Left + this->buttonDoubleDown->Width + padding, y);
		this->buttonSurrender->Location = Point(this->buttonSplit->Left + this->buttonSplit->Width + padding, y);
	}

	//
	void ResizeButtons(float size) {
		Font^ font = gcnew Font("Arial", size);

		this->buttonHit->Font = font;
		this->buttonStand->Font = font;
		this->buttonDoubleDown->Font = font;
		this->buttonSplit->Font = font;
		this->buttonSurrender->Font = font;
	}

	//
	void AlignDealerCards(List<PictureBox^>^ list) {
		double maxRelativeHeight = 0.25;
		double maxRelativeWidth = 0.9;
		double widthToHeightRatio = 1.452;

		int topPadding = 10;
		int sidePadding = 10;
		int totalSidePadding = (list->Count - 1) * sidePadding;

		int maxCardWidth = (int)(this->form->ClientSize.Width * maxRelativeWidth + totalSidePadding) / (list->Count + 1);
		int maxCardHeight = (int)(this->form->ClientSize.Height * maxRelativeHeight);

		Drawing::Size cardSize = maxCardHeight >= maxCardWidth / widthToHeightRatio ? Drawing::Size((int)(maxCardWidth / widthToHeightRatio), maxCardWidth) : Drawing::Size(maxCardHeight, (int)(maxCardHeight * widthToHeightRatio));

		// Placera alla kort
		for each (PictureBox^ currentCard in list) {
			int currentCardIndex = list->IndexOf(currentCard);
			int x = 
				this->form->ClientSize.Width/2
				- ((list->Count - 1) * (cardSize.Width + sidePadding))/2
				+ currentCardIndex*(sidePadding + cardSize.Width)
				- cardSize.Width / 2;
			int y = topPadding;
			currentCard->Size = cardSize;
			currentCard->Location = Point(x, y);
		}
	}


public:
	PlayingScreenManager(Form^ form) {
		this->form = form;
		this->getMaxFontSize = gcnew GetMaxFontSize(form);
		this->dealerCards = gcnew List<PictureBox^>(0);

		// H�mta knapparna
		array<Control^>^ controls = form->Controls->Find("button_Hit", true);
		this->buttonHit = (Button^)controls[0];
		controls = form->Controls->Find("button_Stand", true);
		this->buttonStand = (Button^)controls[0];
		controls = form->Controls->Find("button_DoubleDown", true);
		this->buttonDoubleDown = (Button^)controls[0];
		controls = form->Controls->Find("button_Split", true);
		this->buttonSplit = (Button^)controls[0];
		controls = form->Controls->Find("button_Surrender", true);
		this->buttonSurrender = (Button^)controls[0];
	}

	// S�tt knapparna p� r�tt st�lle
	void AlignAll() {
		AlignChoiceButtons();
		AlignDealerCards(this->dealerCards);
	}

	// Visa/d�lj det som ska visar eller inte
	void SetVisibility(String^ screen) {
		int value = true;
		if (screen != "playingScreen") { value = false; }

		this->buttonHit->Visible = value;
		this->buttonStand->Visible = value;
		this->buttonDoubleDown->Visible = value;
		this->buttonSplit->Visible = value;
		this->buttonSurrender->Visible = value;
	}

	// S�tt p� eller st�ng av hit/stand/double down/split/surrender knapparna
	void SetChoiceButtonsStates(bool state) {
		this->buttonHit->Enabled = state;
		this->buttonStand->Enabled = state;
		this->buttonDoubleDown->Enabled = state;
		this->buttonSplit->Enabled = state;
		this->buttonSurrender->Enabled = state;
	}

	// Visa ett till kort hos dealern
	void AddDealerCard(String^ cardName) {
		//
		PictureBox^ newCard = gcnew PictureBox();
		newCard->Image = Image::FromFile("playing cards/" + cardName + ".png");
		newCard->SizeMode = PictureBoxSizeMode::Zoom;
		this->dealerCards->Add(newCard);
		this->form->Controls->Add(newCard);

		AlignDealerCards(this->dealerCards);
	}
};

private ref class BettingScreenManager {
private:
	Form^ form;

	GetMaxFontSize^ getMaxFontSize;

	NumericUpDown^ numericUpDown;
	TrackBar^ trackBar;
	Label^ label;
	Button^ button;

	// S�tt trackbaren p� r�tt st�lle
	void AlignTrackBar() {
		ResizeTrackBar();

		int x = this->form->ClientSize.Width/2 - this->trackBar->Size.Width / 2;
		int y = (this->form->ClientSize.Height / 2) - this->trackBar->Size.Height / 2;

		this->trackBar->Location = Point(x, y);
	}

	// S�tt storleken 
	void ResizeTrackBar() {
		this->trackBar->Width = this->form->ClientSize.Width*0.65;
	}

	// 
	void AlignNumericUpDown() {
		ResizeNumericUpDown();

		int x = this->trackBar->Left + this->trackBar->Size.Width + 10;
		int y = this->trackBar->Top;

		this->numericUpDown->Location = Point(x, y);
	}

	// 
	void ResizeNumericUpDown() {
		numericUpDown->Height = trackBar->Size.Height;
	}

	//
	void AlignLabel() {
		ResizeLabel();

		int x = this->form->Size.Width / 2 - label->Size.Width / 2;
		int y = this->trackBar->Top - this->label->Height;

		this->label->Location = Point(x, y);
	}

	//
	void ResizeLabel() {
		int width = this->form->ClientSize.Width * 0.28;
		int height = this->form->ClientSize.Height * 0.10;

		float fontSize = this->getMaxFontSize->Get(width, height, this->label->Text);

		this->label->Font = gcnew Font("Arial", fontSize);
	}

	void AlignButton() {
		ResizeButton();

		int x = this->form->ClientSize.Width / 2 - this->button->Width / 2;
		int y = this->trackBar->Top + this->trackBar->Height + 10;

		this->button->Location = Point(x, y);
	}

	void ResizeButton() {
		int width = this->form->ClientSize.Width * 0.15;
		int height = this->form->ClientSize.Height * 0.08;

		float fontSize = this->getMaxFontSize->Get(width, height, this->button->Text);

		this->button->Font = gcnew Font("Arial", fontSize);
	}


public:
	BettingScreenManager(Form^ form) {
		this->form = form;
		this->getMaxFontSize = gcnew GetMaxFontSize(form);

		array<Control^>^ controls = form->Controls->Find("numericUpDown_Bet", true);
		this->numericUpDown = (NumericUpDown^)controls[0];
		controls = form->Controls->Find("trackBar_Bet", true);
		this->trackBar = (TrackBar^)controls[0];
		controls = form->Controls->Find("label_BetName", true);
		this->label = (Label^)controls[0];
		controls = form->Controls->Find("button_ConfirmBet", true);
		this->button = (Button^)controls[0];
	}

	// S�tt allt p� r�tt plats
	void AlignAll() {
		AlignTrackBar();
		AlignNumericUpDown();
		AlignLabel();
		AlignButton();
	}

	// Visa eller d�lj
	void SetVisibility(String^ screen) {
		bool value = true;

		if (screen != "bettingScreen") { value = false; }

		this->numericUpDown->Visible = value;
		this->trackBar->Visible = value;
		this->label->Visible = value;
		this->button->Visible = value;
	}

	//
	void SetBetMax(int value) {
		this->numericUpDown->Maximum = value;
		this->trackBar->Maximum = value;

		this->numericUpDown->Value = 0;
		this->trackBar->Value = 0;
	}
};

private ref class ShowCardsManager {
private:
	Form^ form;
	String^ currentScreen;

	int playerAmount; // Hur m�nga spelare som finns i spelet
	int borderPadding; // Hur m�nga pixlar det ska vara mellan korten och toppen/botten
	int cardPadding; // Hur m�nga pixlar det ska vara mellan korten

	Button^ button; // Continue-knappen

	List<PictureBox^>^ cardPictureBoxes;
	List<Player^>^ players;

	// 
	void AlignCards() {
		String^ orientation = this->form->ClientSize.Width >= this->form->ClientSize.Height ? "h" : "v"; // Om f�nstret �r horisontalt eller vertikalt (h = horisontalt, v = vertikalt)
		Size size = ResizeCards(orientation); // S�tt och f� storleken p� korten
		int x = 0, y = 0;
		
		// S�tt den gemensamma coordinaten f�r alla kort 
		if (orientation == "h") {
			y = (this->form->ClientSize.Height / 2) - (size.Height / 2);
		} else {
			x = (this->form->ClientSize.Width / 2) - (size.Width / 2);
		}
	
		for each (PictureBox ^ currentCard in this->cardPictureBoxes) {
			int cardNumber = this->cardPictureBoxes->IndexOf(currentCard) + 1;
			int cardHeight = currentCard->Height;
			int cardWidth = currentCard->Width;
			int totalWidth = this->playerAmount * cardWidth + this->cardPadding * (this->playerAmount - 1);
			int totalHeight = this->playerAmount * cardHeight + this->cardPadding * (this->playerAmount - 1);

			if (orientation == "h") {
				x = (cardNumber - 1) * cardWidth + this->cardPadding * (cardNumber - 1) + (this->form->ClientSize.Width/2 - totalWidth/2);
			} else {
				y = (cardNumber - 1) * cardHeight + this->cardPadding * (cardNumber - 1) + (this->form->ClientSize.Height / 2 - totalHeight / 2);
			}

			currentCard->Location = Point(x, y);
		}
	}

	// 
	Drawing::Size ResizeCards(String^ orientation) {
		double widthToHeightRatio = 1.452;

		int cardWidths, cardHeights;

		if (orientation == "h") {
			cardWidths = (this->form->ClientSize.Width - this->borderPadding * 2) / this->playerAmount - (this->cardPadding / this->playerAmount) * (this->playerAmount - 1);
			cardHeights = this->form->ClientSize.Height * 0.5;
		} else {
			cardWidths = this->form->ClientSize.Width * 0.35;
			cardHeights = (this->form->ClientSize.Height - this->borderPadding * 2) / this->playerAmount - (this->cardPadding / this->playerAmount) * (this->playerAmount - 1);
		}

		// Samma just nu men kanske ska �ndra i framtiden
		Size size = cardHeights <= cardWidths * widthToHeightRatio ? Size(cardHeights / widthToHeightRatio, cardHeights) : Size(cardWidths, cardWidths * widthToHeightRatio);
	
		// S�tt storleken p� alla
		for each (PictureBox ^ currentCard in this->cardPictureBoxes) {
			currentCard->Size = size;
		}

		return size;
	}

public:
	ShowCardsManager(Form^ form) {
		this->form = form;
		this->currentScreen = currentScreen;

		this->borderPadding = form->ClientSize.Height * 0.05; // Hur m�nga pixlar det ska vara mellan korten och toppen/botten
		this->cardPadding = 15; // Hur m�nga pixlar det ska vara mellan korten

		this->button = (Button^)GetControl("button_ShowCardsContinue", form);

		this->cardPictureBoxes = gcnew List<PictureBox^>(0);
		this->players = gcnew List<Player^>(0);
	}

	// 
	void AlignAll() {
		if (this->cardPictureBoxes->Count > 0) {
			AlignCards();
		}
	}

	// 
	void SetVisibility(String^ currentScreen) {
		bool value = true;

		if (currentScreen != "showCardsScreen") {
			value = false;
		}

		// ALLA CONTROLS
		this->button->Visible = value;
	}

	// 
	void ShowCards(List<Player^>^ players, List<String^>^ cards) {
		this->playerAmount = players->Count;

		// Skapa PictureBoxes till alla kort
		for (int i = 0; i < this->playerAmount; i++) {
			PictureBox^ newCard = gcnew PictureBox();
			newCard->Image = Image::FromFile("playing cards/" + cards[i] + ".png");
			newCard->SizeMode = PictureBoxSizeMode::Zoom;
			this->cardPictureBoxes->Add(newCard);
			this->form->Controls->Add(newCard);
		}

		AlignCards();
	}
};

public ref class WindowManager {
private:
	Form^ form;
	String^ currentScreen;

	PlayerChoiceScreenManager^ playerChoiceScreenManager;
	PlayerNameChoiceManager^ playerNameChoiceManager;
	PlayingScreenManager^ playingScreenManager;
	BettingScreenManager^ bettingScreenManager;
	ShowCardsManager^ showCardsManager;


public:
	WindowManager(Form^ form) {
		this->form = form;
		this->playerChoiceScreenManager = gcnew PlayerChoiceScreenManager(form);
		this->playerNameChoiceManager = gcnew PlayerNameChoiceManager(form);
		this->playingScreenManager = gcnew PlayingScreenManager(form);
		this->bettingScreenManager = gcnew BettingScreenManager(form);
		this->showCardsManager = gcnew ShowCardsManager(form);

		this->currentScreen = "playerChoice";
	}

	//
	void AlignAll() {
		if (this->form->WindowState == FormWindowState::Minimized) { return; }
		playerChoiceScreenManager->AlignAll();
		playerNameChoiceManager->AlignAll();
		playingScreenManager->AlignAll();
		bettingScreenManager->AlignAll();
		showCardsManager->AlignAll();
	}

	//
	void SetAllVisibility() {
		playerChoiceScreenManager->SetVisibility(this->currentScreen);
		playerNameChoiceManager->SetVisibility(this->currentScreen);
		playingScreenManager->SetVisibility(this->currentScreen);
		bettingScreenManager->SetVisibility(this->currentScreen);
		showCardsManager->SetVisibility(this->currentScreen);
	}

	// 
	void SetPlayingChoiceButtonsStates(bool state) {
		this->playingScreenManager->SetChoiceButtonsStates(state);
	}

	// S�tt den aktiva sk�rmen
	void SetScreen(String^ screen) {
		this->currentScreen = screen;
	}

	//
	void AddDealerCard(String^ cardName) {
		playingScreenManager->AddDealerCard(cardName);
	}

	//
	void SetBetMax(int value) {
		this->bettingScreenManager->SetBetMax(value);
	}

	// 
	void SetBetName(String^ name) {
		Label^ label = (Label^)GetControl("label_BetName", this->form);

		label->Text = name + "'s bet:";
	}

	//
	void ShowCards(List<Player^>^ players, List<String^>^ cards) {
		this->showCardsManager->ShowCards(players, cards);
	}
};