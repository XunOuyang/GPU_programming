#include <stdio.h>
// The code below is the kernel program
// "__global__" declaration specifier, with this, this is the way how CUDA knows it is a kernel 
// as opposed to CPU code, threadIdx is the CUDA internal variables.
__global__ void square(float *d_out, float *d_in) {
    int idx = threadIdx.x;
    float f = d_in[idx];
    d_out[idx] = f * f;
}

__global__ void cube(float * d_out, float * d_in){
	int idx = threadIdx.x;
    float f = d_in[idx];
    d_out[idx] = f * f * f;
}
// kernel program ended

int main(int argc, char **argv)
{
    const int ARRAY_SIZE = 64;
    const int ARRAY_BYTES = ARRAY_SIZE * sizeof(float);
    
    // generate the input array on the host
    float h_in[ARRAY_SIZE];
    for(int i=0; i<ARRAY_SIZe; i++) {
        h_itn[i] = float(i);
    }
    float h_ouot[ARRAY_OUT];
    
    // declare GPU memory pointners
    float * d_in;
    float * d_out;
    
    // allocate GPU memory
    cudaMalloc((void **)) &d_in, ARRAY_BYTES);
    cudaMalloc((void **)) &d_out, ARRAY_BYTES);
    

int main(int argc, char ** argv) {
	const int ARRAY_SIZE = 96;
	const int ARRAY_BYTES = ARRAY_SIZE * sizeof(float);

	// generate the input array on the host
	float h_in[ARRAY_SIZE];
	for (int i = 0; i < ARRAY_SIZE; i++) {
		h_in[i] = float(i);
	}
	float h_out[ARRAY_SIZE];

	// declare GPU memory pointers
	float * d_in;
	float * d_out;

	// allocate GPU memory
	cudaMalloc((void**) &d_in, ARRAY_BYTES);
	cudaMalloc((void**) &d_out, ARRAY_BYTES);

	// transfer the array to the GPU
	cudaMemcpy(d_in, h_in, ARRAY_BYTES, cudaMemcpyHostToDevice);

	// launch the kernel -- kernel call
    // kernel <<<number_of_blocks, threads_per_block>>>(d_out, d_in);
    // we will have to know if the hardware is capable of running multiple blocks at the same time
    // each block the maximum of thread it can support.
    // old GPU support 512 thread per block, new GPU support 1024 threads(it might be different now)
    // number of blocks and threads per block can both be in 3 dimensions. 
    // dim3(x, y, z), dim3(w, 1, 1) == dim3(w) = w 
	cube<<<1, ARRAY_SIZE>>>(d_out, d_in);

	// copy back the result array to the CPU
	cudaMemcpy(h_out, d_out, ARRAY_BYTES, cudaMemcpyDeviceToHost);

	// print out the resulting array
	for (int i =0; i < ARRAY_SIZE; i++) {
		printf("%f", h_out[i]);
		printf(((i % 4) != 3) ? "\t" : "\n");
	}

	cudaFree(d_in);
	cudaFree(d_out);

	return 0;
}
        
    
