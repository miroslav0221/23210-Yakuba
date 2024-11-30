#include <iostream>
#include <Model.h>
#include <Controller.h>
#include <View.h>


int main(int argc, char * argv[])
{
    int mode, count_iter = 1;
    Model model;
    View view(model);
    Controller controller(model, view);
    std::string namefile_in, namefile_out;
    switch (argc) {
        case 1:
            mode = 0;
            namefile_in = "base.life";
            controller.read_file(namefile_in);
            view.image_field();
            controller.play();
            break;
        case 2:
            mode = 1;
            namefile_in = argv[1];
            controller.read_file(namefile_in);
            view.image_field();
            controller.play();
            break;
        case 6: //.exe in.life -i x -o out.life
            if (static_cast<std::string>(argv[2]) == "-i" && static_cast<std::string>(argv[4]) == "-o") {
                //mode = 2;
                namefile_in = argv[1];
                namefile_out = argv[5];
                count_iter = std::stoi(std::string(argv[3]));
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
    //
    // controller.play();
    // controller.read_file(namefile_in);
    // view.image_field();
    return 0;
}
