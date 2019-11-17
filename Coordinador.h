#pragma once
#include<iostream>
#include <Windows.h>
#include <string.h>
#include <commdlg.h>
#include "resource.h"
using namespace std;
OPENFILENAME ofn;
//Arbol
class Coordinador
{
private:
	int id{ 0 };
	bool usuario{ 0 };
	char contraseña[100]{ 0 };
	char nombre[100]{ 0 };
	char apellido[100]{ 0 };
	char rol[100]{ 0 };
	char carrera[100]{ 0 };
	char clave[100]{ 0 };
	char siglas[100]{ 0 };
	char descripcion[500]{ 0 };
	Coordinador* izq;
	Coordinador* der;
public:
	char foto[MAX_PATH]{ 0 };
	Coordinador* raiz;
	Coordinador* temp;
	int i = 0;
	void Insertar(Coordinador*& nodo, int, bool, char[100], char[100], char[100], char[100], char[MAX_PATH], char[100], char[100], char[100], char[500]);
	void PreOrden(Coordinador* nodo, HWND Dlg);
	void InOrden(Coordinador* nodo);
	void PostOrden(Coordinador* nodo);
	void AgregarCarrera(HWND Dlg);
	void Busqueda(Coordinador* nodo, int);
	void openfilename();
	~Coordinador() {
		delete raiz;
	}
};
void Coordinador::Insertar(Coordinador*& nodo,int _id,bool _usuario,char _contraseña[100], char _nombre[100], char _apellido[100], char _rol[100],char _foto[MAX_PATH],char _carrera[100],char _clave[100], char _siglas[100], char _descripcion[500]) {
	if (nodo != NULL) {
		if (strcmp(_nombre, nodo->nombre) < 0) {
			Insertar(nodo->izq, _id, _usuario, _contraseña, _nombre, _apellido, _rol, _foto, _carrera, _clave, _siglas, _descripcion);
		}
		else {
			if (strcmp(_nombre, nodo->nombre) > 0)
				Insertar(nodo->der, _id, _usuario, _contraseña, _nombre, _apellido, _rol, _foto, _carrera, _clave, _siglas, _descripcion);
			else
				int opc = MessageBox(0, "Este coordinador ya fue ingresado", "Aviso", MB_ICONINFORMATION + MB_OKCANCEL);
		}
	}
	else {
		Coordinador* nuevo = new Coordinador;
		nuevo->izq = NULL;
		nuevo->der = NULL;
		nuevo->id = _id;
		nuevo->usuario = _usuario;
		strcpy_s(nuevo->contraseña, _contraseña);
		strcpy_s(nuevo->nombre, _nombre);
		strcpy_s(nuevo->apellido, _apellido);
		strcpy_s(nuevo->rol, _rol);
		strcpy_s(nuevo->foto, _foto);
		strcpy_s(nuevo->carrera, _carrera);
		strcpy_s(nuevo->clave, _clave);
		strcpy_s(nuevo->siglas, _siglas);
		strcpy_s(nuevo->descripcion, _descripcion);
		nodo = nuevo;
		temp = nodo;
	}
}
void Coordinador::PreOrden(Coordinador* nodo, HWND Dlg) {
	if (nodo != NULL) {
		/*int opc = MessageBox(0, nodo->nombre, "PreOrden", MB_ICONINFORMATION + MB_OKCANCEL);*/
		SendDlgItemMessage(Dlg, IDC_LIST2, LB_ADDSTRING, 100, (LPARAM)nodo->nombre);
		PreOrden(nodo->izq,Dlg);
		PreOrden(nodo->der,Dlg);
	}
}
void Coordinador::InOrden(Coordinador* nodo) {
	if (nodo != NULL) {
		InOrden(nodo->izq);
		int opc = MessageBox(0, nodo->nombre, "InOrden", MB_ICONINFORMATION + MB_OKCANCEL);
		InOrden(nodo->der);
	}
}
void Coordinador::PostOrden(Coordinador* nodo) {
	if (nodo != NULL) {
		PostOrden(nodo->izq);
		PostOrden(nodo->der);
		int opc = MessageBox(0, nodo->nombre, "PostOrden", MB_ICONINFORMATION + MB_OKCANCEL);
	}
}
void Coordinador::AgregarCarrera(HWND Dlg) {
	SendDlgItemMessage(Dlg, IDC_NOMBRE, WM_GETTEXT, 100, (LPARAM)nombre);
	SendDlgItemMessage(Dlg, IDC_APELLIDO, WM_GETTEXT, 100, (LPARAM)apellido);
	SendDlgItemMessage(Dlg, IDC_CONTRA, WM_GETTEXT, 100, (LPARAM)contraseña);
	SendDlgItemMessage(Dlg, IDC_INFO, WM_GETTEXT, 100, (LPARAM)foto);
	SendDlgItemMessage(Dlg, IDC_CN, WM_GETTEXT, 100, (LPARAM)carrera);
	SendDlgItemMessage(Dlg, IDC_CC, WM_GETTEXT, 100, (LPARAM)clave);
	SendDlgItemMessage(Dlg, IDC_CS, WM_GETTEXT, 100, (LPARAM)siglas);
	SendDlgItemMessage(Dlg, IDC_CD, WM_GETTEXT, 500, (LPARAM)descripcion);
	id = id + 1;
	Insertar(raiz,id,usuario,contraseña,nombre,apellido,rol,foto,carrera,clave,siglas,descripcion);
}
void Coordinador::Busqueda(Coordinador* nodo, int _id) {
	if (nodo != NULL) {
		if (_id < nodo->id)
			Busqueda(nodo->izq, _id);
		else {
			if (_id > nodo->id)
				Busqueda(nodo->der, _id);
			else {
				/*cout << nodo->id << endl;
				cout << nodo->nombre << endl;
				cout << nodo->apellidoPaterno << endl;
				cout << nodo->apellidoMaterno << endl;
				cout << nodo->carrera << endl;*/
			}
		}
	}
}
void Coordinador::openfilename() {
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.lpstrFilter = "Todos\0*.*\0Archivos Texto\0*.TXT\0Archivos Word (97-2003)\0*.doc\0Archivos Word\0*.docx\0Imagenes jpg\0*.jpg\0";
	ofn.lpstrFile = foto;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = "txt";
}