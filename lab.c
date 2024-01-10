/* INF2610 - TP1
/ Matricule 1 : 2247399
/ Matricule 2 : 2141605
*/
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h> 
#include <stdbool.h>

struct Wheel{
    int id;
    bool isRearWheel;
};

struct Wing{
    int id[9];
};

struct Plane{
        char id[10];
        char planeType[10];
        bool isAvailable;
        struct Wheel wheels[7];
        struct Wing wings[2];
};

void createWheels(struct Wheel wheels[7], int id)
{
    for (int i = 0; i < 7; i++)
    {
        struct Wheel tempWheel;
        tempWheel.id = id;
        id++;
        if(i <= 2)
        {
            tempWheel.isRearWheel = false;
        }
        else
        {
            tempWheel.isRearWheel = true;
        }
        wheels[i] = tempWheel;
    }
}

void createPlanes(struct Plane* planes[], char id[], int numberOfPlanes, int idWheel, long idWings)
{
    for (int i = 0; i < numberOfPlanes; i++)
    {
        struct Plane tempPlane;
        for (int j = 0; j < 10; j++)
        {
            tempPlane.id[j] = id[j];
            tempPlane.planeType[j] = *" ";
        }

        tempPlane.isAvailable = true;
        
        *planes[i] = tempPlane;
        
        struct Wheel wheels[7];
        createWheels(wheels, idWheel);

        struct Wing wings[2] = createWings(idWings);

        for (int t = 0; t < 7; t++)
        {
            planes[i]->wheels[t] = wheels[t];
        }

        for (int g = 0; g < 2; g++)
        {
            planes[i]->wings[g] = wings[g];
        }
    }
}

void setAvailability(struct Plane* plane, bool availability)
{
    plane->isAvailable = availability;
}

void getAvailablePlanes(struct Plane* planes[], int numberOfPlanes)
{
    for (int i = 0; i < numberOfPlanes; i++)
    {
        if (planes[i]->isAvailable)
        {
            printf(planes[i]->id);
            printf("\n");
        }
    }
}

int main(int argc, char** argv) {
    printf("Hello\n");
    /* Remove comment once the code is completed for the given section to test */

    int id = 1;

    /* PARTIE 2 - [10 points] */

    /* Create wheel - [2 points] */
    
    struct Wheel wheels[7];
    createWheels(wheels, id);

    /* Create wing - [4 points] */
    
    long longId = 1;
    //struct Wing wings[2] = createWings(longId);
    

    /* Create plane - [4 points] */
    
    char idPlane[10] = {};
    int numberOfPlanes = 3;
    struct Plane* planes = malloc(sizeof(struct Plane) * numberOfPlanes);
    createPlanes(&planes, idPlane, numberOfPlanes, id, longId);
    

    /* PARTIE 3 - [6 points] */

    /* Set availabilities - [1 point] */
    
    struct Plane plane = planes[0];
    setAvailability(&plane, true);
    

    /* Get available planes - [1 point] */
    
    getAvailablePlanes(&planes, numberOfPlanes);
    

    /* Classify planes - [2 points] */
    /*
    Plane plane = planes[1];
    setPlaneType(plane);
    */

    /* Return type specific planes - [2 points] */
    /*
    char planeType[] = "Small";
    getPlanesByType(planes, planeType,numberOfPlanes);
    */
}
