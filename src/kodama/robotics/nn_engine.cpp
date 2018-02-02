#include "nn_engine.h"


void nn_engine_set(int16_t *array, int16_t value, unsigned int size)
{
  while (size >= 4)
  {
    *array = value; array++;
    *array = value; array++;
    *array = value; array++;
    *array = value; array++;

    size-= 4;
  }

  while (size)
  {
    *array = value; array++;
    size--;
  }
}

int64_t nn_engine_neuron(int16_t *input, int8_t *weights, unsigned int size)
{
  int64_t result = 0;

  while (size >= 4)
  {
    result+= (*input)*(*weights); input++; weights++;
    result+= (*input)*(*weights); input++; weights++;
    result+= (*input)*(*weights); input++; weights++;
    result+= (*input)*(*weights); input++; weights++;

    size-= 4;
  }

  while (size)
  {
    result+= (*input)*(*weights); input++; weights++;
    size--;
  }

  return result;
}


void nn_engine_relu(int16_t *array, unsigned int size)
{
  for (unsigned int i = 0; i < size; i++)
  {
    if (array[i] < 0)
      array[i] = 0;
  }
}
