#include "vpu.h"



VPU::VPU()
{
  __rnda__ = 1;
  __rndb__  = 2;
}

VPU::~VPU()
{

}

float VPU::abs(float x)
{
  float result;
  __asm volatile ("vabs.f32 %0, %1" : "=w" (result) : "w" (x) );
  return(result);
}

float VPU::sqrt(float x)
{
  float result;
  __asm volatile ("vsqrt.f32 %0, %1" : "=w" (result) : "w" (x) );
  return(result);
}

float VPU::cos(float x)
{
  float t , s ;

  int p;

  p = 0;
  s = 1.0;
  t = 1.0;

  while ((abs(t/s) > 0.001) && (p < 10))
  {
        p++;
        t = (-t * x * x) / ((2 * p - 1) * (2 * p));
        s += t;
  }
    return s;
}

void VPU::srand(unsigned int seed)
{
  __rnda__ = seed;
  __rndb__  = 2;
}

unsigned int VPU::rand()
{
  __rnda__ = __rnda__ *(unsigned int)1103515245 + (unsigned int)12345;
	__rndb__ = (__rndb__ >> 1) ^ (-(__rndb__ & 1u) & 0xD0000001u);

	return (__rnda__ ^ __rndb__);
}

float VPU::rnd()
{
  return (rand()%2000000)/1000000.0 - 1.0;
}


float VPU::max(float a, float b)
{
  if (a > b)
    return a;
  return b;
}

float VPU::min(float a, float b)
{
  if (a < b)
    return a;
  return b;
}

float VPU::sgn(float v)
{
  if (v > 0.0)
    return 1.0;
  if (v < 0.0)
    return -1.0;
  return 0.0;
}

float VPU::constrain(float value, float min_, float max_)
{
  if (value > max_)
    value = max_;

  if (value < min_)
    value = min_;

  return value;
}

float VPU::shrink(float value, float range)
{
  value = max(abs(value) - range, 0.0)*sgn(value);
  return value;
}

void VPU::v_set(float *v_res, float value, unsigned int size)
{
  unsigned int ptr = 0;

  #ifdef VPU_UNROLL
  while (size > 8)
  {
    v_res[ptr] = value; ptr++;
    v_res[ptr] = value; ptr++;
    v_res[ptr] = value; ptr++;
    v_res[ptr] = value; ptr++;

    v_res[ptr] = value; ptr++;
    v_res[ptr] = value; ptr++;
    v_res[ptr] = value; ptr++;
    v_res[ptr] = value; ptr++;

    size-= 8;
  }
  #endif

  while (size > 0)
  {
    v_res[ptr] = value; ptr++;
    size--;
  }
}


void VPU::v_set_rnd(float *v_res, float range, unsigned int size)
{
  for (unsigned int i = 0; i < size; i++)
    v_res[i] = rnd()*range;
}

void VPU::v_copy(float *v_res, float *v_in, unsigned int size)
{
  unsigned int ptr = 0;

  #ifdef VPU_UNROLL
  while (size > 8)
  {
    v_res[ptr] = v_in[ptr]; ptr++;
    v_res[ptr] = v_in[ptr]; ptr++;
    v_res[ptr] = v_in[ptr]; ptr++;
    v_res[ptr] = v_in[ptr]; ptr++;

    v_res[ptr] = v_in[ptr]; ptr++;
    v_res[ptr] = v_in[ptr]; ptr++;
    v_res[ptr] = v_in[ptr]; ptr++;
    v_res[ptr] = v_in[ptr]; ptr++;


    size-= 8;
  }
  #endif

  while (size > 0)
  {
    v_res[ptr] = v_in[ptr]; ptr++;
    size--;
  }
}

void VPU::v_add(float *v_res, float *va, float *vb, unsigned int size)
{
  unsigned int ptr = 0;

  #ifdef VPU_UNROLL
  while (size > 8)
  {
    v_res[ptr] = va[ptr] + vb[ptr]; ptr++;
    v_res[ptr] = va[ptr] + vb[ptr]; ptr++;
    v_res[ptr] = va[ptr] + vb[ptr]; ptr++;
    v_res[ptr] = va[ptr] + vb[ptr]; ptr++;

    v_res[ptr] = va[ptr] + vb[ptr]; ptr++;
    v_res[ptr] = va[ptr] + vb[ptr]; ptr++;
    v_res[ptr] = va[ptr] + vb[ptr]; ptr++;
    v_res[ptr] = va[ptr] + vb[ptr]; ptr++;

    size-= 8;
  }
  #endif

  while (size > 0)
  {
    v_res[ptr] = va[ptr] + vb[ptr]; ptr++;
    size--;
  }
}

void VPU::v_sub(float *v_res, float *va, float *vb, unsigned int size)
{
  unsigned int ptr = 0;

  #ifdef VPU_UNROLL
  while (size > 8)
  {
    v_res[ptr] = va[ptr] + vb[ptr]; ptr++;
    v_res[ptr] = va[ptr] + vb[ptr]; ptr++;
    v_res[ptr] = va[ptr] + vb[ptr]; ptr++;
    v_res[ptr] = va[ptr] + vb[ptr]; ptr++;

    v_res[ptr] = va[ptr] + vb[ptr]; ptr++;
    v_res[ptr] = va[ptr] + vb[ptr]; ptr++;
    v_res[ptr] = va[ptr] + vb[ptr]; ptr++;
    v_res[ptr] = va[ptr] + vb[ptr]; ptr++;

    size-= 8;
  }
  #endif

  while (size > 0)
  {
    v_res[ptr] = va[ptr] + vb[ptr]; ptr++;
    size--;
  }
}

float VPU::v_dot(float *va, float *vb, unsigned int size)
{
  float result = 0.0;

  unsigned int ptr = 0;

  #ifdef VPU_UNROLL
  while (size > 8)
  {
    result+= va[ptr]*vb[ptr]; ptr++;
    result+= va[ptr]*vb[ptr]; ptr++;
    result+= va[ptr]*vb[ptr]; ptr++;
    result+= va[ptr]*vb[ptr]; ptr++;

    result+= va[ptr]*vb[ptr]; ptr++;
    result+= va[ptr]*vb[ptr]; ptr++;
    result+= va[ptr]*vb[ptr]; ptr++;
    result+= va[ptr]*vb[ptr]; ptr++;
    size-= 8;
  }
  #endif

  while (size > 0)
  {
    result+= va[ptr]*vb[ptr]; ptr++;
    size--;
  }

  return result;
}

float VPU::v_length(float *va, float *vb, unsigned int size)
{
  float result = 0.0;

  unsigned int ptr = 0;

  #ifdef VPU_UNROLL
  while (size > 8)
  {
    result+= (va[ptr]-vb[ptr])*(va[ptr]-vb[ptr]); ptr++;
    result+= (va[ptr]-vb[ptr])*(va[ptr]-vb[ptr]); ptr++;
    result+= (va[ptr]-vb[ptr])*(va[ptr]-vb[ptr]); ptr++;
    result+= (va[ptr]-vb[ptr])*(va[ptr]-vb[ptr]); ptr++;

    result+= (va[ptr]-vb[ptr])*(va[ptr]-vb[ptr]); ptr++;
    result+= (va[ptr]-vb[ptr])*(va[ptr]-vb[ptr]); ptr++;
    result+= (va[ptr]-vb[ptr])*(va[ptr]-vb[ptr]); ptr++;
    result+= (va[ptr]-vb[ptr])*(va[ptr]-vb[ptr]); ptr++;

    size-= 8;
  }
  #endif

  while (size > 0)
  {
    result+= (va[ptr]-vb[ptr])*(va[ptr]-vb[ptr]); ptr++;
    size--;
  }

  return sqrt(result);
}

float VPU::v_l0_norm(float *v, unsigned int size)
{
  float res = 0.0;

  for (unsigned int i = 0; i < size; i++)
    if (v[i] != 0.0)
      res+= 1.0;

  return res;
}

float VPU::v_l1_norm(float *v, unsigned int size)
{
  float res = 0.0;

  for (unsigned int i = 0; i < size; i++)
    res+= abs(v[i]);

  return res;
}

float VPU::v_l2_norm(float *v, unsigned int size)
{
  float res = 0.0;

  for (unsigned int i = 0; i < size; i++)
    res+= v[i]*v[i];

  return sqrt(res);
}

float VPU::v_l_infinity_norm(float *v, unsigned int size)
{
  float res = v[0];

  for (unsigned int i = 0; i < size; i++)
    if (v[i] > res)
      res = v[i];

  return res;
}


void VPU::v_relu(float *v_res, float *v, unsigned int size)
{
  unsigned int ptr = 0;

  #ifdef VPU_UNROLL
  while (size > 8)
  {
    if (v[ptr] < 0) v_res[ptr] = 0; else v_res[ptr] = v[ptr]; ptr++;
    if (v[ptr] < 0) v_res[ptr] = 0; else v_res[ptr] = v[ptr]; ptr++;
    if (v[ptr] < 0) v_res[ptr] = 0; else v_res[ptr] = v[ptr]; ptr++;
    if (v[ptr] < 0) v_res[ptr] = 0; else v_res[ptr] = v[ptr]; ptr++;

    if (v[ptr] < 0) v_res[ptr] = 0; else v_res[ptr] = v[ptr]; ptr++;
    if (v[ptr] < 0) v_res[ptr] = 0; else v_res[ptr] = v[ptr]; ptr++;
    if (v[ptr] < 0) v_res[ptr] = 0; else v_res[ptr] = v[ptr]; ptr++;
    if (v[ptr] < 0) v_res[ptr] = 0; else v_res[ptr] = v[ptr]; ptr++;

    size-= 8;
  }
  #endif

  while (size > 0)
  {
    if (v[ptr] < 0) v_res[ptr] = 0; else v_res[ptr] = v[ptr]; ptr++;

    size--;
  }
}



void VPU::v_fast_tanh(float *v_res, float *v, unsigned int size)
{
  unsigned int ptr = 0;

  #ifdef VPU_UNROLL
  while (size > 8)
  {
    v_res[ptr] = v[ptr]/(1.0 + abs(v[ptr])); ptr++;
    v_res[ptr] = v[ptr]/(1.0 + abs(v[ptr])); ptr++;
    v_res[ptr] = v[ptr]/(1.0 + abs(v[ptr])); ptr++;
    v_res[ptr] = v[ptr]/(1.0 + abs(v[ptr])); ptr++;

    v_res[ptr] = v[ptr]/(1.0 + abs(v[ptr])); ptr++;
    v_res[ptr] = v[ptr]/(1.0 + abs(v[ptr])); ptr++;
    v_res[ptr] = v[ptr]/(1.0 + abs(v[ptr])); ptr++;
    v_res[ptr] = v[ptr]/(1.0 + abs(v[ptr])); ptr++;

    size-= 8;
  }
  #endif

  while (size > 0)
  {
    v_res[ptr] = v[ptr]/(1.0 + abs(v[ptr])); ptr++;
    size--;
  }
}

void VPU::v_shrink(float *v_res, float *v, float range, unsigned int size)
{
  for (unsigned int i = 0; i < size; i++)
    v_res[i] = shrink(v[i], range);
}


void VPU::v_normalise(float *v_res, float *v, unsigned int size)
{
  float len = v_l2_norm(v, size);
  if (len > 0.0)
  {
    unsigned int ptr = 0;

    #ifdef VPU_UNROLL
    while (size > 8)
    {
      v_res[ptr] = v[ptr]/len; ptr++;
      v_res[ptr] = v[ptr]/len; ptr++;
      v_res[ptr] = v[ptr]/len; ptr++;
      v_res[ptr] = v[ptr]/len; ptr++;

      v_res[ptr] = v[ptr]/len; ptr++;
      v_res[ptr] = v[ptr]/len; ptr++;
      v_res[ptr] = v[ptr]/len; ptr++;
      v_res[ptr] = v[ptr]/len; ptr++;

      size-= 8;
    }
    #endif

    while (size > 0)
    {
      v_res[ptr] = v[ptr]/len; ptr++;
      size--;
    }
  }
}

void VPU::v_mac(float *v_acc, float *v_in, float k, unsigned int size)
{
  unsigned int ptr = 0;

  #ifdef VPU_UNROLL
  while (size > 8)
  {
    v_acc[ptr]+= k*v_in[ptr]; ptr++;
    v_acc[ptr]+= k*v_in[ptr]; ptr++;
    v_acc[ptr]+= k*v_in[ptr]; ptr++;
    v_acc[ptr]+= k*v_in[ptr]; ptr++;

    v_acc[ptr]+= k*v_in[ptr]; ptr++;
    v_acc[ptr]+= k*v_in[ptr]; ptr++;
    v_acc[ptr]+= k*v_in[ptr]; ptr++;
    v_acc[ptr]+= k*v_in[ptr]; ptr++;

    size-= 8;
  }
  #endif

  while (size > 0)
  {
    v_acc[ptr]+= k*v_in[ptr]; ptr++;
    size--;
  }
}


unsigned int VPU::v_argmax(float *v, unsigned int size)
{
  unsigned int result = 0;
  for (unsigned int i = 0; i < size; i++)
    if (v[i] > v[result])
      result = i;

  return result;
}

unsigned int VPU::v_argmin(float *v, unsigned int size)
{
  unsigned int result = 0;
  for (unsigned int i = 0; i < size; i++)
    if (v[i] < v[result])
      result = i;

  return result;
}

void VPU::ojas_rule(float *weights, float *input, float neuron_output, float learning_rate, unsigned int size)
{
  unsigned int ptr = 0;

  #ifdef VPU_UNROLL
  while (size > 8)
  {
    weights[ptr]+= learning_rate*neuron_output*(input[ptr] - neuron_output*weights[ptr]); ptr++;
    weights[ptr]+= learning_rate*neuron_output*(input[ptr] - neuron_output*weights[ptr]); ptr++;
    weights[ptr]+= learning_rate*neuron_output*(input[ptr] - neuron_output*weights[ptr]); ptr++;
    weights[ptr]+= learning_rate*neuron_output*(input[ptr] - neuron_output*weights[ptr]); ptr++;

    weights[ptr]+= learning_rate*neuron_output*(input[ptr] - neuron_output*weights[ptr]); ptr++;
    weights[ptr]+= learning_rate*neuron_output*(input[ptr] - neuron_output*weights[ptr]); ptr++;
    weights[ptr]+= learning_rate*neuron_output*(input[ptr] - neuron_output*weights[ptr]); ptr++;
    weights[ptr]+= learning_rate*neuron_output*(input[ptr] - neuron_output*weights[ptr]); ptr++;

    size-= 8;
  }
  #endif

  while (size > 0)
  {
    weights[ptr]+= learning_rate*neuron_output*(input[ptr] - neuron_output*weights[ptr]); ptr++;
    size--;
  }
} 

void VPU::gradient_descent(float *weights, float *input, float error, float learning_rate, unsigned int size)
{
  unsigned int ptr = 0;

  #ifdef VPU_UNROLL
  while (size > 8)
  {
    weights[ptr]+= learning_rate*error*input[ptr]; ptr++;
    weights[ptr]+= learning_rate*error*input[ptr]; ptr++;
    weights[ptr]+= learning_rate*error*input[ptr]; ptr++;
    weights[ptr]+= learning_rate*error*input[ptr]; ptr++;

    weights[ptr]+= learning_rate*error*input[ptr]; ptr++;
    weights[ptr]+= learning_rate*error*input[ptr]; ptr++;
    weights[ptr]+= learning_rate*error*input[ptr]; ptr++;
    weights[ptr]+= learning_rate*error*input[ptr]; ptr++;

    size-= 8;
  }
  #endif

  while (size > 0)
  {
    weights[ptr]+= learning_rate*error*input[ptr]; ptr++;
    size--;
  }
}
