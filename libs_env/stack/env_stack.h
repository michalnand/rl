#ifndef _STACK_H_
#define _STACK_H_

#include "env.h"
#include "visualisation/glvisualisation.h"

#include "stack_item.h"


class EnvStack: public Env
{
    private:

      std::vector<StackItem*> items;

      unsigned int width, height;
      unsigned int item_width, item_height;

      float redner_iteration;

    protected:
      GLVisualisation visualisation;

    public:
      // Default constructor
      EnvStack( unsigned int width = 21,
                unsigned int height = 21);

      // Copy constructor
      EnvStack(EnvStack& other);

      // Copy constructor
      EnvStack(const EnvStack& other);

      // Destructor
      virtual ~EnvStack();

      // Copy assignment operator
      EnvStack& operator= (EnvStack& other);

      // Copy assignment operator
      EnvStack& operator= (const EnvStack& other);

    protected:
      void copy_stack(EnvStack& other);
      void copy_stack(const EnvStack& other);

    public:
      void action(unsigned int action_id);

      void render();

      void print();

    private:
      void draw_item(unsigned int idx);

      void reset();
      void update_state();
      float get_overlap();


};



#endif
