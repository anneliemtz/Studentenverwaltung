#include <iostream>
using namespace std;

struct node{
    char * name;
    int matr;
    char* lehrveranstaltungen[30];
}; typedef struct node node;

/**
 * Ausgabe eines Students 
 */
void printStudent(node student){
    cout << "\nDie Daten des Studenten: " << endl;
    cout << "-------------------------------" << endl;
    cout << "Matrikelnummer: " << student.matr << endl;
    cout << "Name: " << student.name << endl;
    cout << "Lehrveranstaltungen: " << endl;


    for(int p  = 0; student.lehrveranstaltungen[p] != 0; p++){
        cout << student.lehrveranstaltungen[p] << endl;
    }

    cout << "\n";
}

/**
 * Hilfsfunktionen für das Einlesen von Strings
 */
char readChar(){
    char b;
    cin >> b;
    return b;
}

char* readString(){
    char * cache = new char[100];
    char * string;
    char c;
    int counter = 0;
    do{
        c = readChar();
        cache[counter] = c;
        counter++;
    }while(c != '.');

    string = new char[counter]; // oder counter -1?

    for (int i = 0; i < counter; ++i) {
        string[i] = cache[i];
    }

    //Speicher wird wieder freigegeben
    delete[] cache;
    return string;
}

/**
 * Gibt die Anzahl der Elemnte im Feld zurück
 */
int returnSize(node* feld){

    int anz = 0;
    while (feld[anz].matr != 0 && anz< 1000){
        anz++;
    }

    return anz;
}

/**
 * Binäre Suche
 */
node binSuche(node* feld){

    int gesucht;
    int anz = returnSize(feld);

    cout << "Welche Matrikelnummer?" << endl;
    cin >> gesucht;

    int rechts = anz-1, links = 0;
    int mitte;

    while (links<=rechts){
        mitte = links + ((rechts - links)/2);

        if(feld[mitte].matr == gesucht){
            return feld[mitte];
        }

        else if(gesucht < feld[mitte].matr){
            rechts = mitte-1;
        }

        else if(gesucht > feld[mitte].matr){
            links = mitte+1;
        }
    }

    cout<< "Element nicht gefunden" << endl;
}

/*
 * Einfügen eines neuen Students
 */
void studentEinfuegen(node* feld){
    //Hilfselement
    node neuStudent;

    /**
     * Es wird nach Nachname gefragt
     */
    cout << "Geben Sie den Nachnamen ein" << endl;
    neuStudent.name = readString();

    /**
     * Es wird nach Matrikelnummer gefragt
     */
    int matr;
    cout << "Geben Sie die Matrikelnummer ein" << endl;
    cin >> matr;
    neuStudent.matr = matr;

    //Nullzeiger für leere Veranstaltungen
    for(int i = 0; i<30; i++){
        neuStudent.lehrveranstaltungen[i] = 0;
    }

    /**
     * Es wird nach Veranstaltungen gefragt
     */
    char wahl;
    int veranstaltungsCounter = 0;

    cout << "Wollen Sie eine Lehrveranstaltung hinzufügen? (j/n)" << endl;
    cin >> wahl;

    // Einschränkung: Max 30 Veranstaltungen
    while(wahl == 'j' && veranstaltungsCounter < 30){

        cout << "Geben Sie den namen der Veranstaltung ein" << endl;

        neuStudent.lehrveranstaltungen[veranstaltungsCounter] = readString();

        cout << "Moechten Sie eine weitere Lehrveranstaltung eingeben? (j/n))" << endl;
        cin >> wahl;
    }

    /**
     * Ausgabe des neuen Studenten, Kontrolle
     */
    cout << "Aktueller Student" << endl;
    printStudent(neuStudent);

    /**
     * Hier erfolgt die Zuweisung im Feld
     */
    if(feld[0].matr == 0){ // Fall Leere Liste
        feld[0] = neuStudent;
    }

    else{
        /**
         * Stelle im Feld wird gesucht (sortierung nach Matrikelnummer)
         */
        int j = 0;
        while (feld[j].matr < neuStudent.matr && feld[j].matr!= 0){
            j++;
        }

        /**
         * Max 1000 Elemente
         */
        if(j < 1000){
            feld[j] = neuStudent;
        }
        else
            cout << "Speicherplatz voll. Löschen Sie einen Eintrag." << endl;

    }

    /*
    *Ausgabe aller Studenten im Feld, Kontrolle
    */
    int anz = returnSize(feld); 
    cout<< "\n \n Restliche Elemente: " << endl;
    for (int j = 0; j < anz ; ++j) {
        printStudent(feld[j]);
    }

}

/**
 * Hilfsfunktion für löschen
 */
int binSuche2(node* feld, int gesucht){

    //Länge des Feldes wird bestimmt
    int anz = returnSize(feld);
    int rechts = anz-1, links = 0;
    int mitte;

    while (links<=rechts){
        mitte = links + ((rechts - links)/2);

        if(feld[mitte].matr == gesucht){
            return mitte;
        }

        else if(gesucht < feld[mitte].matr){
            rechts = mitte-1;
        }

        else if(gesucht > feld[mitte].matr){
            links = mitte+1;
        }
    }

    cout<< "Element nicht gefunden" << endl;
}

void loeschen(node* feld){
    int loeschen;
    cout << "Welche Matrikelnummer löschen? " << endl;
    cin >>loeschen;

    //Die Position des zu löschenden Elements wird gesucht
    int pos = binSuche2(feld, loeschen);
    //Anzahl aller Elemente im Feld
    int anz = returnSize(feld);

    /**
    *Gesuchter Feld im Array wird überschrieben und alle Elemente danach um eins nach links verrückt
    */
    for(int i = pos; i <= anz; i++){
        feld[i] = feld[i+1];
    }

    //Anzahl muss neu bestimmt werden 
    anz = returnSize(feld);
    /**
    *Kontrolle
    */
    cout<< "Restliche Elemente: " << endl;
    for (int j = 0; j < anz ; ++j) {
        printStudent(feld[j]);
    }

}

int main() {

    //Die Menge aller Studenten soll in einem Feld von Zeigern mit genau 1000 Elementen verwaltet werden.
    node* feldStudenten = new node[1000];

    //Feld mit Nullzeiger initialisieren
    for(int i = 0; i< 1000; i++){
        feldStudenten[i].matr = 0;
    }

    /**
    * Menü
    */
    char wahl;
    do{
        cout << "Studentenverwaltung" << endl;
        cout << "Auswahlmenü:" << endl;
        cout << "A - Anlegen eines neuen Studenten und der bisher belegten Lehrveranstaltungen" << endl;
        cout << "S - Suchen eines Studenten" << endl;
        cout << "L - Löschen eines Studenten" << endl;
        cout << "E - Programmende" << endl;

        cin >> wahl;

        switch (wahl){
            case 'a': studentEinfuegen(feldStudenten);
                break;

            case 's': printStudent(binSuche(feldStudenten));
                break;

            case 'l': loeschen(feldStudenten);
                break;

            case 'e': return 0;
        }

    }while(wahl != 'e');




    return 0;
}