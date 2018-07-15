// ------------------------------------------------------------------------
//          Programma demo della funzioni di I/O della ADLINK9112
//         Versione 0.90  (5 Nov 2014)   per Compilatore Visual Studio2012
//         prof. Vicenzi Giuliano
// ------------------------------------------------------------------------


#include <stdio.h>
#include <conio.h>
#include <Windows.h>     //necessario per poter eseguire la Sleep()

#include "dask64Simul2012.h"    //necessario x gestione ADLINK9112
                          // è INDISPENSABILE aggiungere anche come 
                          // file di risorse: PCI-Dask2012Simul.LIB

// Nel caso si desideri passare alla versione 'HARDWARE' occorre 
// #include "dask64HW2012.h"    //necessario x gestione ADLINK9112
// e aggiungere come file di risorse PCI-Dask2012HW.LIB


void SuperCar( short card, int Tempo_ms); // accende led in sequenza con SuperCar
void SuperCar2( short card, int Tempo_ms);



void main(void)
{
	short card=0;       //codice scheda rilevata; se <0 significa errore scheda ADLINK9112
    short card_num=0;   // numero della scheda da attivare 0..N , se inserite una sola scheda 9112 usare:0
	unsigned long stato_port;
	int x;
    unsigned short stato_line;  

	printf ("Programma prototipo per gestione I/O simulati in VisualStudio 2012");

	// attivazione della scheda I/O (simulata)
	if ((card=Register_Card (PCI_9112, card_num)) <0 ) {
		printf("Register_Card error=%d\n", card);
		getchar();
		return;
	}


	printf("\ninizio esecuzione SuperCar");

	printf ("\nTempo 250ms");  
	SuperCar( card, 250);       //esegue funzione SuperCar con tempo 250ms per led

	printf ("\nTempo 100ms");
	SuperCar( card, 100);

    DO_WritePort(card,0,0x00);  // spengo tutte le uscite

	printf("\n ======== inizio esecuzione SuperCar2 ===========");
	
    printf ("\nTempo 250ms");
	SuperCar2( card, 250);      //esegue funzione SuperCar con tempo 250ms per led

	printf ("\nTempo 100ms");
    SuperCar2( card, 100);

	printf("\ninizio test interruttore 3");
    DI_ReadLine(card,0,3,&stato_line);  // leggo lo stato del bit 3 in input
    DO_WriteLine(card,0,3,stato_line);  // scrivo lo stato del bit 3 in output
    
    Sleep(2000);    
    printf("\n============ inizio test ON/OFF interruttori =================");
    printf("\n\n (batti  un tasto per terminare il programma)");
    while (!_kbhit()) {
		DI_ReadPort(card,0,&stato_port);  // leggo tutt interruttori	        
		DO_WritePort(card,0,stato_port);  // accendo tutte le uscite
		Sleep(100);
	}
    
    
	Release_Card(card);
    
}  // fine main()


// ogni LED resta acceso per un tempo in ms pari al valore di Tempo_ms
// <input> card: numero della scheda da utilizzare 
// <input> Tempo_ms: numero ni ms di accensione di ogni singolo led
void SuperCar( short card, int Tempo_ms)
{
	int Conta; // contatore generico 
	unsigned char ByteOut=1;

	for (Conta=0 ; Conta <8 ; Conta++ ){
		DO_WritePort(card,0,ByteOut);
		Sleep(Tempo_ms);
		ByteOut=ByteOut << 1;  //shift a sinistra di una posizione i bit
	}

} // fine SuperCar()

// simile funzionalità alla SuperCar(), ma utilizza DO_WriteLine()
// <input> card: numero della scheda da utilizzare 
// <input> Tempo_ms: numero ni ms di accensione di ogni singolo led
void SuperCar2( short card, int Tempo_ms) 
{
	int Conta; // contatore generico 
	unsigned char ByteOut=1;        

	for (Conta=0 ; Conta <8 ; Conta++ ){
		DO_WriteLine(card,0,Conta,1);	// accendo il singolo bit
		Sleep(Tempo_ms);
		DO_WriteLine(card,0,Conta,0);  //spengo il bit appena acceso        
	}

} //fine SuperCar2()


