//Aplicatia gestioneaza senzorii dintr-un sistem IOT. Informatiile pot fi transmise de la tastatura sau preluate din fisier
//Sunt implementatea diferite functionalitati pentru respectivii senzori.

#include<iostream>
#include<string>
#include<fstream>
using namespace std;

//Tipurile acceptate 
enum TipSenzor {
	Generic,
	Temperatura,
	Lumina,
	Miscare,
	Fum,
	Umiditate,
};
//Clase exceptii
class ExceptieSetter :public exception {
public:
	string what() {
		return "A aparut o exceptie de setter. Introdu date valide.";
	}
};
class ExceptieGetter :public exception {
public:
	string what() {
		return "A aparut o exceptie de getter. Introdu date valide pentru pozitia din vector.";
	}
};
class ExceptieCustom :public exception {
public:
	string what() {
		return "Senzorul introdus este invalid.Acesta nu apartine SistemuluiIOT. Introduceti o valoare corecta.";
	}
};
class ExceptieDeschidereFisier :public exception {
public:
	string what() {
		return "Nu s-a putut deschide fisierul. Introduceti o cale valida.";
	}
};
class Senzor {
private:
	TipSenzor tip;
	const int idSenzor;
	int numarInteractiuni;
	int numarResetari;
	int anFabricatie;
	char* producator;
	int durataViata;
	string amplasare;
	float timpRaspuns;
	int* istoricDateLunare;
	int numarLuniInregistrate;
	bool conectareWireless;
	string situatieUrgenta;
	TipSenzor* SenzoriConectati;
	int numarSenzConectati;
	static int numarSenzori;
public:
	//Constructori si op. egal
	Senzor() :idSenzor(numarSenzori++) {
		tip = (TipSenzor)0;
		numarInteractiuni = 0;
		numarResetari = 0;
		anFabricatie = 0;
		producator = nullptr;
		durataViata = 0;
		amplasare = "Generic";
		timpRaspuns = 0;
		istoricDateLunare = nullptr;
		numarLuniInregistrate = 0;
		conectareWireless = 0;
		situatieUrgenta = "Generic";
		SenzoriConectati = nullptr;
		numarSenzConectati = 0;
	}
	Senzor(TipSenzor new_tip, int new_numarInteractiuni, int new_numarResetari, int new_anFabricatie, const char* new_producator, int new_durataViata, string new_amplasare
		, float new_timpRaspuns, int* new_istoricDateLunare, int new_numarLuniInregistrate, bool new_conectareWireless, string new_situatieUrgenta, TipSenzor* new_SenzoriConectati, int new_numarSenzConectati) :idSenzor(numarSenzori++) {
		tip = new_tip;
		numarInteractiuni = new_numarInteractiuni;
		numarResetari = new_numarResetari;
		anFabricatie = new_anFabricatie;
		producator = new char[strlen(new_producator) + 1];
		strcpy_s(producator, strlen(new_producator) + 1, new_producator);
		durataViata = new_durataViata;
		amplasare = new_amplasare;
		timpRaspuns = new_timpRaspuns;
		numarLuniInregistrate = new_numarLuniInregistrate;
		istoricDateLunare = new int[new_numarLuniInregistrate];
		for (int i = 0; i < new_numarLuniInregistrate; i++) {
			istoricDateLunare[i] = new_istoricDateLunare[i];
		}
		conectareWireless = new_conectareWireless;
		situatieUrgenta = new_situatieUrgenta;
		numarSenzConectati = new_numarSenzConectati;
		SenzoriConectati = new TipSenzor[new_numarSenzConectati];
		for (int i = 0; i < new_numarSenzConectati; i++) {
			SenzoriConectati[i] = new_SenzoriConectati[i];
		}

	}
	Senzor(const Senzor& s) :idSenzor(numarSenzori++) {
		tip = s.tip;
		numarInteractiuni = s.numarInteractiuni;
		numarResetari = s.numarResetari;
		anFabricatie = s.anFabricatie;
		producator = new char[strlen(s.producator) + 1];
		strcpy_s(producator, strlen(s.producator) + 1, s.producator);
		durataViata = s.durataViata;
		amplasare = s.amplasare;
		timpRaspuns = s.timpRaspuns;
		numarLuniInregistrate = s.numarLuniInregistrate;
		istoricDateLunare = new int[s.numarLuniInregistrate];
		for (int i = 0; i < s.numarLuniInregistrate; i++) {
			istoricDateLunare[i] = s.istoricDateLunare[i];
		}
		conectareWireless = s.conectareWireless;
		situatieUrgenta = s.situatieUrgenta;
		numarSenzConectati = s.numarSenzConectati;
		SenzoriConectati = new TipSenzor[s.numarSenzConectati];
		for (int i = 0; i < s.numarSenzConectati; i++) {
			SenzoriConectati[i] = s.SenzoriConectati[i];
		}
	}
	Senzor& operator=(const Senzor& s) {
		tip = s.tip;
		numarInteractiuni = s.numarInteractiuni;
		numarResetari = s.numarResetari;
		anFabricatie = s.anFabricatie;
		producator = new char[strlen(s.producator) + 1];
		strcpy_s(producator, strlen(s.producator) + 1, s.producator);
		durataViata = s.durataViata;
		amplasare = s.amplasare;
		timpRaspuns = s.timpRaspuns;
		numarLuniInregistrate = s.numarLuniInregistrate;
		istoricDateLunare = new int[s.numarLuniInregistrate];
		for (int i = 0; i < s.numarLuniInregistrate; i++) {
			istoricDateLunare[i] = s.istoricDateLunare[i];
		}
		conectareWireless = s.conectareWireless;
		situatieUrgenta = s.situatieUrgenta;
		numarSenzConectati = s.numarSenzConectati;
		SenzoriConectati = new TipSenzor[s.numarSenzConectati];
		for (int i = 0; i < s.numarSenzConectati; i++) {
			SenzoriConectati[i] = s.SenzoriConectati[i];
		}
		return *this;
	}
	//Destructor
	~Senzor() {
		if (producator != NULL) {
			delete[]producator;
		}
		if (istoricDateLunare != NULL) {
			delete[]istoricDateLunare;
		}
		if (SenzoriConectati != NULL) {
			delete[]SenzoriConectati;
		}
	}
	//Getters settters
	TipSenzor getTip() {
		return tip;
	}
	int getNumarInteractiuni() {
		return numarInteractiuni;
	}
	int getNumarResetari() {
		return numarResetari;
	}
	int getNAnFabricatie() {
		return anFabricatie;
	}
	char* getProducator() {
		return producator;
	}
	int getDurataViata() {
		return durataViata;
	}
	string getAmplasare() {
		return amplasare;
	}
	float getTimpRaspuns() {
		return timpRaspuns;
	}
	int getNumarLuniInreg() {
		return numarLuniInregistrate;
	}
	int* getIstoric() {
		return istoricDateLunare;
	}
	int getIstoricAnumitaLuna(int pozitie) {
		if (pozitie >= 0 && pozitie < numarLuniInregistrate) {
			return istoricDateLunare[pozitie];
		}
		else
		{
			throw ExceptieGetter();
		}
	}
	bool getConectareWireless() {
		return conectareWireless;
	}
	string getSituatieUrgenta() {
		return situatieUrgenta;
	}
	int getNumarSenzoriConectati() {
		return numarSenzConectati;
	}
	TipSenzor* getTipuriSenzoriConectati() {
		return SenzoriConectati;
	}
	TipSenzor getAnumitTipSenzorConectat(int pozitie) {
		if (pozitie >= 0 && pozitie < numarSenzConectati) {
			return SenzoriConectati[pozitie];
		}
		else
		{
			throw ExceptieGetter();
		}
	}
	int getNumarSenzori() {
		return numarSenzori;
	}
	void setTip(TipSenzor new_tip) {
		if (new_tip == TipSenzor::Fum || new_tip == TipSenzor::Lumina || new_tip == TipSenzor::Miscare || new_tip == TipSenzor::Temperatura || new_tip == TipSenzor::Umiditate) {
			tip = new_tip;
		}
		else {
			throw ExceptieCustom();
		}
	}
	void setNumarInteractiuni(int new_numarInteractiuni) {
		if (new_numarInteractiuni >= 0) {
			numarInteractiuni = new_numarInteractiuni;
		}
		else {
			throw ExceptieSetter();
		}
	}
	void setNumarResetari(int new_numarResetari) {
		if (new_numarResetari >= 0) {
			numarResetari = new_numarResetari;
		}
		else {
			throw ExceptieSetter();
		}
	}
	void setAnFabricatie(int new_anFabricatie) {
		if (new_anFabricatie > 0) {
			anFabricatie = new_anFabricatie;
		}
		else {
			throw ExceptieSetter();
		}
	}
	void setDurataViata(int new_DurataViata) {
		if (new_DurataViata > 0) {
			durataViata = new_DurataViata;
		}
		else {
			throw ExceptieSetter();
		}
	}
	void setNumarLuniInreg(int new_NumarLuniInreg) {
		if (new_NumarLuniInreg >= 0) {
			numarLuniInregistrate = new_NumarLuniInreg;
		}
		else {
			throw ExceptieSetter();
		}
	}
	void setNumarSenzConnectati(int new_NumarSenzConnectati) {
		if (new_NumarSenzConnectati != 0) {
			numarSenzConectati = new_NumarSenzConnectati;
		}
		else {
			throw ExceptieSetter();
		}
	}
	void setProducator(const char* newProducator) {
		if (newProducator != nullptr) {
			if (producator != nullptr) {
				delete[]producator;
			}
			producator = new char[strlen(newProducator) + 1];
			strcpy_s(producator, strlen(newProducator) + 1, newProducator);
		}
		else {
			throw ExceptieSetter();
		}
	}
	void setIstoricDateLunare(int* new_istoricDateLunare, int new_NumarLuniInreg) {
		if (new_NumarLuniInreg > 0) {
			if (new_istoricDateLunare != nullptr) {
				setNumarLuniInreg(new_NumarLuniInreg);
				if (istoricDateLunare != nullptr) {
					delete[]istoricDateLunare;
				}
				istoricDateLunare = new int[new_NumarLuniInreg];
				for (int i = 0; i < new_NumarLuniInreg; i++) {
					istoricDateLunare[i] = new_istoricDateLunare[i];
				}
			}
			else
			{
				throw ExceptieSetter();
			}
		}
		else
		{
			throw ExceptieSetter();
		}

	}
	void setTipSenzoriConectati(TipSenzor* new_SenzoriConectati, int new_numarSenzConectati) {
		if (new_numarSenzConectati > 0) {
			if (new_SenzoriConectati != nullptr) {
				for (int i = 0; i < new_numarSenzConectati; i++) {
					if (new_SenzoriConectati[i] != TipSenzor::Fum && new_SenzoriConectati[i] != TipSenzor::Lumina && new_SenzoriConectati[i] != TipSenzor::Miscare && new_SenzoriConectati[i] != TipSenzor::Temperatura && new_SenzoriConectati[i] != TipSenzor::Umiditate) {
						throw ExceptieCustom();
					}
				}
				setNumarSenzConnectati(new_numarSenzConectati);
				if (SenzoriConectati != nullptr) {
					delete[]SenzoriConectati;
				}
				SenzoriConectati = new TipSenzor[new_numarSenzConectati];
				for (int i = 0; i < new_numarSenzConectati; i++) {
					this->SenzoriConectati[i] = new_SenzoriConectati[i];
				}
			}
			else
			{
				throw ExceptieSetter();
			}
		}
		else
		{
			throw ExceptieSetter();
		}

	}
	void setAmplasare(string new_amplasare) {
		if (new_amplasare.length() != 0) {
			amplasare = new_amplasare;
		}
		else {
			throw ExceptieSetter();
		}
	}
	void setSituatieUrgenta(string new_SituatieUrgenta) {
		if (new_SituatieUrgenta.length() != 0) {
			situatieUrgenta = new_SituatieUrgenta;
		}
		else {
			throw ExceptieSetter();
		}
	}
	void setTimpRaspuns(float new_timpRaspuns) {
		if (new_timpRaspuns > 0) {
			timpRaspuns = new_timpRaspuns;
		}
		else {
			throw ExceptieSetter();
		}
	}
	void setConectareWireless(bool new_conectareWireless) {
		if (new_conectareWireless == 0 or new_conectareWireless == 1) {
			conectareWireless = new_conectareWireless;
		}
		else
		{
			throw ExceptieSetter();
		}
	}
	void setAnumitaLuna(int interctiuneLuna, int pozitie) {
		if (pozitie >= 0 && pozitie < numarLuniInregistrate) {
			if (interctiuneLuna >= 0) {
				istoricDateLunare[pozitie] = interctiuneLuna;
			}
			else
			{
				throw ExceptieSetter();
			}
		}
		else
		{
			throw ExceptieSetter();
		}
	}
	void setAnumitSenzor(TipSenzor senzorNou, int pozitie) {
		if (pozitie >= 0 && pozitie < numarSenzConectati) {
			if (senzorNou == TipSenzor::Fum || senzorNou == TipSenzor::Lumina || senzorNou == TipSenzor::Miscare || senzorNou == TipSenzor::Temperatura || senzorNou == TipSenzor::Umiditate) {
				SenzoriConectati[pozitie] = senzorNou;
			}
			else
			{
				throw ExceptieCustom();
			}
		}
		else
		{
			throw ExceptieSetter();
		}

	}

	//operator <<
	friend ostream& operator<<(ostream& afisare, const Senzor& s) {
		afisare << "Senzorul de";
		switch (s.tip) {
		case TipSenzor::Umiditate:
			afisare << " umiditate ";
			break;
		case TipSenzor::Temperatura:
			afisare << " temperatura ";
			break;
		case TipSenzor::Miscare:
			afisare << " miscare ";
			break;
		case TipSenzor::Lumina:
			afisare << " lumina ";
			break;
		case TipSenzor::Fum:
			afisare << " fum ";
			break;
		case TipSenzor::Generic:
			afisare << " generic ";
			break;
		}
		afisare << " a avut " << s.numarInteractiuni << " interactiuni cu locatarii astazi, a avut " << s.numarResetari << " resetari. Acesta a fost fabricat in anul " << s.anFabricatie << " de catre ";
		if (s.producator != NULL)
		{
			afisare << s.producator;
		}
		else
		{
			afisare << "producator necunoscut";
		}
		afisare << " avand o durata medie de viata de " << s.durataViata << " ani. Timpul sau de raspuns este de aproximativ " << s.timpRaspuns << " milisecunde." << endl;
		afisare << "In caz de urgenta:" << s.situatieUrgenta << endl;

		if (s.numarSenzConectati > 0) {
			afisare << endl << "Acest senzor se afla in conexiune cu urmatorii " << s.numarSenzConectati << " senzori:";
			for (int i = 0; i < s.numarSenzConectati; i++) {
				switch (s.SenzoriConectati[i])
				{
				case TipSenzor::Umiditate:
					afisare << " Senzorul de umiditate " << endl;
					break;
				case TipSenzor::Temperatura:
					afisare << " Senzorul de temperatura " << endl;
					break;
				case TipSenzor::Miscare:
					afisare << " Senzorul de miscare " << endl;
					break;
				case TipSenzor::Lumina:
					afisare << " Senzorul de lumina " << endl;
					break;
				case TipSenzor::Fum:
					afisare << " Senzorul de fum " << endl;
					break;
				default:
					break;
				}
			}
		}
		else
		{
			afisare << "Acesta nu este conectat cu vreun alt senzor." << endl;

		}
		if (s.numarLuniInregistrate > 0) {
			afisare << "Senzorul de asemenea prezinta istoricul datelor din ultimele " << s.numarLuniInregistrate << " luni." << endl << "Acesta a interactionat lunar de:" << endl;;
			for (int i = 0; i < s.numarLuniInregistrate; i++) {
				afisare << "In luna " << i + 1 << " a interactionat de " << s.istoricDateLunare[i] << " ori. " << endl;
			}
		}
		else {
			afisare << "Acesta nu prezinta istoric." << endl;
		}
		if (s.conectareWireless == true) {
			afisare << "Senzorul permite conectare wireless." << endl;
		}
		else
		{
			afisare << "Senzorul nu permite conectare wireless." << endl;
		}
		return afisare;

	}

	friend istream& operator>>(istream& citire, Senzor& s) {
		int b;
		cout << "--Tipuri de senzori--" << endl << "1- Temperatura" << endl << "2-Lumina" << endl << "3-Miscare" << endl << "4-Fum" << endl << "5-Umiditate" << endl << "Introduceti tipul:";
		citire >> b;
		s.setTip((TipSenzor)b);
		cout << "Numar Interactiunilor Astazi:";
		citire >> s.numarInteractiuni;
		cout << "Numar Resetari:";
		citire >> s.numarResetari;
		cout << "Anul de fabricatie:";
		citire >> s.anFabricatie;
		char a[100];
		cout << "Producatorul:";
		citire >> a;
		if (s.producator != nullptr) {
			delete[]s.producator;
		}
		s.producator = new char[strlen(a) + 1];
		strcpy_s(s.producator, strlen(a) + 1, a);
		cout << "Durata de viata:";
		citire >> s.durataViata;
		cout << "Amplasarea:";
		citire >> s.amplasare;
		cout << "Timp de raspuns:";
		citire >> s.timpRaspuns;
		cout << "Numar luni inregistrate:";
		citire >> s.numarLuniInregistrate;
		if (s.istoricDateLunare != NULL) {
			delete[]s.istoricDateLunare;
		}
		s.istoricDateLunare = new int[s.numarLuniInregistrate];
		for (int i = 0; i < s.numarLuniInregistrate; i++) {
			cout << "Datele pentru luna " << i + 1 << ":";
			citire >> s.istoricDateLunare[i];
		}
		cout << "Senzorul poate fi conecta wireless? [0/1]:";
		citire >> s.conectareWireless;
		cout << "Raspuns in caz de urgenta:";
		citire >> s.situatieUrgenta;
		cout << "Numarul de senzori conectati la acesta:";
		citire >> s.numarSenzConectati;
		if (s.SenzoriConectati != NULL) {
			delete[]s.SenzoriConectati;
		}
		s.SenzoriConectati = new TipSenzor[s.numarSenzConectati];
		for (int i = 0; i < s.numarSenzConectati; i++) {
			cout << "Tipul senzorului " << i + 1 << endl << "1- Temperatura" << endl << "2-Lumina" << endl << "3-Miscare" << endl << "4-Fum" << endl << "5-Umiditate" << endl << "Introduceti tipul:";
			citire >> b;
			s.setAnumitSenzor((TipSenzor)b, i);
		}
		return citire;
	}
	friend ifstream& operator>>(ifstream& citire, Senzor& s) {
		int b;
		citire >> b;
		s.setTip((TipSenzor)b);
		citire >> s.numarInteractiuni;
		citire >> s.numarResetari;
		citire >> s.anFabricatie;
		char a[100];
		citire >> a;
		if (s.producator != nullptr) {
			delete[]s.producator;
		}
		s.producator = new char[strlen(a) + 1];
		strcpy_s(s.producator, strlen(a) + 1, a);
		citire >> s.durataViata;
		citire >> s.amplasare;
		citire >> s.timpRaspuns;
		citire >> s.numarLuniInregistrate;
		if (s.istoricDateLunare != NULL) {
			delete[]s.istoricDateLunare;
		}
		s.istoricDateLunare = new int[s.numarLuniInregistrate];
		for (int i = 0; i < s.numarLuniInregistrate; i++) {
			citire >> s.istoricDateLunare[i];
		}
		citire >> s.conectareWireless;
		citire >> s.situatieUrgenta;
		citire >> s.numarSenzConectati;
		if (s.SenzoriConectati != NULL) {
			delete[]s.SenzoriConectati;
		}
		s.SenzoriConectati = new TipSenzor[s.numarSenzConectati];
		for (int i = 0; i < s.numarSenzConectati; i++) {
			citire >> b;
			s.setAnumitSenzor((TipSenzor)b, i);
		}
		return citire;

	}

	Senzor& operator-(const Senzor& s) {
		Senzor aux = s;
		if (this->anFabricatie < aux.anFabricatie) {
			aux.anFabricatie = this->anFabricatie;
		}
		if (this->conectareWireless < aux.conectareWireless) {
			aux.conectareWireless = this->conectareWireless;
		}
		if (this->numarInteractiuni < aux.numarInteractiuni) {
			aux.numarInteractiuni = this->numarInteractiuni;
		}
		if (this->numarResetari < aux.numarResetari) {
			aux.numarResetari = this->numarResetari;
		}
		return aux;
	}
	Senzor& operator-(int numar) {
		if (numar < this->numarInteractiuni) {
			this->numarInteractiuni -= numar;
		}
		if (numar < this->numarResetari) {
			this->numarResetari -= numar;
		}
		if (numar < this->durataViata) {
			this->durataViata -= numar;
		}
		return *this;
	}
	friend Senzor& operator-(Senzor s, int numar) {
		if (numar < s.numarInteractiuni) {
			s.numarInteractiuni -= numar;
		}
		if (numar < s.numarResetari) {
			s.numarResetari -= numar;
		}
		if (numar < s.durataViata) {
			s.durataViata -= numar;
		}
		return s;
	}

	int operator()() {
		int suma = 0;
		int medie = 0;
		if (this->numarLuniInregistrate > 0) {
			for (int i = 0; i < this->numarLuniInregistrate; i++) {
				suma += this->istoricDateLunare[i];
			}
			medie = suma / this->numarLuniInregistrate;
		}
		else
		{
			medie = 0;
		}
		return medie;

	}
	Senzor operator++() {
		for (int i = 0; i < numarLuniInregistrate; i++) {
			this->istoricDateLunare[i]++;
		}
		this->numarInteractiuni++;
		this->numarResetari++;
		this->durataViata++;
		this->timpRaspuns++;
		return *this;
	}
	Senzor operator++(int) {
		Senzor aux = *this;
		for (int i = 0; i < numarLuniInregistrate; i++) {
			this->istoricDateLunare[i]++;
		}
		this->numarInteractiuni++;
		this->numarResetari++;
		this->durataViata++;
		this->timpRaspuns++;
		return aux;
	}
	void operator-=(const Senzor& s) {
		if (this->anFabricatie > s.anFabricatie) {
			this->anFabricatie = s.anFabricatie;
		}
		if (this->conectareWireless > s.conectareWireless) {
			this->conectareWireless = s.conectareWireless;
		}
		if (this->numarInteractiuni > s.numarInteractiuni) {
			this->numarInteractiuni = s.numarInteractiuni;
		}
		if (this->numarResetari > s.numarResetari) {
			this->numarResetari = s.numarResetari;
		}
	}
	void operator-=(int numar) {
		if (numar < this->numarInteractiuni) {
			this->numarInteractiuni -= numar;
		}
		if (numar < this->numarResetari) {
			this->numarResetari -= numar;
		}
		if (numar < this->durataViata) {
			this->durataViata -= numar;
		}
	}
	void operator+=(const Senzor& s) {
		if (this->anFabricatie < s.anFabricatie) {
			this->anFabricatie = s.anFabricatie;
		}
		if (this->conectareWireless < s.conectareWireless) {
			this->conectareWireless = s.conectareWireless;
		}
		if (this->numarInteractiuni < s.numarInteractiuni) {
			this->numarInteractiuni = s.numarInteractiuni;
		}
		if (this->numarResetari < s.numarResetari) {
			this->numarResetari = s.numarResetari;
		}
	}
	void operator+=(int numar) {
		this->numarInteractiuni += numar;
		this->numarResetari += numar;
		this->durataViata += numar;
	}
	Senzor& operator/(const Senzor& s) {
		Senzor aux = *this;
		aux.durataViata = (this->durataViata / s.durataViata);
		return aux;
	}
	Senzor& operator/(int numar) {
		Senzor aux = *this;
		aux.durataViata = (this->durataViata / numar);
		return aux;
	}
};
int Senzor::numarSenzori = 1;



class SistemIOT {
private:
	const int idSistem;
	char* numeSistemIOT;
	int numarSenzori;
	Senzor* senzoriSistem;
	static int numarSistemeIOT;
public:
	SistemIOT() :idSistem(numarSistemeIOT++) {
		numeSistemIOT = new char[strlen("Generic") + 1];
		strcpy_s(numeSistemIOT, strlen("Generic") + 1, "Generic");
		numarSenzori = 0;
		senzoriSistem = nullptr;
	}
	SistemIOT(const char* new_nume_SistemIOT, int new_numarSenzori, Senzor* new_senzoriSistem) :idSistem(numarSistemeIOT++) {
		this->numeSistemIOT = new char[strlen(new_nume_SistemIOT) + 1];
		strcpy_s(this->numeSistemIOT, strlen(new_nume_SistemIOT) + 1, new_nume_SistemIOT);
		this->numarSenzori = new_numarSenzori;
		senzoriSistem = new Senzor[new_numarSenzori];
		for (int i = 0; i < new_numarSenzori; i++) {
			senzoriSistem[i] = new_senzoriSistem[i];
		}
	}
	SistemIOT(const SistemIOT& sistem) :idSistem(numarSistemeIOT++) {
		this->numeSistemIOT = new char[strlen(sistem.numeSistemIOT) + 1];
		strcpy_s(this->numeSistemIOT, strlen(sistem.numeSistemIOT) + 1, sistem.numeSistemIOT);
		this->numarSenzori = sistem.numarSenzori;
		senzoriSistem = new Senzor[sistem.numarSenzori];
		for (int i = 0; i < sistem.numarSenzori; i++) {
			senzoriSistem[i] = sistem.senzoriSistem[i];
		}
	}
	~SistemIOT() {
		if (numeSistemIOT != NULL) {
			delete[]numeSistemIOT;
		}
		if (senzoriSistem != NULL) {
			delete[]senzoriSistem;
		}
	}
	char* getNumeSistem() {
		return this->numeSistemIOT;
	}
	int getNumarSenzori() {
		return this->numarSenzori;
	}
	Senzor* getVectorSenzori() {
		return senzoriSistem;
	}
	Senzor getAnumitSenzor(int pozitie) {
		if (pozitie >= 0 && pozitie < this->numarSenzori) {
			return this->senzoriSistem[pozitie];
		}
		else
		{
			throw ExceptieGetter();
		}
	}
	int getNumarSisitemeIOT() {
		return numarSistemeIOT;
	}
	void setNumeSistem(const char* newNumeSistem) {
		if (newNumeSistem != NULL) {
			if (this->numeSistemIOT != NULL) {
				delete[]this->numeSistemIOT;
			}
			this->numeSistemIOT = new char[strlen(newNumeSistem) + 1];
			strcpy_s(this->numeSistemIOT, strlen(newNumeSistem) + 1, newNumeSistem);
		}
		else
		{
			throw ExceptieSetter();
		}
	}
	void setNumarSenzori(int newNumarSenzori) {
		if (newNumarSenzori > 0) {
			this->numarSenzori = newNumarSenzori;
		}
		else
		{
			throw ExceptieSetter();
		}
	}
	void setVectorSenzori(int newNumarSenzori, const Senzor* vector) {
		if (newNumarSenzori > 0) {
			this->setNumarSenzori(newNumarSenzori);
			if (vector != NULL) {
				if (this->senzoriSistem != NULL) {
					delete[]senzoriSistem;
				}
				this->senzoriSistem = new Senzor[newNumarSenzori];
				for (int i = 0; i < newNumarSenzori; i++) {
					this->senzoriSistem[i] = vector[i];
				}
			}
			else
			{
				throw ExceptieSetter();
			}
		}
		else
		{
			throw ExceptieSetter();
		}
	}
	void setAnumitSenzor(Senzor s, int pozitie) {
		if (pozitie >= 0 && pozitie < this->numarSenzori) {
			this->senzoriSistem[pozitie] = s;
		}
		else
		{
			throw ExceptieSetter();
		}
	}
	SistemIOT& operator=(const SistemIOT sistem) {
		this->numeSistemIOT = new char[strlen(sistem.numeSistemIOT) + 1];
		strcpy_s(this->numeSistemIOT, strlen(sistem.numeSistemIOT) + 1, sistem.numeSistemIOT);
		this->numarSenzori = sistem.numarSenzori;
		senzoriSistem = new Senzor[sistem.numarSenzori];
		for (int i = 0; i < sistem.numarSenzori; i++) {
			senzoriSistem[i] = sistem.senzoriSistem[i];
		}
		return *this;
	}
	friend ostream& operator<<(ostream& afisare, const SistemIOT& sistem) {
		afisare << endl << "=====AFISARE SISTEM IOT =====" << endl;
		afisare << "Sistemul IOT " << sistem.numeSistemIOT << " prezinta " << sistem.numarSenzori << " senzori iar acestia sunt urmatorii:" << endl;
		for (int i = 0; i < sistem.numarSenzori; i++) {
			afisare << i + 1 << ". " << sistem.senzoriSistem[i] << endl;
		}
		return afisare;
	}

	friend istream& operator>>(istream& citire, SistemIOT& sistem) {
		char nume[100];
		cout << "Numele Sistemului:";
		citire >> nume;
		sistem.setNumeSistem(nume);
		cout << "Numarul de senzori al sistemului:";
		citire >> sistem.numarSenzori;
		if (sistem.senzoriSistem != NULL) {
			delete[]sistem.senzoriSistem;
		}
		sistem.senzoriSistem = new Senzor[sistem.numarSenzori];
		for (int i = 0; i < sistem.numarSenzori; i++) {
			citire >> sistem.senzoriSistem[i];
		}
		return citire;
	}
	friend ifstream& operator>>(ifstream& citire, SistemIOT& sistem) {
		char nume[100];
		citire >> nume;
		sistem.setNumeSistem(nume);
		citire >> sistem.numarSenzori;
		if (sistem.senzoriSistem != NULL) {
			delete[]sistem.senzoriSistem;
		}
		sistem.senzoriSistem = new Senzor[sistem.numarSenzori];
		for (int i = 0; i < sistem.numarSenzori; i++) {
			citire >> sistem.senzoriSistem[i];
		}
		return citire;
	}

	Senzor operator[](int pozitie) {
		if (pozitie >= 0 && pozitie < this->numarSenzori) {
			return this->senzoriSistem[pozitie];
		}
	}
	SistemIOT& operator+(int numar) {
		for (int i = this->numarSenzori; i < numar + this->numarSenzori; i++) {
			cin >> this->senzoriSistem[i];
		}
		this->numarSenzori += numar;
		return *this;
	}
	friend SistemIOT& operator+(int numar, SistemIOT& sistem) {
		for (int i = sistem.numarSenzori; i < numar + sistem.numarSenzori; i++) {
			cin >> sistem.senzoriSistem[i];
		}
		sistem.numarSenzori += numar;
		return sistem;
	}
	SistemIOT operator--() {
		Senzor* vectorTemporar;
		vectorTemporar = new Senzor[this->numarSenzori - 1];
		for (int i = 0; i < this->numarSenzori - 1; i++) {
			vectorTemporar[i] = this->senzoriSistem[i];
		}
		delete[]this->senzoriSistem;
		this->numarSenzori--;
		this->senzoriSistem = new Senzor[this->numarSenzori];
		for (int i = 0; i < this->numarSenzori; i++) {
			this->senzoriSistem[i] = vectorTemporar[i];
		}
		delete[]vectorTemporar;
		return *this;
	}
	SistemIOT operator--(int) {
		SistemIOT sistemAUX = *this;
		Senzor* vectorTemporar;
		vectorTemporar = new Senzor[this->numarSenzori - 1];
		for (int i = 0; i < this->numarSenzori - 1; i++) {
			vectorTemporar[i] = this->senzoriSistem[i];
		}
		delete[]this->senzoriSistem;
		this->numarSenzori--;
		this->senzoriSistem = new Senzor[this->numarSenzori];
		for (int i = 0; i < this->numarSenzori; i++) {
			this->senzoriSistem[i] = vectorTemporar[i];
		}
		delete[]vectorTemporar;
		return sistemAUX;
	}
	void operator()(Senzor& s) {
		Senzor* vectorTemporar;
		this->numarSenzori++;
		vectorTemporar = new Senzor[this->numarSenzori];
		for (int i = 0; i < this->numarSenzori - 1; i++) {
			vectorTemporar[i] = this->senzoriSistem[i];
		}
		vectorTemporar[this->numarSenzori - 1] = s;
		delete[]this->senzoriSistem;
		this->senzoriSistem = new Senzor[this->numarSenzori];
		for (int i = 0; i < this->numarSenzori; i++) {
			this->senzoriSistem[i] = vectorTemporar[i];
		}
		delete[]vectorTemporar;
	}
	bool operator!=(int numar) {
		return !(this->numarSenzori == numar);
	}
	friend bool operator!=(int numar, const SistemIOT& sistem) {
		return!(sistem.numarSenzori == numar);
	}
	bool operator==(int numar) {
		return this->numarSenzori == numar;
	}
	friend bool operator==(int numar, const SistemIOT& sistem) {
		return sistem.numarSenzori == numar;
	}

};
int SistemIOT::numarSistemeIOT = 1;

template<typename T1, typename T2> class Actiune {
private:
public:
	virtual T1 executa(T2) = 0;
};

class CreeazaProfilSenzor :public Actiune<float, Senzor> {
public:
	virtual float executa(Senzor s) {
		float scor = 0;
		switch (s.getConectareWireless())
		{
		case 1:scor += 2;
			break;
		default:scor += 1;
			break;
		}
		if (s.getTimpRaspuns() <= 3) {
			scor += 2;
		}
		else
		{
			if (s.getTimpRaspuns() <= 10) {
				scor += 1;
			}
			else
			{
				scor += 0.5;
			}
		}
		if (s.getNumarLuniInreg() > 0) {
			scor += 2;
		}
		else
		{
			scor += 1;
		}
		if (s.getNAnFabricatie() >= 2020) {
			scor += 2;
		}
		else
		{
			if (s.getNAnFabricatie() >= 2015) {
				scor += 1;
			}
			else
			{
				scor += 0.5;
			}
		}
		if (s.getDurataViata() >= 10) {
			scor += 2;
		}
		else
		{
			if (s.getDurataViata() >= 5) {
				scor += 1;
			}
			else
			{
				scor += 0.5;
			}
		}
		return scor;
	}
};

class CalculeazaInteligentaSistem :public Actiune<float, SistemIOT> {
private:
	float scorInteligenta;
public:
	float executa(SistemIOT sistem) {
		scorInteligenta = 0;
		Actiune<float, Senzor>* Profil = new CreeazaProfilSenzor;
		for (int i = 0; i < sistem.getNumarSenzori(); i++) {
			scorInteligenta += Profil->executa(sistem.getVectorSenzori()[i]);
		}
		return scorInteligenta / sistem.getNumarSenzori();
		delete Profil;
	}
	float getScorInteligenta() {
		return scorInteligenta;
	}
	void setScorInteligenta(float newScorInteligenta) {
		if (newScorInteligenta >= 0 and newScorInteligenta <= 10) {
			this->scorInteligenta = newScorInteligenta;
		}
		else
		{
			throw ExceptieSetter();
		}
	}
};

class ModificaSenzor :public Actiune<Senzor, Senzor> {
public:
	Senzor executa(Senzor s) {
		int optiune = 9;

		while (optiune != 8 && optiune != 1)
		{
			cout << endl << endl << "---Modificare Senzor---" << endl << endl;
			cout << "1-Modificare intreg senzor." << endl << "2-Modificare numar interactiuni." << endl << "3-Modificare durata de viata." << endl << "4-Modificati timpul de raspuns." << endl << "5-Modificati istoric date lunare." << "6-Modificati conectarea wireless." << endl << "7-Modificati senzorii conectati";
			cout << endl << "Pentru orice alta valoare, modificarea se va sfarsi.";
			cout << endl << "Introduceti varianta dorita:";
			cin >> optiune;
			switch (optiune)
			{
			case 1:
			{
				cin >> s;
			}
			break;
			case 2:
			{
				int numar;
				cout << "Introduceti noul numar de interactiuni:";
				cin >> numar;
				s.setNumarInteractiuni(numar);
			}
			break;
			case 3:
			{
				int durata;
				cout << "Introduceti noua durata de viata:";
				cin >> durata;
				s.setDurataViata(durata);
			}
			break;
			case 4:
			{
				float newTimp;
				cout << "Introduceti noul timp de raspuns:";
				cin >> newTimp;
				s.setTimpRaspuns(newTimp);
			}
			break;
			case 5:
			{
				int newNumarLuni;
				int* vector;
				cout << "Introduceti noul numar de luni inregistrate de catre senzor:"; cin >> newNumarLuni;
				vector = new int[newNumarLuni];
				for (int i = 0; i < newNumarLuni; i++) {
					cout << "Numarul de interactiuni pentru luna " << i + 1 << " a fost:";
					cin >> vector[i];
				}
				s.setIstoricDateLunare(vector, newNumarLuni);
				delete[]vector;
			}
			break;
			case 6:
			{
				bool newConectare;
				cout << "Introduceti posibilitatea de conectare wireless:" << endl << "0-nu se poate conecta" << endl << "1-se poate conecta" << endl << "Valoarea:";
				cin >> newConectare;
				s.setConectareWireless(newConectare);
			}
			break;
			case 7:
			{
				int newSenzConectati;
				TipSenzor* vector;
				int aux;
				cout << "Introduceti noul numar de senzori conectati la senzorul curent:"; cin >> newSenzConectati;
				vector = new TipSenzor[newSenzConectati];
				for (int i = 0; i < newSenzConectati; i++) {
					cout << "--Tipuri de senzori--" << endl << "1- Temperatura" << endl << "2-Lumina" << endl << "3-Miscare" << endl << "4-Fum" << endl << "5-Umiditate" << endl << "Introduceti tipul:";
					cin >> aux;
					vector[i] = (TipSenzor)aux;
				}
				s.setTipSenzoriConectati(vector, newSenzConectati);
				delete[]vector;
			}
			break;
			default:
			{
				optiune = 8;
				cout << endl << "Modificarea s-a terminat." << endl;
			}
			break;
			}
		}
		return s;

	}
};

class Adauga :public Actiune<SistemIOT, SistemIOT> {
public:
	SistemIOT executa(SistemIOT sistem) {
		Senzor* s = new Senzor;
		int numar;
		cout << endl << "--Adaugare Senzor -- " << endl;
		cout << "Introduceti numarul de senzori pe care doriti sa ii adaugati.";
		cin >> numar;
		for (int i = 0; i < numar; i++)
		{
			cin >> *s;
			sistem(*s);
		}
		delete s;
		return sistem;
	}
};

class StergeSenzor :public Actiune<SistemIOT, SistemIOT> {
public:
	SistemIOT executa(SistemIOT sistem) {
		int numar;
		cout << endl << "--Stergere senzor" << endl;
		cout << "Introduceti numarul de senzori pe care doriti sa ii stergeti, " << sistem.getNumeSistem() << " prezinta " << sistem.getNumarSenzori() << " senzori:";
		cin >> numar;
		if (numar <= sistem.getNumarSenzori()) {
			for (int i = 0; i < numar; i++) {
				sistem--;
			}
			cout << endl << "Stergerea s-a realizat cu succes." << endl;
		}
		else {
			throw 404;
		}
		return sistem;
	}
};

int main() {
	cout << "===PROIECT POO - PASCARU CRISTIAN 1044 ===" << endl << endl;
	int optiune = 3;
	SistemIOT sistemIOT;
	while (optiune == 3) {
		cout << "\nPrecizati cum doriti sa introduceti datele despre Sistemul IOT:" << endl;
		cout << "1-Tastatura" << endl;
		cout << "2-Din fisierul 'Senzori.txt' predefinit cu date" << endl;
		cin >> optiune;
		switch (optiune)
		{
		case 1:
		{
			cout << "Ati ales optiunea pentru introducere de la tastatura.Va rog introduceti datele." << endl;
			try
			{
				cin >> sistemIOT;
				cout << endl << "Adaugarea sistemului s-a realizat cu succes!" << endl;
			}
			catch (ExceptieCustom a)
			{
				cout << a.what();
				optiune = 3;
			}
			catch (ExceptieSetter b) {
				cout << b.what();
				optiune = 3;
			}
		}
		break;
		case 2:
		{
			cout << "Ati ales optiunea pentru introducere din fisierul predefinit." << endl;
			try
			{
				ifstream fin("Senzori.txt", ios::in);
				if (!(fin.is_open())) {
					throw ExceptieDeschidereFisier();
				}
				fin >> sistemIOT;
				cout << endl << "Adaugarea sistemului s-a realizat cu succes!" << endl;
				fin.close();
			}
			catch (ExceptieCustom a)
			{
				optiune = 3;
				cout << a.what();
			}
			catch (ExceptieSetter b) {
				optiune = 3;
				cout << b.what();
			}
			catch (ExceptieDeschidereFisier c) {
				optiune = 3;
				cout << c.what();
			}

		}
		break;
		default: {
			cout << endl << "===Optiune invalida===" << endl << endl;
			optiune = 3;
		}
			   break;
		}
	}
	optiune = 3;
	while (optiune != 5) {
		cout << endl << "Precizati urmatoare optiune:" << endl;
		cout << "1-Afisare Sistem" << endl;
		cout << "2-Calcul Profil Senzori." << endl;
		cout << "3-Calcul Inteligenta SistemIOT." << endl;
		cout << "4-Scriere in fisier a profilelor si a inteligentei." << endl;
		cout << "5-Iesire Meniu" << endl;
		cin >> optiune;
		switch (optiune)
		{
		case 1: {
			cout << endl << "Ati selectat optiune 1. Se va afisa sistemul." << endl;
			cout << sistemIOT;
			cout << endl << "Afisarea s-a realizat cu succes!" << endl;
		}
			  break;
		case 2: {
			cout << endl << "Ati selectat optiunea 2. Se vor calcula profilele senzorilor." << endl;
			Actiune<float, Senzor>* ProfilSenzor = new CreeazaProfilSenzor;
			for (int i = 0; i < sistemIOT.getNumarSenzori(); i++) {
				cout << "Profilul senzorului ";
				switch (sistemIOT[i].getTip())
				{
				case TipSenzor::Umiditate:
					cout << " de umiditate ";
					break;
				case TipSenzor::Temperatura:
					cout << " de temperatura ";
					break;
				case TipSenzor::Miscare:
					cout << " de miscare ";
					break;
				case TipSenzor::Lumina:
					cout << " de lumina ";
					break;
				case TipSenzor::Fum:
					cout << " de fum ";
					break;
				default:
					break;
				}
				cout << " este:" << ProfilSenzor->executa(sistemIOT[i]) << "/10." << endl;
			}
			cout << "Ati realizat cu succes profilele senzorilor!" << endl;
			delete ProfilSenzor;
		}
			  break;
		case 3: {
			cout << endl << "Ati selectat optiunea 3. Se va calcula inteligenta sistemului IOT." << endl;
			Actiune<float, SistemIOT>* inteligentaSistem = new CalculeazaInteligentaSistem;
			cout << "Inteligenta sistemului este:" << inteligentaSistem->executa(sistemIOT) << "/10." << endl;
			cout << "Ati calculat cu succes Inteligenta Sistemului IOT!" << endl;
			delete inteligentaSistem;

		}
			  break;
		case 4: {
			cout << endl << "Ati selectat optiunea 4. Se vor scrie in fisier profilele si inteligenta sistemului." << endl;
			string numeFisier;
			cout << "Introduceti numele fisierului in care doriti sa se scrie.";
			cin >> numeFisier;
			ofstream fout(numeFisier, ios::out);
			Actiune<float, Senzor>* ProfilSenzor = new CreeazaProfilSenzor;
			Actiune<float, SistemIOT>* inteligentaSistem = new CalculeazaInteligentaSistem;
			try {
				if (!(fout.is_open())) {
					throw ExceptieDeschidereFisier();
				}
				fout << sistemIOT;
				fout << endl << "Pentru acest SistemIOT, s-au calculat urmatoarele:" << endl;
				for (int i = 0; i < sistemIOT.getNumarSenzori(); i++) {
					fout << "Profilul senzorului " << i + 1 << " este:" << ProfilSenzor->executa(sistemIOT[i]) << endl;
				}
				fout << "Inteligenta sistemului este:" << inteligentaSistem->executa(sistemIOT) << "/10" << endl;
				cout << "Ati scris cu succes Profilul Senzorilor si Inteligenta Sistemului IOT!" << endl;

			}
			catch (ExceptieCustom a)
			{
				cout << a.what();
			}
			catch (ExceptieSetter b) {
				cout << b.what();
			}
			catch (ExceptieDeschidereFisier a) {
				cout << a.what();
			}
			fout.close();
			if (ProfilSenzor != NULL) {
				delete ProfilSenzor;
			}
			if (inteligentaSistem != NULL) {
				delete inteligentaSistem;
			}
		}
			  break;
		case 5: {
			optiune = 5;
		}
			  break;
		default: {
			cout << endl << "===Optiune invalida===" << endl << endl;
			optiune = 6;
		}
			   break;
		}
	}while (optiune != 4) {
		cout << "Precizati actiunile urmatorare in functie de Profilele obtinute." << endl;
		cout << "1-Adaugare senzor nou in sistem" << endl;
		cout << "2-Modificare senzor" << endl;
		cout << "3-Stergere senzor" << endl;
		cout << "4-Iesire Meniu" << endl;
		cin >> optiune;
		switch (optiune)
		{
		case 1: {
			cout << endl << "Ati selectat optiune 1. Se va adauga un nou senzor." << endl;
			Actiune<SistemIOT, SistemIOT>* adauga = new Adauga();
			try {
				sistemIOT = adauga->executa(sistemIOT);
				cout << endl << "Ati adaugat cu succes, se va realiza afisarea sistemului modificat." << endl;
				cout << sistemIOT;
			}
			catch (ExceptieSetter a) {
				cout << a.what();
			}
			catch (ExceptieCustom a)
			{
				cout << a.what();
			}
			catch (ExceptieGetter a) {
				cout << a.what();
			}
			if (adauga != NULL) {
				delete adauga;
			}

		}
			  break;
		case 2: {
			int numar;
			cout << endl << "Ati selectat optiune 1." << endl << "Sistemul are " << sistemIOT.getNumarSenzori() << " senzori." << endl << "Introduceti numarul senzorului care trebuie modificat";
			cin >> numar;
			Actiune<Senzor, Senzor>* Modificare = new ModificaSenzor;
			try {
				if ((numar - 1) >= 0 && (numar - 1) < sistemIOT.getNumarSenzori()) {
					sistemIOT.getVectorSenzori()[numar - 1] = Modificare->executa(sistemIOT.getVectorSenzori()[numar - 1]);
					cout << endl << "Ati modificat cu succes, se va realiza afisarea senzorului modificat." << endl << endl;
					cout << sistemIOT.getVectorSenzori()[numar - 1];
				}
				else
				{
					cout << endl << "Numar introdus eronat" << endl;
				}
			}
			catch (ExceptieSetter a) {
				cout << a.what();
			}
			catch (ExceptieCustom a)
			{
				cout << a.what();
			}
			catch (ExceptieGetter a) {
				cout << a.what();
			}
			if (Modificare != NULL) {
				delete Modificare;
			}
		}
			  break;
		case 3: {
			cout << endl << "Ati selectat optiune 1.";
			Actiune<SistemIOT, SistemIOT>* sterge = new StergeSenzor;
			try {
				sistemIOT = sterge->executa(sistemIOT);
				cout << endl << "Ati sters cu succes, se va realiza afisarea sistemului!" << endl << endl;
				cout << sistemIOT;
			}
			catch (ExceptieSetter a) {
				cout << a.what();
			}
			catch (ExceptieCustom a)
			{
				cout << a.what();
			}
			catch (ExceptieGetter a) {
				cout << a.what();
			}
			catch (int a) {
				cout << "Erorr " << a << " numarul de senzori de sters a fost introdus gresit." << endl;
			}
			delete sterge;
		}
			  break;
		case 4: {
			cout << endl << "Gestionarea profilelor a luat sfarsit. Va multumesc." << endl;
		}
			  break;
		default: {
			cout << endl << "===Optiune invalida===" << endl << endl;
			optiune = 5;
		}
			   break;
		}
	}
	return 0;
}
