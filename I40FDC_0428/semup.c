/* 	semup.c	 */
/*	Ez is futtatható program, a sembuf.sem_op=1 értékkel
	inkrementálja a semaphor-t.
	A deklaraciokat a semset.c-ben magyarazzuk, ill. a
	beleertett file-okbol nezhetok! 	*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#define SEMKEY 123456L  /* kulcs a semget-nek; remelem, egyedi */

	int semid,nsems,rtn;
	unsigned nsops;	/* semop-ban ezzel adjuk meg, hany semaphore
			   strukturaval foglakozzon */
	int semflg;
	struct sembuf sembuf, *sop;


main()
{


	nsems = 1;	/* Egy semaphore legyen */
	semflg = 00666 | IPC_CREAT;
	semid = semget (SEMKEY, nsems, semflg);
	if (semid < 0 ) {perror(" semget hiba"); exit(0);}
	else printf("\n semid: %d ",semid);
	printf ("\n");
	
	nsops = 1;		/* Egy operacio van */
	sembuf.sem_num = 0;	/* A 0-ik semaphor-ral foglakozunk */
	sembuf.sem_op = 1;	/* Inkrementaciot kerunk! */
	sembuf.sem_flg = 0666;	/* Flag beallitas */
	sop = &sembuf;		/* Igy keri a semop az argumentumot */
	rtn = semop(semid, sop, nsops);
		/* 0-val visszatero semop sikeres. */
	printf("\n up rtn: %d ",rtn);
	printf("\n");

}