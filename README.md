# GreenGrassEngine-
Es un repositorio de la clase de "Arquitectura de motores gráficos".
Proyecto de Carga y Renderizado de Modelos 3D en DirectX
Descripción
Este proyecto es una aplicación gráfica desarrollada en C++ que permite la carga, procesamiento y renderizado de modelos 3D en formato FBX utilizando DirectX y el SDK de Autodesk FBX. El objetivo principal es permitir la manipulación y visualización de modelos 3D, con capacidades para modificar atributos como posición, rotación, y escala, así como procesar y aplicar materiales y texturas.

Características
Carga de Modelos FBX: Utiliza el SDK de Autodesk FBX para importar modelos 3D, extrayendo vértices, índices, UVs y materiales.
Procesamiento de Mallas: Permite procesar cada malla contenida en los modelos, extrayendo información geométrica y de texturas.
Renderizado con DirectX: Implementa un pipeline de renderizado utilizando DirectX, con shaders personalizables para la representación gráfica de los modelos.
Manipulación de Atributos: Los usuarios pueden modificar atributos de los modelos como posición, rotación y escala.
Gestión de Materiales: Procesa y aplica materiales extraídos de los modelos FBX, incluyendo la gestión de texturas difusas.
Estructura del Proyecto
ModelLoader: Clase principal para la carga y procesamiento de modelos FBX. Maneja la importación de modelos, extracción de datos geométricos y materiales, y organiza la información en estructuras adecuadas para su uso en DirectX.

LoadModel: Carga el archivo FBX y procesa su contenido.
ProcessNode: Procesa cada nodo del modelo, identificando si contiene mallas.
ProcessMesh: Extrae vértices, índices y UVs de las mallas.
ProcessMaterials: Procesa los materiales asociados a las mallas, extrayendo nombres de texturas.
ShaderProgram: Clase encargada de la gestión de shaders. Compila y maneja shaders de vértices y píxeles, y gestiona los layouts de entrada para la renderización.

CompileShaderFromFile: Compila un shader a partir de un archivo.
CreateShader: Crea y configura los shaders de vértices y píxeles.
CreateInputLayout: Configura el layout de entrada para los shaders.
Viewport: Clase que maneja el viewport de renderizado, definiendo el área de la ventana donde se renderizan los modelos.

Requisitos
Microsoft Visual Studio
DirectX 11 SDK
Autodesk FBX SDK
Instalación
Clona el repositorio del proyecto.
Configura tu entorno de desarrollo para incluir las rutas de DirectX y el FBX SDK.
Compila el proyecto en Visual Studio.
Uso
Ejecuta la aplicación para cargar un modelo FBX.
Utiliza la interfaz para manipular el modelo cargado.
Observa el renderizado en tiempo real en la ventana de la aplicación.