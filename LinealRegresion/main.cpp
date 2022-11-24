/*
 * Fecha: 21 sept 2022
 * Autor: Valentina Franco
 * Materia: HPC
 * Tópico: Implementación de la Regresión Lineal como
 * modelo en C++
 * Requerimientos:
 * - Construir una clase Extraction, que permita
 * manipular, extraer y cargar los datos.
 * - Construir una clase LinearRegression, que permita
 * los calculos de la función de costo, gradiente descendiente
 * entre otras. */

#include "Extraccion/extractiondata.h"
#include "Regression/linearregresion.h"
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <eigen3/Eigen/Dense>
#include <list>
#include <vector>
#include <fstream>

int main(int argc, char* argv[])
{
    /* Se crea un objeto tipo Estraccion */
    ExtractionData ExData(argv[1], argv[2], argv[3]);

    /* Se instancia la clase de regression lineal en un objeto */
    LinearREgresion modeloLR;

    /* Se crea un vector de vectores del tipo String para cargar objeto ExData lectura */
    std::vector<std::vector<std::string>> dataframe = ExData.LeerCSV();

    /* Cantidad de filas y columnas */
    int filas = dataframe.size() + 1;
    int columnas = dataframe[0].size();

    //std::cout << "Filas: " << filas << std::endl;
    //std::cout << "Columnas: " << columnas << std::endl;

    /* Se crea una matriz Eigen, para ingresar los valores de esa matriz */
    Eigen::MatrixXd matData = ExData.CSVtoEigen(dataframe, filas, columnas);

    /*Se normaliza la matriz de los datos */
    Eigen::MatrixXd matNorm = ExData.Norm(matData);

    /*Se divide en datos de entrenamiento y datos de prueba*/
    Eigen::MatrixXd X_train, y_train, X_test, y_test;

    std::tuple<Eigen::MatrixXd,Eigen::MatrixXd,Eigen::MatrixXd,Eigen::MatrixXd> div_datos = ExData.TrainTestSplit(matNorm, 0.8);
    /*Se descomprime la tupla en 4 conjuntos */

    std::tie(X_train,y_train,X_test,y_test) = div_datos;

    //std::cout<<"Matriz de entrenamiento, número " << X_train.rows() << " de Filas"<<std::endl;
    //std::cout<<"Matriz de prueba, número " << X_test.rows() << " de Filas"<<std::endl;
    //std::cout<<"Matriz total, número " << matNorm.rows() << " de Filas"<<std::endl;

    /* Se crean vectores auxiliares para prueba y entrenamiento inicializando en 1 */
    Eigen::MatrixXd V_train = Eigen::VectorXd::Ones(X_train.rows());
    Eigen::MatrixXd V_test = Eigen::VectorXd::Ones(X_test.rows());

    /* Se redimensiona la matriz de entrenamiento y de prueba para ser
     * ajustadas a los vectores auxiliares anteriores */
    X_train.conservativeResize(X_train.rows(), X_train.cols()+1);
    X_train.col(X_train.cols()-1) = V_train;

    X_test.conservativeResize(X_test.rows(), X_test.cols()+1);
    X_test.col(X_test.cols()-1) = V_test;

    /* Se crea el vector de coeficientes theta */
    Eigen::VectorXd theta = Eigen::VectorXd::Zero(X_train.cols());
    Eigen::VectorXd thetaN = Eigen::VectorXd::Zero(X_test.cols());

    /* Se establece el alpha como ratio de aprendizaje de tipo flotante */
    float alpha = 0.01;
    int num_iter = 1000;

    /* Se crea un vector para almacenar la theta de salida (Parametros m y d) */
    Eigen::VectorXd theta_out;
    Eigen::VectorXd theta_outN;
    /* Se crea un vector sencillo (std) de flotantes
     * para almacenar los valores del costo */
    std::vector<float> costo;
    std::vector<float> costoN;
    /* Se calcula el gradiente descendiente */
    std::tuple<Eigen::VectorXd, std::vector<float>> g_descendiente = modeloLR.GradientDescent(X_train,
                                                                                              y_train,
                                                                                              theta,
                                                                                              alpha,
                                                                                              num_iter);
    /* Se desempaqueta la gradiente descendiente */
    std::tie(theta_out, costo) = g_descendiente;
    std::tie(theta_outN, costoN) = g_descendiente;

    /* Se almacena los valores de thetas y costos en un fichero
     * para posteriormente ser visualizados */
    ExData.VectorToFile(costo, "costos.txt");
    ExData.EigenToFile(theta_out, "thetas.txt");
    ExData.VectorToFile(costoN, "costosN.txt");
    ExData.EigenToFile(theta_outN, "thetasN.txt");

    /* Se extrae el promedio de la matriz de entrada */
    auto prom_data = ExData.Promedio(matData);

    /* Se extraen los valores de las variables independientes */
    auto var_prom_independientes = prom_data(0, 8);

    /* Se escalan los datos */
    auto datos_escalados = matData.rowwise() - matData.colwise().mean();

    /* Se extrae la desviación estandar de los datos escalados */
    auto desv_stand = ExData.DevStand(datos_escalados);

    /* Se extraen los valores de la variable independiente */
    auto var_desv_independientes = desv_stand(0, 8);

    /* Se crea una matriz para almacenar los valores estimados de entrenamiento */
    Eigen::MatrixXd y_train_hat = (X_train * theta_out * var_desv_independientes).array() + var_prom_independientes;
    Eigen::MatrixXd y_test_hat = (X_test * theta_out * var_desv_independientes).array() + var_prom_independientes;

    /* Matriz para los valores reales de Y */
    Eigen::MatrixXd y_train_real = matData.col(8).topRows(825);
    Eigen::MatrixXd y_test_real = matData.col(8).bottomRows(206);

    //std::cout << "Metrica R2: " <<  y_train_real.rows() << std::endl;
    //std::cout << "Metrica R2: " <<  y_train_hat.rows() << std::endl;

    /* Se revisa que tan bueno fue el modelo a traves de la metrica de rendimiento */
    float metrica_R21 = modeloLR.R2_Score(y_train_real, y_train_hat);
    std::cout << "Metrica R2 con entrenamiento: " << metrica_R21 << std::endl;
    float metrica_R22 = modeloLR.R2_Score(y_test_real, y_test_hat);
    std::cout << "Metrica R2 con prueba: " << metrica_R22 << std::endl;
    float metrica_MSE = modeloLR.mse(y_train_real, y_train_hat);
    std::cout<< "Métrica MSE: "<<metrica_MSE<<std::endl;
    float metrica_RMSE = modeloLR.rmse(y_train_real, y_train_hat);
    std::cout<< "Métrica RMSE: "<<metrica_RMSE<<std::endl;

    std::cout << "Promedio con C++: " << ExData.Promedio(matData) << std::endl;
    std::cout << "Desviación con C++: " << ExData.DevStand(datos_escalados) << std::endl;

    return EXIT_SUCCESS;
}
