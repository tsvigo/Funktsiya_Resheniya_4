#include "dialog.h"
#include "ui_dialog.h"
//###########################################################################
#include <QDataStream>
#include <QDebug>
#include <QFile>
#include <fstream>
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
bool writeVectorToFileLL(const std::vector<long long> &vec, const std::string &filename)
{
    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile) {
        std::cerr << "Cannot open the file for writing: " << filename << std::endl;
        return false;
    }

    size_t size = vec.size();
    outFile.write(reinterpret_cast<const char *>(&size), sizeof(size));
    outFile.write(reinterpret_cast<const char *>(vec.data()), size * sizeof(long long));

    outFile.close();
    return true;
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
bool readVectorFromFileLL(std::vector<long long> &vec, const std::string &filename)
{
    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile) {
        std::cerr << "Cannot open the file for reading: " << filename << std::endl;
        return false;
    }

    size_t size;
    inFile.read(reinterpret_cast<char *>(&size), sizeof(size));
    vec.resize(size);
    inFile.read(reinterpret_cast<char *>(vec.data()), size * sizeof(long long));

    inFile.close();
    return true;
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
bool compareVectorsLL(const std::vector<long long> &vec1, const std::vector<long long> &vec2)
{
    if (vec1.size() != vec2.size()) {
        return false;
    }
    for (size_t i = 0; i < vec1.size(); ++i) {
        if (vec1[i] != vec2[i]) {
            return false;
        }
    }
    return true;
}
//###########################################################################
// Функция для чтения чисел из бинарного файла
std::vector<unsigned long long> readNumbersFromFile2(const QString &fileName, size_t count)
{
    std::vector<unsigned long long> list_of_synapses;
    list_of_synapses.reserve(count);

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        std::cerr << "Failed to open file for reading." << std::endl;
        return list_of_synapses;
    }

    QDataStream in(&file);
    unsigned long long number;
    while (list_of_synapses.size() < count && !in.atEnd()) {
        in >> number;
        list_of_synapses.push_back(number);
    }

    file.close();
    return list_of_synapses;
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
    //    std::vector<unsigned long long> list_of_synapses = readVectorFromFileU(
    //        //    "/home/viktor/my_projects_qt_2/Funktsiya_Resheniya_2/synapses.txt"
    //        "/home/viktor/my_projects_qt_2/sgenerirovaty_sinapsi/random_sinapsi.bin");
    //###########################################################################
    const QString fileName
        = "/home/viktor/my_projects_qt_2/sgenerirovaty_sinapsi/random_sinapsi.bin"; // Имя бинарного файла
    const size_t numberCount = 10105;

    // Чтение чисел из бинарного файла
    std::vector<unsigned long long> list_of_synapses = readNumbersFromFile2(fileName, numberCount);

    // Проверка, что прочитано правильное количество чисел
    if (list_of_synapses.size() != numberCount) {
        std::cerr << "File does not contain the expected number of numbers." << std::endl;
    }
    std::cout << "конец чтения синапсов в вектор" << std::endl;
    std::cout << "//"
                 "#################################################################################"
                 "#######################"
              << std::endl;
    //########################################################################################################
    // читаем нейроны в вектор
    std::vector<long long> list_of_neurons;
    //    std::vector<long long> list_of_neurons =
    readVectorFromFileLL(
        list_of_neurons,
        //  std::vector<long long> list_of_neurons,
        //                "/mnt/6017d124-d970-486e-b68f-59b516dd0511/risunki_Stability_Matrix/"
        //               "chars74k_png_Fnt_Sample1_black-white/300/txt/1/neurons_and_signal.txt"
        //"/home/viktor/my_projects_qt_2/podacha_signala/combined_numbers.bin"
        "/home/viktor/my_projects_qt_2/podacha_signala_long_long/combined_numbers.bin");
    std::cout << "конец чтения нейронов в вектор" << std::endl;

    ///#################### считываем синапсы из файла в вектор #######################################################

    //###########################################################################
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
             ++neuron_index,
            synapse_index = synapse_index + 100 // вроде тут ошибка
        )

        { // // ошибка сегментации

            //if (synapse_index>10100 )
            if (neuron_index < 200 //&& synapse_index<200
            )
                //###########################################################################
                //                try {
                //                    int value = vec.at(100);  // Это вызовет std::out_of_range
                //                } catch (const std::out_of_range& e) {
                //                    std::cerr << "Caught an exception: " << e.what() << '\n';
                //                }
                //###########################################################################
                try {
                    list_of_neurons.at(var)
                        //###########################################################################
                        = list_of_neurons.at(var) //-5310911  // valgrind
                          + ((list_of_neurons.at(neuron_index)
                              //  /   // деление
                              -                                     // вычитаем
                              list_of_synapses.at(synapse_index))); // + на -
                } catch (const std::out_of_range &e) {
                    std::cerr << "Caught an exception: " << e.what() << '\n';
                }

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
