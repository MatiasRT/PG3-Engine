#include "Importer.h"

Header Importer::LoadBMP(const char * name) {

	// Lectura de información del encabezado del archivo
	unsigned char header[54]; // Each BMP file begins by a 54-bytes header
	FILE * file;
	fopen_s(&file, name, "rb");
	Header h;

	if (CheckFormat(name, header, file)) {
		// Lectura de los enteros desde el arreglo de bytes
		h.dataPos = *(int*)&(header[0x0A]);
		h.imageSize = *(int*)&(header[0x22]);
		h.width = *(int*)&(header[0x12]);
		h.height = *(int*)&(header[0x16]);
	}

	// Algunos archivos BMP tienen un mal formato, así que adivinamos la información faltante
	if (h.imageSize == 0)    
		h.imageSize = h.width * h.height * 3;	// 3 : un byte por cada componente Rojo (Red), Verde (Green) y Azul(Blue)
	if (h.dataPos == 0)      
		h.dataPos = 54;						// El encabezado del BMP está hecho de ésta manera

	// Se crea un buffer
	h.data = new unsigned char[h.imageSize];

	// Leemos la información del archivo y la ponemos en el buffer
	fread(h.data, 1, h.imageSize, file);

	//Todo está en memoria ahora, así que podemos cerrar el archivo
	fclose(file);

	return h;
}

bool Importer::CheckFormat(const char * name, unsigned char header[], FILE * file) {

	if (!file) {
		printf("Image could not be opened\n"); 
		return 0; 
	}

	if (fread(header, 1, 54, file) != 54) { // If not 54 bytes read : problem
		printf("Not a correct BMP file\n");
		return false;
	}

	if (header[0] != 'B' || header[1] != 'M') {
		printf("Not a correct BMP file\n");
		return 0;
	}


}