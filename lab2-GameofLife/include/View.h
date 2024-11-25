#ifndef VIEW_H
#define VIEW_H
#include "Model.h"


class View {
private:
      Model & model;
public:
      explicit View(Model & new_model);
      void image_field();
};



#endif
