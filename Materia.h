#pragma once
#include<iostream>
#include "resource.h"
class Materia
{
private:
	int id{ 0 };
	char nombre[100]{ 0 };
	char clave[100]{ 0 };
	char descripcion[500]{ 0 };
	char creditos[100]{ 0 };
	char horas[100]{ 0 };
	char semestre[100]{ 0 };
	Materia* ant;
	Materia* sig;
public:
	int temp_id;
	Materia* lista = NULL;
	Materia* tempant = NULL;
	void Leer();
	void Escribir();
	void InsertarNodo(int, char[100], char[100], char[500], char[100], char[100], char[100]);
	void AgregaNodo(HWND Dlg);
	void EliminarNodo(Materia* _temp);
	void Mostrar(HWND Dlg, int item);
	Materia* BuscarNodo(char[100]);
	int BuscarID(char[100]);
	void EditarNodo(HWND Dlg, Materia* _temp);
	void TransferirNodo(HWND Dlg, Materia* _temp);
	void eliminarnodos();
};
void Materia::Leer() {
	fstream archivo("Materia.txt", ios::out | ios::app);
	archivo.close();
	archivo.open("Materia.txt", ios::in | ios::binary);
	if (archivo.is_open()) {
		Materia* nuevo = new Materia;
		archivo.read((char*)nuevo, sizeof(Materia));
		while (!archivo.eof()) {
			nuevo->sig = NULL;
			Materia* ultimo = lista;
			while (ultimo != NULL && ultimo->sig != NULL) {
				ultimo = ultimo->sig;
			}
			if (ultimo != NULL)
				ultimo->sig = nuevo;
			else
				lista = nuevo;
			nuevo = new Materia;
			archivo.read((char*)nuevo, sizeof(Materia));
		}
		archivo.close();
	}
	else {
		MessageBox(0, "No es posible abrir el archivo.", "Aviso", MB_ICONINFORMATION);
	}
}
void Materia::Escribir() {
	ofstream archivo;
	archivo.open("Materia.txt", ios::binary);
	if (archivo.is_open()) {
		Materia* borrar = NULL;
		Materia* aux = lista;
		while (aux != NULL) {
			archivo.write((char*)aux, sizeof(Materia));
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
void Materia::InsertarNodo(int _id, char _nombre[100], char _clave[100], char _descripcion[500], char _creditos[100], char _horas[100], char _semestre[100]) {
	Materia* nuevo = new Materia;
	nuevo->id = _id;
	strcpy_s(nuevo->nombre, _nombre);
	strcpy_s(nuevo->clave, _clave);
	strcpy_s(nuevo->descripcion, _descripcion);
	strcpy_s(nuevo->creditos, _creditos);
	strcpy_s(nuevo->horas, _horas);
	strcpy_s(nuevo->semestre, _semestre);
	nuevo->ant = NULL;
	nuevo->sig = NULL;
	if (lista == NULL) {
		lista = nuevo;
	}
	else {
		Materia* aux = lista;
		while (aux->sig != NULL) {
			aux = aux->sig;
		}
		aux->sig = nuevo;
		aux->sig->ant = aux;
	}
}
void Materia::AgregaNodo(HWND Dlg) {
	SendDlgItemMessage(Dlg, IDC_MATERIA, WM_GETTEXT, 100, (LPARAM)nombre);
	SendDlgItemMessage(Dlg, IDC_CLAVE, WM_GETTEXT, 100, (LPARAM)clave);
	SendDlgItemMessage(Dlg, IDC_DESCRIPCION, WM_GETTEXT, 500, (LPARAM)descripcion);
	SendDlgItemMessage(Dlg, IDC_CREDITOS, WM_GETTEXT, 100, (LPARAM)creditos);
	SendDlgItemMessage(Dlg, IDC_HORAS, WM_GETTEXT, 100, (LPARAM)horas);
	SendDlgItemMessage(Dlg, IDC_SEMESTRE, WM_GETTEXT, 100, (LPARAM)semestre);
	id = id + 1;
	InsertarNodo(id, nombre, clave,descripcion,creditos,horas,semestre);
}
void Materia::EliminarNodo(Materia* _temp) {
	Materia* aux = _temp;
	Materia* ant = tempant;
	if (aux == lista) {
		lista = lista->sig;
	}
	else {
		ant->sig = aux->sig;
	}
	delete aux;
}
void Materia::Mostrar(HWND Dlg, int item) {
	Materia* aux = lista;
	while (aux != NULL) {
		SendDlgItemMessage(Dlg, item, LB_ADDSTRING, 100, (LPARAM)aux->nombre);
		aux = aux->sig;
	}
}
Materia* Materia::BuscarNodo(char dato[100]) {
	Materia* buscado = NULL;
	Materia* aux = lista;
	while (aux != NULL) {
		if (strcmp(dato, aux->nombre) == 0) {
			buscado = aux;
			return buscado;
			break;
		}
		tempant = aux;
		aux = aux->sig;
	}
}
int Materia::BuscarID(char dato[100]) {
	Materia* buscado = NULL;
	Materia* aux = lista;
	while (aux != NULL) {
		if (strcmp(dato, aux->nombre) == 0) {
			buscado = aux;
			return buscado->id;
			break;
		}
		aux = aux->sig;
	}
}
void Materia::EditarNodo(HWND Dlg, Materia* _temp) {
	Materia* aux = _temp;
	SendDlgItemMessage(Dlg, IDC_MATERIA, WM_GETTEXT, 100, (LPARAM)aux->nombre);
	SendDlgItemMessage(Dlg, IDC_CLAVE, WM_GETTEXT, 100, (LPARAM)aux->clave);
	SendDlgItemMessage(Dlg, IDC_DESCRIPCION, WM_GETTEXT, 500, (LPARAM)aux->descripcion);
	SendDlgItemMessage(Dlg, IDC_CREDITOS, WM_GETTEXT, 100, (LPARAM)aux->creditos);
	SendDlgItemMessage(Dlg, IDC_HORAS, WM_GETTEXT, 100, (LPARAM)aux->horas);
	SendDlgItemMessage(Dlg, IDC_SEMESTRE, WM_GETTEXT, 100, (LPARAM)aux->semestre);
}
void Materia::TransferirNodo(HWND Dlg, Materia* _temp) {
	SendDlgItemMessage(Dlg, IDC_MATERIA, WM_SETTEXT, 100, (LPARAM)_temp->nombre);
	SendDlgItemMessage(Dlg, IDC_CLAVE, WM_SETTEXT, 100, (LPARAM)_temp->clave);
	SendDlgItemMessage(Dlg, IDC_DESCRIPCION, WM_SETTEXT, 500, (LPARAM)_temp->descripcion);
	SendDlgItemMessage(Dlg, IDC_CREDITOS, WM_SETTEXT, 100, (LPARAM)_temp->creditos);
	SendDlgItemMessage(Dlg, IDC_HORAS, WM_SETTEXT, 100, (LPARAM)_temp->horas);
	SendDlgItemMessage(Dlg, IDC_SEMESTRE, WM_SETTEXT, 100, (LPARAM)_temp->semestre);
}
void Materia::eliminarnodos() {
	if (lista == NULL) {
		delete lista;
	}
	else {
		Materia* aux = lista;
		while (aux->sig != NULL) {
			lista = aux->sig;
			delete aux;
			aux = lista;
		}
		delete lista;
		lista = aux = NULL;
	}
}