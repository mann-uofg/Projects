#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct user {
    char name[50];
    double latitude;
    double longitude;
    double altitude;
    double time;
};

void scanUser(struct user *u) {
    printf("Enter name: ");
    scanf("%s", u->name);

    printf("Enter latitude: ");
    scanf("%lf", &(u->latitude));

    printf("Enter longitude: ");
    scanf("%lf", &(u->longitude));

    printf("Enter altitude: ");
    scanf("%lf", &(u->altitude));

    printf("Enter time: ");
    scanf("%lf", &(u->time));
}

void readUsersFromFile(struct user *users, int *numUsers, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    fscanf(file, "%d", numUsers);

    for (int i = 0; i < *numUsers; ++i) {
        fscanf(file, "%lf", &users[i].latitude);
        fscanf(file, "%lf", &users[i].longitude);
        fscanf(file, "%lf", &users[i].altitude);
        fscanf(file, "%lf", &users[i].time);
        fscanf(file, "%s", users[i].name);
    }

    fclose(file);
}

void calculateDistances(struct user *ourUser, struct user *otherUsers, double *distances, int numUsers) {
    for (int i = 0; i < numUsers; ++i) {
        distances[i] = sqrt(pow(ourUser->latitude - otherUsers[i].latitude, 2) +
                            pow(ourUser->longitude - otherUsers[i].longitude, 2) +
                            pow(ourUser->altitude - otherUsers[i].altitude, 2));
    }
}

struct user findClosestUser(struct user *ourUser, struct user *otherUsers, double *distances, int numUsers) {
    int minIndex = 0;
    for (int i = 1; i < numUsers; ++i) {
        if (distances[i] < distances[minIndex]) {
            minIndex = i;
        }
    }
    return otherUsers[minIndex];
}

int main() {
    struct user ourUser;
    int numOtherUsers;

    printf("\nEnter data for our user:\n");
    scanUser(&ourUser);

    char filename[100];
    printf("Enter the path of the input file: ");
    scanf("%s", filename);

    struct user otherUsers[10];
    double distances[10];

    readUsersFromFile(otherUsers, &numOtherUsers, filename);
    calculateDistances(&ourUser, otherUsers, distances, numOtherUsers);

    printf("\nReference user:\n");
    printf("User Me:\n");
    printf("Latitude   %.2lf\n", ourUser.latitude);
    printf("Longitude  %.2lf\n", ourUser.longitude);
    printf("Altitude   %.2lf\n", ourUser.altitude);

    printf("\nList of other users:\n");
    for (int i = 0; i < numOtherUsers; ++i) {
        printf("User %s:\n", otherUsers[i].name);
        printf("Latitude  %.2lf\n", otherUsers[i].latitude);
        printf("Longitude %.2lf\n", otherUsers[i].longitude);
        printf("Altitude  %.2lf\n", otherUsers[i].altitude);
    }

    printf("\nActual distances from our user were:\n");
    for (int i = 0; i < numOtherUsers; ++i) {
        printf("User number: %d at distance %.6lf named %s\n", i, distances[i], otherUsers[i].name);
    }

    struct user closestUser = findClosestUser(&ourUser, otherUsers, distances, numOtherUsers);

    printf("\nNearest user to reference user:\n");
    printf("User %s:\n", closestUser.name);
    printf("Latitude  %.2lf\n", closestUser.latitude);
    printf("Longitude %.2lf\n", closestUser.longitude);
    printf("Altitude  %.2lf\n\n", closestUser.altitude);

    return 0;
}
