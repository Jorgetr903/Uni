#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define CAPACITY 5
#define CLIENT_TYPE_STR(type) ((type == 2) ? "special" : ((type == 1) ? "  vip  " : "normal"))

int turno_actual_vip=0; //pantalla de vips
int turno_actual=0; //pantalla de no vips
int dispensador_turnos=0;
int dispensador_turnos_vip=0;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condvar = PTHREAD_COND_INITIALIZER;
pthread_cond_t condvar_vip = PTHREAD_COND_INITIALIZER;
pthread_cond_t condvar_especial = PTHREAD_COND_INITIALIZER;

int aforoActual = 0;
int aforoEspecial = 0;
int vipsEsperando = 0;
int especialesEsperando = 0;

struct infoHilo{
    int id, tipo;
};

void enter_normal_client(int id)
{
   int turnoAct;

   pthread_mutex_lock(&m);

   turnoAct = dispensador_turnos++;

   while(turnoAct != turno_actual  || aforoActual == CAPACITY || vipsEsperando > 0 || especialesEsperando > 0 || aforoEspecial > 0)
   {
      pthread_cond_wait(&condvar, &m);
   }

   aforoActual++;
   turno_actual++;

   printf("Client %2d (normal ) entering the disco\n", id);

    if (especialesEsperando>0)
      pthread_cond_broadcast(&condvar_especial);
   else if (vipsEsperando>0)
      pthread_cond_broadcast(&condvar_vip);
   else // Avisar a los normales si hay alguno
      pthread_cond_broadcast(&condvar);

   pthread_mutex_unlock(&m);
}

void enter_vip_client(int id)
{
    int turnoAct;

   pthread_mutex_lock(&m);
   
   turnoAct = dispensador_turnos_vip++;   //le da el siguiente y se suma uno

   vipsEsperando++;
   
   while(turnoAct!= turno_actual_vip || aforoActual == CAPACITY || especialesEsperando > 0 || aforoEspecial > 0)
   {
        pthread_cond_wait(&condvar_vip, &m);
   }

   vipsEsperando--;
   aforoActual++;
   turno_actual_vip++; 

   printf("Client %2d (  vip  ) entering the disco\n", id);

   if (especialesEsperando>0)
      pthread_cond_broadcast(&condvar_especial);
   if (vipsEsperando>0)
      pthread_cond_broadcast(&condvar_vip);
   else // Avisar a los normales si hay alguno
      pthread_cond_broadcast(&condvar);
  
   pthread_mutex_unlock(&m);
}

void enter_especial_client(int id)
{
   pthread_mutex_lock(&m);

   especialesEsperando++;

   printf("Client %2d (special) waiting on the queue\n", id);
   
   while(aforoActual > 0)
   {
        pthread_cond_wait(&condvar_especial, &m);
   }

   especialesEsperando--;
   aforoEspecial++; 

   printf("Client %2d (special) entering the disco\n", id);

   if (especialesEsperando>0)
      pthread_cond_broadcast(&condvar_especial);
   else // Avisar a los normales si hay alguno
      pthread_cond_broadcast(&condvar);
  
   pthread_mutex_unlock(&m);
}

void exit_client(int id, int tipo)
{
   pthread_mutex_lock(&m);

   if (tipo == 2) {
      aforoEspecial--;
   }
   else {
      aforoActual--;
   }

   printf("Client %2d (%s) exits the disco\n", id, CLIENT_TYPE_STR(tipo));
  
   if (especialesEsperando>0)
      pthread_cond_broadcast(&condvar_especial); 
   if (vipsEsperando>0)
     pthread_cond_broadcast(&condvar_vip);
   else // Avisar a los normales si hay alguno
     pthread_cond_broadcast(&condvar);

   
   pthread_mutex_unlock(&m);
}

void dance(int id, int tipo)
{
    printf("Client %2d (%s) dancing in disco\n", id, CLIENT_TYPE_STR(tipo));
    sleep((rand() % 3) + 1);
}


void *client(void *arg)
{
	struct infoHilo *info = (struct infoHilo *) arg;

    printf("Starting client %d\n", info->id);

    if (info->tipo == 1)      
        enter_vip_client(info->id);
        
    else if (info->tipo == 2){
        enter_especial_client(info->id);
    }
    else {
        enter_normal_client(info->id);
    }

    //printf("%d",(info->id));
    dance(info->id, (info->tipo));
    exit_client(info->id, (info->tipo));

	free(info);
	pthread_exit(0);
}

int main(int argc, char *argv[])
{
    FILE *file;
    int numPersonas;
    int persona;

    file = fopen("ejemplo.txt", "r");

    if(file == NULL){
        printf("error al abrir el archivo");
        fclose(file);
        return 1;
    }

    fscanf(file, "%d", &numPersonas);

    pthread_t threads[numPersonas];


    for(int i = 0; i < numPersonas; i++){
        fscanf(file, "%d", &persona);

		struct infoHilo *info = (struct infoHilo *)malloc(sizeof(struct infoHilo));

		info->id = i;
		info->tipo = persona;

        printf("client %d is %s\n", i, CLIENT_TYPE_STR(persona));
        
        pthread_create(&threads[i], NULL, client, info);
    }

    for(int h = 0; h < numPersonas; h++){
        pthread_join(threads[h], NULL);
    }

    fclose(file);

    return 0;
}
