/* 	semval.c	*/
/*	Lekérdi és kiírja a pillanatnyi semaphor értéket.
        Valtozok ertelmezeset lasd a semset.c-ben	*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#define SEMKEY 123456L  /* kulcs a semget-nek; remelem, egyedi */


	int semid,nsems,rtn;
	int semflg;
	struct sembuf sembuf, *sop;
	union semun arg;
	int cmd;

main()
{


	nsems = 1;
	semflg = 00666 | IPC_CREAT;
	semid = semget (SEMKEY, nsems, semflg);
	if (semid < 0 ) {perror(" semget hiba"); exit(0);}
	else printf("\n semid: %d ",semid);
	printf ("\n");

	cmd = GETVAL;	/* E parancsra a semctl visszaadja a currens
			   semaphor erteket. Itt az rtn-be.  */
	rtn = semctl(semid,0, cmd, NULL);

	printf("\n semval: %d ",rtn);
	printf("\n");

}