#include <boost/program_options.hpp>
#include <iostream>
#include <string>
#include <vector>
namespace po = boost::program_options;
void usage()
{
    std::cout << "-o operand1 operand2 operand3 operand4" << std::endl;
    std::cout << "-o - тип операции" << std::endl;
};
int main(int argc, char** argv)
{
    std::string type_operation;
    try {
        // создание пустой коллекции ПКС
        po::options_description opts("Allowed options"); // параметр - заголовок справки по коллекции ПКС
        // добавление параметров в коллекцию ПКС
        opts.add_options()
        ("help,h", "Show help") // парметр-переключатель - имя (длинное и короткое) и текст справки
        //дальше все параметры со значениями
        // параметр --first
        ("operation,o", // имя (длинное)
         po::value<std::string>(&type_operation), // значение типа std::string, сохраняется дополнительно в переменную s
         "option(summa/sub)");

        po::variables_map vm;
        std::vector<std::string> additionalParameters;

        po::parsed_options parsed = po::command_line_parser(argc, argv).options(opts).allow_unregistered().run();
        po::store(parsed, vm);
        additionalParameters = collect_unrecognized(parsed.options,po::include_positional);
        notify(vm);
        if(vm.count("help")) {
            std::cout << opts << "\n";
            std::cout << "Usage: operation(summa/sub) operand1 operand2 (от 2 до 5 включительно)\n";
            exit(0);
        };
        if(additionalParameters.empty() or additionalParameters.size() < 3 or additionalParameters.size() > 5) {
            std::cerr << "missing operands\n";
            std::cout << opts << "\n";
            std::cout << "Usage: operation(summa/sub) operand1 operand2 (от 3 до 5 включительно)\n";
            exit(0);
        } else {
            if(vm["operation"].as<std::string>()=="summa") {
                int summa = 0;
                for(auto e:additionalParameters) {
                    summa += stoi(e);
                }

                std::cout <<"Сумма операндов: "<< summa <<std::endl;
            } else {
                if(vm["operation"].as<std::string>()=="sub") {
                    int res = stoi(additionalParameters[0]);
                    for(int i = 1;i < additionalParameters.size();i++) {
                        res -= stoi(additionalParameters[i]);
                    }
                    std::cout <<"Разность операндов: "<< res <<std::endl;
                }else{
                    std::cerr << "error: operation not found (use -h for help)" << std::endl;
                    }
            }
        }
    } catch(po::error& e) {
        std::cerr << "error: " << e.what() << "\n";
        std::cerr << "Use -h for help\n";
        return 1;
    } catch(std::exception& e) {
        std::cerr << "error: " << e.what() << "\n";
        return 2;
    } catch(...) {
        std::cerr << "Exception of unknown type!\n";
        std::terminate();
    }
    return 0;
}
