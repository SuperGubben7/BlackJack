#pragma once

#include "windowManager.h"
#include <algorithm>
#include <random>
#include <ctime>

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Collections::Generic;


ref class Game {
private:
	List<String^>^ deck;
	List<String^>^ deckUsed;
	List<Player^>^ players;

	Form^ form; 
	WindowManager^ windowManager; 
	Timer^ timerNameError; // Måste importeras här för att den inte är en control

	int turnPlayerNumber;

	// 
	Control^ getControl(String^ controlName) {
		return this->form->Controls->Find(controlName, true)[0];
	}

public:
	Game(int playerAmount, Form^ form, WindowManager^ windowManager, Timer^ timerNameError) {
		this->form = form;
		this->windowManager = windowManager;
		this->timerNameError = timerNameError;

		array<String^>^ cardArray = gcnew array<String^> {
			"2_of_hearts", "2_of_diamonds", "2_of_spades", "2_of_clubs",
			"3_of_hearts", "3_of_diamonds", "3_of_spades", "3_of_clubs",
			"4_of_hearts", "4_of_diamonds", "4_of_spades", "4_of_clubs",
			"5_of_hearts", "5_of_diamonds", "5_of_spades", "5_of_clubs",
			"6_of_hearts", "6_of_diamonds", "6_of_spades", "6_of_clubs",
			"7_of_hearts", "7_of_diamonds", "7_of_spades", "7_of_clubs",
			"8_of_hearts", "8_of_diamonds", "8_of_spades", "8_of_clubs",
			"9_of_hearts", "9_of_diamonds", "9_of_spades", "9_of_clubs",
			"10_of_hearts", "10_of_diamonds", "10_of_spades", "10_of_clubs",
			"jack_of_hearts", "jack_of_diamonds", "jack_of_spades", "jack_of_clubs",
			"queen_of_hearts", "queen_of_diamonds", "queen_of_spades", "queen_of_clubs",
			"king_of_hearts", "king_of_diamonds", "king_of_spades", "king_of_clubs",
			"ace_of_hearts", "ace_of_diamonds", "ace_of_spades", "ace_of_clubs"
		};

		this->deck = gcnew List<String^>(cardArray);
		RandomizeDeck();

		this->deckUsed = gcnew List<String^>(0);
		this->players = gcnew List<Player^>(0);

		this->AddPlayers(playerAmount);

		this->turnPlayerNumber = 1;
	}

	// 
	void ManageWindow() {
		if (windowManager != nullptr) {
			this->windowManager->AlignAll();
			this->windowManager->SetAllVisibility();
		}
	}

	//
	void RandomizeDeck() {
		Random^ rng = gcnew Random();

		for (int i = this->deck->Count - 1; i > 0; i--) {
			int j = rng->Next(i + 1); // random index between 0 and i

			// Swap players[i] and players[j]
			String^ temp = this->deck[i];
			this->deck[i] = this->deck[j];
			this->deck[j] = temp;
		}
	}

	//
	int GetCardValue(String^ card, int playerValue) {	
		int value = 1;

		if (card->StartsWith("2_")) {
			value = 2;
		}
		else if (card->StartsWith("3_")) {
			value = 3;
		}
		else if (card->StartsWith("4_")) {
			value = 4;
		}
		else if (card->StartsWith("5_")) {
			value = 5;
		}
		else if (card->StartsWith("6_")) {
			value = 6;
		}
		else if (card->StartsWith("7_")) {
			value = 7;
		}
		else if (card->StartsWith("8_")) {
			value = 8;
		}
		else if (card->StartsWith("9_")) {
			value = 9;
		}
		else if (card->StartsWith("10_")) {
			value = 10;
		}
		else if (card->StartsWith("jack_")) {
			value = 10;
		}
		else if (card->StartsWith("queen_")) {
			value = 10;
		}
		else if (card->StartsWith("king_")) {
			value = 10;
		}

		// Om kortet är ace, gör 


		return value;
	}

	// Lägg till ett visst antal spelare
	void AddPlayers(int amount) {
		for (int i = 0; i < amount; i++) {
			Player^ player = gcnew Player(i+1);
			this->players->Add(player);
		}
	}

	//
	void SetPlayerName(String^ name) {
		Player^ player = this->players[turnPlayerNumber-1];

		player->SetName(name);
	}
	// Sätt allas bals, används i början av spelet
	void SetAllBals(int startBal) {
		for each(Player^ player in this->players) {
			player->SetBal(startBal);
		}
	}

	// Ge vilket nummer det är på den som spelar
	int GetTurnPlayerNumber() { return this->turnPlayerNumber; }

	// 
	List<Player^>^ GetPlayerList() { return this->players; }

	// Nästa spelares tur
	void NextTurn(bool gameActive) {
		// Om den sista spelaren spelade precis ska turnPlayerNumber bli 1, annars blir den 1 högre
		if (turnPlayerNumber >= this->players->Count) { turnPlayerNumber = 1; }
		else { turnPlayerNumber++; }

		// Börja inte ny runda om spelet inte har börjat än (om man bara väljer namn) 
		if (gameActive == false) { return; }


	}

	//
	String^ GetCard() {
		String^ card = this->deck[0];
		this->deck->Remove(card);
		this->deckUsed->Add(card);

		return card;
	}

	// Stand
	void Stand() {
	
	}

	// Hit
	void Hit() {
	
	}

	// Double Down
	void DoubleDown() {
		
	}

	// Split
	void Split() {
	
	}

	// Surrender
	void Surrender() {
	
	}



	// Få allas namn
	void GetNames() {
		TextBox^ textBox = (TextBox^)this->getControl("textBox_Name");

		this->windowManager->SetScreen("nameChoice");
		ManageWindow();
		textBox->Focus();
	}

	// Sätt en spelares namn
	void SetName() {
		// Få alla controls
		TextBox^ textBox = (TextBox^)this->getControl("textBox_Name");
		Label^ labelNameInfo = (Label^)this->getControl("label_NameInfo");
		Label^ labelNameError = (Label^)this->getControl("label_NameError");

		bool finished = false;

		// Om man inte har skrivit in ett namn (lägg till fler felaktiga namn senare)
		if (String::IsNullOrWhiteSpace(textBox->Text)) {
			labelNameError->Text = "Det kan du ju inte heta";
			labelNameError->Visible = true;
			this->timerNameError->Interval = 3000;
			this->timerNameError->Start();
			return;
		}
		if (this->GetTurnPlayerNumber() >= this->GetPlayerList()->Count) {
			finished = true;
		}

		// Sätt namnet och gör så nästa spelare kan välja
		this->SetPlayerName(textBox->Text);
		textBox->Clear();
		this->NextTurn(false);
		labelNameInfo->Text = "Spelare " + this->GetTurnPlayerNumber() + "'s namn:";
		textBox->Focus();

		// Uppdatera fönstret
		this->ManageWindow();

		// Fortsätt om alla har valt sina namn
		if (finished) {
			this->GameStartRound();
		}
	}


	
	// Få vad alla bettar innan varje runda
	void GetBets() {
		Label^ label = (Label^)this->form->Controls->Find("label_BetName", true)[0];

		Player^ player = this->GetPlayerList()[this->GetTurnPlayerNumber() - 1];
		label->Text = player->GetName() + "'s bet:";
		this->windowManager->SetScreen("bettingScreen");
		SetBetMax();
		this->ManageWindow();
	}

	// Sätt en spelares bet
	void SetBet() {
		NumericUpDown^ numericUpDown = (NumericUpDown^)this->form->Controls->Find("numericUpDown_Bet", true)[0];

		bool finished = false; // Blir true om alla har valt sina bets

		int playerNumber = this->GetTurnPlayerNumber();
		Player^ player = this->GetPlayerList()[playerNumber - 1];

		// 
		if (numericUpDown->Value <= 0) {
			// GRRRR
			return;
		}
		if (this->GetTurnPlayerNumber() >= this->GetPlayerList()->Count) {
			finished = true;
		}

		player->SetBet((int)numericUpDown->Value);
		this->NextTurn(false);

		if(finished) {
			this->GameShowAllCards();

			return;
		}

		// Om någon mer ska betta:
		Player^ nextPlayer = this->GetPlayerList()[playerNumber]; // playerNumber istället för playerNumber - 1 (kommer aldrig vara out of range for att den kollar det innan)

		this->windowManager->SetBetName(nextPlayer->GetName());
		this->SetBetMax();

		this->ManageWindow();
	}

	// Sätt hur mycket en spelare kan betta
	void SetBetMax() {
		int playerNumber = this->GetTurnPlayerNumber();
		Player^ player = this->GetPlayerList()[playerNumber - 1];
		int value = player->GetBal();

		windowManager->SetBetMax(value);
	}
	
	// ------------------------------------------- GAME LOGIC ------------------------------------------- //
	

	// Starta ett spel, körs bara 1 gång
	void GameStart(int startBal) {
		this->SetAllBals(startBal);

		this->GetNames();
	}

	// Starta en runda, körs många gånger
	void GameStartRound() {
		GetBets();
		this->ManageWindow();
	}

	// Visa allas kort
	void GameShowAllCards() {
		List<String^>^ cards = gcnew List<String^>(0);

		for each (Player ^ currentPlayer in this->players) {
			String^ card = this->GetCard();
			cards->Add(card);
			currentPlayer->AddCard(card);
		}

		this->windowManager->ShowCards(this->players, cards);
		this->windowManager->SetScreen("showCards");
		this->ManageWindow();
	}

	// Fortsätt rundan efter alla har valt sina bets
	void GameContinueRound() {
		this->windowManager->SetScreen("playingScreen");
		this->ManageWindow();

	}


};