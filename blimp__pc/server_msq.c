/* server_msq.c */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include "msq_header.h"

static int setup_server( key_t key, int flag ) {
   int res;
   res = msgget( key, flag );
   if( res < 0 ) {
      printf("Serverfehler beim Einrichten Message Queues\n");
      return -1;
   }
   return res;
}

static void verteilen( const char *str, int p ) {
   	int res;
   	server2client s2c;
   	struct id_verwaltung *ptr = id_first;
   	s2c.prioritaet = p;
   	//sprintf(s2c.message,"baum %i", p);
	sprintf(s2c.message,"baum , %s",str);
	res = msgsnd(p, &s2c, MSG_LEN, 0);
   	while(ptr != NULL) {
		//res = msgsnd(ptr->id, &s2c, MSG_LEN, 0);
		if( res < 0 )
			printf("Konnte Nachricht an Client MQ %d nicht zustellen ...\n",ptr->id);
		else
		printf("Nachricht an Client MQ %d zugestellt\n", ptr->id);
		ptr=ptr->next;
	}
}

int main(void) {
   int server_id, res;
   client2server c2s;
   char puffer[MSG_LEN];
   int client_id;

   server_id = setup_server( KEY, PERM  | IPC_CREAT );
   if( server_id < 0 )
      return EXIT_FAILURE;
   printf("Server läuft ...\n");
   while(1) {
      /* Nachricht empfangen */
      printf ("Nachricht empfange \n");
      res = msgrcv( server_id, &c2s, MSG_LEN, 0, 0 );
      if( res < 0 ) {
         printf("Fehler beim empfangen einer Nachricht ... ?\n");
         return EXIT_FAILURE;
      }
      /*Nachricht auswerten */
      printf ("Nachricht auswerten \n");
      if( c2s.prioritaet == 1 ) {
         /* Message Queues aus der Verwaltung entfernen ... */
         sscanf(c2s.message,"%d",&client_id);
         printf("Client MQ %d löschen ...\n",client_id);
         mq_verwaltung_remove( client_id );
      }
      else {
         sscanf(c2s.message,"%d:%s",&client_id, puffer);
         /* client_id eventuell zur Liste hinzufügen */
         	printf("Client MQ %d anmelden ...\n",client_id);
         mq_verwaltung_add( client_id );
         /* Alle anderen User einen Hinweis schicken */
         
	verteilen( puffer, client_id );
      }
   }
   printf(" --- Server-Ende ---\n");
   return EXIT_SUCCESS;
}
