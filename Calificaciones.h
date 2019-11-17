#pragma once
#include<iostream>
#include "resource.h"
class Calificaciones
{
private:
	int id{ 0 };
	char materia[100]{ 0 };
	char clave[100]{ 0 };
	char semestre[100]{ 0 };
	char cal[100]{ 0 };
	Calificaciones* ant;
	Calificaciones* sig;
public:
	Calificaciones* lista = NULL;
	Calificaciones* tempant = NULL;
	void Leer();
	void Escribir();
	void InsertarNodo(int, char[100], char[100],  char[100], char[100]);
	void AgregaNodo(HWND Dlg);
	void EliminarNodo(Calificaciones* _temp);
	void BuscarNodo();
	void EditarNodo();
	void eliminarnodos();
};
void Calificaciones::Leer() {
	fstream archivo("Calificaciones.txt", ios::out | ios::app);
	archivo.close();
	archivo.open("Calificaciones.txt", ios::in | ios::binary);
	if (archivo.is_open()) {
		Calificaciones* nuevo = new Calificaciones;
		archivo.read((char*)nuevo, sizeof(Calificaciones));
		while (!archivo.eof()) {
			nuevo->sig = NULL;
			Calificaciones* ultimo = lista;
			while (ultimo != NULL && ultimo->sig != NULL) {
				ultimo = ultimo->sig;
			}
			if (ultimo != NULL)
				ultimo->sig = nuevo;
			else
				lista = nuevo;
			nuevo = new Calificaciones;
			archivo.read((char*)nuevo, sizeof(Calificaciones));
		}
		archivo.close();
	}
	else {
		MessageBox(0, "No es posible abrir el archivo.", "Aviso", MB_ICONINFORMATION);
		PostQuitMessage(0);
	}
}
void Calificaciones::Escribir() {
	ofstream archivo;
	archivo.open("Calificaciones.txt", ios::binary);
	if (archivo.is_open()) {
		Calificaciones* borrar = NULL;
		Calificaciones* aux = lista;
		while (aux != NULL) {
			archivo.write((char*)aux, sizeof(Calificaciones));
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
void Calificaciones::InsertarNodo(int _id, char _materia[100], char _clave[100], char _semestre[100], char _cal[100]) {
	Calificaciones* nuevo = new Calificaciones;
	nuevo->id = _id;
	strcpy_s(nuevo->materia, _materia);
	strcpy_s(nuevo->clave, _clave);
	strcpy_s(nuevo->semestre, _semestre);
	strcpy_s(nuevo->cal, _cal);
	nuevo->ant = NULL;
	nuevo->sig = NULL;
	if (lista == NULL) {
		lista = nuevo;
	}
	else {
		Calificaciones* aux = lista;
		while (aux->sig != NULL) {
			aux = aux->sig;
		}
		aux->sig = nuevo;
		aux->sig->ant = aux;
	}
}
void Calificaciones::AgregaNodo(HWND Dlg) {
	SendDlgItemMessage(Dlg, IDC_CAL, WM_GETTEXT, 100, (LPARAM)cal);
	InsertarNodo(id, materia, clave, semestre, cal);
}
void Calificaciones::EliminarNodo(Calificaciones* _temp) {
	Calificaciones* aux = _temp;
	Calificaciones* ant = tempant;
	if (aux == lista) {
		lista = lista->sig;
	}
	else {
		ant->sig = aux->sig;
	}
	delete aux;
}
void Calificaciones::BuscarNodo() {

}
void Calificaciones::EditarNodo() {

}
void Calificaciones::eliminarnodos() {
	if (lista == NULL) {
		delete lista;
	}
	else {
		Calificaciones* aux = lista;
		while (aux->sig != NULL) {
			lista = aux->sig;
			delete aux;
			aux = lista;
		}
		delete lista;
		lista = aux = NULL;
	}
}