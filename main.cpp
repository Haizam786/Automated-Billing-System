#include<fstream>
#include<string>
#include<iostream>

using namespace std;

// declarations
void cashier_menu(string username);                                       //Function definition to cashier menu
void loginMenu();                                                           //Function definition to login menu
void adminmenu();                                                       //Function definition to admin menu
void saveProduct();                                                  //Function definition to create products for admin
void show_all_product();                                                //Function definition to view all products
void display_record(int num);                                           //Function definition to query
void edit_product();                                                  //Function definition to Modify products for admin
void pos();                                                       //Function definition to calculate products for cashier
void cashierlogout(string username);                                    //Function definition to logout menu for cashier
void adminlogout();                                                     //Function definition to logout menu for admin

struct product
{
    int pno;
    char pname[50];
    float pprice;

    void insertProduct()
    {
        cout << endl << "Please Enter The Product Number: ";
        cin >> pno;
        cout << endl << "Please Enter The Name of The Product: ";
        cin.ignore();
        cin.getline(pname,50);
        cout << endl << "Please Enter The Price of The Product: ";
        cin >> pprice;
    }

    void displayProduct ()
    {
        cout << endl <<endl<< "Product Number: " << pno;
        cout << endl <<endl<< "Product Name: " << pname;
        cout << endl <<endl<<"Product Price: " << pprice;
    }

    int retProduct()
    {
        return pno;
    }

    float retPrice()
    {
        return pprice;
    }

    char* retName()
    {
        return pname;
    }
};

fstream fp;
product produc;

void saveProduct()
{
    char ch = 'Y';
    do{
    fp.open("Shop.dat", ios::out | ios::app);
    produc.insertProduct();
    fp.write((char*)&produc, sizeof(product));
    fp.close();
    cout << endl << endl << "The Product Has Been Successfully Created...";
    cout << endl << endl << "Do You Want To Create Another Product?(y/n)";
    cin >> ch;
    }while (ch == 'y' || ch == 'Y');
    cout << "\n\nThank You...";
    std::cin.get();
}

void show_all_product()
{
    system("cls");
    cout << endl << "\t\t____________________________________";
    cout << endl << "\t\tRECORDS.";
    cout << endl << "\t\t____________________________________\n";
    fp.open("Shop.dat", ios::in);
    if (!fp)
    {
        cout << "This file is not found or corrupted .For maintenance, please contact the administrator ";
        cout << "\n\n\n Program is closing ....";
        std::cin.get();
    }
    while (fp.read((char*)&produc, sizeof(product)))
    {
        produc.displayProduct();
        cout << endl << "_____________________________________\n" << endl;
        std::cin.get();
    }
    fp.close();

}

void display_record(int num)
{
    bool found = false;
    fp.open("Shop.dat", ios::in);
    while (fp.read((char*)&produc, sizeof(product)))
    {
        if (produc.retProduct() == num)
        {
            system("cls");
            produc.displayProduct();
            found = true;
        }
    }

    fp.close();
    if (found == false)
        cout << "\nNo record available\n\n";
    std::cin.get();
}

void edit_product()
{
    int num;
    bool found = false;
    system("cls");
    cout << endl << endl << "\tPlease Enter The Product No That Need To Modify: ";
    cin >> num;

    fp.open("Shop.dat", ios::in | ios::out);            //file is opened for reading and writing
    while (fp.read((char*)&produc, sizeof(product)) && found == false)
    {
        if (produc.retProduct() == num)
        {
            produc.displayProduct();
            cout << "\nPlease Enter The New Details of Product: " << endl;
            produc.insertProduct();
            int pos = -1* sizeof(produc);
            fp.seekp(pos, ios::cur);
            fp.write((char*)&produc, sizeof(product));
            cout << endl << endl << "\t Record Successfully Updated...";        // notification of success
            found = true;
        }
    }
    fp.close();
    if (found == false)
        cout << endl << endl << "Record Not Found...";      //error notification
    std::cin.get();
}

void product_menu()
{
    system("cls");
    fp.open("Shop.dat", ios::in);                    //open file

    cout << endl << endl << "\t\tPRODUCT MENU\n\n";
    cout << "--------------------------------------------\n";
    cout << "Product NO\tProduct Name\tProduct Price\n";
    cout << "--------------------------------------------\n";
    while (fp.read((char*)&produc, sizeof(product)))
    {
        cout << produc.retProduct() << "\t\t" << produc.retName() << "\t\t" << produc.retPrice() << endl;
    }
    fp.close();
}

void pos()
{
    int order_arr[50], quan[50], c = 0;
    float amount, total=0;
    char ch = 'Y';
    product_menu();
    cout << "\n____________________________________________";
    cout << "\n Point of System";
    cout << "\n____________________________________________\n";
    do {
        cout << "\n\nEnter The Product NO: ";
        cin >> order_arr[c];
        cout << "\nQuantity: ";
        cin >> quan[c];
        c++;
        cout << "\n\tDo You Want To Add Another Product ? (y/n)";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    cout << "\n\nThank You...";
    std::cin.get();
    system("cls");
    cout << "\t\t\t---------------------_ _ _ _ SUDU ARALIYA_ _ _ _ _ -------------------\t\t\t" << endl;
	cout << "\t\t\t\t_ _ _ _ _ _ _ _ _ _ _ SUPER MART_ _ _ _ _ _ _ _ _ _ _\t\t\t" << endl;
    cout << "\t\t\t\t\tNo 101  Colombo - Hanwella Low Level Rd, Kaduwela\t\t\t\t\t";
    cout << "\t\t\t\t\t\tTEL # 0112 500000 / 0114 000000\t\t\t\t\t\t";

    cout << "\t\t\t\t\nProduct No\tProduct Name\tQuantity\tPrice \tAmount \t\t\t\t\n";
    for (int x = 0; x <= c; x++)
    {
        fp.open("Shop.dat", ios::in);
        fp.read((char*)&produc, sizeof(product));
        while (!fp.eof())               // if not at end of file, continue reading
        {
            if (produc.retProduct() == order_arr[x])
            {
                amount = produc.retPrice() * quan[x];
                cout << "\n\t" << order_arr[x] << "\t" << produc.retName() << "\t" << quan[x] << "\t\t" << produc.retPrice() << "\t" << amount << "\t\t\t";
                total+=amount;
            }
            fp.read((char*)&produc, sizeof(product));
        }
        fp.close();
    }
    cout << "\n\n\t\t\t\t\tTOTAL = " << total;
    std::cin.get();
}

void cashierlogout(string username){

    char ch ;
    do
    {
        cout << endl << endl << "Do You Want To Logout?(y/n)";
        cin >> ch;

        if (ch == 'y')
        {
            system("cls");
            loginMenu();
        }
        else if (ch == 'n')
        {
            system("cls");
            cashier_menu(username);
        }
    } while (ch != 'y'||ch != 'n');
}

void adminlogout(){

    char ch ;

    do
    {
        cout << endl << endl << "Do You Want To Logout?(y/n)";
        cin >> ch;
        if (ch == 'y')
        {
            // login Menu Will Clear The Screen
            loginMenu();
        }
        else if (ch == 'n')
        {
            system("cls");
            adminmenu();
        }
    } while (ch != 'y'||ch != 'n');       //entering a default option
}

void cashier_menu(string username)
{
    system("cls");
    int option;

    cout << "\n\tPress 1 to POS";                    //To calculate products
    cout << "\n\tPress 2 to SHOW ALL PRODUCTS";             //To see all product list of the super mart
    cout << "\n\tPress 3 to QUERY";                     //To view each records
    cout << "\n\tPress 4 to LOGOUT";                 //logging out


    cout << "\n\n\tOption: ";
    cin >> option;
    switch (option)
    {
    case 1: system("cls");                      //clear CMD
            pos();
            system("cls");
            system("pause");
            cashier_menu(username);
            break;

    case 2: show_all_product();          //Calling show all products function
            system("pause");
            cashier_menu(username);
            break;

    case 3: int num;
            cout << "\n\n\tPlease Enter The Product Number: ";
            cin >> num;
            system("cls");
            display_record(num);
            system("pause");
            system("cls");
            cashier_menu(username);
            break;

    case 4: system("cls");
            cashierlogout(username);
            break;

            default:
            system("cls");
            cashier_menu(username);
            break;
}
}

void adminmenu()
{
    system("cls");
    int option;

    cout << "\n\tPress 1 to CREATE PRODUCT";                //Create & add products
    cout << "\n\tPress 2 to SHOW ALL PRODUCTS";                 //To see all product list of the super mart
    cout << "\n\tPress 3 to QUERY ";                        //To view each records
    cout << "\n\tPress 4 to MODIFY PRODUCT";                    //To edit a product
    cout << "\n\tPress 5 to Logout";                        //logging out

    cout << "\n\n\tOption: ";
    cin >> option;
    switch (option)
    {
    case 1: saveProduct();                     // calling function to add a product
            system("pause");
            adminmenu();
            break;

    case 2: show_all_product();
            system("pause");
            adminmenu();
            break;

    case 3: int num;
            cout << "\n\n\tPlease Enter The Product Number: ";
            cin >> num;
            system("cls");                                              //clear CMD
            display_record(num);
            system("pause");
            system("cls");
            adminmenu();
            break;

    case 4: edit_product();
            system("pause");
            adminmenu();
            break;

    case 5: system("cls");
            adminlogout();
            break;

            default:
            system("cls");
            adminmenu();                    //calling the function to re-enter
            break;
    }
}

void loginMenu()
{
    system("cls");

    string username, password;                          //username & password
	bool LoginSuccess = false;                          //boolean expression for login
	int attempt = 1;

	cout << "\t\t\t---------------------_ _ _ _ SUDU ARALIYA_ _ _ _ _ -------------------\t\t\t" << endl;
	cout << "\t\t\t\t_ _ _ _ _ _ _ _ _ _ _ SUPER MART_ _ _ _ _ _ _ _ _ _ _\t\t\t" << endl;
	cout << "Login\n"<<"_______"<< endl;
	do {
		cout << "Enter User Name:" << endl;
		cin >> username;
		cout << "Enter Password:" << endl;
		cin >> password;

		if ((username == "Haizam" && password == "123")) {
			cout << "Access granted!\n" << endl;
			cout << "Welcome\t" << username+ "!" << endl;
			system("pause");
			LoginSuccess = true;
			adminmenu();

		}
		else if ((username == "Naazar" && password == "1234") || (username == "Faahim" && password == "12345")) {
			cout << "Access granted!\n" << endl;
			cout << "Welcome\t" << username+ "!"<< endl;
			system("pause");
			LoginSuccess = true;
			cashier_menu(username);

		}
		else {
			cout << "Username or Password do not match \t" << 3 - attempt << " Attempt remaining" << endl;
			++attempt;

		}


	} while (attempt<=3);
	if (attempt = 3) {
		cout << "Error:Program Terminated" << endl;
	}
}

int main()
{
    loginMenu();
}

