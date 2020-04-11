#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <fstream>
#include <cstdlib>
using namespace std;
//declaramos las funciones que serviran de menu de cada tienda
void menuGadis();
void menuMercadona();
void menuObrador();
void menuGasolinera();
//declaramos la variable que será el dinero total a pagar
float total;
//creamos la clase tienda con sus atributos y métodos
class Tienda{
	protected: 
		int agua,refres,patat,choco;
		float pagua,prefres,ppatat,pchoco;
	public:
		Tienda(int,float,int,float,int,float,int,float); 
		void stock();
		void compra();
		void catalogo();
		float ventaAgua(float);
		float ventaRefresco(float);
		float ventaPatatas(float);
		float ventaChocolate(float);
};
//creamos la clase gasolinera, que tiene herencia de la clase tienda y además sus metodos propios
class Gasolinera : public Tienda{
	public:
		int gasol;
		float pgasol;
		Gasolinera(int,float,int,float,int,float,int,float,int,float);
		float ventaGasolina(float);
};
//creamos la clase cliente con sus atributos y métodos
class Cliente{
	private:
		int edad;
		
		string nombre;
	public:
		float dinero;
		Cliente(string,int,float);
		void tarjetaCliente();
		void verTarjeta();
};
//constructor de Tienda
Tienda::Tienda(int _agua,float _pagua,int _refres,float _prefres,int _patat,float _ppatat,int _choco,float _pchoco){
	agua=_agua;
	pagua=_pagua;
	refres= _refres;
	prefres= _prefres;
	patat =_patat;
	ppatat =_ppatat;
	choco =_choco;
	pchoco=_pchoco;
}
//constructor de Gasolinera
Gasolinera::Gasolinera(int _agua,float _pagua,int _refres,float _prefres,int _patat,float _ppatat,int _choco,float _pchoco,int _gasol,float _pgasol):Tienda(_agua,_pagua,_refres,_prefres,_patat,_ppatat,_choco,_pchoco){
	gasol=_gasol;
	pgasol=_pgasol;
}
//Constructor de cliente
Cliente::Cliente(string _nombre, int _edad, float _dinero){
	nombre=_nombre;
	edad=_edad;
	dinero=_dinero;
}
//Creamos un objeto de tipo cliente en el scope general para que pueda ser usado por todos los métodos
Cliente cliente1("Juan",20,90);

//definimos la funcion de tienda stock, donde se muestra la cantidad y los precios de cada producto
void Tienda::stock(){
	cout<<"====================================="<<endl;
	cout<<"La cantidad de agua disponible es: "<<agua<<". A "<<pagua<<"$ cada una"<<endl;
	cout<<"La cantidad de refrescos disponible es: "<<refres<<". A "<<prefres<<"$ cada uno"<<endl;
	cout<<"La cantidad de patatas disponible es: "<<patat<<". A "<<ppatat<<"$ cada bolsa"<<endl;
	cout<<"La cantidad de chocolate disponible es: "<<choco<<". A "<<pchoco<<"$ cada uno"<<endl;
	cout<<"====================================="<<endl;
}

//definimois el métoodo de tienda comprar, donde puedes elegir en un menú lo que quieres comprar 
//y cuando haces una selección elijes la cantidad y se ejecuta la función de venta de ese producto
void Tienda::compra(){
	int op;
	cout<<"====================================="<<endl;
	cout<<"1-Comprar agua"<<endl;
	cout<<"2-Comprar refrescos"<<endl;
	cout<<"3-Comprar patatas"<<endl;
	cout<<"4-Comprar chocolate"<<endl;
	cout<<"5-Salir"<<endl;
	cout<<"====================================="<<endl;
	cin>>op;
	switch(op){
			case 1: 
				float a;
				cout<<"Elija la cantidad que desea"<<endl;
				cin>>a;
				ventaAgua(a);
				break;
			
			case 2:
				float r;
				cout<<"Elija la cantidad que desea"<<endl;
				cin>>r;
				ventaRefresco(r);
				break;
			case 3:
				float p;
				cout<<"Elija la cantidad que desea"<<endl;
				cin>>p;
				ventaPatatas(p);
				break;
			case 4:
				float c;
				cout<<"Elija la cantidad que desea"<<endl;
				cin>>c;
				ventaChocolate(c);
				break;
			case 5:
				cout<<"Hasta la próxima!!!";
				break;
			default: cout<<"Opcion incorrecta"<<endl;
		}while(op!=5);
			
		}
//definimos el método de tienda catálogo, donde se abre y se lee un fichero creado previamente
void Tienda::catalogo(){
	ifstream fichero;
		string linea;
		fichero.open("catalogo.txt");
		
		if(fichero.fail()){
			cout<<"No se pudo ver el catalogo";
			exit(1);
		}
		while(!fichero.eof()){
			getline(fichero, linea);
			cout<<linea<<endl;
		}
		fichero.close();
}

//se define el método de cliente tarjetaCliente, donde se crea un fichero y el cliente escribe sus datos en él
void Cliente::tarjetaCliente(){
 	ofstream fichero("tarjeta.txt");
	string ape1;
	string ape2;
	string linea;
	
	if(fichero.fail()){
		cout<<"No puede abrir la lista";
		exit(1);
	}
	fichero<<cliente1.nombre<< endl;
	cout << "";
	getline(cin,ape1);
	fichero<<ape1;
	cout << "Primer apellido: ";
	getline(cin,ape1);
	fichero<<ape1<<endl;
	cout << "Segundo apellido: ";
	getline(cin,ape2);
	fichero<<ape2<<endl;
	cout << "DNI: ";
	getline(cin,linea);
	fichero<<linea<<endl;
	fichero<<"Edad: "<<cliente1.edad<<"años"<<endl;
	cout<<"Su tarjeta de cliente ha sido creada con exito!!!"<<endl;
	fichero.close();
	}
//se abre y lee el fichero tarjeta.txt que ha creado anteriormente el cliente con sus datos
void Cliente::verTarjeta(){
	ifstream fichero;
		string linea;
		fichero.open("tarjeta.txt");
		
		if(fichero.fail()){
			cout<<"No se pudo ver tu tarjeta de cliente";
			exit(1);
		}
		while(!fichero.eof()){
			getline(fichero, linea);
			cout<<linea<<endl;
		}
		fichero.close();
}
//los siguientes métodos son funciones con un parámetro que se pide en el método compra
//cuando seleccionas el producto que deseas comprar. En el se vende cierta cantidad del producto
//sólo si esa cantidad está en stock y el cliente puede pagarlo, despúes se muestran las unidades 
//vendidas, las que quedan, el precio a pagar y el dinero que le queda al cliente después de pagar 
 float Tienda::ventaAgua(float x){
	if((agua<x)||((pagua*x)>cliente1.dinero)){
		cout<<"No es posible suministrar la cantidad solicitada\n";
		cout<<"solo hay "<<agua<<" unidades disponibles y tienes "<<cliente1.dinero<<"€ para gastar";
		return 0;
	}
	else if(agua>=x){
		agua=agua-x;
		total=pagua*x;
		cout<<"====================================="<<endl;
		cout<<"\n\nUnidades vendidas: "<<(x)<<endl;
		cout<<"\nUnidades disponibles: "<<agua<<endl;
		cout<<"\nCantidad a pagar: "<<total<< "€"<<endl;
		cliente1.dinero=cliente1.dinero-total;
		cout<<"Saldo restante del cliente:"<<cliente1.dinero<<endl;
		cout<<"====================================="<<endl;
		return 0;
	}
	
}
 float Tienda::ventaRefresco(float x){
	if((refres<x)||((prefres*x)>cliente1.dinero)){
		cout<<"No es posible suministrar la cantidad solicitada\n";
		cout<<"solo hay "<<refres<<" unidades disponibles y tienes "<<cliente1.dinero<<"€ para gastar";
	}
	else if(refres>=x){
		refres=refres-x;
		total=prefres*x;
		cout<<"====================================="<<endl;
		cout<<"\n\nUnidades vendidas: "<<(x)<<endl;
		cout<<"\nUnidades disponibles: "<<refres<<endl;
		cout<<"\nCantidad a pagar: "<<total<< "€"<<endl;
		cliente1.dinero=cliente1.dinero-total;
		cout<<"Saldo restante del cliente:"<<cliente1.dinero<<endl;
		cout<<"====================================="<<endl;
	}
	return 0;
}
 float Tienda::ventaPatatas(float x){
	if((patat<x)||((ppatat*x)>cliente1.dinero)){
		cout<<"No es posible suministrar la cantidad solicitada\n";
		cout<<"solo hay "<<patat<<" unidades disponibles y tienes "<<cliente1.dinero<<"€ para gastar";
	}
	else if(patat>=x){
		patat=patat-x;
		total=ppatat*x;
		cout<<"====================================="<<endl;
		cout<<"\n\nUnidades vendidas: "<<(x)<<endl;
		cout<<"\nUnidades disponibles: "<<patat<<endl;
		cout<<"\nCantidad a pagar: "<<total<< "€"<<endl;
		cliente1.dinero=cliente1.dinero-total;
		cout<<"Saldo restante del cliente:"<<cliente1.dinero<<endl;
		cout<<"====================================="<<endl;
	}
	return 0;
}
float Tienda::ventaChocolate(float x){
	if((choco<x)||((pchoco*x)>cliente1.dinero)){
		cout<<"No es posible suministrar la cantidad solicitada\n";
		cout<<"solo hay "<<choco<<" unidades disponibles y tienes "<<cliente1.dinero<<"€ para gastar";
	}
	else if(choco>=x){
		choco=choco-x;
		total=pchoco*x;
		cout<<"====================================="<<endl;
		cout<<"\n\nUnidades vendidas: "<<(x)<<endl;
		cout<<"\nUnidades disponibles: "<<choco<<endl;
		cout<<"\nCantidad a pagar: "<<total<< "€"<<endl;
		cliente1.dinero=cliente1.dinero-total;
		cout<<"Saldo restante del cliente:"<<cliente1.dinero<<endl;
		cout<<"====================================="<<endl;
	}
	return 0;
}
float Gasolinera::ventaGasolina(float x){
	if((gasol<x)||((pgasol*x)>cliente1.dinero)){
		cout<<"No es posible suministrar la cantidad solicitada\n";
		cout<<"solo hay "<<gasol<<" unidades disponibles y tienes "<<cliente1.dinero<<"€ para gastar";
	}
	else if(gasol>=x){
		gasol=gasol-x;
		total=pgasol*x;
		cout<<"====================================="<<endl;
		cout<<"\n\nUnidades vendidas: "<<(x)<<endl;
		cout<<"\nUnidades disponibles: "<<gasol<<endl;
		cout<<"\nCantidad a pagar: "<<total<< "€"<<endl;
		cliente1.dinero=cliente1.dinero-total;
		cout<<"Saldo restante del cliente:"<<cliente1.dinero<<endl;
		cout<<"====================================="<<endl;
	}
	return 0;
}
//en la función principal creamos un menu en el que se ofrecen todas las opciones y 
//se llaman a los distintos métodos dependiendo de la elección
int main(){

	int tienda;
	do{
		cout<<"====================================="<<endl;
		cout<<"Elije la tienda en la que quieres comprar o si desea registrarse como cliente"<<endl;
		cout<<"1-Gadis"<<endl;
		cout<<"2-Mercadona"<<endl;
		cout<<"3-Obrador"<<endl;
		cout<<"4-Gasolinera"<<endl;
		cout<<"5-Crear una tarjeta de cliente"<<endl;
		cout<<"6-Ver tarjeta de cliente"<<endl;
		cout<<"7-Salir"<<endl;
		cout<<"====================================="<<endl;
		cin>>tienda;
		switch(tienda){
			case 1: menuGadis();
			break;
			case 2:
				menuMercadona();
			break;
			case 3:
				menuObrador();
			break;
			case 4:
				menuGasolinera();
				break;
			case 5:
				cliente1.tarjetaCliente();
			break;
			case 6:
				cliente1.verTarjeta();
			case 7:
				break;
			default: cout<<"Opcion incorrecta"<<endl;
		}
			
		}while(tienda!=7);
	
	return 0;	
} 

//se definen las funciones que crean los objetos de tipo tienda y que crean el menú para
//cada una de ellas
void menuGadis(){
	Tienda gadis(100,0.95,150,2,75,1.25,100,1);
	int opcion;
	do{
		cout<<"====================================="<<endl;
		cout<<"Elije una de las siguientes opciones"<<endl;
		cout<<"1-Ver stock"<<endl;
		cout<<"2-Comprar en tienda"<<endl;
		cout<<"3-Catalogo"<<endl;
		cout<<"4-Salir"<<endl;
		cout<<"====================================="<<endl;
		cin>>opcion;
		switch(opcion){
			case 1: 
				gadis.stock();
			break;
			case 2:
				gadis.compra();
			break;
			case 3:
				gadis.catalogo();
			break;
			case 4:
				break;
			default: cout<<"Opcion incorrecta"<<endl;
		}
			
		}while(opcion!=4);
}
void menuMercadona(){
	Tienda mercadona(500,1,300,1.90,200,1.40,250,0.80);
	int opcion;
	do{
		cout<<"====================================="<<endl;
		cout<<"Elije una de las siguientes opciones"<<endl;
		cout<<"1-Ver stock"<<endl;
		cout<<"2-Comprar en tienda"<<endl;
		cout<<"3-Catalogo"<<endl;
		cout<<"4-Salir"<<endl;
		cout<<"====================================="<<endl;
		cin>>opcion;
		switch(opcion){
			case 1: 
				mercadona.stock();
			break;
			case 2:
				mercadona.compra();
			break;
			case 3:
				mercadona.catalogo();
			break;
			case 4:
				break;
			default: cout<<"Opcion incorrecta"<<endl;
		}
			
		}while(opcion!=4);
}
void menuObrador(){
	Tienda obrador(20,0.90,25,2,15,1.15,20,1.20);
	int opcion;
	do{
		cout<<"====================================="<<endl;
		cout<<"Elije una de las siguientes opciones"<<endl;
		cout<<"1-Ver stock"<<endl;
		cout<<"2-Comprar en tienda"<<endl;
		cout<<"3-Catalogo"<<endl;
		cout<<"4-Salir"<<endl;
		cout<<"====================================="<<endl;
		cin>>opcion;
		switch(opcion){
			case 1: 
				obrador.stock();
			break;
			case 2:
				obrador.compra();
			break;
			case 3:
				obrador.catalogo();
			break;
			case 4:
				break;
			default: cout<<"Opcion incorrecta"<<endl;
		}
			
		}while(opcion!=4);
}

void menuGasolinera(){
	Gasolinera gasolinera(25,1,25,2.10,30,1.25,25,1.05,1500,1.33);
	int opcion;
	do{
		cout<<"====================================="<<endl;
		cout<<"Elije una de las siguientes opciones"<<endl;
		cout<<"1-Ver stock"<<endl;
		cout<<"2-Comprar en tienda"<<endl;
		cout<<"3-Comprar gasolina"<<endl;
		cout<<"4-Catalogo"<<endl;
		cout<<"5-Salir"<<endl;
		cout<<"====================================="<<endl;
		cin>>opcion;
		switch(opcion){
			case 1: 
				gasolinera.stock();
			break;
			case 2:
				gasolinera.compra();
			break;
			case 3:
				float g;
				cout<<"Hay "<<gasolinera.gasol<<" litros disponibles a "<<gasolinera.pgasol<<"€/litro"<<endl;
				cout<<"Elija la cantidad que desea"<<endl;
				cin>>g;
				gasolinera.ventaGasolina(g);
			break;
			case 4:
				gasolinera.catalogo();
			break;
			case 5:
				break;
			default: cout<<"Opcion incorrecta"<<endl;
		}
			
		}while(opcion!=5);
}


