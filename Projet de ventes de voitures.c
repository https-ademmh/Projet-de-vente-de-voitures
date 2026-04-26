#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct CarNode {
    int id;
    char brand[30];
    char model[30];
    int year;
    float price;
    int available;
    struct CarNode* next;
} CarNode;

typedef struct SaleNode {
    int id;
    int car_id;
    char buyer[30];
    float price;
    struct SaleNode* next;
} SaleNode;

CarNode* cars = NULL;
SaleNode* sales = NULL;
int car_count = 0, sale_count = 0;

CarNode* create_car_node(int id, char* brand, char* model, int year, float price) {
    CarNode* node = (CarNode*)malloc(sizeof(CarNode));
    node->id = id;
    strcpy(node->brand, brand);
    strcpy(node->model, model);
    node->year = year;
    node->price = price;
    node->available = 1;
    node->next = NULL;
    return node;
}

SaleNode* create_sale_node(int id, int car_id, char* buyer, float price) {
    SaleNode* node = (SaleNode*)malloc(sizeof(SaleNode));
    node->id = id;
    node->car_id = car_id;
    strcpy(node->buyer, buyer);
    node->price = price;
    node->next = NULL;
    return node;
}

void add_car() {
    CarNode c;
    c.id = car_count + 1;
    printf("Marque: "); scanf("%s", c.brand);
    printf("Modele: "); scanf("%s", c.model);
    printf("Annee: ");  scanf("%d", &c.year);
    printf("Prix: "); scanf("%f", &c.price);
    
    CarNode* new_node = create_car_node(c.id, c.brand, c.model, c.year, c.price);
    
    if (cars == NULL) {
        cars = new_node;
    } else {
        CarNode* temp = cars;
        while (temp->next != NULL) temp = temp->next;
        temp->next = new_node;
    }
    car_count++;
    printf("Voiture ajoutee.\n");
}

void delete_car() {
    int id;
    printf("ID de la voiture a supprimer: "); scanf("%d", &id);
    
    CarNode* temp = cars;
    CarNode* prev = NULL;
    
    while (temp != NULL) {
        if (temp->id == id) {
            if (prev == NULL) {
                cars = temp->next;
            } else {
                prev->next = temp->next;
            }
            free(temp);
            car_count--;
            printf("Supprimee.\n");
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("Non trouvee.\n");
}

void list_cars() {
    if (car_count == 0) { printf("Aucune voiture.\n"); return; }
    printf("\n%-5s %-15s %-15s %-6s %-10s\n", "ID", "Marque", "Modele", "Annee", "Prix");
    CarNode* temp = cars;
    while (temp != NULL) {
        if (temp->available)
            printf("%-5d %-15s %-15s %-6d %.2f\n", temp->id, temp->brand, temp->model, temp->year, temp->price);
        temp = temp->next;
    }
}

void view_sales() {
    if (sale_count == 0) { printf("Aucune vente.\n"); return; }
    printf("\n%-5s %-10s %-15s %-10s\n", "ID", "ID Voiture", "Acheteur", "Prix");
    SaleNode* temp = sales;
    while (temp != NULL) {
        printf("%-5d %-10d %-15s %.2f\n", temp->id, temp->car_id, temp->buyer, temp->price);
        temp = temp->next;
    }
}

void admin_menu() {
    int choice;
    do {
        printf("\n--- ADMIN ---\n1. Voir les voitures\n2. Ajouter une voiture\n3. Supprimer une voiture\n4. Voir les ventes\n0. Retour\nChoix: ");
        scanf("%d", &choice);
        if (choice == 1) list_cars();
        else if (choice == 2) add_car();
        else if (choice == 3) delete_car();
        else if (choice == 4) view_sales();
    } while (choice != 0);
}

void buy_car() {
    int id; char buyer[30];
    list_cars();
    printf("ID de la voiture a acheter: "); scanf("%d", &id);
    
    CarNode* temp = cars;
    while (temp != NULL) {
        if (temp->id == id && temp->available) {
            printf("Votre nom: "); scanf("%s", buyer);
            temp->available = 0;
            
            SaleNode* new_sale = create_sale_node(sale_count + 1, id, buyer, temp->price);
            
            if (sales == NULL) {
                sales = new_sale;
            } else {
                SaleNode* t = sales;
                while (t->next != NULL) t = t->next;
                t->next = new_sale;
            }
            sale_count++;
            printf("Achat reussi! Total: %.2f\n", temp->price);
            return;
        }
        temp = temp->next;
    }
    printf("Voiture non disponible.\n");
}

void client_menu() {
    int choice;
    do {
        printf("\n--- CLIENT ---\n1. Voir les voitures\n2. Acheter une voiture\n0. Retour\nChoix: ");
        scanf("%d", &choice);
        if (choice == 1) list_cars();
        else if (choice == 2) buy_car();
    } while (choice != 0);
}

void init_cars() {
    cars = create_car_node(1, "Toyota", "Corolla", 2023, 20000);
    CarNode* t = cars;
    t->next = create_car_node(2, "Honda", "Civic", 2022, 22000);
    t = t->next;
    t->next = create_car_node(3, "Ford", "Mustang", 2024, 35000);
    t = t->next;
    t->next = create_car_node(4, "Tesla", "Model 3", 2023, 45000);
    car_count = 4;
}

int main() {
    init_cars();

    int choice;
    do {
        printf("\n=== VENTE DE VOITURES ===\n1. Client\n2. Admin\n0. Quitter\nChoix: ");
        scanf("%d", &choice);
        if (choice == 1) client_menu();
        else if (choice == 2) admin_menu();
    } while (choice != 0);
    return 0;
}