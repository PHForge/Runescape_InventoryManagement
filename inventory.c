#include <stdio.h>
#include <stdlib.h>
#include "inventory.h"
#include "utils.h"

// Creates an empty inventory
Inventory* create_inventory(float max_weight) {
    Inventory* inv = malloc(sizeof(Inventory)); // Allocate memory for the inventory
    if (inv) {
        inv->head = NULL; // Initialize the head of the linked list to NULL
        inv->total_weight = 0.0f; // Initialize total weight to 0
        inv->phgold = 100; // Initialize PHGold to a default value (e.g., 100)
        inv->max_weight = max_weight; // Set the maximum weight for the inventory
    }
    return inv;
}

// Adds an item to the inventory
void add_item(Inventory* inv, Item* item, int language) { 
    if (!inv || !item) return;
    if (inv->total_weight + item->weight > inv->max_weight) { // Check if adding the item exceeds the maximum weight
        printf("%s\n", get_message(MSG_INVENTORY_FULL, language));
        free_item(item);
        return;
    }
    InventoryNode* node = malloc(sizeof(InventoryNode)); // Allocate memory for the new node
    if (node) {
        node->item = item;
        node->next = inv->head;
        inv->head = node;
        inv->total_weight += item->weight;
    } else {
        free_item(item);
    }
}

// Displays all items
void display_inventory(const Inventory* inv, int language) {
    if (!inv || !inv->head) { // Check if the inventory is empty
        printf("\n/!\\ %s /!\\\n", get_message(MSG_INVENTORY_EMPTY, language));
        return;
    }

    printf("\n=== %s ===\n\n", get_message(MSG_BROWSE, language));
    InventoryNode* current = inv->head; // Start from the head of the linked list
    while (current) { // Traverse the linked list
        print_item(current->item, language);
        printf("\n");
        current = current->next;
    }
    printf("%s: %.1f/%.1f kg\n", get_message(MSG_ACTUAL_BAG_WEIGHT, language), inv->total_weight, inv->max_weight);
    printf("%s: %d PHGold\n", get_message(MSG_WALLET, language), inv->phgold);
}

// Frees the inventory
void free_inventory(Inventory* inv) {
    InventoryNode* current = inv->head; 
    while (current) {
        InventoryNode* next = current->next; 
        free_item(current->item);
        current->item = NULL; // Avoid dangling pointer
        free(current);
        current = next;
    }
    free(inv);
}