// ==================================================================================
//       Include file per gestione I/O simulato su ADLINK 9112
//	Versione 0.90  Novembre 2014 , per Compilatore Visual Studio 2012
//
//  N.B. Non sono ancora state ritestate le funzioni di I/O Analogico
//  	Realizzata dai docenti di elettronica dell I.T.I.S. F. Corni 
// ==================================================================================

#ifndef __DASKSIMUL1_H
  #define __DASKSIMUL1_H

#define PCI_9112        (22)

#define IN_PORT_A   (0x100)
#define IN_PORT_B   (0x101)
#define IN_PORT_AD0 (0x102)
#define IN_PORT_AD1 (0x103)
#define IN_PORT_SYNC (0x104)

#define OUT_PORT_A   (0x100)
#define OUT_PORT_B   (0x101)
#define OUT_PORT_DA0 (0x102)
#define OUT_PORT_DA1 (0x103)
#define OUT_PORT_BCD (0x104)



// Ridefinizione delle porte di input e di output

#define _PORT_DEFS

extern void outport(int portid, unsigned int value);
extern void outportb(int portid, unsigned char value);
extern unsigned int inport(int portid);
extern unsigned char inportb(int portid);
extern int init_io(void);

extern void DI_ReadPort( unsigned short CardNumber, unsigned short Port, unsigned long *value);
extern void DO_WritePort (unsigned short CardNumber, unsigned short port, unsigned long value);
extern void DI_ReadLine (unsigned short CardNumber, unsigned short Port, unsigned short Line, unsigned short *state);
extern void DO_WriteLine (unsigned short CardNumber, unsigned short Port, unsigned short Line, unsigned short value);
extern void AI_ReadChannel (unsigned short CardNumber, unsigned short Channel, unsigned short AdRange, unsigned short *value);
extern void AO_WriteChannel (unsigned short CardNumber, unsigned short Channel, short Value);
extern short Register_Card (unsigned short CardType, unsigned short CardNumber);
extern void Release_Card  (unsigned short CardNumber);

#endif


