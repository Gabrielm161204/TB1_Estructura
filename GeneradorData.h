#pragma once
#include "GestorInventario.h"
#include "Marketplace.h"
class GeneradorData {
private:
	GestorInventario* inventario;
	Marketplace* market;
public:
	GeneradorData()
	{
	}

	~GeneradorData()
	{
	}

	void CargarDatosEjemplo(GestorInventario& inventario, Marketplace& market) {
		// importa el ordenamiento de productos y categorias desde un archivo o base de datos
		generarCategorias(market);
		generarProductos(inventario, market);
	}

	void CargarCantidadProductos(GestorInventario& inventario, int cantidad) {
		for (int i = 1; i <= cantidad; i++) {
			string nombre = "Producto_" + to_string(i);
			int stock = rand() % 100 + 1; // Stock aleatorio entre 1 y 100
			string categoria = (i % 3 == 0) ? "Electronica" : (i % 3 == 1) ? "Ropa" :   "Accesorios";
			double precio = (rand() % 200 + 10) * 1.5; // Precio a(i % 3 == 1) ?leatorio entre 10 y 210
			inventario.registrarProductoDirecto(Producto(nombre, stock, categoria, precio));
		}
	}

	void generarCategorias(Marketplace& market) {
		market.agregarCategoria(Categoria(1, "Electronica", "Dispositivos electronicos y accesorios"));
		market.agregarCategoria(Categoria(2, "Ropa", "Ropa y calzado para toda la familia"));
		market.agregarCategoria(Categoria(3, "Accesorios", "Mochilas, bolsos y accesorios varios"));
		//market.agregarCategoria(Categoria(4, "Libros", "Libros de diferentes generos y accesorios de ellos"));
	}
	void generarProductos(GestorInventario& inventario, Marketplace& market) {
		inventario.registrarProductoDirecto(Producto("Laptop HP", 15, "Electronica", 2500.00));
		inventario.registrarProductoDirecto(Producto("Mouse Gamer", 40, "Electronica", 85.00));
		inventario.registrarProductoDirecto(Producto("Teclado USB", 30, "Electronica", 60.00));
		inventario.registrarProductoDirecto(Producto("Polo Casual", 50, "Ropa", 35.00));
		inventario.registrarProductoDirecto(Producto("Zapatillas", 25, "Ropa", 180.00));
		inventario.registrarProductoDirecto(Producto("Mochila", 20, "Accesorios", 75.00));
		inventario.registrarProductoDirecto(Producto("Auriculares", 18, "Electronica", 120.00));
		inventario.registrarProductoDirecto(Producto("Camisa Formal", 35, "Ropa", 45.00));
	}
};
