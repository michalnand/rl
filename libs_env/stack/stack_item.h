#ifndef _STACK_ITEM_H_
#define _STACK_ITEM_H_

#include <vector>

class StackItem
{
  protected:

    int area_width, area_height;
    int width, height;

    unsigned int move_type, state;

    int x, y, position;
    int target_x, target_y;

    StackItem *other;

  public:
    std::vector<std::vector<float>> values;

  public:
    StackItem(  unsigned int area_width, unsigned int area_height,
                unsigned int width, unsigned int height);

    StackItem(StackItem *other);

    float compute_overlap();
    void process(unsigned int action);
    void print();

  protected:
    void fill_values();
};

#endif
