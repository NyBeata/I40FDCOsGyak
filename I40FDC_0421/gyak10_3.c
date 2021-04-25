#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define SHMKEY 123456L

main()
{
	int shmid;
	key_t key;
	int size=512;
	int shmflg;
	key = SHMKEY;

	/********************1. feladatrész*********************/
	shmflg = 0;
	if ((shmid=shmget( key, size, shmflg)) < 0) {
	   printf("\nSzegmens letrehozasa");
	   shmflg = 00666 | IPC_CREAT;
	   if ((shmid=shmget( key, size, shmflg)) < 0) {
	      perror("\nAz shmget system-call sikertelen!");
	      exit(-1);
	   }
	} else printf("\nMar letezik szegmens");

	/********************2. feladatrész********************/
	struct vmi {
		int  hossz;
		char szoveg[512-sizeof(int)];
	} *segm;

	shmflg = 00666 | SHM_RND;
	segm = (struct vmi *)shmat(shmid, NULL, shmflg);
	if (segm == (void *)-1) {
		perror("Sikertelen attach");
		exit (-1);
	}

	if (strlen(segm->szoveg) > 0)
		printf("\nKiolvasva: %s (%d hosszon)",segm->szoveg,segm->hossz);

	printf("\nMit irjak bele?!\n");
	gets(segm->szoveg);
	printf("\nBeleirva: %s\n",segm->szoveg);
	segm->hossz=strlen(segm->szoveg);

	/********************3. feladatrész********************/
	int i;
	int rtn;
	struct shmid_ds shmid_ds, *buf;
	buf = &shmid_ds;

	printf("\nMit szeretne?\n");
	printf("1 - statusz lekerdezese\n");
	printf("2 - osztott memoria megszuntetese\n");
	printf("3 - kilepes\n");
	scanf("%d", &i);

	switch (i){
        case 1:
            rtn = shmctl(shmid, IPC_STAT, buf);
            printf("\nSzegmens merete: %d", buf->shm_segsz);
            printf("\nUtolso shmop-os proc. pid: %d", buf->shm_lpid);
            break;
        case 2:
            rtn = shmctl(shmid, IPC_RMID, NULL);
            printf("\nSzegmens torolve");
            break;
        case 3:
            exit(0);
	}

	shmdt(segm);

	exit (0);
}
