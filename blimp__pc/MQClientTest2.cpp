#include "MessageQueueClient.cpp"




int main () {
	MessageQueueClient  mqc;
	char *cTest = "12345";
	string sRec = "";
	//while (1) {
	mqc.StartMessageQueueClient(123L);
	mqc.SendMessage (cTest, 5);
	usleep(50);
	cTest = "12345 baum";
	mqc.SendMessage (cTest, 10);
	usleep(50);
	
	cTest = "12346 moe";
	mqc.SendMessage (cTest, 9);
	usleep(50);
	
	cTest = "12347 oeoep";
	mqc.SendMessage (cTest, 11);
	usleep(50);
	
	mqc.EndMessageQueueClient ();
	usleep(50);
//	}
}
