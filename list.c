struct osoba {
    string imie;
    string nazwisko;
    int wiek;
    osoba *nastepna;    // wskaźnik na następny element
    osoba();            // konstruktor
};
 
osoba::osoba() {
    nastepna = 0;       // konstruktor
}
 
struct lista {
    osoba *pierwsza;  // wskaźnik na początek listy
    void dodaj_osobe (string imie, string nazwisko, int wiek);
    void usun_osobe (int nr);
    void wyswietl_liste ();
    lista();
};
void lista::dodaj_osobe(string imie, string nazwisko, int wiek)
{
    osoba *nowa = new osoba;    // tworzy nowy element listy
 
    // wypełniamy naszymi danymi
    nowa->imie = imie;
    nowa->nazwisko = nazwisko;
    nowa->wiek = wiek;
 
    if (pierwsza==0) // sprawdzamy czy to pierwszy element listy
    {
        // jeżeli tak to nowy element jest teraz początkiem listy
        pierwsza = nowa;
    }
 
    else
    {
        // w przeciwnym wypadku wędrujemy na koniec listy
        osoba *temp = pierwsza;
 
        while (temp->nastepna)
        {
            // znajdujemy wskaźnik na ostatni element
            temp = temp->nastepna;
        }
 
        temp->nastepna = nowa;  // ostatni element wskazuje na nasz nowy
        nowa->nastepna = 0;     // ostatni nie wskazuje na nic
    }
}
