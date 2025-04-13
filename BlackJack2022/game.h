#include "player.h"
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

	int startBal;
	int turnPlayerNumber;

public:
	Game(int playerAmount) {
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

		this->startBal = 5000;


		this->deckUsed = gcnew List<String^>();
		this->players = gcnew List<Player^>();

		this->AddPlayers(playerAmount);

		this->turnPlayerNumber = 1;
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

	// Lägg till ett visst antal spelare
	void AddPlayers(int amount) {
		for (int i = 0; i < amount; i++) {
			Player^ player = gcnew Player(i+1);
			this->players->Add(player);
		}
	}

	//
	void SetName(String^ name) {
		Player^ player = this->players[turnPlayerNumber-1];

		player->SetName(name);
	}

	// Sätt hur mycket pengar man börjar med
	void SetBal(int value) {
		this->startBal = value;
	}

	// Sätt allas bals, används i början av spelet
	void SetAllBals() {
		for each(Player^ player in this->players) {
			player->SetBal(this->startBal);
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
};