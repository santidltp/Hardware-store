/******************************************************************************************************************
 *	This program, which is called Hard Ware Store, is way too far to look like Amazon.com.                        *
 *	But it has the basic features that Amazon.com has. This program keeps a "Data base" of						  *
 *	hard ware store in a linked list(followed by specifications), the options; "Add to cart",					  *
 *	"Remove from cart", "View Inventory"... are included in a menu bar(followed by specifications).               *
 *	The first option, which is “view inventory” in Inventory menu, prints on the client are the current stock.    *
 *	The “Check Out” option will print on the client area of the program the items added previosly,                *
 *	the total cost of all products in the cart, two text boxes to provide name and addres,                        *
 *	and a “Check out” button. If the button is pressed and there is nothing on the cart an error                  *
 *	message will pump up. If the button is pressed and the text boxes have the default information                *
 *	an error message will pump up. Clicking on the “Customer” menu will show three submenus: “Add to Cart”,       *
 *	”Remove from cart”, and “Display Cart”.”Add to cart” submenu allows you to add an item from                   *         
 *	the invetory to the cart, if the item you are trying to add does not exist or is out of stock                 *
 *	an error message will pump up. “Remove from cart” submenu will ask you which of the items from                *
 *	the cart you want to delete, in case you don’t have that item in your current cart an error                   *
 *	message will pump up. Finally the display submenu from the menu “Customer” is going to print                  *
 *	in the client area the current cart. The Icon has been provided by Iconarchive.com                            *
 *                                                                                                                *
 *	Develped by: Santiago De La Torre.                                                                            *
 *	Educational Center: Bunker Hill Community College.                                                            *
 *	Last modification: 24-Nov-2010.                                                                               *
 *                                                                                                                *
 *                                                                                                                *
 ******************************************************************************************************************/


#include <afxwin.h>
#include "resource1.h"
#include "Hard Ware Store.h"
#include "Linkedlist.h"
#include "Dialog.h"

HardWare hardware;
/* Two instances of the link list, on for the
 * inventory and the other one for the "cart"
 */
Linked_List invent, customer; 


BOOL HardWare::InitInstance()
{
	m_pMainWnd = new CMainWindow();
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();
	return true;
}
BEGIN_MESSAGE_MAP(CMainWindow,CWnd)
	ON_WM_PAINT()
	ON_COMMAND(ID_INVENTORY_VIEWINVENTORY,OnViewInventory)
	ON_COMMAND(ID_CUSTOMER_DISPLAYCART ,OnViewCart)
	ON_COMMAND(ID_INVENTORY_CHECKOUT, OnCheckOut)
	ON_COMMAND(ID_CUSTOMER_ADDTOCART,OnAddToCart)
	ON_COMMAND(ID_INVENTORY_EXIT,OnExit)
	ON_BN_CLICKED(BUTTON,OnButton)
	ON_COMMAND(ID_CUSTOMER_REMOVEFROMCART, OnRemoveCart)
END_MESSAGE_MAP()


CMainWindow::CMainWindow()
{
	CMenu Menu;					//let's create an instance of a menu
	Populate_LinkedList();		//populate the inventory
	CString strWndClass = AfxRegisterWndClass (
        CS_VREDRAW | CS_HREDRAW,
        AfxGetApp ()->LoadStandardCursor (IDC_ARROW),   
        (HBRUSH) (COLOR_3DFACE),					
		AfxGetApp ()->LoadIconW ( IDI_ICON1 )	
    );
	CreateEx(0,strWndClass, _T("Hard Ware Store"), WS_OVERLAPPED|WS_SYSMENU|WS_CAPTION|WS_MINIMIZEBOX,
		 CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL,
		 NULL);
	CRect size(0,0,400,450);
	CalcWindowRect(&size);

	Menu.LoadMenuW(IDR_MENU1);
	SetMenu(&Menu);

	SetWindowPos(NULL,0,0,size.Width(),size.Height(),
			 SWP_NOZORDER | SWP_NOMOVE| SWP_NOREDRAW);
}
void CMainWindow::Destroy()
{
	delete this;
}
void CMainWindow::OnPaint()
{
	CPaintDC dc(this); 

	/* Depending on what the user chooses in the menu
	 * we are going to print one thing or another.
	 * [PSEUDO CODE]
	 * If the user chooses "View Inventory" then print 
	 *		 the CURRENT inventory on the client area.
	 * If the user chooses "Display Cart" then print
	 *				the current cart of the customer.
	 * If the user chooses "Check Out" print on the 
	 * on the client area the current cart, subtotal,
	 * tax, shipping and handling,and total.
	 * 
	 * Note: We don't want the two text boxes and the "check out"
	 * button in every choice, so we are going to "destroy"
	 * them everytime the user chooses anything else other
	 * than "Check Out".
	 */
	if(PRINT == PRINT_INVENT)
		invent.display(&dc);
	else if(PRINT == PRINT_CART )
		customer.display(&dc);
	else if(PRINT == PRINT_CHECK)
	{
		customer.display(&dc);
		customer.Total(&dc);
	}
	if(!(PRINT == PRINT_CHECK))
	{
		MFCText.DestroyWindow();
		MFCText2.DestroyWindow();
		button.DestroyWindow();
	}
}
void CMainWindow::OnExit()
{
	//Are you sure you wan to quit?
	int iMsg = MessageBox(L"Are you sure you want to quit?",L"Exit",MB_YESNO|MB_ICONQUESTION);
	if(iMsg == IDYES) Destroy();
}

void CMainWindow::OnViewInventory()
{
	/* When the user chooses "View Inventory"
	 * PRINT get the value of PRINT_INVENT
	 * and we "repaint" the client area"
	 *
	 * Note: The value of print is what determines
	 *		 what is going to be printed in the 
	 *		 client area.
	 */
	PRINT = PRINT_INVENT;
	Invalidate();
}
void CMainWindow::Populate_LinkedList()
{
		//Add the inventory to the invent Linked list.
		invent.insert("A100",20,"Hammer",9.95);
		invent.insert("A250",25,"Saw",13.95);
		invent.insert("B400",50,"Flat-Head Nails",11.99);
		invent.insert("C888",50,"Flat-Head Screwdriver",6.59);
		invent.insert("A499",75,"Pliers",4.95);
		invent.insert("C667",50,"Drill",22.95);
		invent.insert("B875",70,"Plumber's Wrench",11.90);
		invent.insert("D547",60,"Ladder 10 foot",70.44);
		invent.insert("A910",85,"Flashlight 10 inch",9.99);
		invent.insert("B123",90,"Assorted Buss Fuses",4.99);
}
void CMainWindow::OnAddToCart()
{
	/*[PSEUDO CODE]
	* Create an instance of dialog.
	*	If the user presses the ok button on the dialog button.
	*		If what the user is trying to add to his/her cart exist in the inventory
	*			and we have is not out of stock. Then Add it to the cart and subtract it from the inventory
	*       otherwise pump up an error message.
	* Give the parent window the "focus" meaning leave it selected.
	* "repaint" the client area.
	*/
	
	Dialog dlg;
		if(dlg.DoModal()==IDOK)
			if(invent.search(dlg.StockN,dlg.Description,dlg.price) && invent.DoWeHaveIT(dlg.StockN,dlg.Qty))
			{
				invent.Add_Subtract(dlg.StockN,dlg.Qty, SUBTRACT);
				customer.insert(dlg.StockN,dlg.Qty,dlg.Description,dlg.price);
			}
			else
			{
				MessageBox(L"The item you are trying to add does not exist\nor we are out of stock - item back ordered.", L"Stock",MB_ICONERROR|MB_OK);
			}
	SetFocus();
	Invalidate();
}
void CMainWindow::OnViewCart()
{
	/* PRINT gets the values of PRINT_CART 
	 * "repaint" the client area.
	 */
	PRINT = PRINT_CART;
	Invalidate();
}
void CMainWindow::OnRemoveCart()
{
	/*[PSEUDO CODE]
     * If there is nothing on the customer's cart pump up an error message.
	 *	If the user presses ok in the dialog box then...
	 *	 If the customer has that item and the customer doesn't deletes more than what he/she has then...
	 *		subtract that item from the customer's cart and added to the inventory.
	 *	 Otherwise pump up an error message.
	 */
	Dialog dlg;

	if(customer.getstart() == NULL){ //empty list
		MessageBox(L"Your cart is empty",L"Cart",MB_ICONERROR|MB_OK);
		return;
	}
	if(dlg.DoModal()==IDOK){

			if(customer.search(dlg.StockN,dlg.Description,dlg.price) && customer.DoWeHaveIT(dlg.StockN,dlg.Qty))
			{
				customer.Delete(dlg.StockN, dlg.Qty);
				invent.Add_Subtract(dlg.StockN,dlg.Qty, ADD);
			}
			else
			{
			MessageBox(L"That item is not in your cart\nor you are trying to delete more than what you have.",L"Cart",MB_ICONERROR|MB_OK);
			}
	}
	SetFocus();
	Invalidate();
}
void CMainWindow::OnCheckOut()
{
	//This function prints the current cart, two text boxes and a button
	
	if(customer.getstart() == NULL){ //empty list
		MessageBox(L"Your cart is empty",L"Cart",MB_ICONERROR|MB_OK);
		return;
	}
	CRect rect(20,350,200,370);
	PRINT = PRINT_CHECK;
	MFCText.Create(WS_CHILD | WS_VISIBLE|WS_BORDER,rect,this,201);
	MFCText.SetWindowTextW(L"Enter Name Here");
	rect.MoveToX(200);
	MFCText2.Create(WS_CHILD | WS_VISIBLE|WS_BORDER,rect,this,202);
	MFCText2.SetWindowTextW(L"Enter Adress Here");
	CRect rect2(310,370,380,390);
	button.Create(L"Check Out",WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,rect2,this,BUTTON);
	Invalidate();
}
void CMainWindow::OnButton()
{
	 /* This function is the one who looks at the textboxes.
	  * Since our specification don't tell us what to do with them.
	  * I decided to make sure that the customer types something different from the default.
	  * Once the user presses this button everything goes bye bye,
	  * meaning that everything was submited succesfully.
	  */
      MFCText.GetWindowTextW(sName);
	  MFCText2.GetWindowTextW(sAddress);
		if( sName == L"Enter Name Here" || sAddress == L"Enter Adress Here")
		{
			MessageBox(L"Please enter a correct name and address",L"Input Error", MB_ICONERROR |MB_OK );
			return;
		}
		if(customer.getstart() == NULL)
		{
			MessageBox(L"There is nothing in your cart",L"Cart", MB_ICONERROR |MB_OK);
			return;
		}
		MFCText.DestroyWindow();
		MFCText2.DestroyWindow();
		button.DestroyWindow();
		customer.EmptyLink();
		Invalidate();
}



