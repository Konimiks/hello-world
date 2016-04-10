#include <stdio.h>
#include <string.h>
#include "workers.h"

int main() {
    worker workers[5];
    workers_fill_array(workers, 5);
    for(int i = 0; i < 5; i++)
    {
        printf("name : %s\n", workers[i].name);
        printf("surname : %s\n", workers[i].surname);
        printf("company (post : %s) : %s\n", workers[i].com.post, workers[i].com.name);
        printf("Working years : %i\n",workers[i].workingyears);
        printf("salary : ");
        printf("amount : %.2f\t",workers[i].sal.amount);
        printf("valuta : %s\n",workers[i].sal.valuta);
        printf("birthdate : %s\n",ctime(&(workers[i].birthdate)));
    }
	return 0;
}
