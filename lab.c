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
#include <string.h>

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

void createWheels(struct Wheel* wheels, int id)
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



void populateWingAttributes( struct Wing* wing, int id ){
    int mod = 0;
    int num = id;
    int idx = 8;
    int* arr = (int*) malloc(9 * sizeof(int));


    while(idx >= 0) {
        mod = num % 10; 
        arr[idx] = mod;
        idx--;
        num = num / 10;    
    }

    for (int i = 0; i < 9; i++) { 
        wing->id[i] = arr[i]; 
    } 
}

struct Wing* createWings(long id) {
    struct Wing* wings = (struct Wing*) malloc(2 * sizeof(struct Wing));

    populateWingAttributes(&wings[0], id);
    populateWingAttributes(&wings[1], id+1);

    return wings;
}


void createPlanes(struct Plane planes[], char id[], int numberOfPlanes, int idWheel, long idWings)
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
        
        planes[i] = tempPlane;
        
        struct Wheel wheels[7];
        createWheels(wheels, idWheel);

        struct Wing* wings = createWings(idWings);

        for (int t = 0; t < 7; t++)
        {
            planes[i].wheels[t] = wheels[t];
        }

        for (int g = 0; g < 2; g++)
        {
            planes[i].wings[g] = wings[g];
        }
    }
}

void setAvailability(struct Plane* plane, bool availability)
{
    plane->isAvailable = availability;
}

void getAvailablePlanes(struct Plane* planes, int numberOfPlanes)
{
    for (int i = 0; i < numberOfPlanes; i++)
    {
        if (planes[i].isAvailable)
        {
            printf("%d", planes[i].id[9]);
            printf("\n");
        }
        else
        {
            continue;
        }
    }
}

void setPlaneType(struct Plane* plane) {

    char small[5] = "Small";
    char medium[6] = "Medium";
    char large[5] = "Large";

    int identifier = 0;
    for (int i = 0; i < 9; i++) {
        identifier = identifier * 10 + plane->wings[0].id[i];
    }

    // printf("OK");
    int mod = identifier % 9;

    if (mod <= 2) {
        for(int i = 0; i<5; i++) {
            plane->planeType[i] = small[i];
        }
        printf("Small\n");

    } else if (mod <= 6) {
        for(int i = 0; i<6; i++) {
            plane->planeType[i] = medium[i];
        }
        printf("Medium\n");

    } else { 
        for(int i = 0; i<5; i++) {
            plane->planeType[i] = large[i];
        }
        printf("Large\n");
    }
}

struct Plane* getPlanesByType(struct Plane* planes, char* type, int numberOfPlanes, int* count) {
    
    int matchCount = 0;
    for (int i = 0; i < numberOfPlanes; i++) {
        if (strcmp(planes[i].planeType, type) == 0) {
            matchCount++;
        }
    }

    struct Plane* matchingPlanes = malloc(sizeof(struct Plane) * matchCount);

    int j = 0;
    for (int i = 0; i < numberOfPlanes; i++) {
        if (strcmp(planes[i].planeType, type) == 0) {
            matchingPlanes[j++] = planes[i];
        }
    }

    *count = matchCount;
    return matchingPlanes;
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
    struct Wing* wings = createWings(longId);
    

    /* Create plane - [4 points] */
    
    char idPlane[10] = {0,0,0,0,0,0,0,0,0,1};
    int numberOfPlanes = 3;
    struct Plane* planes = malloc(sizeof(struct Plane) * numberOfPlanes);
    createPlanes(planes, idPlane, numberOfPlanes, id, longId);
    

    /* PARTIE 3 - [6 points] */

    /* Set availabilities - [1 point] */
    
    struct Plane plane = planes[0];
    setAvailability(planes, true);
    

    /* Get available planes - [1 point] */
    
    getAvailablePlanes(planes, numberOfPlanes);
    

    /* Classify planes - [2 points] */
    
    // struct Plane plane = planes[1];
    setPlaneType(&planes[1]);
    

    /* Return type specific planes - [2 points] */
    
    char planeType[] = "Small";
    int numMatchingPlanes = 0;
    getPlanesByType(planes, planeType, numberOfPlanes, &numMatchingPlanes);
    
}
