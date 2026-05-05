#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct Food {
    char name[50];
    float price;
};

struct Cart {
    char name[50];
    int quantity;
    float totalPrice;
};

// 50 Food Items
struct Food menu[] = {
{"Kacchi Biryani",250},{"Tehari",180},{"Morog Polao",220},{"Chicken Biryani",200},
{"Beef Bhuna",220},{"Chicken Roast",200},{"Hilsha Curry",300},{"Rui Fish",180},
{"Pabda Fish",200},{"Chingri Malai Curry",350},{"Dal",60},{"Mixed Vegetables",80},
{"Egg Curry",100},{"Paratha",20},{"Naan",40},{"Roti",15},{"Khichuri",120},
{"Fried Rice",150},{"Chicken Fry",180},{"Beef Steak",300},{"Burger",150},
{"Pizza",400},{"Sandwich",120},{"French Fries",100},{"Shawarma",150},
{"Fuchka",80},{"Chotpoti",70},{"Jhalmuri",50},{"Faluda",120},{"Borhani",60},
{"Lassi",100},{"Cold Coffee",150},{"Tea",20},{"Coffee",50},{"Mineral Water",30},
{"Soft Drinks",40},{"Ice Cream",80},{"Cake",200},{"Pastry",100},{"Donut",90},
{"Chicken Soup",120},{"Beef Soup",140},{"Vegetable Soup",100},{"Noodles",130},
{"Pasta",180},{"Grill Chicken",250},{"BBQ Chicken",300},{"Beef Kebab",200},
{"Chicken Kebab",180},{"Egg Sandwich",90}
};

struct Cart cart[100];
int cartCount = 0;

// Login Save
void saveLogin(char phone[], char password[]) {
    FILE *fp = fopen("login.txt", "w");
    fprintf(fp, "%s %s", phone, password);
    fclose(fp);
}

// Login
int login() {
    char phone[20], password[20];

    printf("Phone (11 digit): ");
    scanf("%s", phone);

    printf("Password: ");
    scanf("%s", password);

    if(strlen(phone) != 11 || strlen(password)==0) {
        printf("Invalid login!\n");
        return 0;
    }

    saveLogin(phone, password);
    printf("Login Successful!\n");
    return 1;
}

// Show Menu
void showMenu() {
    printf("\n--- MENU ---\n");
    for(int i=0;i<50;i++) {
        printf("%d. %s - %.2f Tk\n", i+1, menu[i].name, menu[i].price);
    }
}

// Search
void searchItem() {
    char search[50];
    printf("Search: ");
    scanf(" %[^\n]", search);

    for(int i=0;i<50;i++) {
        if(strstr(menu[i].name, search)) {
            printf("Found: %s - %.2f Tk\n", menu[i].name, menu[i].price);
        }
    }
}

// Add to Cart
void addToCart() {
    int choice, qty;

    showMenu();
    printf("Choose item: ");
    scanf("%d", &choice);

    if(choice < 1 || choice > 50) {
        printf("Invalid item!\n");
        return;
    }

    printf("Quantity (1-100): ");
    scanf("%d", &qty);

    if(qty < 1 || qty > 100) {
        printf("⚠ Quantity must be 1-100!\n");
        return;
    }

    strcpy(cart[cartCount].name, menu[choice-1].name);
    cart[cartCount].quantity = qty;
    cart[cartCount].totalPrice = qty * menu[choice-1].price;

    cartCount++;
    printf("Added to cart!\n");
}

// Remove
void removeItem() {
    int index;
    printf("Remove item no: ");
    scanf("%d", &index);

    if(index < 1 || index > cartCount) {
        printf("Invalid!\n");
        return;
    }

    for(int i=index-1;i<cartCount-1;i++) {
        cart[i] = cart[i+1];
    }

    cartCount--;
    printf("Removed!\n");
}

// Show Cart
float showCart() {
    float total = 0;

    printf("\n--- CART ---\n");
    for(int i=0;i<cartCount;i++) {
        printf("%d. %s x%d = %.2f Tk\n",
        i+1, cart[i].name, cart[i].quantity, cart[i].totalPrice);
        total += cart[i].totalPrice;
    }

    printf("Total: %.2f Tk\n", total);
    return total;
}

// Save History
void saveHistory() {
    FILE *fp = fopen("history.txt", "a");

    time_t t = time(NULL);
    fprintf(fp, "\nTime: %s", ctime(&t));

    for(int i=0;i<cartCount;i++) {
        fprintf(fp, "%s x%d\n", cart[i].name, cart[i].quantity);
    }

    fclose(fp);
}

// Payment
int payment(float total) {
    int method;
    printf("\n1. Cash\n2. Card\nChoose: ");
    scanf("%d", &method);

    if(method == 2) {
        char card[30];
        printf("Enter 16-digit Card Number: ");
        scanf("%s", card);

        if(strlen(card) != 16) {
            printf("⚠ Card must be 16 digits!\n");
            return 0;
        }
    }

    printf("Payment Successful!\n");
    return 1;
}

// Order Form
int isValidPhone(char phone[]) {
    // length must be 11
    if(strlen(phone) != 11) return 0;

    // must start with 01 (BD format)
    if(phone[0] != '0' || phone[1] != '1') return 0;

    // all must be digits
    for(int i = 0; i < 11; i++) {
        if(phone[i] < '0' || phone[i] > '9') {
            return 0;
        }
    }

    return 1;
}

int orderForm() {
    char name[50], phone[20];
    char house[20], road[20], ps[50], po[50], dist[50];

    printf("\n--- ORDER FORM ---\n");

    printf("Name: ");
    scanf(" %[^\n]", name);

    // 🔥 Loop until valid phone
    while(1) {
        printf("Phone (11 digit, start with 01): ");
        scanf("%s", phone);

        if(isValidPhone(phone)) {
            break;
        } else {
            printf("⚠ Invalid phone! Try again.\n");
        }
    }

    printf("House no: ");
    scanf("%s", house);

    printf("Road no: ");
    scanf("%s", road);

    printf("PS: ");
    scanf(" %[^\n]", ps);

    printf("PO: ");
    scanf(" %[^\n]", po);

    printf("District: ");
    scanf(" %[^\n]", dist);

    if(strlen(name)==0 || strlen(house)==0 ||
       strlen(road)==0 || strlen(ps)==0 || strlen(po)==0 || strlen(dist)==0) {
        printf("⚠ All fields are required!\n");
        return 0;
    }

    return 1;
}

// Receipt
void generateReceipt(float total) {
    FILE *fp = fopen("receipt.txt", "w");

    printf("\n--- RECEIPT ---\n");
    fprintf(fp, "--- RECEIPT ---\n");

    for(int i=0;i<cartCount;i++) {
        printf("%s x%d = %.2f Tk\n",
        cart[i].name, cart[i].quantity, cart[i].totalPrice);

        fprintf(fp, "%s x%d = %.2f Tk\n",
        cart[i].name, cart[i].quantity, cart[i].totalPrice);
    }

    printf("Total: %.2f Tk\n", total);
    fprintf(fp, "Total: %.2f Tk\n", total);

    fclose(fp);
}

// Main
int main() {
    if(!login()) return 0;

    int op;
    float total;

    while(1) {
        printf("\n1.Add\n2.View Cart\n3.Remove\n4.Search\n5.Order\n6.Exit\nChoose: ");
        scanf("%d", &op);

        switch(op) {
            case 1: addToCart(); break;
            case 2: total = showCart(); break;
            case 3: removeItem(); break;
            case 4: searchItem(); break;
            case 5:
                total = showCart();
                if(orderForm() && payment(total)) {
                    saveHistory();
                    generateReceipt(total);
                    printf("✅ Order Complete!\n");
                }
                break;
            case 6: exit(0);
            default: printf("Invalid!\n");
        }
    }
}
