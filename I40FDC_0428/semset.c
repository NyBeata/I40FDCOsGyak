/*	semset.c	*/
/*	Kreál/azonosít
	semaphor készletet, benne egyetlen semaphor-t. 
	Bekéri stdin-rôl a kezdô értéket, és ezt beállítja.

	(Megjegyzem, a többi programocska ugyanezen semaphor 
	set-et azonosítja, hasonló semget() hívásokkal.)
*/
	
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#define SEMKEY 123456L  /* kulcs a semget-nek; remelem, egyedi */

	int semid,	/* semaphor set azonosito */
	    nsems,	/* semaphorok szama a keszletben */
	    semnum,	/* semapho szam a set-en belul */
	    rtn;	/* visszateresi ertek */

	int semflg;	/* flag */
	struct sembuf sembuf, *sop; 
	union semun arg; /* union a semctl parancs argumentumnak */
	int cmd;	/* semctl-nek szolo parancs */

main()
{


	nsems = 1;	/* egyetlen semaphore a set-ben */
	semflg = 00666 | IPC_CREAT;
	semid = semget (SEMKEY, nsems, semflg);
	if (semid < 0 ) {perror(" semget hiba"); exit(0);}
	else printf("\n semid: %d ",semid);
	printf ("\n kerem a semval erteket ");

	semnum = 0;	/* 0-i semaphort azonositom */

	cmd = SETVAL;	/* allitsd be a semaphor erteket */
	scanf("%d",&arg.val);
	rtn = semctl(semid,semnum, cmd, arg); /* a semid-vel azonositott
					    set 0-ik semaphorat ! */

	printf("\n set  rtn: %d ,semval: %d ",rtn,arg.val);
	printf("\n");

}