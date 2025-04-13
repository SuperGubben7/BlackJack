using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

// Få största font-storleken man kan ha i en label eller knapp utan att den skär sig
private ref class GetMaxFontSize {
private:
	Form^ form;
	Graphics^ graphics;
	float maxFontSize;

	int textWidth;
	int textHeight;

	void GetStringSize(System::String^ text) {
		// Använd MeasureString för att räkna ut bredden och längden
		System::Drawing::Font^ font = gcnew System::Drawing::Font("Arial", maxFontSize);
		SizeF size = this->graphics->MeasureString(text, font);

		// Sätt storleken
		textWidth = static_cast<int>(size.Width);
		textHeight = static_cast<int>(size.Height);
	}

public:
	// Initialization
	GetMaxFontSize(Form^ form) {
		this->form = form;
		this->graphics = form->CreateGraphics();
	}

	// Den functionen som man använder utanför
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

	// Funktionen som kallar allt annat, kallas från public void AlignAll för varje knapp
	void Align(Button^ button, double xRelative, double yRelative) {
		SetRelativeButtonPosition(button, xRelative, yRelative);
		SetRelativeButtonSize(button, 0.15, 0.11);
		SetRelativeButtonTextSize(button);
	}

	// Sätt en relativ position (x=0-1, y=0-1)
	void SetRelativeButtonPosition(Button^ button, double xRelative, double yRelative) {
		int xAbsolute = (int)(this->form->ClientSize.Width * xRelative);
		int yAbsolute = (int)(this->form->ClientSize.Height * yRelative);

		// Gör så den sätter mitten av knappen där och inte hörnet
		xAbsolute -= button->Width / 2;
		yAbsolute -= button->Height / 2;

		PlaceButton(button, xAbsolute, yAbsolute);
	}

	// Ändra storleken på en knapp
	void SetRelativeButtonSize(Button^ button, double widthRelative, double heightRelative) {
		int widthAbsolute = (int)(this->form->ClientSize.Width * widthRelative);
		int heightAbsolute = (int)(this->form->ClientSize.Height * heightRelative);

		ResizeButton(button, widthAbsolute, heightAbsolute);
	}

	// Gör så texten passas bra med höjden och längden av knappen
	void SetRelativeButtonTextSize(Button^ button) {
		int buttonWidth = button->Width;
		int buttonHeight = button->Height;


		float largestFontSize = this->getMaxFontSize->Get(button->Width, button->Height, button->Text);

		ResizeButtonText(button, largestFontSize);
	}

	// Sätt en knapp vid en viss coordinat
	void PlaceButton(Button^ button, int x, int y) {
		button->Location = System::Drawing::Point(x, y);
	}

	// Ändra storleken på en knapp
	void ResizeButton(Button^ button, int width, int height) {
		button->Width = width;
		button->Height = height;
	}

	// Ändra storleken 
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

	// Funtion som man kallar varje gång alla player choice ska sättas på rätt plats
	void AlignAll() {
		Align(buttonPlayerAmountOne, 0.16, 0.5);
		Align(buttonPlayerAmountTwo, 0.33, 0.5);
		Align(buttonPlayerAmountThree, 0.5, 0.5);
		Align(buttonPlayerAmountFour, 0.66, 0.5);
		Align(buttonPlayerAmountFive, 0.82, 0.5);
	}

	// Gör så alla knappar visas eller inte visas, beroende på om denna skärm visas
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

	// Sätt TextBoxen där man skriver sitt namn på rätt ställe
	void AlignTextBox(TextBox^ textBox) {
		textBox->Width = form->ClientSize.Width / 3;
		textBox->Font = gcnew Font("Arial", (float)(form->ClientSize.Height / 20));

		int width = textBox->Width;
		int height = textBox->Height;

		int x = (form->ClientSize.Width / 2) - (width / 2);
		int y = (form->ClientSize.Height / 2) - (height / 2);

		textBox->Location = System::Drawing::Point(x, y);
	}

	// Sätt confirm-knappen rätt
	void AlignButton(Button^ button, TextBox^ textBox) {
		button->Font = gcnew Font("Arial", (float)(form->ClientSize.Height / 20));

		int x = (form->ClientSize.Width / 2) - (button->Width / 2);
		int y = (textBox->Height) + (textBox->Top) + (10);

		button->Location = Point(x, y);
	}

	// Sätt labeln där det står vem som väljer namn på rätt plats
	void AlignInfoLabel(Label^ label) {
		label->Font = textBox->Font;

		int x = (this->form->Width / 2) - (label->Width / 2);
		int y = (this->textBox->Top) - (label->Height) - 10;

		label->Location = Point(x, y);
	}

	// Sätt labeln som visar om man har skrivit ett ogiltigt namn
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
		// this->infoLabel->Visible sköts av timern
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

		ResizeButtons(100.0); // För att få ett mer exakt värde
		// Totala bredden av alla knapparna
		int totalButtonWidth =
			this->buttonHit->Width +
			this->buttonStand->Width +
			this->buttonDoubleDown->Width +
			this->buttonSplit->Width +
			this->buttonSurrender->Width;

		// Få fonten på alla knappar genom att få vilken font buttonHit ska ha
		double hitButtonWidthPart = (double)(this->buttonHit->Width) / (double)totalButtonWidth;
		float fontSize = this->getMaxFontSize->Get(hitButtonWidthPart * buttonLayoutWidth, this->form->Height, buttonHit->Text);

		// Sätt allas font size
		ResizeButtons(fontSize);

		// 10px över botten
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

	void ResizeButtons(float size) {
		Font^ font = gcnew Font("Arial", size);

		this->buttonHit->Font = font;
		this->buttonStand->Font = font;
		this->buttonDoubleDown->Font = font;
		this->buttonSplit->Font = font;
		this->buttonSurrender->Font = font;
	}

	void AlignDealerCards(List<PictureBox^>^ list) {
		double maxRelativeHeight = 0.25;
		double maxRelativeWidth = 0.9;
		double heightToWidthRatio = 1.452;

		int topPadding = 10;
		int sidePadding = 10;
		int totalSidePadding = (list->Count - 1) * sidePadding;

		int maxCardWidth = (int)(this->form->ClientSize.Width * maxRelativeWidth + totalSidePadding) / (list->Count + 1);
		int maxCardHeight = (int)(this->form->ClientSize.Height * maxRelativeHeight);

		Drawing::Size cardSize = maxCardHeight >= maxCardWidth / heightToWidthRatio ? Drawing::Size((int)(maxCardWidth / heightToWidthRatio), maxCardWidth) : Drawing::Size(maxCardHeight, (int)(maxCardHeight * heightToWidthRatio));

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
		this->dealerCards = gcnew List<PictureBox^>();

		// Hämta knapparna
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

	// Sätt knapparna på rätt ställe
	void AlignAll() {
		AlignChoiceButtons();
		AlignDealerCards(this->dealerCards);
	}

	// Visa/dölj det som ska visar eller inte
	void SetVisibility(String^ screen) {
		int value = true;
		if (screen != "playingScreen") { value = false; }

		this->buttonHit->Visible = value;
		this->buttonStand->Visible = value;
		this->buttonDoubleDown->Visible = value;
		this->buttonSplit->Visible = value;
		this->buttonSurrender->Visible = value;
	}

	// Sätt på eller stäng av hit/stand/double down/split/surrender knapparna
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

	// Sätt trackbaren på rätt ställe
	void AlignTrackBar() {
		ResizeTrackBar();

		int x = this->form->ClientSize.Width/2 - this->trackBar->Size.Width / 2;
		int y = (this->form->ClientSize.Height / 2) - this->trackBar->Size.Height / 2;

		this->trackBar->Location = Point(x, y);
	}

	// Sätt storleken 
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


public:
	BettingScreenManager(Form^ form) {
		this->form = form;

		array<Control^>^ controls = form->Controls->Find("numericUpDown_Bet", true);
		this->numericUpDown = (NumericUpDown^)controls[0];
		controls = form->Controls->Find("trackBar_Bet", true);
		this->trackBar = (TrackBar^)controls[0];

	}

	// Sätt allt på rätt plats
	void AlignAll() {
		AlignTrackBar();
		AlignNumericUpDown();
	}

	// Visa eller dölj
	void SetVisibility(String^ screen) {
		bool value = true;

		if (screen != "bettingScreen") { value = false; }

		this->numericUpDown->Visible = value;
		this->trackBar->Visible = value;
	}

	//
	void SetBetMax(int value) {
		this->numericUpDown->Maximum = value;
		this->trackBar->Maximum = value;
	}
};

public ref class WindowManager {
private:
	Form^ form;
	PlayerChoiceScreenManager^ playerChoiceScreenManager;
	PlayerNameChoiceManager^ playerNameChoiceManager;
	PlayingScreenManager^ playingScreenManager;
	BettingScreenManager^ bettingScreenManager;

	String^ currentScreen;

public:
	WindowManager(Form^ form) {
		this->form = form;
		this->playerChoiceScreenManager = gcnew PlayerChoiceScreenManager(form);
		this->playerNameChoiceManager = gcnew PlayerNameChoiceManager(form);
		this->playingScreenManager = gcnew PlayingScreenManager(form);
		this->bettingScreenManager = gcnew BettingScreenManager(form);

		this->currentScreen = "playerChoice";
	}

	void AlignAll() {
		if (this->form->WindowState == FormWindowState::Minimized) { return; }
		playerChoiceScreenManager->AlignAll();
		playerNameChoiceManager->AlignAll();
		playingScreenManager->AlignAll();
		bettingScreenManager->AlignAll();
	}

	void SetAllVisibility() {
		playerChoiceScreenManager->SetVisibility(this->currentScreen);
		playerNameChoiceManager->SetVisibility(this->currentScreen);
		playingScreenManager->SetVisibility(this->currentScreen);
		bettingScreenManager->SetVisibility(this->currentScreen);
	}

	// 
	void SetPlayingChoiceButtonsStates(bool state) {
		this->playingScreenManager->SetChoiceButtonsStates(state);
	}

	// Sätt den aktiva skärmen
	void SetScreen(String^ screen) {
		this->currentScreen = screen;
	}

	void AddDealerCard(String^ cardName) {
		playingScreenManager->AddDealerCard(cardName);
	}

	void SetBetMax(int value) {
		this->bettingScreenManager->SetBetMax(value);
	}
};