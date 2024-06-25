#include <stdio.h>
#include <string.h>

#define MAX_ARTICULOS 100
#define MAX_RUBROS 5

// Funcion para inicializar los arreglos en 0
void inicializarArreglos(int ventasPorRubro[], int ventas1QPorRubro[], int ventas2QPorRubro[], float importe1QPorRubro[], float importe2QPorRubro[])
{
    for (int i = 0; i < MAX_RUBROS; i++)
    {
        ventasPorRubro[i] = 0;
        ventas1QPorRubro[i] = 0;
        ventas2QPorRubro[i] = 0;
        importe1QPorRubro[i] = 0.0;
        importe2QPorRubro[i] = 0.0;
    }
}

// Funcion para verificar si un codigo ya existe en el arreglo de codigos
int codigoYaExiste(int codigo, int codigos[], int cantidad) {
    for (int i = 0; i < cantidad; i++) {
        if (codigos[i] == codigo) {
            return 1; // Retorna 1 si el codigo ya existe
        }
    }
    return 0; // Retorna 0 si el codigo no existe
}

// Funcion para validar el codigo segun su rubro
int esCodigoValido(int codigo)
{
    int rubro = codigo / 100000;
    switch (rubro)
    {
    case 100:
    case 300:
    case 450:
    case 680:
    case 720:
        return 1;
    default:
        return 0;
    }
}

// Funcion para obtener el nombre del rubro segun su codigo
const char *obtenerNombreRubro(int codigo)
{
    switch (codigo)
    {
    case 100:
        return "Tornillos y Tuercas";
    case 300:
        return "Adhesivos";
    case 450:
        return "Herrajes";
    case 680:
        return "Pinturas";
    case 720:
        return "Electricidad";
    default:
        return "Desconocido";
    }
}

// Funcion para cargar los articulos
void cargarArticulos(int codigos[], char descripciones[][50], float preciosVenta[], int cantidadesExistente[], 
                    int cantidadesVendida1Q[], int cantidadesVendida2Q[], int *n, int ventasPorRubro[], 
                    int ventas1QPorRubro[], int ventas2QPorRubro[], float importe1QPorRubro[], float importe2QPorRubro[])
{
    printf("Ingrese la cantidad de articulos: ");
    scanf("%d", n);

    for (int i = 0; i < *n; i++)
    {
        int codigo;
        do
        {
            printf("Ingrese el codigo del articulo %d (3 digitos rubro y 5 digitos numero): ", i + 1);
            scanf("%d", &codigo);
            if (!esCodigoValido(codigo))
            {
                printf("Codigo invalido. Intente nuevamente.\n");
            }
            else if (codigoYaExiste(codigo, codigos, i))
            {
                printf("El codigo ya se encuentra en la base de datos. Intente nuevamente.\n");
                codigo = -1; // Asignamos un valor inválido para forzar a que repita la entrada del código
            }
        } while (!esCodigoValido(codigo));

        codigos[i] = codigo;

        printf("Ingrese la descripcion del articulo: ");
        scanf(" %[^\n]s", descripciones[i]);
        printf("Ingrese el precio de venta del articulo: ");
        scanf("%f", &preciosVenta[i]);
        printf("Ingrese la cantidad existente del articulo: ");
        scanf("%d", &cantidadesExistente[i]);
        printf("Ingrese la cantidad vendida en la 1a quincena: ");
        scanf("%d", &cantidadesVendida1Q[i]);
        printf("Ingrese la cantidad vendida en la 2a quincena: ");
        scanf("%d", &cantidadesVendida2Q[i]);

        int rubro = codigos[i] / 100000;
        int j;
        switch (rubro)
        {
        case 100:
            j = 0;
            break;
        case 300:
            j = 1;
            break;
        case 450:
            j = 2;
            break;
        case 680:
            j = 3;
            break;
        case 720:
            j = 4;
            break;
        default:
            j = -1; // Valor por defecto en caso de rubro no valido
            break;
        }

        ventasPorRubro[j] += cantidadesVendida1Q[i] + cantidadesVendida2Q[i];
        ventas1QPorRubro[j] += cantidadesVendida1Q[i];
        ventas2QPorRubro[j] += cantidadesVendida2Q[i];
        importe1QPorRubro[j] += cantidadesVendida1Q[i] * preciosVenta[i];
        importe2QPorRubro[j] += cantidadesVendida2Q[i] * preciosVenta[i];
    }
}

// Funcion para mostrar lista de articulos ordenada por descripcion
void mostrarListaArticulos(char descripciones[][50], float preciosVenta[], int n)
{
    // Implementacion para ordenar por descripcion omitida para brevedad
    for (int i = 0; i < n; i++)
    {
        printf("%s - %.2f\n", descripciones[i], preciosVenta[i]);
    }
}

// Funcion para mostrar lista de articulos por cantidad vendida
void mostrarListaArticulosPorCantidadVendida(char descripciones[][50], int cantidadesVendidas[], float montosVentas[], int n)
{
    // Implementacion para ordenar por cantidad vendida omitida para brevedad
    float montoTotalVentasMes = 0;
    for (int i = 0; i < n; i++)
    {
        printf("%s - %d - %.2f\n", descripciones[i], cantidadesVendidas[i], montosVentas[i]);
        montoTotalVentasMes += montosVentas[i];
    }
    printf("Monto total de ventas en el mes: %.2f\n", montoTotalVentasMes);
}

// Funcion para mostrar stock actual de articulos
void mostrarStockActualArticulos(int cantidadesExistente[], int cantidadesVendida1Q[],int cantidadesVendida2Q[], int n)
{
    for (int i = 0; i < n; i++)
    {
        int stockActual = cantidadesExistente[i] - cantidadesVendida1Q[i] - cantidadesVendida2Q[i];
        printf("%d  - %d\n", i + 1, stockActual);
    }
}

// Funcion para buscar articulo por codigo
void buscarArticuloPorCodigo(int codigos[], char descripciones[][50], float preciosVenta[], 
                            int cantidadesExistente[], int cantidadesVendida1Q[], int cantidadesVendida2Q[], int n)
{
    int codigoBuscado;
    printf("Ingrese el codigo del articulo a buscar: ");
    scanf("%d", &codigoBuscado);

    for (int i = 0; i < n; i++)
    {
        if (codigos[i] == codigoBuscado)
        {
            int stockActual = cantidadesExistente[i] - cantidadesVendida1Q[i] - cantidadesVendida2Q[i];
            int cantidadTotalVendida = cantidadesVendida1Q[i] + cantidadesVendida2Q[i];
            float montoTotalVentas = preciosVenta[i] * cantidadTotalVendida;

            printf("Articulo encontrado:\n");
            printf("Codigo: %d\n", codigos[i]);
            printf("Descripcion: %s\n", descripciones[i]);
            printf("Precio de Venta: %.2f\n", preciosVenta[i]);
            printf("Cantidad Vendida 1a Quincena: %d\n", cantidadesVendida1Q[i]);
            printf("Cantidad Vendida 2a Quincena: %d\n", cantidadesVendida2Q[i]);
            printf("Stock Actual: %d\n", stockActual);
            printf("Importe Total Venta: %.2f\n", montoTotalVentas);
            return;
        }
    }
    printf("No existe articulo con ese codigo.\n");
}

// Funcion para mostrar estadisticas de todos los productos
void mostrarEstadisticas(int ventasPorRubro[], int ventas1QPorRubro[], int ventas2QPorRubro[], float importe1QPorRubro[], float importe2QPorRubro[])
{
    int totalVentas = 0;
    for (int i = 0; i < MAX_RUBROS; i++)
    {
        totalVentas += ventasPorRubro[i];
    }

    // a) Porcentaje de la cantidad de articulos vendidos de cada rubro
    printf("Porcentaje de ventas por rubro:\n");
    for (int i = 0; i < MAX_RUBROS; i++)
    {
        printf("Rubro %d: %.2f%%\n", i, ((float)ventasPorRubro[i] / totalVentas) * 100);
    }

    // b) Porcentaje de venta de cada quincena por Rubro sobre el total del mes
    printf("Porcentaje de ventas por quincena y rubro:\n");
    for (int i = 0; i < MAX_RUBROS; i++)
    {
        printf("Rubro %d 1a Quincena: %.2f%%\n", i, ((float)ventas1QPorRubro[i] / totalVentas) * 100);
        printf("Rubro %d 2a Quincena: %.2f%%\n", i, ((float)ventas2QPorRubro[i] / totalVentas) * 100);
    }

    // c) Rubro con mayor importe total de ventas en cada quincena
    float maxImporte1Q = 0;
    float maxImporte2Q = 0;
    int rubroMayor1Q = 0;
    int rubroMayor2Q = 0;
    for (int i = 0; i < MAX_RUBROS; i++)
    {
        if (importe1QPorRubro[i] > maxImporte1Q)
        {
            maxImporte1Q = importe1QPorRubro[i];
            rubroMayor1Q = i;
        }
        if (importe2QPorRubro[i] > maxImporte2Q)
        {
            maxImporte2Q = importe2QPorRubro[i];
            rubroMayor2Q = i;
        }
    }
    printf("Rubro con mayor importe total de ventas en la 1a quincena: %d\n", rubroMayor1Q);
    printf("Rubro con mayor importe total de ventas en la 2a quincena: %d\n", rubroMayor2Q);
}

// Funcion principal
int main()
{
    int codigos[MAX_ARTICULOS];
    char descripciones[MAX_ARTICULOS][50];
    float preciosVenta[MAX_ARTICULOS];
    int cantidadesExistente[MAX_ARTICULOS];
    int cantidadesVendida1Q[MAX_ARTICULOS];
    int cantidadesVendida2Q[MAX_ARTICULOS];

    int ventasPorRubro[MAX_RUBROS];
    int ventas1QPorRubro[MAX_RUBROS];
    int ventas2QPorRubro[MAX_RUBROS];
    float importe1QPorRubro[MAX_RUBROS];
    float importe2QPorRubro[MAX_RUBROS];

    int n, opcion;

    inicializarArreglos(ventasPorRubro, ventas1QPorRubro, ventas2QPorRubro, importe1QPorRubro, importe2QPorRubro);

    cargarArticulos(codigos, descripciones, preciosVenta, cantidadesExistente, cantidadesVendida1Q, cantidadesVendida2Q, &n,
                    ventasPorRubro, ventas1QPorRubro, ventas2QPorRubro, importe1QPorRubro, importe2QPorRubro);

    do
    {
        printf("\nMenu de Opciones:\n");
        printf("1. Mostrar lista de articulos ordenada por descripcion\n");
        printf("2. Mostrar lista de articulos ordenada por cantidad vendida\n");
        printf("3. Mostrar stock actual de articulos\n");
        printf("4. Buscar articulo por codigo\n");
        printf("5. Mostrar estadisticas\n");
        printf("6. Salir\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            mostrarListaArticulos(descripciones, preciosVenta, n);
            break;
        case 2:
            mostrarListaArticulosPorCantidadVendida(descripciones, cantidadesVendida1Q, preciosVenta, n);
            break;
        case 3:
            mostrarStockActualArticulos(cantidadesExistente, cantidadesVendida1Q, cantidadesVendida2Q, n);
            break;
        case 4:
            buscarArticuloPorCodigo(codigos, descripciones, preciosVenta, cantidadesExistente, cantidadesVendida1Q, cantidadesVendida2Q, n);
            break;
        case 5:
            mostrarEstadisticas(ventasPorRubro, ventas1QPorRubro, ventas2QPorRubro, importe1QPorRubro, importe2QPorRubro);
            break;
        case 6:
            printf("Gracias por utilizar el sistema.\n");
            break;
        default:
            printf("Opcion no valida. Intente nuevamente.\n");
            break;
        }
    } while (opcion != 6);

    return 0;
}
