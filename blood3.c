#include<stdio.h>          // header files
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<ctype.h>
                            //macros
#define MAX_DONORS 30
#define MAX_HOSPITALS 20
#define MAX_BLOOD_PACKETS 30

                         //global variables
int hospital_count=0;
int donor_count=0;
int price=2200;

typedef struct donor   //struct for donor info
{
    char name[50];
    char f_name[50];
    char contact_no[12];
    char cnic[13];
    int age;
    int fitness;
    int DNR_id;
    char type;
    char rhesus;
}donor;
typedef struct Hospital    //struct for hospital info
{
     int HP_ID;
     char name[50];
     char contactno[11];
     char rhesius;
     char type;

}hospital;

typedef struct bloodpacket   //struct for blood packet info
{
    char t_1;
    char r_1;
    int expiry;

}blood_packets;

typedef struct bloodbank    //struct for bloodbank
{
    char username[20];
    char password[20];
    int donor_count;
    int hospital_count;
    donor donors[MAX_DONORS];
    hospital hps[MAX_HOSPITALS];
    blood_packets b_packets[MAX_BLOOD_PACKETS];

}B_b;

   // Function prototypes for authentication, updation and other functionalities

void saveBloodBankData(B_b *b);
void loadBloodBankData(B_b *b);
void d_registration(donor *d);
void b_register(B_b *b);
void d_updation(donor *d);
void update(B_b *b);
void h_register(hospital *h);
void h_registration(B_b *b);
void donate(B_b *b);
void show(B_b *b);
void payment_check();
void accept(struct bloodbank *b);
bool authenticate(B_b*b);

int main()         //main function
{
    int ch,count=0;
    B_b b={"cui","0000"};        //Saving username and password

    donor d;                      //struct donor declaration
    hospital h;                 //struct hospital declaration

    printf("**  *     **   **  **       **   **  *   * *  *\n");
    printf("* * *    *  * *  * *  *     * * *  * **  * * *\n");
    printf("**  *    *  * *  * *  *     **  **** * * * **\n");
    printf("* * *    *  * *  * *  *     * * *  * *  ** * * \n");
    printf("**  ****  **   **  **       **  *  * *   * *  *\n");


    while(count<3)               //loop for login authentication
    {
        if(authenticate(&b))     //function call in condition
        {
            break;
        }
        count++;
        if(count==3)
        {
            printf("Invalid access: Attempted beyond 3 times\n");
            return 0;
        }
    }

    loadBloodBankData(&b);          // Saving blood bank data before exiting

     donor_count = b.donor_count;        // Increment the donor_count based on loaded data

    while(1)                             //menu driven loop
    {
       puts("\n\nSelect one of the given options:\n");
       puts("1)Add Donor");
       puts("2)Add Hospital");
       puts("3)Update Donor Information");
       puts("4)Donate");
       puts("5)Blood Request");
       puts("6)Check available blood packets");
       puts("7)Exit");

       scanf("%d",&ch);
       switch(ch)
       {
           case 1:
                b_register(&b);
                saveBloodBankData(&b); // Saving data after registering a donor
                break;

            case 2:
                h_registration(&b);
                saveBloodBankData(&b);     // Saving data after registering a hospital
                break;

            case 3:
                update(&b);
                saveBloodBankData(&b);     // Saving data after updating donor information
                break;

            case 4:
                donate(&b);
                saveBloodBankData(&b);    // Saving data after donating blood
                break;

            case 5:
                accept(&b);
                saveBloodBankData(&b);   // Saving data after requesting blood
                 break;

            case 6:
                show(&b);
                saveBloodBankData(&b);   // Saving data after donating blood
                break;

            case 7:
                saveBloodBankData(&b);   // Saving data before exiting
                printf("Exiting the program\n");
                exit(0);   // Exit function
                break;

            default:
                printf("Invalid input!");
                break;
        }

    }
     return 0;
}

void saveBloodBankData(B_b *b)      // Function to write the blood bank data to a binary file
{
    b->donor_count = donor_count;
    FILE *file = fopen("bloodbank.bin","wb");
    if (file != NULL) {
        fwrite(b, sizeof(B_b), 1, file);
        fclose(file);
    } else {
        printf("Error: Unable to save blood bank data.\n");
    }
}

void loadBloodBankData(B_b *b)      // Function to load the blood bank data from a binary file
{
    FILE *file = fopen("bloodbank.bin", "rb");
    if (file != NULL) {
        fread(b, sizeof(B_b), 1, file);
        fclose(file);
        printf("Blood bank data loaded successfully.");
    } else {
        printf("Error: Unable to load blood bank data.");
    }
}

void d_registration(donor *d)        //function for donor registration

{
    d->DNR_id = donor_count+1;
   char c,n[2];
   char type[3]={'A','B','O'};

        //validation loop to restrict the name length upto maximum 50 characters.
     do{
         printf("\nEnter donor name:");
         fflush(stdin);
         gets(d->name);
         for (int i=0;i<50;i++)
            if (strlen(d->name) > 50 || !isalpha(d->name[0]))
            {
               printf("Invalid input \n");
            }
       }while(strlen(d->name) > 50 || !isalpha(d->name[0]));

       //validation loop to restrict the name length upto maximum 50 characters.

     do
        {
         printf("Enter father name:");
         fflush(stdin);
         gets(d->f_name);
            if (strlen(d->f_name) > 50 || !isalpha(d->f_name[0]))
            {
               printf("Invalid input \n");
            }
       }while(strlen(d->f_name) > 50 || !isalpha(d->f_name[0]));


    //validating the contact number length upto 11 characters
     do{
        printf("Enter contact number (11 digits):");
        scanf("%s",d->contact_no);
            if(strlen(d->contact_no)!=11)
                printf("Invalid Input\n");
       }while(strlen(d->contact_no)!=11);

     //validating the CNIC number length upto 13 characters
     do{
        printf("Enter CNIC (13 digits):");
        scanf("%s",d->cnic);
            if(strlen(d->cnic)!=13)
                printf("Invalid Input\n");
       }while(strlen(d->cnic)!=13);

      //validating the age between 1-100
    do
     {
        printf("Enter age:");
        scanf("%d",&d->age);

        if(d->age<0||d->age>=100)
        {
           printf("Invalid input\n");
        }
     }while(d->age<0||d->age>=100);

     if(d->age<18||d->age>65)
        {
           printf("Age is not suitable to donate blood\n");
           return;
        }
    //validation loop to restrict user to enter only '1' or '0' for fitness

     do {
         printf("Enter fitness (1-fit, 0-unfit):");
         scanf("%d", &d->fitness);

         if (d->fitness != 1 && d->fitness != 0)
              printf("Invalid Input\n");
        } while (d->fitness != 1 && d->fitness != 0);


 printf("Enter Blood type (A, B, AB, O): ");
    scanf("%s", n);
    for(int i=0;i<strlen(n);i++)      //loop to convert the string in  uppercase
    {
         n[i] = toupper(n[i]);
    }
      n[2]='\0';

if (strcmp(n, "AB") == 0)
    {
    d->type = 'x';
    }
    else if (strlen(n) == 1 && (n[0] == 'A' || n[0] == 'B' || n[0] == 'O'))
    {
        d->type = n[0];

     } else
      {
    printf("\nInvalid Blood Type!");
}
    while (1)
      {
        printf("Enter Rhesus(+/-):");
        scanf(" %c", &d->rhesus);
        if (d->rhesus == '+' || d->rhesus == '-') {
            break;
        } else {
            printf("\nInvalid rhesus");
        }
    }

    printf("\nYour donor ID is: %d", d->DNR_id);
}
void b_register(B_b *b) {
    if (donor_count < MAX_DONORS)
        {
        d_registration(&(b->donors[donor_count])); // Register the donor directly at the global count index

            donor_count++;         // Increment the count of registered donors
            saveBloodBankData(b);
        }
    else {
        printf("Maximum donor capacity reached. Cannot register more donors.\n");
    }
}



void d_updation(donor *d)
{
    int choice;
    char c;
    printf("\nEnter your choice:\n");
    puts("1) Update Fitness State");
    puts("2) Update Contact Number");
    scanf("%d",&choice);
    switch(choice){
      case 1:
          do
          {
        printf("Enter new fitness state (1-fit, 0-unfit):");
        scanf("%d",&d->fitness);
        fflush(stdin);
            if(d->fitness!=1||d->fitness!=0)
                printf("Invalid Input\n");

         }while((d->fitness)!=1||(d->fitness)!=0);

          break;
      case 2:
          do{
        printf("\nEnter new contact number:");
        scanf("%s",d->contact_no);
            if(strlen(d->contact_no)!=11)
                printf("Invalid Input\n");
          }while(strlen(d->contact_no)!=11);
          break;
      default:
          printf("Invalid Input");
    }
    printf("Your information has been successfully updated.");
   // printf("\nupdated fitness:%d",d->fitness);
   // printf("\nupdated contact number:%s",d->contact_no);
}
void update(B_b *b)
{
    int r;
    printf("Enter donor ID:");
    scanf("%d", &r);
    if (r <= donor_count)
        {
        d_updation(&(b->donors[r - 1])); // Pass the address of the donor at index r - 1

        saveBloodBankData(b); // Save data after updating donor information
        }
    else
        {
        printf("Donor ID doesn't exist\n");
        return;
    }
}


void h_register(hospital *h)
{

    h->HP_ID = hospital_count+1;
    do{
         printf("\nEnter hospital name:");
         fflush(stdin);
         gets(h->name);
            if(strlen(h->name)>50 || !isalpha(h->name[0]))
               printf("Enter valid input \n");
       }while(strlen(h->name)>50 || !isalpha(h->name[0]));

     do{
        printf("\nEnter contact number:");
        scanf("%s",h->contactno);

            if(strlen(h->contactno)!=11)
                 printf("Invalid Input\n");

        }while(strlen(h->contactno)!=11);

    printf("Your Hospital ID is: %d\n", h->HP_ID);
}
void h_registration(B_b *b) {
    if (b->hospital_count < MAX_HOSPITALS)
        {
            // Passing the address of the hospital at index hospital_count in the array
        h_register(&(b->hps[b->hospital_count]));
        hospital_count++;        // Incrementing the hospital count after registration
        printf("Hospital registered successfully!\n");
        saveBloodBankData(b);     // Save data after registering a hospital
        }
    else
        {
        printf("Hospital registration limit reached!\n");
        }
}

void donate(B_b *b) {
    int donor_id;
    printf("\nEnter donor ID: ");
    if (scanf("%d", &donor_id) != 1 || donor_id <= 0 || donor_id > donor_count) {
        printf("Invalid donor ID\n");
        while (getchar() != '\n');
        return;
    }

    printf("Donor Information\n");
    printf("Name: %s\n", b->donors[donor_id - 1].name);
    printf("Father Name: %s\n", b->donors[donor_id - 1].f_name);
    printf("Contact Number: %s\n", b->donors[donor_id - 1].contact_no);
    printf("CNIC: %s\n", b->donors[donor_id - 1].cnic);
    printf("Age: %2d\n", b->donors[donor_id - 1].age);
    printf("Blood Type: %c%c\n", b->donors[donor_id - 1].type, b->donors[donor_id - 1].rhesus);
    printf("Fitness state: %d\n", b->donors[donor_id - 1].fitness);

    if (b->donors[donor_id - 1].fitness == 0) {
        printf("Sorry, the donor is unfit to donate blood.\n");
        return;
    }

    char donor_type = b->donors[donor_id - 1].type;
    char donor_rhesus = b->donors[donor_id - 1].rhesus;

    int found = 0;

    for (int i = 0; i < MAX_BLOOD_PACKETS; i++) {
        if (b->b_packets[i].expiry < 2024) {
            if (b->b_packets[i].t_1 == '\0' || b->b_packets[i].t_1 == donor_type) {
                // Found an empty slot or matching blood type
                if (b->b_packets[i].t_1 == '\0') {
                    // Empty slot, add the blood packet details
                    b->b_packets[i].t_1 = donor_type;
                    b->b_packets[i].r_1 = donor_rhesus;

                    printf("Enter expiry: ");
                    if (scanf("%d", &b->b_packets[i].expiry) != 1 || b->b_packets[i].expiry < 0) {
                        printf("Invalid expiry value\n");
                        while (getchar() != '\n'); // Clearing input buffer
                        return;
                    }

                    printf("Blood packet added successfully!\n");
                    found = 1;
                    break;
                } else if (b->b_packets[i].t_1 == donor_type && b->b_packets[i].r_1 != donor_rhesus) {
                    // Same blood type but different Rhesus factor, proceed to next packet
                    continue;
                }
            }
        }
    }

    if (!found) {
        printf("No available slot for the blood packet matching the donor's blood type.\n");
    }

    saveBloodBankData(b); // Save data after donating blood
}



void payment_check()
{
    char ch;
    printf("Has payment been made?(y/n)");
    scanf(" %c", &ch);
    if (ch == 'Y' || ch == 'y')
        {
        printf("Transaction complete");
    } else {
        printf("Transaction incomplete");
    }
}



void accept(B_b *b) {
    int h_id, flag = 0, i;
    char req_t, req_r;

    do {
        printf("Enter Hospital ID: ");
        if (scanf("%d", &h_id) <= 0 || h_id > MAX_HOSPITALS)
            printf("Invalid Hospital ID\n");
    } while (h_id <= 0 || h_id > MAX_HOSPITALS);

    printf("Enter required blood type: ");
    scanf(" %c", &req_t);

    req_t = toupper(req_t); // Convert to uppercase

    printf("Enter required rhesus type(+/-): ");
    scanf(" %c", &req_r);

    for (i = 0; i < MAX_BLOOD_PACKETS; i++) {
        if (b->b_packets[i].expiry < 2024 && b->b_packets[i].t_1 == req_t && b->b_packets[i].r_1 == req_r) {
            flag = 1; // Blood packet found
            b->b_packets[i].t_1 = '0';
            b->b_packets[i].r_1 = '0';
            b->b_packets[i].expiry = 0;
            break;
        }
    }

    if (flag != 0) {
        printf("Cost of the required Blood Packet is: Rs.%d\n", price);
        payment_check();
    } else {
        printf("Required Blood Packet not available\n");
    }
}

void show(B_b *b)
 {
    int a_pos = 0, a_neg = 0, b_pos = 0, b_neg = 0, o_pos = 0, o_neg = 0, ab_pos = 0, ab_neg = 0;

    for (int i = 0; i < MAX_BLOOD_PACKETS; i++) {
        if (b->b_packets[i].expiry < 2024 && b->b_packets[i].t_1 != '\0') {
            switch (b->b_packets[i].t_1) {
                case 'A':
                    if (b->b_packets[i].r_1 == '+') {
                        a_pos++;
                    } else {
                        a_neg++;
                    }
                    break;
                case 'B':
                    if (b->b_packets[i].r_1 == '+') {
                        b_pos++;
                    } else {
                        b_neg++;
                    }
                    break;
                case 'O':
                    if (b->b_packets[i].r_1 == '+') {
                        o_pos++;
                    } else {
                        o_neg++;
                    }
                    break;
                case 'x':
                    if (b->b_packets[i].r_1 == '+') {
                        ab_pos++;
                    } else {
                        ab_neg++;
                    }
                    break;
                default:
                    break;
            }
        }
    }

    printf("BLOOD BANK DETAILS\n");
    printf("Available Blood Packets:\n");
    printf("Total blood packets available: %d\n", a_pos + a_neg + b_pos + b_neg + o_pos + o_neg + ab_pos + ab_neg);
    printf("\n A+   : %d", a_pos);
    printf("\n A-   : %d", a_neg);
    printf("\n B+   : %d", b_pos);
    printf("\n B-   : %d", b_neg);
    printf("\n O+   : %d", o_pos);
    printf("\n O-   : %d", o_neg);
    printf("\n AB+  : %d", ab_pos);
    printf("\n AB-  : %d", ab_neg);

      //function call

    saveBloodBankData(b); // Saving  data after donating blood
}





bool authenticate(B_b*b)        //bool function to check for authentication
{
    char username[20];
    char password[20];
    printf("Enter username:");
    gets(username);
    printf("Enter password:");
    gets(password);

     if (strcmp(username, b->username) == 0 && strcmp(password, b->password) == 0)
    {
        printf("\nAuthentication successful!\n\n");
        return true;
    }
    else
    {
        printf("\nAuthentication failed!\n");
         printf("\n");
        return false;
    }
}
