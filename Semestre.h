#pragma once
#include<fstream>
#include<iostream>
#include "resource.h"
class Semestre
{
private:
	int id{ 0 };
	char periodo[100]{ 0 };
	char año[5]{ 0 };
	Semestre* ant;
	Semestre* sig;
public:
	Semestre* lista = NULL;
	Semestre* tempant = NULL;
	void Leer();
	void Escribir();
	void InsertarNodo(int,char[100],char[5]);
	void AgregaNodo(HWND Dlg);
	void EliminarNodo(Semestre* _temp);
	void Mostrar(HWND Dlg);
	Semestre* BuscarNodo(char[100]);
	void EditarNodo(Semestre* _temp);
	void eliminarnodos();
};
void Semestre::Leer() {
	fstream archivo("Semestre.txt", ios::out | ios::app);
	archivo.close();
	archivo.open("Semestre.txt", ios::in | ios::binary);
	if (archivo.is_open()) {
		Semestre* nuevo = new Semestre;
		archivo.read((char*)nuevo, sizeof(Semestre));
		while (!archivo.eof()) {
			nuevo->sig = NULL;
			Semestre* ultimo = lista;
			while (ultimo != NULL && ultimo->sig != NULL) {
				ultimo = ultimo->sig;
			}
			if (ultimo != NULL)
				ultimo->sig = nuevo;
			else
				lista = nuevo;
			nuevo = new Semestre;
			archivo.read((char*)nuevo, sizeof(Semestre));
		}
		archivo.close();
	}
	else {
		MessageBox(0, "No es posible abrir el archivo.", "Aviso", MB_ICONINFORMATION);
	}
}
void Semestre::Escribir() {
	ofstream archivo;
	archivo.open("Semestre.txt", ios::binary);
	if (archivo.is_open()) {
		Semestre* borrar = NULL;
		Semestre* aux = lista;
		while (aux != NULL) {
			archivo.write((char*)aux, sizeof(Semestre));
			borrar = aux;
			aux = (*aux).sig;
			delete borrar;
		}
		archivo.close();
	}
	else {
		MessageBox(0, "No es posible abrir el archivo.", "Aviso", MB_ICONINFORMATION);
		eliminarnodos();
		PostQuitMessage(0);
	}
}
void Semestre::InsertarNodo(int _id, char _periodo[100], char _año[5]) {
	Semestre* nuevo = new Semestre;
	nuevo->id = _id;
	strcpy_s(nuevo->periodo, _periodo);
	strcpy_s(nuevo->año, _año);
	nuevo->ant = NULL;
	nuevo->sig = NULL;
	if (lista == NULL) {
		lista = nuevo;
	}
	else {
		Semestre* aux = lista;
		while (aux->sig != NULL) {
			aux = aux->sig;
		}
		aux->sig = nuevo;
		aux->sig->ant = aux;
	}
}
void Semestre::AgregaNodo(HWND Dlg) {
	SendDlgItemMessage(Dlg, IDC_FECHA, WM_GETTEXT, 5, (LPARAM)año);
	if (SendDlgItemMessage(Dlg, IDC_RADIO1, BM_GETCHECK, 0, 0) == BST_CHECKED) {
		strcpy_s(this->periodo, "Enero-Junio");
	}
	if (SendDlgItemMessage(Dlg, IDC_RADIO2, BM_GETCHECK, 0, 0) == BST_CHECKED) {
		strcpy_s(this->periodo, "Agosto-Diciembre");
	}
	InsertarNodo(id, periodo, año);
}
void Semestre::EliminarNodo(Semestre* _temp) {
	Semestre* aux = _temp;
	Semestre* ant = tempant;
	if (aux == lista) {
		lista = lista->sig;
	}
	else {
		ant->sig = aux->sig;
	}
	delete aux;
}
void Semestre::Mostrar(HWND Dlg) {
	Semestre* aux = lista;
	while (aux != NULL) {
		SendDlgItemMessage(Dlg, IDC_LIST2, LB_ADDSTRING, 100, (LPARAM)aux->periodo);
		aux = aux->sig;
	}
}
Semestre* Semestre::BuscarNodo(char dato[100]) {
	Semestre* buscado = NULL;
	Semestre* aux = lista;
	while (aux != NULL) {
		if (strcmp(dato, aux->periodo) == 0) {
			buscado = aux;
			return buscado;
			break;
		}
		tempant = aux;
		aux = aux->sig;
	}
}
void Semestre::EditarNodo(Semestre* _temp) {
	/*_temp->periodo=new periodo
	_temp->año=new año*/
}
void Semestre::eliminarnodos() {
	if (lista == NULL) {
		delete lista;
	}
	else {
		Semestre* aux = lista;
		while (aux->sig != NULL) {
			lista = aux->sig;
			delete aux;
			aux = lista;
		}
		delete lista;
		lista = aux = NULL;
	}
}
