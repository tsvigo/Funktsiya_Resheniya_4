#include "dialog.h"
#include "ui_dialog.h"
//###########################################################################
#include <QDataStream>
#include <QDebug>
#include <QFile>
#include <iostream>
//###########################################################################
// переменные:
bool Odin_Uchitelia;
bool Odin_Programmi;
int var;
int neuron_index = 0, synapse_index = 0;
//###########################################################################
// функции:
//###########################################################################
// 1.) Function to write a vector to a file
// writeVectorToFile:

//                     Открывает файл в режиме только для записи.
//                     Использует QDataStream для сериализации размера и элементов вектора.
//                     Обрабатывает ошибки, если файл не может быть открыт.
void writeVectorToFileU(const std::vector<unsigned long long> &vec, const QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
        qCritical() << "Не могу открыть файл для записи:" << filename;
        return;
    }

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_5_0);     // Ensure the same version for reading and writing
    out << static_cast<quint32>(vec.size()); // Write the size of the vector
    for (unsigned long long value : vec) {
        out << static_cast<quint64>(value); // Write each element of the vector
    }

    file.close();
}

//###########################################################################
//###########################################################################
// 2.) Function to read a vector from a file
// readVectorFromFileU:

//                      Открывает файл в режиме только для чтения.
//                      Использует QDataStream для десериализации размера и элементов вектора.
//                      Обрабатывает ошибки, если файл не может быть открыт.

std::vector<unsigned long long> readVectorFromFileU(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        qCritical() << "Не могу открыть файл для чтения:" << filename;
        return {};
    }

    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_5_0); // Ensure the same version for reading and writing
    quint32 size;
    in >> size; // Read the size of the vector

    std::vector<unsigned long long> vec(size);
    for (quint32 i = 0; i < size; ++i) {
        quint64 value;
        in >> value; // Read each element of the vector
        vec[i] = static_cast<unsigned long long>(value);
    }

    file.close();
    return vec;
}
//###########################################################################
//###########################################################################
// 3.) Function to compare two vectors
// Сравнительные векторы:

//       Сравнивает два вектора, используя оператор равенства (==).
bool compareVectorsU(const std::vector<unsigned long long> &vec1,
                     const std::vector<unsigned long long> &vec2)
{
    return vec1 == vec2;
}
//###########################################################################
// конец объявлений функций
//###########################################################################
Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    //########################################################################################################
    std::cout << "Funktsiya_Resheniya_4" << std::endl;
    //########################################################################################################
    //########################################################################################################
    // читаем нейроны в вектор
    std::vector<unsigned long long> list_of_neurons = readVectorFromFileU(
        "/mnt/6017d124-d970-486e-b68f-59b516dd0511/risunki_Stability_Matrix/"
        "chars74k_png_Fnt_Sample1_black-white/300/txt/1/neurons_and_signal.txt");
    std::cout << "конец чтения нейронов в вектор" << std::endl;
    ///#################### считываем синапсы из файла в вектор #######################################################
    std::vector<unsigned long long> list_of_synapses = readVectorFromFileU(
        "/home/viktor/my_projects_qt_2/Funktsiya_Resheniya_2/synapses.txt");
    std::cout << "конец чтения синапсов в вектор" << std::endl;
    std::cout << "//"
                 "#################################################################################"
                 "#######################"
              << std::endl;
    // блок вычисления-решения 200 нейрона
    //###########################################################################//###########################################################################
    //###########################################################################//###########################################################################
    // проверка - решение
    for (var = 100; // первый for
         var < 200;
         ++var) // This is the range of neurons
    {
        //    if (list_of_neurons->at(200)<0) break;
        for (neuron_index = 0, synapse_index = 0;

             /*,*/ synapse_index < 10100;
             ++neuron_index, synapse_index = synapse_index + 100)

        { // // ошибка сегментации

            //if (synapse_index>10100 )
            if (neuron_index < 200 //&& synapse_index<200
            )

                list_of_neurons.at(var)
                    //###########################################################################
                    = list_of_neurons.at(var) //-5310911
                      + ((list_of_neurons.at(neuron_index)
                          //  /   // деление
                          -                                     // вычитаем
                          list_of_synapses.at(synapse_index))); // + на -

        } //
    }
    //////////////////////
    for (int neuron_index = 100, synapse_index = 10000; // второй for

         synapse_index < 10100;
         ++neuron_index, ++synapse_index) {
        //      if (list_of_synapses->at(synapse_index)!=0)
        list_of_neurons.at(200)
            //###########################################################################
            = list_of_neurons.at(200) //-5310911
              + ((list_of_neurons.at(neuron_index)
                  //  / // деление
                  -                                     // вычитание
                  list_of_synapses.at(synapse_index))); // + на -
    }

    //###########################################################################
    //###########################################################################
    //########################################################################################################
    /////////////   показываем что определила программа
    if
        //  ( variable_error <=0)
        (list_of_neurons.at(200) < 0)

    {
        ui->label->setText("Программа считает что это 1.");
        std::cout << "Программа считает что это 1." << std::endl;
        Odin_Programmi = true;
        // std::cout << "Программа остановлена. Ошибки в форматах синапсов или нейронов."<< std::endl;
    }
    //         else
    if (list_of_neurons.at(200) >= 0) {
        ui->label->setText("Программа считает что это не 1.");
        std::cout << "Программа считает что это не 1." << std::endl;
        Odin_Programmi = false;
    }
    //########################################################################################################
    std::cout << "240 строка (после решения): list_of_neurons->at(200) = "
              << list_of_neurons.at(200) << std::endl;

} // конец диалога

Dialog::~Dialog()
{
    delete ui;
}
