#include "Linkedlist.h"
#include <cstringt.h> 
#include "Hard Ware Store.h"
#include <afxwin.h>


void Linked_List::insert(CString StockN, int Qty, CString Description, double Price)
{
	node* temp = new node;
	temp->StockN = StockN;
	temp->Qty = Qty;
	temp->Description= Description;
	temp->Price = Price;
	temp->next=NULL;
	
	/*[PSEUDO CODE]
	 * If the list is empty start gets the values inserted.
	 * and will become the firs "node"... continue
	 */
	if(start ==NULL)
	{
		start=temp;
	}
	/* If the first node has a values then lets look for a
	 * node which value is null so we can inser our values.
	 *
	 * Note: The if statement inside the loop is to avoid add 
	 *		 item that has been previously added.Instead we are going
	 *       to add the quantity to the same value.
	 *       For example: if you add three hammers and then you add 2 more to the cart
	 *					  you wanna see those items in a list as a 5 hammers 
	 *                    in one line not in two.
	 */
	else
	{
		node* temp2 = new node;
		temp2=start;

		while(temp2->next!=NULL)
		{
				if(temp2->StockN == StockN)
				{
				temp2->Qty += Qty;
				return;
				}
				temp2=temp2->next;
		}			
			
		if(start->StockN == StockN)
				{
				start->Qty += Qty;
				return;
				}
	
	temp2->next=temp;
	}
}

void Linked_List::display(CPaintDC *dc)
{
	//Displays the linked list in a list format.
	node* print = new node;
	print = start;
	
	CString temp;
	int x, y=30;
	
	CRect title(0,0,420,20);
	dc->DrawText("Stock Number     Qty           Description                     Price",title,DT_SINGLELINE);
	if(print != NULL)
	do{
	x = 0;
		CRect wow(25,y+=20,220,800);
	dc->DrawText(print->StockN ,wow, DT_SINGLELINE); 
	
	wow.MoveToX(x+=118);
	temp.Format(_T("%d"),print->Qty);
	dc->DrawText (temp,wow, DT_SINGLELINE); 
	
	
	wow.MoveToX(x+=60);
	dc->DrawText(print->Description ,wow, DT_SINGLELINE); 
	
	wow.MoveToX(x+=155);
	temp.Format(_T("%.2f"),print->Price);
	dc->DrawText( temp,wow, DT_SINGLELINE); 
	print = print->next;
	}while(print != NULL);
		
}
bool Linked_List::search(CString  StockN, CString Description, double Price)
{
	//This function looks for an item in a list.
	node* temp;
	temp=start;

	do
	{
		if(temp->StockN == StockN && temp->Description == Description && temp->Price == Price)
				return true;
		temp = temp->next; 
	}while(temp !=NULL);
return false;
}
void Linked_List::Add_Subtract(CString StockN, int Qty, int addsub)
{
   //we want to use this function to add of subtract from the inventory
	node* temp;
	temp=start;

	do
	{
		if(temp->StockN == StockN)
		{
			if(addsub == SUBTRACT)
					temp->Qty -= Qty;
			if(addsub == ADD)
				temp->Qty += Qty;
		}
		temp = temp->next;
	}while(temp !=NULL);
}
void Linked_List::Delete(CString StockN, int Qty)
{
	node* pFirst, *pSecond;
	pFirst = pSecond = start;

	while(pFirst->StockN != StockN)
	{	
		if(pFirst->next != NULL) 
			{
				pSecond = pFirst;
				pFirst = pFirst->next;
			}
	}	/* If the user want to delete some but not all then 
	     * just subtract it.
		 */
	if(pFirst->Qty - Qty > 0)
	{
		pFirst->Qty -= Qty;
		return;
	}	
	if(pSecond == pFirst)
		start = start->next;
	else
		pSecond->next = pFirst->next;
	delete pFirst;
}
bool Linked_List::DoWeHaveIT(CString StockN, int Qty)
{

	node* current;
	current = start;

	do{
		if(current->StockN == StockN)
		{
			if (current->Qty - Qty < 0)
				return false;
		}
		current = current->next;
	}while(current !=NULL);
return true;
}
void Linked_List::Total(CPaintDC *dc)
{
	double  total =0.0;
	node* current = start;
	CRect rect(0,250,500,800);
	CString msg;

	if(current == NULL)
		return;//print a total

	do
	{
		total += current->Price * current->Qty;

		current = current->next;
	}while(current != NULL);
	
	msg.Format(_T("Subtotal:     %.2f"),total);
	dc->DrawText(msg,rect,DT_SINGLELINE);
	rect.MoveToY(270);
	dc->DrawText(L"Tax:   5%", rect, DT_SINGLELINE);
	rect.MoveToY(290);
	total *= 1.05;
	dc->DrawText(L"Shipping and Handling:     9.95",rect, DT_SINGLELINE);
	total += 9.95;
	rect.MoveToY(310);
		 msg.Format(_T("Total:  %.2f"),total);
	dc->DrawText(msg,rect,DT_SINGLELINE);
}

void Linked_List::EmptyLink()
{
	start=NULL;
}

