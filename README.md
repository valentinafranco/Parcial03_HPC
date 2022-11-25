# Parcial03_HPC

**Universidad Sergio Arboleda**

*Autor:* Valentina Del Pilar Franco Suárez

*Correo institucional:* valentina.franco01@correo.usa.edu.co

*Fecha:* 23/11/2022

*Escuela:* Ciencias exactas e ingeniería

*Materia:* Introducción a HPC para IA

*Docente:* John Jairo Corredor Franco

-------------------------------------------------------

## **Introducción**

Como parcial del tercer corte de la materia Intrpducción a HPC para IA se realizo la construcción de dos modelos de Regresión Lineal en dos lenguajes diferentes, Python y C++. El proyecto se divide en 5 objetivos específicos.

### 1. Seleccionar un dataset

Se debía elegir un dataset diferente por ingeniero, esto para poder hacer pruebas en multiples modelos con multiples datos. En mi caso elegí el dataset de Concrete Compressive Strength. El concreto es un material muy importante en la ingeniería civil, se compone de varios ingredientes y para este dataset se mide la resistencia como problema.

##### Variables de entrada

*   **Cement:** Es un polvo fino de una mezcla de piedra caliza, arcilla y mineral de hierro. Cantidad que se tiene en el concreto con las unidades kg en una mezcla de m3.
*   **Blast Furnace Slag:** Se genera en la granulación de la escoria del alto horno (apagado rápido de la escoria con agua), se utiliza en la producción de cemento. La escoria, material granular vítreo, se forma a partir de la ganga de los minerales y las cenizas provenientes del coque y el carbón. Cantidad que se tiene en el concreto con las unidades kg en una mezcla de m3.
*   **Fly Ash:** Son el residuo finamente dividido resultante de la combustión del carbón, ya sea en trozos o en polvo. Cantidad que se tiene en el concreto con las unidades kg en una mezcla de m3.
*   **Water:** Es un líquido inodoro, insípido e incoloro. Cantidad que se tiene en el concreto con las unidades kg en una mezcla de m3.
*   **Superplasticizer:** Aumenta la manejabilidad de las pastas de cemento y por lo tanto la manejabilidad del concreto. Este incremento en la manejabilidad hace posible disminuir el contenido de agua y de cemento (son ahorradores de pasta) manteniendo la fluidez del material y su resistencia. Cantidad que se tiene en el concreto con las unidades kg en una mezcla de m3.
*   **Coarse Aggregate** Es aquel que es retenido 100% en el tamiz N° 4 o superior. Cantidad que se tiene en el concreto con las unidades kg en una mezcla de m3.
*   **Fine Aggregate:** Es aquel que es retenido 100% el tamiz 3/8” y queda retenido en la malla N° 200. Cantidad que se tiene en el concreto con las unidades kg en una mezcla de m3.
*   **Age:** Edad del concreto medida en días (1 - 365).


#### Variable de salida
*   **Concrete compressive strength:** La resistencia a la compresión simple es la característica mecánica principal del concreto. Se define como la capacidad para soportar una carga por unidad de área, y se expresa en términos de esfuerzo, generalmente en kg/cm2, MPa.

### 2. Análitica de datos sobre el dataset seleccionado

Está analítica de datos se realizo con respecto a la necesidad de las variables a estudiar, todo esto puede ser encontrado en el colab Parcial3HPC_FrancoValentina que se encuentra en este mismo repositorio.

### 3. Modelar usando la regresión lineal usando: Python,  Scikit-Learn

El modelo está construido en el mismo colab que la analítica de datos, lo encuentra en este repositorio.

### 4. Modelar usando la regresión lineal usando: C++

El modelo está diseñado en la carpeta de LinealRegresion donde se encuentra el main, la carpeta de regression, la carpeta extraccion, el dataset y los archivos generados. En este repositorio lo puede encontrar.

### 5. Comparación de modelos

La comparación de los modelos se realizo en el colab que encuentra en este repositorio.

## **RECORDATORIO: Todo el proyecto fue trabajado en el colab Parcial3HPC_FrancoValentina exceptuando el modelo en C++ que se encuentra en la carpeta de LinealRegresion**
