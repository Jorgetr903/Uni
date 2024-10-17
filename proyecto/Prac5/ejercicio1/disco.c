#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define CAPACITY 5
#define VIPSTR(vip) ((vip) ? "  vip  " : "not vip")

int turno_actual_vip=0; //pantalla de vips
int turno_actual=0; //pantalla de no vips
int dispensador_turnos=0;
int dispensador_turnos_vip=0;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condvar = PTHREAD_COND_INITIALIZER;
pthread_cond_t condvar_vip = PTHREAD_COND_INITIALIZER;

int aforoActual = 0;
int vipsEsperando = 0;

struct infoHilo{
    int id, prio;
};

void enter_normal_client(int id)
{
   int turnoAct;

   pthread_mutex_lock(&m);

   turnoAct = dispensador_turnos++;

   while(turnoAct != turno_actual  || aforoActual == CAPACITY || vipsEsperando > 0)
   {
      pthread_cond_wait(&condvar, &m);
   }

   printf("Vips esperando: %d \n", vipsEsperando);
   aforoActual++;
   turno_actual++;

   if (vipsEsperando>0)
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
   
   while(turnoAct!= turno_actual_vip || aforoActual == CAPACITY)
   {
        pthread_cond_wait(&condvar_vip, &m);
   }

   vipsEsperando--;
  

   //ENTRA A LA DISCOTECA
   aforoActual++;

   //SE ATENDERÁ AL SIGUIENTE
   turno_actual_vip++; 

   //Si hay vips esperando avisar solo vip
   if (vipsEsperando>0)
      pthread_cond_broadcast(&condvar_vip);
   else // Avisar a los normales si hay alguno
      pthread_cond_broadcast(&condvar);
  
   pthread_mutex_unlock(&m);
}

void exit_client(int id, int isvip)
{
   pthread_mutex_lock(&m);

   aforoActual--;

   printf("Client %2d (%s) exits disco\n", id, VIPSTR(isvip));
  
  //Si hay vips esperando avisar solo vip 
   if (vipsEsperando>0)
     pthread_cond_broadcast(&condvar_vip);
   else // Avisar a los normales si hay alguno
     pthread_cond_broadcast(&condvar);

   
   pthread_mutex_unlock(&m);
}

void dance(int id, int isvip)
{
    printf("Client %2d (%s) dancing in disco\n", id, VIPSTR(isvip));
    sleep((rand() % 3) + 1);
}


void *client(void *arg)
{
	struct infoHilo *info = (struct infoHilo *) arg;

    if (info->prio)
        //printf("arg1");
        
        enter_vip_client(info->id);
        
    else{
        enter_normal_client(info->id);
    }


    //printf("%d",(info->id));
    dance(info->id, (info->prio));
    exit_client(info->id, (info->prio));

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
		info->prio = persona;

        
        pthread_create(&threads[i], NULL, client, info);
    }

    for(int h = 0; h < numPersonas; h++){
        pthread_join(threads[h], NULL);
    }

    fclose(file);

    return 0;
}
