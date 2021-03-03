//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
#include <time.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
void TForm1::draw(){
	DrawGrid1->Canvas->Brush->Color = clWhite;
	for(int i=0; i<4; i++)#123456789
		for(int j=0; j<4; j++){
			DrawGrid1->Canvas->FillRect(DrawGrid1->CellRect(j,i));
			ImageList1->Draw(DrawGrid1->Canvas,DrawGrid1->CellRect(j, i).Left, DrawGrid1->CellRect(j, i).Top, StringGrid1->Cells[j][i].ToInt(), true);
		}
}//---------------------------------------------------------------------------
void TForm1::newgame(){
	for(int i=0; i<4; i++)
		for(int j=0; j<4; j++)
			StringGrid1->Cells[j][i] = 0;

}//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner): TForm(Owner){
	time(0);
	newgame();
	Form1->DoubleBuffered = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::N3Click(TObject *Sender){
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::N1Click(TObject *Sender){
	int k = 0, i1 = 0, j1 = 0;
	newgame();
	while(k<16){
		i1 = rand()%4;
		j1 = rand()%4;
		if(StringGrid1->Cells[j1][i1] == 0){
			StringGrid1->Cells[j1][i1] = k;
			k++;
		}
	}
	draw();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::DrawGrid1DrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,TGridDrawState State){
	ImageList1->Draw(DrawGrid1->Canvas,DrawGrid1->CellRect(ACol, ARow).Left, DrawGrid1->CellRect(ACol, ARow).Top, StringGrid1->Cells[ACol][ARow].ToInt(), true);
}
//---------------------------------------------------------------------------
bool TForm1::win(){
	int win = 1;
	for(int i=0; i<4; i++)
		for(int j=0; j<4; j++)
			if(StringGrid1->Cells[j][i].ToInt() == win) win++;
	if(StringGrid1->Cells[3][3].ToInt() == 0) win++;
	win--;
	if(win == 16) return 1;
	else return 0;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::DrawGrid1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift){
	bool tmp = 0;
	for(int j=0; j<4; j++){
		for(int i=0; i<4; i++)
			if(StringGrid1->Cells[j][i].ToInt() == 0){
				if(Key == VK_LEFT){
					if(j!=0){
						StringGrid1->Cells[j][i] = StringGrid1->Cells[j-1][i];
						StringGrid1->Cells[j-1][i] = 0;
					}
				}
				if(Key == VK_RIGHT){
					if(j!=3){
						StringGrid1->Cells[j][i] = StringGrid1->Cells[j+1][i];
						StringGrid1->Cells[j+1][i] = 0;
						tmp = 1;
					}
				}
				if(Key == VK_UP){
					if(i!=0){
						StringGrid1->Cells[j][i] = StringGrid1->Cells[j][i-1];
						StringGrid1->Cells[j][i-1] = 0;
					}
				}
				if(Key == VK_DOWN){
					if(i!=3){
						StringGrid1->Cells[j][i] = StringGrid1->Cells[j][i+1];
						StringGrid1->Cells[j][i+1] = 0;
					}
				}
				break;
			}
		if(tmp) break;
	}
	draw();
	if(win()) Form2->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::N2Click(TObject *Sender){
	int win1 = 1;
	for(int i=0; i<4; i++)
		for(int j=0; j<4; j++)
			StringGrid1->Cells[j][i] = win1++;
	StringGrid1->Cells[3][3] = 0;
	draw();
	if(win()) Form2->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::N4Click(TObject *Sender){
	Form3->ShowModal();
}
//---------------------------------------------------------------------------

