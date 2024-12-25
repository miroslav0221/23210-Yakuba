#include <iostream>
#include <Model.h>
#include <Controller.h>
#include <View.h>
#include <Handler_file.h>

int main(int argc, char * argv[]) {
    int count_iter = 1;
    Field field;
    Model model(field);
    Handler_file handler(model);
    View view(model);
    Controller controller(model, view);
    std::string namefile_in, namefile_out;
    switch (argc) {
        case 1:
            namefile_in = "base.life";
            handler.read_file(namefile_in);
            view.image_field();
            controller.play();
            break;
        case 2:
            namefile_in = argv[1];
            handler.read_file(namefile_in);
            view.image_field();
            controller.play();
            break;
        case 6:
            if (static_cast<std::string>(argv[2]) == "-i" && static_cast<std::string>(argv[4]) == "-o") {
                namefile_in = argv[1];
                namefile_out = argv[5];
                count_iter = std::stoi(std::string(argv[3]));
                handler.read_file(namefile_in);
                controller.offline_mode(count_iter, namefile_out);
            }
            else {
                std::cout << "Неверный формат ключей" << std::endl;
                return 1;
            }
            break;
        default:
            std::cout << "Неверный формат ввода" << std::endl;
            return 1;

    }
    return 0;
}
