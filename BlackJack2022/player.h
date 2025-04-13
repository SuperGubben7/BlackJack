using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Collections::Generic;


ref class Player {
private:
	String^ name; // Spelarens namn
	int playerNumber; // Numret på spelaren (1/2/3/4/5)
	int bal; // Hur mycket pengar spelaren har (balance)
	int refills; // Hur många gånger spelaren har behövt sätta in mer pengar

public:
	Player(int playerNumber) {
		this->playerNumber = playerNumber;
	}

	// Sätt spelarens namn
	void SetName(String^ name) {
		this->name = name;
	}

	String^ GetName() {
		return this->name;
	}

	// Sätt spelarens bal
	void SetBal(int bal) {
		this->bal = bal;
	}

	// 
	int GetBal() {
		return this->bal;
	}

	// Refilla
	void Refill(int bal) {
		this->bal = bal;
		this->refills++;
	}
};