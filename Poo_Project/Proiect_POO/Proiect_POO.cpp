#include <iostream>
#include <map>
#include <string>
using namespace std;

class Produs {
public:
	int ID;
	string nume;
	int cantitate;
	double pret;
	Produs() : ID(0), nume(""), cantitate(0), pret(0.0) {}
	Produs(int i, string n, int c, double p) : ID(i), nume(n), cantitate(c), pret(p) {}
	virtual void afisare() const {
		cout << "ID: " << ID << endl;
		cout << "Nume: " << nume << endl;
		cout << "Cantitate: " << cantitate << endl;
		cout << "Pret per unitate: " << pret << endl;
		cout << "Pret: " << pretFinalCantitate() << endl;
		}
	virtual double pretFinalCantitate() const {
		double pretFinal = pret * cantitate;
		return pretFinal;
	}
	virtual ~Produs() {}
};
class Exceptie : public exception {
	string mesaj;
public:
	Exceptie(string m) : mesaj(m) {}
	const char* what() const noexcept override {
		return mesaj.c_str();
	}
};
class Depozit {
private:
	map<int, Produs> produse; // ID-ul produsului este cheia, iar valoarea obiectului Produs
public:
	void adaugaProdus(Produs p) {
		produse[p.ID] = p; // Adauga produsul in map folosind ID-ul ca si cheie
	}
	void stergeProdus(int id) {
		auto it = produse.find(id);
		if (it != produse.end()) {
			produse.erase(it); // Sterge produsul gasit
		}
		else {
			throw Exceptie("Produsul cu ID-ul " + to_string(id) + " nu a fost găsit pentru ștergere.");
		}
	}
	void actualizeazaCantitate(int id, int cantitate, bool esteVanzare) {
		auto it = produse.find(id);
		if (it == produse.end()) {
			throw Exceptie("Produsul cu ID-ul " + to_string(id) + " nu a fost gasit.");
		}

		if (esteVanzare) {
			if (it->second.cantitate < cantitate) {
				throw Exceptie("Stoc insuficient! Stoc disponibil: " + to_string(it->second.cantitate));
			}
			it->second.cantitate -= cantitate;
			cout << "Vanzare realizata. Stoc ramas: " << it->second.cantitate << endl;
		}
		else {
			it->second.cantitate += cantitate;
			cout << "Restock realizat. Stoc nou: " << it->second.cantitate << endl;
		}
	}
	Produs cautaProdus(int id) const {
		auto it = produse.find(id);
		if (it != produse.end()) {
			return it->second; // Returneaza produsul gasit
		}
		else {
			throw Exceptie("Produsul cu ID-ul " + to_string(id) + " nu a fost gasit.");
		}
	}
};

int main() {
	Depozit depozit;

	// Adaugare produse 
	cout << "=== Adaugare produse ===" << endl;
	depozit.adaugaProdus(Produs(1, "Lapte", 50, 5.99));
	depozit.adaugaProdus(Produs(2, "Paine", 30, 3.49));
	depozit.adaugaProdus(Produs(3, "Unt", 20, 12.50));
	cout << "Produse adaugate cu succes." << endl;

	// Cautare produs 
	cout << "\n=== Cautare produs (ID 2) ===" << endl;
	try {
		Produs p = depozit.cautaProdus(2);
		p.afisare();
	}
	catch (const Exceptie& e) {
		cout << e.what() << endl;
	}

	// Vanzare 
	cout << "\n=== Vanzare (ID 1, cantitate 10) ===" << endl;
	try {
		depozit.actualizeazaCantitate(1, 10, true);
	}
	catch (const Exceptie& e) {
		cout << e.what() << endl;
	}

	// Vanzare cu stoc insuficient 
	cout << "\n=== Vanzare cu stoc insuficient (ID 3, cantitate 999) ===" << endl;
	try {
		depozit.actualizeazaCantitate(3, 999, true);
	}
	catch (const Exceptie& e) {
		cout << e.what() << endl;
	}

	//  Restock 
	cout << "\n=== Restock (ID 2, cantitate 50) ===" << endl;
	try {
		depozit.actualizeazaCantitate(2, 50, false);
	}
	catch (const Exceptie& e) {
		cout << e.what() << endl;
	}

	//  Stergere produs 
	cout << "\n=== Stergere produs (ID 1) ===" << endl;
	try {
		depozit.stergeProdus(1);
		cout << "Produsul a fost sters." << endl;
	}
	catch (const Exceptie& e) {
		cout << e.what() << endl;
	}

	//  Cautare produs sters
	cout << "\n=== Cautare produs sters (ID 1) ===" << endl;
	try {
		depozit.cautaProdus(1);
	}
	catch (const Exceptie& e) {
		cout << e.what() << endl;
	}

	return 0;
}