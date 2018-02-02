#ifndef _VPU_MATH_
#define _VPU_MATH_

#define VPU_UNROLL   1

class VPU
{
  private:
    unsigned int __rnda__, __rndb__;

  public:
    VPU();
    ~VPU();

    float abs(float x);
    float sqrt(float x);
    float cos(float x);

    void srand(unsigned int seed);
    unsigned int rand();
    float rnd();

    float max(float a, float b);
    float min(float a, float b);
    float sgn(float v);
    float constrain(float value, float min_, float max_);
    float shrink(float value, float range);

    void  v_set(float *v_res, float value, unsigned int size);
    void  v_set_rnd(float *v_res, float range, unsigned int size);
    void  v_copy(float *v_res, float *v_in, unsigned int size);

    void  v_add(float *v_res, float *va, float *vb, unsigned int size);
    void  v_sub(float *v_res, float *va, float *vb, unsigned int size);
    float v_dot(float *va, float *vb, unsigned int size);
    float v_length(float *va, float *vb, unsigned int size);
    float v_l0_norm(float *v, unsigned int size);
    float v_l1_norm(float *v, unsigned int size);
    float v_l2_norm(float *v, unsigned int size);
    float v_l_infinity_norm(float *v, unsigned int size);

    void v_relu(float *v_res, float *v, unsigned int size);
    void v_fast_tanh(float *v_res, float *v, unsigned int size);
    void v_shrink(float *v_res, float *v, float range, unsigned int size);
    void v_normalise(float *v_res, float *v, unsigned int size);


    void v_mac(float *v_acc, float *v_in, float k, unsigned int size);

    unsigned int v_argmax(float *v, unsigned int size);
    unsigned int v_argmin(float *v, unsigned int size);

    void ojas_rule(float *weights, float *input, float neuron_output, float learning_rate, unsigned int size);
    void gradient_descent(float *weights, float *input, float error, float learning_rate, unsigned int size);
};


#endif
