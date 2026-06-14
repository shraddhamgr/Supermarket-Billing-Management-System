#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<conio.h>
#include<time.h>



// ===== Structures =====
//to store the details of products
typedef struct 
{
    int id;
    char name[50];
    float price;
    int quantity;
} Product;


//to store the details of Bills
typedef struct 
{
    char customer[50];
    char product[50];
    int quantity;
    float rate;
    float total;
} Bill;


// ===== Global Variables =====
//validate the input 
int valid_choice;

// ===== Function Declarations =====
// Admin
int admin_login();
void admin_menu();
void add_product();
void edit_product();
void delete_product();
void display_products();                                     
void display_bills();                                                        
void search_bill();  
void sales_trends(); 

// Cashier
int cashier_login();
void cashier_menu();
void create_bill();

// ===== Main Function =====
int main() 
{
	
    int choice;
    printf("\n\n");  	
	printf("\t\t---------------------------------------------\n");
	printf("\t\t-\t\t\t\t\t    -\n");
	printf("\t\t-  Welcome to SuperMarket Billing  System   -\n");
	printf("\t\t-\t\t\t\t\t    -\n");
	printf("\t\t---------------------------------------------\n");
	printf("\n\t\tPress any keyword to continue ....! ");
	getch(); 
	

    while(1) 
     {
            system("cls");
            printf("\t\t Main menu : \n");
            printf("\t\t===============\n");
            printf("\t\t1. Admin\n");
            printf("\t\t2. Cashier\n");
            printf("\t\t3. Exit\n");
            printf("\t\t--------------------\n");
            printf("\n\t\tEnter your choice(1-3): ");
            
            
            valid_choice =scanf("%d", &choice);
            
               if (valid_choice != 1) 
               {
                    printf("\n\t\tInvalid input. Please enter a valid number between 1 and 3.\n");
                    printf("\n\t\tPress any keyword to continue ....! ");
                    getch();
                    while (getchar() != '\n');  // Clear input buffer
                    continue;  // Ask for input again if invalid
        
        		}


        switch (choice) 
        {
            case 1:
        
                if (admin_login()) 
                {
                    admin_menu();
                } else 
                {
                    printf("\n\t\tWrong credentials.\n");
                    printf("\n\t\tPress any keyword to Continue....!");
                    getch();
                }
                break;

            case 2:
           
            	if (cashier_login()) 
            	{
	                system("cls");
	                cashier_menu();  
             	} 
             	else
              	{
	                printf("\t\tWrong credentials\n");
	                printf("\n\t\tPress any key to continue...!");
                	getch();
                }
                break;

            case 3:
                printf("\n\n\t\t Thank you for using , Have a nice day.! \n");
                exit(0);
                break;

            default:
            	printf("\n\t\tInvalid input. Please enter a valid number between 1 and 3.\n");
            	printf("\n\t\tPress any keyword to continue ....! ");
				getch();
        }
    }

    return 0;
 }

// ===== Admin Functions =====



 int admin_login() 
 {
    FILE *fp;
    char storedUser[50], storedPass[50];
    char user[50], pass[50];

    fp = fopen("admin.txt", "r");   // open the file in read mode
      if (!fp)
         {
             printf("\n\t\tError: admin credentials file missing!\n");
             return 0;
         }

    // read username and password from file
    fscanf(fp, "%49s %49s", storedUser, storedPass);
    fclose(fp);

    system("cls");
    printf("\t\tAdmin Login: \n");
    printf("\t\t===============\n");

    printf("\t\tEnter username: ");
    scanf("%49s", user);

    printf("\t\tEnter password: ");
    scanf("%49s", pass);

    if (strcmp(user, storedUser) == 0 && strcmp(pass, storedPass) == 0) 
    {
        return 1;   // success
    }

    return 0;   // failure
}



void admin_menu() {
    int choice;
    do 
    {
        system("cls");
        printf("\n\t\tAdmin Menu\n");
        printf("\t\t=============\n");
        printf("\t\t1. Add Product\n");
        printf("\t\t2. Display Products\n");
        printf("\t\t3. Edit Product\n");
        printf("\t\t4. Delete Product\n");
        printf("\t\t5. Search Bill\n");
        printf("\t\t6. Display Bills\n");
        printf("\t\t7. Sales Trends\n");
        printf("\t\t8. Logout\n");
        
        printf("\t\tEnter your choice (1-7): ");
        valid_choice = scanf("%d", &choice);
        
         if (valid_choice != 1) 
         {
            printf("\n\t\tInvalid input. Please enter a valid number between 1 and 7.\n");
            printf("\n\t\t\t\tPress any keyword to continue ....! ");
			getch();
            while (getchar() != '\n');  // Clear input buffer
            continue;  // Ask for input again if invalid
        
         }
        system("cls");
        switch(choice)
         {
            case 1: 
                 add_product(); 
                 break;
            case 2:
                 display_products(); 
                 break;
            case 3: 
                 edit_product(); 
                 break;
            case 4: 
                 delete_product(); 
                 break;
            case 5:
                 search_bill(); 
                 break;
            case 6: 
                 display_bills(); 
                 break;
            case 7:
                  sales_trends();
                  break ;    
            case 8: 
                 printf("\n\t\tLogging out...\n"); 
                 printf("\n\t\tPress any keyword to continue ....! ");
				 getch();
                 break;
            default: 
				printf("\n\t\tInvalid input. Please enter a valid number between 1 and 7.\n");
	            printf("\n\t\tPress any keyword to continue ....! ");
				getch();
        }
        
    } while(choice != 8);
}


  

void add_product() 
{
	
    Product p, temp;  // p is the new product, temp is used to check existing products
    FILE *fp, *readFp; // fp is used to write new products, readFp is used to check existing products

    fp = fopen("products.txt", "a");  // Open file to add new product
    if (!fp) 
    {
        printf("\n\t\tFile error!\n");  // If file can't be opened
        return;
    }
      
    printf("\n\t\tEnter Product Details:\n");
    printf("\t\t=========================\n");

    // ====== Enter Product ID and check if it's unique =====
    while (1) 
    {
        int exists = 0;
        printf("\n\t\tEnter Product ID: ");
        if (scanf("%d", &p.id) != 1 || p.id <= 0)           // Validate input   (not =to 1 and negative)
        {  
            printf("\n\t\tInvalid ID!\n");
            while (getchar() != '\n');  // Clear invalid input
            continue;
        }
        while (getchar() != '\n');  // Clear newline

        // Check if the ID already exists
        readFp = fopen("products.txt", "r");
        if (readFp) 
        {
            while (fscanf(readFp, "%d|%49[^|]|%f|%d", &temp.id, temp.name, &temp.price, &temp.quantity) == 4) {
                if (temp.id == p.id) 
				{
					exists = 1;
				}
            }
            fclose(readFp);
        }
        if (exists)
		 { 
			printf("\n\t\tID already exists!\n");
		 }  // ID must be unique
        else break;
    }

    // ===== Enter Product Name =====
    printf("\n\t\tEnter Product Name: ");
    fgets(p.name, sizeof(p.name), stdin);
    p.name[strcspn(p.name, "\n")] = 0;  // Remove newline from input

    // ===== Enter Product Price =====
    while (1) 
    {
        printf("\n\t\tEnter Price: ");
        if (scanf("%f", &p.price) != 1 || p.price <= 0)             // Validate price
        {  
            printf("\n\t\tInvalid Price!\n");
            while (getchar() != '\n');  // Clear invalid input
            continue;
        }
        while (getchar() != '\n');  // Clear newline
        break;
    }

    // ===== Enter Product Quantity =====
    while (1) 
    {
        printf("\n\t\tEnter Quantity: ");   
        if (scanf("%d", &p.quantity) != 1 || p.quantity <= 0)           // Validate quantity
        {  
            printf("\n\t\tInvalid Quantity!\n");
            while (getchar() != '\n');  // Clear invalid input
            continue;
        }
        while (getchar() != '\n');  // Clear newline
        break;
    }

    // ===== Save product into file =====
    fprintf(fp, "%d|%s|%.2f|%d\n", p.id, p.name, p.price, p.quantity);
    fclose(fp);

    printf("\n\t\tProduct Added Successfully...!\n");  // Success message
    printf("\n\t\tPress any keyword to continue....!");
    getch();
}


void display_products() 
{
    Product p;   // To store each product while reading from file
    FILE *fp = fopen("products.txt", "r");   // Open products file for reading
    if(!fp)              // If file doesn't exist or can't be opened
    {   
        printf("\t\t\tNo products available.\n");
        printf("\n\t\tPress any keyword to continue....!");
        getch();
        return;
    }

    // Print the header for the product list
    printf("\n\t\t\t\t--- Product List  ---\n");
    printf("\n\t\t%-5s %-25s %-10s %-10s\n", "ID", "Name", "Price", "Qty");

    // Read each product from file and print it
    while(fscanf(fp, "%d|%49[^|]|%f|%d\n", &p.id, p.name, &p.price, &p.quantity) == 4) 
    {
        printf("\n\t\t%-5d %-25s %-10.2f %-10d\n", p.id, p.name, p.price, p.quantity);
    }

    fclose(fp);   // Close the file
    printf("\n\t\tPress any keyword to continue . . .");   // Pause for user
    getch();
}



void edit_product() {
    Product p;
    int id, found = 0, choice;

    FILE *fp = fopen("products.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!fp || !temp) {
        printf("\t\tFile error!\n");
        return;
    }

    display_products(); // show products before editing

    printf("\n\t\tEnter Product ID to Edit: ");
    scanf("%d", &id);
    while (getchar() != '\n'); // clear buffer

    while (fscanf(fp, "%d|%49[^|]|%f|%d", &p.id, p.name, &p.price, &p.quantity) == 4) {
        if (p.id == id) {
            found = 1;
            printf("\n\t\tProduct Found: %s | Price: %.2f | Qty: %d\n", p.name, p.price, p.quantity);

            printf("\n\t\tWhat do you want to edit?\n");
            printf("\t\t1. Name, Price & Quantity (Full Edit)\n");
            printf("\t\t2. Price & Quantity only\n");
            printf("\t\t3. Quantity only\n");
            printf("\n\t\tEnter choice (1-3): ");
            scanf("%d", &choice);
            while (getchar() != '\n');

            if (choice == 1) { // full edit
                printf("\n\t\tNew Name: ");
                fgets(p.name, sizeof(p.name), stdin);
                p.name[strcspn(p.name, "\n")] = 0;

                printf("\n\t\tNew Price: ");
                scanf("%f", &p.price);
                printf("\n\t\tNew Quantity: ");
                scanf("%d", &p.quantity);
            }
            else if (choice == 2) { // price + qty
                printf("\n\t\tNew Price: ");
                scanf("%f", &p.price);
                printf("\n\t\tNew Quantity: ");
                scanf("%d", &p.quantity);
            }
            else if (choice == 3) { // qty only
                printf("\n\t\tNew Quantity: ");
                scanf("%d", &p.quantity);
            }
            else {
                printf("\n\t\tInvalid choice! No changes made.\n");
            }
        }
        fprintf(temp, "%d|%s|%.2f|%d\n", p.id, p.name, p.price, p.quantity);
    }

    fclose(fp);
    fclose(temp);

    remove("products.txt");
    rename("temp.txt", "products.txt");

    if (found) printf("\n\t\tProduct Updated Successfully!\n");
    else printf("\n\t\tProduct Not Found!\n");

    printf("\n\t\tPress any key to continue....!");
    getch();
}


void display_bills() 
{
    Bill b;   // To store each bill while reading from file
    FILE *fp = fopen("bills.txt", "r");   // Open bills file for reading
    if(!fp)                 // If file doesn't exist or can't be opened
     {   
        printf("\t\t\tNo bills available.\n");
        printf("\n\t\tPress any keyword to continue . . .");
        getch();
        return;
     }

    printf("\n\t\t\t--- Bill List ---\n\n");
    printf("\t%-20s %-20s %-5s %-10s %-10s\n", "Customer", "Product", "Qty", "Rate", "Total");

    // Each bill
    while (fscanf(fp, "%49[^|]|%49[^|]|%d|%f|%f\n", 
                 b.customer, b.product, &b.quantity, &b.rate, &b.total) == 5) {
        printf("\t%-20s %-20s %-5d %-10.2f %-10.2f\n", 
               b.customer, b.product, b.quantity, b.rate, b.total);
    }
   

    fclose(fp);   // Close the file
    printf("\n\t\tPress any keyword to continue . . .");   // Pause for user
    getch();
}




void search_bill() 
{
    char input[50];   // To store what user wants to search
    int found = 0;    // Flag to check if any match is found

    // Clear leftover newline from previous input
    while(getchar() != '\n');

    printf("\n\t\t\tEnter Customer name or Product name to search: ");
    fgets(input, sizeof(input), stdin);    // Read input from user

    // Remove trailing newline from input
    input[strcspn(input, "\n")] = 0;

    // If user enters nothing
    if(strlen(input) == 0) 
     {
        printf("\t\t\nYou didn't enter any name!\n");
        printf("\n\t\tPress any keyword to continue . . .");
        getchar();
        return;
     }
 
    // Open the bills file to search
    FILE *fp = fopen("bills.txt", "r");
    if(!fp)             // If file doesn't exist
    {    
        printf("\t\tNo bills found!\n");
        printf("\n\t\tPress any keyword to continue . . .");
        getchar();
        return;
    }

    char line[200];   // To read each line from the file
    printf("\n\t\t\t--- Search Results ---\n");

    // Go through each line in the file
    while(fgets(line, sizeof(line), fp)) 
    {
        char cust[50], prod[50];
        int qty;
        float rate, total;

        // Extract details from the line
        if(sscanf(line, "%49[^|]|%49[^|]|%d|%f|%f", cust, prod, &qty, &rate, &total) == 5) 
        {
            // Check if customer or product matches input (case-insensitive)
            if (strcmpi(cust, input) == 0 || strcmpi(prod, input) == 0)
              {
                    printf("\n\t\t\tCustomer: %s\n", cust);
                    printf("\n\t\t\tProduct: %s\n", prod);
                    printf("\n\t\t\tQuantity: %d\n", qty);
                    printf("\n\t\t\tRate: %.2f\n", rate);
                    printf("\n\t\t\tTotal: %.2f\n", total);
                    found = 1;   // Found a match
              }
        }
    }

    fclose(fp);   // Close the file

    // If no match was found found ==0 
    if(!found)
     {
        printf("\n\t\t\tNo bills found for '%s'\n", input);
     }

    printf("\n\t\t\tPress any keyword to continue . . .");
    getch();
}



void delete_product() 
{
    Product p;              // Temporary variable to read product info
    int id, found = 0;      // id = product to delete, found = flag if product exists

    FILE *fp = fopen("products.txt", "r");   // Open file with all products
    FILE *temp = fopen("temp.txt", "w");     // Temp file to save updated products
    if(!fp || !temp)
     {                       // Check if files opened correctly
        printf("\t\tError opening file.\n");
        return;
     }
    
    display_products("Admin");               // Show all products before deleting

    printf("\n\n\t\tEnter Product ID to delete: ");
    scanf("%d", &id);                        // Read product ID to delete
    while(getchar() != '\n');                // Clear leftover newline

    // Read all products one by one
    while(fscanf(fp, "%d|%49[^|]|%f|%d\n", &p.id, p.name, &p.price, &p.quantity) == 4)
     {
        if(p.id != id)                        // If not the one to delete, write to temp
            fprintf(temp, "%d|%s|%.2f|%d\n", p.id, p.name, p.price, p.quantity);
        else
            found = 1;                        // Product found, mark as deleted
     }

    fclose(fp);
    fclose(temp);

    remove("products.txt");                   // Remove old file
    rename("temp.txt", "products.txt");      // Rename temp as main file

    if(found)
        printf("\t\tProduct deleted successfully!\n"); // Show success message
    else
        printf("\t\tProduct not found!\n");            // Show not found message

    printf("\n\t\tPress any keyword to continue....!"); // Pause
    getch();
} 





void sales_trends()
{
    FILE *fp = fopen("bills.txt", "r");
    if (!fp)
    {
        printf("\n\t\tNo sales data available!\n");
        printf("\n\t\tPress any key to continue...");
        getch();
        return;
    }

    float daily = 0, weekly = 0, monthly = 0;
    Bill b;
    char line[200];
    time_t now = time(NULL);
    struct tm *today = localtime(&now);

    while (fgets(line, sizeof(line), fp))
    {
        char cust[50], prod[50];
        int qty;
        float rate, total;
        int y, m, d;

        if (sscanf(line, "%49[^|]|%49[^|]|%d|%f|%f|%d-%d-%d", 
                   cust, prod, &qty, &rate, &total, &y, &m, &d) == 8)
        {
            struct tm saleDate = {0};
            saleDate.tm_year = y - 1900;
            saleDate.tm_mon = m - 1;
            saleDate.tm_mday = d;

            time_t saleTime = mktime(&saleDate);
            double diffDays = difftime(now, saleTime) / (60 * 60 * 24);

            if (diffDays < 1) daily += total;
            if (diffDays < 7) weekly += total;
            if (diffDays < 30) monthly += total;
        }
    }
    fclose(fp);

    printf("\n\t\t--- Sales Trends ---\n");
    printf("\t\tDaily Sales   : %.2f\n", daily);
    printf("\t\tWeekly Sales  : %.2f\n", weekly);
    printf("\t\tMonthly Sales : %.2f\n", monthly);
    printf("\n\t\tPress any key to continue...");
    getch();
}


// ===== Cashier Functions =====

	
    int cashier_login() 
    {
         FILE *fp;
         char storedUser[50], storedPass[50];
         char user[50], pass[50];

         fp = fopen("cashier.txt", "r");   // open the file in read mode
            if (!fp)
                {
                    printf("\n\t\tError: cashier credentials file missing!\n");
                    return 0;
                }

            // read username and password from file
    
         fscanf(fp, "%49s %49s", storedUser, storedPass);
         fclose(fp);

         system("cls");
         printf("\t\tCashier Login : \n");
         printf("\t\t===============\n");

         printf("\t\tEnter username: ");
         scanf("%49s", user);

         printf("\t\tEnter password: ");
         scanf("%49s", pass);

         if (strcmp(user, storedUser) == 0 && strcmp(pass, storedPass) == 0) 
            {
                return 1;   // success
            }

        return 0;   // failure
}



void cashier_menu() 
{
    int choice;
    do 
    {
        system("cls");
        printf("\n\t\tCashier Menu\n");
        printf("\t\t=============\n");
        printf("\t\t1. View Products\n");
        printf("\t\t2. Create Bill\n");
        printf("\t\t3. View All Bills\n");
        printf("\t\t4. Logout\n");

        printf("\n\t\tEnter choice (1-4): ");
        scanf("%d", &choice);
        while(getchar() != '\n');
        system("cls");
        switch(choice) 
         {
            case 1: 
                display_products("Cashier");                //calls for display products (cashier role)
                break;
            case 2: 
                create_bill(); 
                break;
            case 3:  
                display_bills("Cashier");               //same as display products
                break;
            case 4: 
                printf("\n\t\t\tLogging out...\n"); 
                printf("\n\t\tPress any keyword to continue....!");
                getch();
                break;
            default: 
                printf("\n\t\tInvalid input. Please enter a valid number between 1 and 7.\n");
	            printf("\n\t\tPress any keyword to continue ....! ");
				getch();
         }

    } while(choice != 4);
}


void create_bill() 
{
    Bill b;                  
    int n, i;               
    float total = 0;        

    FILE *billFp = fopen("bills.txt", "a"); 
    if (!billFp) 
    {
        printf("\n\t\tError opening bills file!\n"); 
        return;
    }

    printf("\n\t\tCustomer Name: ");
    fgets(b.customer, sizeof(b.customer), stdin);      
    b.customer[strcspn(b.customer, "\n")] = 0;        

    // ===== Ask how many products =====
    int attempts = 0;
    while (1)
    {
        printf("\n\t\tHow many products? ");
        if (scanf("%d", &n) != 1 || n <= 0)
        {
            printf("\n\t\tInvalid number of products. Enter a positive integer.\n");
            while (getchar() != '\n');  
            attempts++;
            if (attempts >= 3) 
            {
                printf("\n\t\tToo many invalid attempts. Exiting...\n");
                fclose(billFp);
                return;
            }
            continue;
        }
        while (getchar() != '\n');  
        break;
    }

    // ===== Loop for each product =====
    for (i = 0; i < n; i++)
    {
        Product p;             
        int pid, found = 0;    

        // ===== Ask for product ID =====
        while (1)
        {
            printf("\n\t\tEnter Product ID (%d of %d): ", i + 1, n);
            if (scanf("%d", &pid) != 1)
            {           
                printf("\n\t\tInvalid Product ID. Please enter numbers only.\n");
                while (getchar() != '\n');  
                continue;
            }
            while (getchar() != '\n');  
            break;
        }

        FILE *prodFp = fopen("products.txt", "r"); 
        FILE *temp = fopen("temp.txt", "w");      

        if (!prodFp || !temp)
        {
            printf("\n\t\tError accessing products file.\n");
            if (prodFp) fclose(prodFp);
            if (temp) fclose(temp);
            fclose(billFp);
            return;
        }

        // ===== Read products to find the one to buy =====
        while (fscanf(prodFp, "%d|%49[^|]|%f|%d", &p.id, p.name, &p.price, &p.quantity) == 4) 
        {
            if (p.id == pid) 
            {                     
                found = 1;
                printf("\n\t\tFound %s | Price %.2f | Stock %d\n", p.name, p.price, p.quantity);

                // ===== Ask for quantity =====
                int validQty = 0;
                while (!validQty) 
                {
                    printf("\n\t\tEnter Quantity: ");
                    if (scanf("%d", &b.quantity) != 1 || b.quantity <= 0)
                    {
                        printf("\n\t\tInvalid Quantity! Please enter a positive integer.\n");
                        while (getchar() != '\n');
                        continue;
                    }
                    while (getchar() != '\n');  
                    validQty = 1;
                }

                if (b.quantity > p.quantity)
                {     
                    printf("\n\t\tNot enough stock! Please enter another product.\n");
                    fprintf(temp, "%d|%s|%.2f|%d\n", p.id, p.name, p.price, p.quantity); 
                    found = 0; // Force user to re-enter product
                } 
                else
                {
                    // ===== Get current date =====
                    time_t now = time(NULL);
                    struct tm *t = localtime(&now);  

                    // ===== Fill bill details =====
                    strcpy(b.product, p.name);       
                    b.rate = p.price;                
                    b.total = b.rate * b.quantity;   
                    total += b.total;                

                    // ===== Write bill to file with date =====
                    fprintf(billFp, "%s|%s|%d|%.2f|%.2f|%d-%d-%d\n", 
                            b.customer, b.product, b.quantity, b.rate, b.total,
                            t->tm_year + 1900, t->tm_mon + 1, t->tm_mday);

                    // ===== Update product quantity =====
                    int newQty = p.quantity - b.quantity;   
                    fprintf(temp, "%d|%s|%.2f|%d\n", p.id, p.name, p.price, newQty); 
                }
            } 
            else 
            {
                fprintf(temp, "%d|%s|%.2f|%d\n", p.id, p.name, p.price, p.quantity); 
            }
        }

        fclose(prodFp);
        fclose(temp);

        if (!found) 
        {
            printf("\n\t\tProduct ID %d not found or insufficient stock. Try again.\n", pid); 
            i--;  // repeat this iteration
            remove("temp.txt");  // discard changes
            continue;
        }

        // ===== Replace original products file with updated stock =====
        remove("products.txt");
        rename("temp.txt", "products.txt");
    }

    fclose(billFp);                               
    printf("\n\t\tBill created! Total = %.2f\n", total); 
    printf("\n\t\tPress any key to continue....!");
    getch();                                      
}
