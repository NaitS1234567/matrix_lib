#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//    C_Library_Matrix : <CLibMat.h> create by @NaitS - B9122 - 10.03.01 (6) Aldar Dabaev     //

struct matrix{ // new type of data - matrix
    int height;
    int weight;
    int** elem;
};
//====================================================================//
//------------------------- Return NULL matrix -----------------------//
//====================================================================//
struct matrix null_matrix(){
    struct matrix mat;
    mat.height = -1;
    mat.weight = -1;
    mat.elem = NULL;
    return mat;
}
//===============================================================================//
// ---------------------------- Create empty matrix------------------------------//
//===============================================================================//
struct matrix init_malloc(int height, int weight){
    struct matrix m;
    m.height = height;
    m.weight = weight;
    if (height > 0 && weight > 0){
        int** arr = (int**)malloc(sizeof(int*) * height);
        for (int i = 0; i < height; i++){
            arr[i] = (int*)malloc(sizeof(int) * weight);
        }
        m.elem = arr;
        return m;
    }
    else
        return null_matrix();
}
//================================================================================//
// ------------------------ Create Matrix of specified elements-------------------//
//================================================================================//
struct matrix init_matrix(int height, int weight, int el){
    struct matrix res = init_malloc(height, weight);
    for (int i = 0; i < height; i++){
        for (int j = 0; j < weight; j++){
            res.elem[i][j] = el;
        }
    }
    return res;
}
//===========================================================================//
//------------------------------- Print Matrix ------------------------------//
//===========================================================================//
void print_matrix(struct matrix mat){
    int h = mat.height;
    int w = mat.weight;
    for (int i = 0; i < h; i++){
        for (int j = 0; j < w; j++){
            printf("%d ",mat.elem[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
//================================================================================//
//---------------------- Create matrix with random elements ----------------------//
//================================================================================//
struct matrix init_rand_matrix(int height, int weight, int start, int stop){
    struct matrix res = init_malloc(height, weight);
    srand(time(0));
    for (int i = 0; i < height; i++){
        for (int j = 0; j < weight; j++){
            res.elem[i][j] = start + rand()%stop+1-start;
        }
    }
    return res;
}
//==============================================================================//
// ------------------------------ Sum of 2 matrix ------------------------------//
//==============================================================================//
struct matrix sum_matrix(struct matrix m1, struct matrix m2){
    int height = m1.height;
    int weight = m1.weight;
    int height2 = m2.height;
    int weight2 = m2.weight;
    if (height == height2 && weight == weight2){
        struct matrix sum_m = init_malloc(height,weight);
        for (int i = 0; i < height; i++){
            for (int j = 0; j < weight; j++){
                sum_m.elem[i][j] = m1.elem[i][j] + m2.elem[i][j];
            }
        }
        return sum_m;
    }
    else{
        return null_matrix();
    }
}
//==============================================================================//
// --------------------------- Difference of 2 matrix --------------------------//
//==============================================================================//
struct matrix diff_matrix(struct matrix m1, struct matrix m2){
    int height = m1.height;
    int weight = m1.weight;
    int height2 = m2.height;
    int weight2 = m2.weight;
    if (height == height2 && weight == weight2){
        struct matrix sum_m = init_malloc(height,weight);
        for (int i = 0; i < height; i++){
            for (int j = 0; j < weight; j++){
                sum_m.elem[i][j] = m1.elem[i][j] - m2.elem[i][j];
            }
        }
        return sum_m;
    }
    else {
        return null_matrix();
    }
}
//============================================================================//
// -------------------------- Transposition Matrix ---------------------------//
//============================================================================//
struct matrix trans_matrix(struct matrix mat){
    int height = mat.height;
    int weight = mat.weight;
    struct matrix trans_mat = init_malloc(weight, height);
    for (int i = 0; i < weight; i++){
        int column[weight];
        for (int j = 0; j < height;j++){
            trans_mat.elem[i][j] = mat.elem[j][i];
        }
    }
    return trans_mat;
}
//==================================================================================//
// -------------------------- Multiplication of 2 matrix ---------------------------//
//==================================================================================//
struct matrix multi_matrix(struct matrix m1, struct matrix m2){
    int weight1 = m1.weight;
    int height1 = m1.height;
    int weight2 = m2.weight;
    int height2 = m2.height;
    if (weight1 == height2){
        struct matrix mul_mat = init_malloc(height1, weight2);
        for (int i = 0; i < height1; i++){
            for (int j = 0; j < weight2; j++){
                int mul_elem = 0;
                for (int z = 0; z < height2; z++){
                    mul_elem += m1.elem[i][z] * m2.elem[z][j];
                    }
                mul_mat.elem[i][j] = mul_elem;
                }
            }
        return mul_mat;
        }
    else {
        return null_matrix();
    }
}
//================================================================================//
// --------------------------- Create copy of matrix -----------------------------//
//================================================================================//
struct matrix copy_matrix(struct matrix mat){
    int weight = mat.weight;
    int height = mat.height;
    struct matrix copy_mat = init_malloc(height,weight);
    for (int i = 0; i < height; i++){
        for (int j = 0; j < weight; j++){
             copy_mat.elem[i][j] = mat.elem[i][j];
        }
    }
    return copy_mat;
}
//========================================================//
// -------------------- delete matrix --------------------//
//========================================================//
void delete_matrix(struct matrix mat){
    int h = mat.height;
    int k = 0;
    while (k < h){
        free(mat.elem[k]);
        k++;
        }
    free(mat.elem);
    mat.height = -1;
    mat.weight = -1;
    mat.elem = NULL;
    }

//     Test     //

int main(){
    printf("Create matrix n*n with same elements\n");
    struct matrix m = init_matrix(3,3,1);
    print_matrix(m);

    printf("create matrix n*n with random elements\n");
    struct matrix rand_m = init_rand_matrix(3,3,1,15);
    print_matrix(rand_m);

    printf("Create matrix n*m with random elements\n");
    struct matrix rand_m2 = init_rand_matrix(3,5,1,15);
    print_matrix(rand_m2);

    printf("Sum of 2 matrix\n");
    struct matrix sum_mat = sum_matrix(m, rand_m);
    struct matrix sum_mat2 = sum_matrix(m, rand_m2);
    print_matrix(sum_mat);
    print_matrix(sum_mat2);

    printf("Difference of 2 matrix\n");
    struct matrix di_mat = diff_matrix(m,rand_m);
    struct matrix di_mat2 = diff_matrix(m,rand_m2);
    print_matrix(di_mat);
    print_matrix(di_mat2);

    printf("Transponsed matrix\n");
    struct matrix tr_mat = trans_matrix(rand_m2);
    print_matrix(tr_mat);

    printf("Multiplication of 2 matrix\n");
    struct matrix mul_mat = multi_matrix(rand_m, rand_m2);
    print_matrix(mul_mat);
    struct matrix mul_mat2 = multi_matrix(rand_m2,rand_m);
    print_matrix(mul_mat2);

    printf("Copy of matrix\n");
    struct matrix copy_mat = copy_matrix(rand_m2);
    print_matrix(copy_mat);

    printf("1st matrix\n");
    print_matrix(m);
    printf("Deleted matrix\n");
    delete_matrix(m);

    return 0;
}