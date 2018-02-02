#ifndef  _NN_ENGINE_H_
#define  _NN_ENGINE_H_

#include <stdint.h>

void nn_engine_set(int16_t *array, int16_t value, unsigned int size);
int64_t nn_engine_neuron(int16_t *input, int8_t *weights, unsigned int size);
void nn_engine_relu(int16_t *array, unsigned int size);

#endif
