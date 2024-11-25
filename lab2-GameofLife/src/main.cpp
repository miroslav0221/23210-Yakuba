#include <Model.h>
#include <Controller.h>
#include <iostream>
#include <View.h>

int main()
{
    std::string namefile = "input.life";
    Model model;
    Controller controller(model);
    View view(model);
    controller.read_file(namefile);
    view.image_field();
    return 0;
}
