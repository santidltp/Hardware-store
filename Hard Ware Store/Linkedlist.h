#include <afxwin.h>

class node
{
public:

	CString StockN;
	int Qty;
	CString Description;
	double Price;
	node *next;

}; 
class Linked_List
{
	private:
		node* start;
	public:
		//constructor
		
		Linked_List(){ start=NULL;};
		//Member functions
	void insert(CString  StockN, int Qty, CString Description, double Price);
	void display(CPaintDC *dc);
	bool search(CString  StockN, CString Description, double Price);
	void Add_Subtract(CString StockN, int Qty, int addsub);
	void Delete(CString StockN, int Qty);
	bool DoWeHaveIT(CString StockN, int Qty);
	void Total(CPaintDC *dc);
	void EmptyLink();
	//accesor
	node* getstart(){return start;};
};
