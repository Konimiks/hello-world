#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#include "queue.h"
#include "event.h"
#include "user.h"
#include "alert.h"
#include "test.h"

// callbacks
void alert_master(user_t * receiver, event_t * event);
void alert_common(user_t * receiver, event_t * event);
void alert_fantasy(user_t * receiver, event_t * event);

int main(void) {
	srand(time(NULL));
	cmockaTest();
	puts("\nPress ANY KEY to continue...");
	getch();
	system("cls");

	queue_t * myQueue = queue_new();
	user_t * me = user_new("Me");
	user_t * firstuser = user_new("First");
	user_t * seconduser = user_new("Second");
	user_t * users[] = { me, firstuser, seconduser };
	int usersSize = sizeof(users) / sizeof(users[0]);

	event_t * firstEvent = event_new("10 measurements \\ everything OK (1st event)");
	event_t * secondEvent = event_new("last 5 measurements \\ not everything OK (2d event)");
	event_t * thirdEvent = event_new("last 5 measurements \\ everything NOT OK (3d event)");

	event_addAlertSingle(me, firstEvent, alert_fantasy);
	event_addAlertSingle(me, secondEvent, alert_master);
	event_addAlertSeveral(users, usersSize, thirdEvent, alert_common);
	while (!kbhit()) {
		event_start(firstEvent, secondEvent, thirdEvent, myQueue);
	}

	event_free(firstEvent);
	event_free(secondEvent);
	event_free(thirdEvent);

	for (int i = 0; i < usersSize; i++) {
		user_free(users[i]);
	}
	queue_free(myQueue);

	getch();
	puts("Press ANY KEY to exit the program...");
	getch();
	return 0;
}

void alert_master(user_t * receiver, event_t * event) {
	char * name = user_getName(receiver);
	char * desc = event_getDesc(event);

	printf("I'm %s. I'm a boss, and I know that this event take place:\n", name);
	printf("It's description:\n%s\n", desc);

	free(name);
	free(desc);
}

void alert_common(user_t * receiver, event_t * event) {
	char * name = user_getName(receiver);
	char * desc = event_getDesc(event);

	printf("I'm user %s.\n", name);
	printf("I was notified that some event happened. Description :::\n%s\n", desc);

	free(name);
	free(desc);
}

void alert_fantasy(user_t * receiver, event_t * event){
    char * name = user_getName(receiver);
	char * desc = event_getDesc(event);

    printf("I'm user %s.\n", name);
	printf("It is fantastic call! U r GOD!. Description :::\n%s\n", desc);

	free(name);
	free(desc);
}
