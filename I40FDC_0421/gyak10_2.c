#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define MSGKEY 654321L

struct msgbuf1 {
	long mtype;
	char mtext[512];
} sndbuf, *msgp;

struct msqid_ds ds, *buf;

main()
{
	int msgid;
	key_t key;
	int msgflg;
	int rtn, msgsz;

	key = MSGKEY;
	msgflg = 00666 | IPC_CREAT;
	msgid = msgget( key, msgflg);
 	if ( msgid == -1) {
                perror("\n The msgget system call failed!");
                exit(-1);
        }

	msgp        = &sndbuf;
	msgp->mtype = 1;
 	strcpy(msgp->mtext,"i40fdc");
	msgsz       = strlen(msgp->mtext) + 1;
    rtn = msgsnd(msgid,(struct msgbuf *) msgp, msgsz, msgflg);
	printf("A kikuldott uzenet: %s\n", msgp->mtext);

    buf = &ds;
    msgsz = 20;
    rtn = msgctl(msgid, IPC_STAT,buf);
    int mtype = 0;
	int i;

	printf("\nMit szeretne?\n1 - uzenetek darabszamanak lekerdezese\n2 - egy uzenet kiolvasasa\n3 - osszes uzenet kiolvasasa\n4 - uzenetsor megszuntetese\n5 - kilepes\n");
	scanf("%d", &i);
	switch (i){
        case 1:
            printf("Az uzenetek szama: %d\n",buf->msg_qnum);
            exit(0);
        case 2:
            printf("Az egyik uzenet: %s\n", msgp->mtext);
            exit(0);
        case 3:
            while(buf->msg_qnum){
                rtn= msgrcv(msgid,(struct msgbuf *)msgp, msgsz, mtype, msgflg);
                printf("Az rtn: %d, a vett uzenet: %s\n", rtn, msgp->mtext);
                rtn = msgctl(msgid,IPC_STAT,buf);
            }
            exit(0);
        case 4:
            rtn = msgctl(msgid, IPC_RMID, NULL);
            printf("Megszuntetve\n");
            exit(0);
        case 5:
            exit(0);
	}
}
