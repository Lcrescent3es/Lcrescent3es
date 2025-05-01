#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define LB32_MASK   0x00000001
#define LB64_MASK   0x0000000000000001
#define L64_MASK    0x00000000ffffffff
#define H64_MASK    0xffffffff00000000
#define SIZE 30

/* Initial Permutation Table */
static char IP[] = {
   58, 50, 42, 34, 26, 18, 10,  2,
   60, 52, 44, 36, 28, 20, 12,  4,
   62, 54, 46, 38, 30, 22, 14,  6,
   64, 56, 48, 40, 32, 24, 16,  8,
   57, 49, 41, 33, 25, 17,  9,  1,
   59, 51, 43, 35, 27, 19, 11,  3,
   61, 53, 45, 37, 29, 21, 13,  5,
   63, 55, 47, 39, 31, 23, 15,  7
};

/* Inverse Initial Permutation Table */
static char IIP[] = {
   40,  8, 48, 16, 56, 24, 64, 32,
   39,  7, 47, 15, 55, 23, 63, 31,
   38,  6, 46, 14, 54, 22, 62, 30,
   37,  5, 45, 13, 53, 21, 61, 29,
   36,  4, 44, 12, 52, 20, 60, 28,
   35,  3, 43, 11, 51, 19, 59, 27,
   34,  2, 42, 10, 50, 18, 58, 26,
   33,  1, 41,  9, 49, 17, 57, 25
};

/*Expansion table */
static char E[] = {
   32,  1,  2,  3,  4,  5,
    4,  5,  6,  7,  8,  9,
    8,  9, 10, 11, 12, 13,
   12, 13, 14, 15, 16, 17,
   16, 17, 18, 19, 20, 21,
   20, 21, 22, 23, 24, 25,
   24, 25, 26, 27, 28, 29,
   28, 29, 30, 31, 32,  1
};

/* Post S-Box permutation */
static char P[] = {
   16,  7, 20, 21,
   29, 12, 28, 17,
    1, 15, 23, 26,
    5, 18, 31, 10,
    2,  8, 24, 14,
   32, 27,  3,  9,
   19, 13, 30,  6,
   22, 11,  4, 25
};

/* The S-Box tables */
static char S[8][64] = { {
        /* S1 */
        14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7,
         0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8,
         4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0,
        15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13
     },{
         /* S2 */
         15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10,
          3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5,
          0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15,
         13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9
      },{
          /* S3 */
          10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8,
          13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1,
          13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7,
           1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12
       },{
           /* S4 */
            7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15,
           13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9,
           10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4,
            3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14
        },{
            /* S5 */
             2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9,
            14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6,
             4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14,
            11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3
         },{
             /* S6 */
             12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11,
             10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8,
              9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6,
              4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13
          },{
              /* S7 */
               4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1,
              13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6,
               1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2,
               6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12
           },{
               /* S8 */
               13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7,
                1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2,
                7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8,
                2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11
            } };

/* Permuted Choice 1 Table */
static char PC1[] = {
   57, 49, 41, 33, 25, 17,  9,
    1, 58, 50, 42, 34, 26, 18,
   10,  2, 59, 51, 43, 35, 27,
   19, 11,  3, 60, 52, 44, 36,
   63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
   14,  6, 61, 53, 45, 37, 29,
   21, 13,  5, 28, 20, 12,  4
};

/* Permuted Choice 2 Table */
static char PC2[] = {
   14, 17, 11, 24,  1,  5,
    3, 28, 15,  6, 21, 10,
   23, 19, 12,  4, 26,  8,
   16,  7, 27, 20, 13,  2,
   41, 52, 31, 37, 47, 55,
   30, 40, 51, 45, 33, 48,
   44, 49, 39, 56, 34, 53,
   46, 42, 50, 36, 29, 32
};

/* Iteration Shift Array */
static char iteration_shift[] = {
    /* 1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16 */
       1,  1,  2,  2,  2,  2,  2,  2,  1,  2,  2,  2,  2,  2,  2,  1
};


void print_uint64_bytes(uint64_t num) {
    unsigned char* ptr = (unsigned char*)&num;
    for (int i = sizeof(uint64_t) - 1; i >= 0; i--) {
        printf("%02x ", ptr[i]);
    }
    printf("\n");
}

// LB64_MASK Permutation function
// input : 64 bit bitstring
// output : N bit permuted bitstring
uint64_t Permutation_64(uint64_t input, char table[], int N, int size) {
    uint64_t output = 0;
    for (int i = 0; i < N; i++) {
        output <<= 1; // 1비트 left shift
        output |= (input >> (size - table[i])) & LB64_MASK; // LSB 1비트 변경
    }
    return output;
}

// LB32_MASK Permutation function
// input : 32 bit bitstring
// output : 32 bit bitstring

uint32_t Permutation_32(uint32_t input, char table[], int N, int size) {
    uint32_t output = 0;
    for (int i = 0; i < N; i++) {
        output <<= 1;
        output |= (input >> (size - table[i])) & LB32_MASK;
    }
    return output;
}

// LB32_MASK Expansion function
// input : 32 bit bitstring
// output : N bit expanded bitstring
uint64_t Expansion_32(uint32_t input, char table[], int N, int size) {
    uint64_t output = 0;
    for (int i = 0; i < N; i++) {
        output <<= 1;
        output |= (uint64_t)((input >> (size - table[i])) & LB32_MASK);
    }
    return output;
}

// input : key
// output : sub_key[16]
void Key_scheduling(uint64_t sub_key[], uint64_t key) {
    // 28 비트 key schedule
    uint32_t C = 0;
    uint32_t D = 0;
    // 56 비트 key permuted choice
    uint64_t permuted_choice_1 = 0;
    uint64_t permuted_choice_2 = 0;

    // Permuted Choice 1
    permuted_choice_1 = Permutation_64(key, PC1, 56, 64);
    // C, D = 28bit, 7byte split
    C = (uint32_t)((permuted_choice_1 >> 28) & 0x000000000fffffff);
    D = (uint32_t)(permuted_choice_1 & 0x000000000fffffff);

    // Key Generation
    for (int i = 0; i < 16; i++) {
        // Left shift
        for (int j = 0; j < iteration_shift[i]; j++) {
            //Rotation shift
            C = 0x0fffffff & (C << 1) | 0x00000001 & (C >> 27);
            D = 0x0fffffff & (D << 1) | 0x00000001 & (D >> 27);
        }
        // Permuted Choice 2
        permuted_choice_2 = 0;
        permuted_choice_2 = (((uint64_t)C) << 28) | (uint64_t)D;
        sub_key[i] = 0;
        sub_key[i] = Permutation_64(permuted_choice_2, PC2, 48, 56);
    }
    return;
}

uint32_t Sbox(uint64_t s_input) {
    int row, column;
    uint32_t s_output = 0;

    for (int j = 0; j < 8; j++) {
        // 00 00 RCCC CR00 00 00 00 00 00 s_input
        // 00 00 1000 0100 00 00 00 00 00 row mask
        // 00 00 0111 1000 00 00 00 00 00 column mask

        row = (int)((s_input & (0x0000840000000000 >> 6 * j)) >> (42 - 6 * j));
        //output : 0x0......0100001
        row = (row >> 4) | (row & 0x01);
        //output : 0x0......0000011
        column = (int)((s_input & (0x0000780000000000 >> 6 * j)) >> (43 - 6 * j));

        s_output <<= 4;
        s_output |= (uint32_t)(S[j][16 * row + column] & 0x0000000f);
    }
    return s_output;
}

void Round(char mode, uint64_t key[], uint32_t* L, uint32_t* R) {
    uint32_t temp;
    uint32_t s_perm_res;
    uint64_t s_input;
    uint32_t s_output;

    // Round 1~15
    for (int i = 0; i < 16; i++) {
        temp = 0;
        s_perm_res = 0;

        // Expansion 32 to 48
        s_input = 0;
        s_input = Expansion_32(*R, E, 48, 32);

        if (mode == 'd') {
            // decryption
            s_input = s_input ^ key[15 - i];

        }
        else if (mode == 'e') {
            // encryption
            s_input = s_input ^ key[i];
        }

        // S-box
        s_output = Sbox(s_input);

        // S-box 이후 Permutation과정
        s_perm_res = Permutation_32(s_output, P, 32, 32);


        // L, R swap
        temp = *R;
        *R = *L ^ s_perm_res;
        *L = temp;
    }
    return;
}

uint64_t DES(uint64_t input, uint64_t key, char mode) {
    // 32 비트 plaintext split, round
    uint32_t L = 0;
    uint32_t R = 0;

    // 48 비트 key
    uint64_t sub_key[16] = { 0 };
    uint64_t s_input = 0;

    // 64 비트 IP / IIP / output
    uint64_t init_perm_res = 0;
    uint64_t inv_init_perm_res = 0;
    uint64_t LRmerge = 0;

    // IP 과정
    init_perm_res = Permutation_64(input, IP, 64, 64);

    // 32 비트씩 L, R로 split
    L = (uint32_t)(init_perm_res >> 32) & L64_MASK;
    R = (uint32_t)init_perm_res & L64_MASK;

    // Key Scheduling
    Key_scheduling(sub_key, key);

    //Round function
    Round(mode, sub_key, &L, &R);
    // L, R merge
    LRmerge = (((uint64_t)R) << 32) | (uint64_t)L;

    // IIP
    inv_init_perm_res = Permutation_64(LRmerge, IIP, 64, 64);

    return inv_init_perm_res;

}

int main() {

    // plaintext 입력
    FILE* fp = NULL;
    FILE* fp2 = NULL;
    uint64_t buffer[SIZE] = { 0, };
    uint64_t crypto[SIZE] = { 0, };
    uint64_t output[SIZE] = { 0, };
    char mode = 'e';
    // 암호화 or 복호화
    while (1) {
        printf("알고리즘 실행 모드를 입력해주세요.\n");
        printf("Encryption : e, Decryption : d\n");
        scanf_s("실행 모드:%c", &mode, 1);

        if (mode != 'e' && mode != 'd') {
            printf("다시 입력해주세요\n");
        }
        break;
    }
    
    // 문서 읽어오기
    if (!(fopen_s(&fp, "plaintext.txt", "rb"))) {
        int size = 0;
        while (feof(fp) == 0) {
            //fgets(buffer, sizeof(buffer), fp);
            fread((buffer + size), sizeof(uint64_t), 1, fp);
            size++;
        }
        for (int i = 0; i < size; i++) {
            printf("buffer[%d] : ", i);
            print_uint64_bytes(buffer[i]);
        }
        fclose(fp);
        
        // 64비트 평문으로 옮긴 후 DES 실행, buffer가 전부 빌때까지 반복
        uint64_t key = 0x9A9A9A9A12341234;
        uint64_t plaintext = 0;
        uint64_t ciphertext = 0;
        uint64_t decoded = 0;
        for (int j = 0; j < size; j++) {
            plaintext = 0;
            ciphertext = 0;
            plaintext |= buffer[j];
            printf("plaintext: ");
            print_uint64_bytes(plaintext);
            
            //DES 실행
            ciphertext = DES(plaintext, key, mode);
            printf("ciphertext : ");
            print_uint64_bytes(ciphertext);
            
            crypto[j] |= ciphertext;

            //DES decrypt
            decoded = DES(ciphertext, key, 'd');
            printf("decoded : ");
            print_uint64_bytes(decoded);

            output[j] |= decoded;

        }

        if (!(fopen_s(&fp, "ciphertext.txt", "wb"))) {
            //ciphertext array에서 ciphertext.txt로 쓰기
            fwrite(crypto, sizeof(uint64_t), size, fp);
            fclose(fp);
        }
        else {
            printf("error_ciphertext output\n");
            return 1;
        }
        if (!(fopen_s(&fp, "decoded.txt", "wb"))) {
            //output array에서 output.txt로 쓰기
            fwrite(output, sizeof(uint64_t), size, fp);
            fclose(fp);
        }
        else {
            printf("error_decoded output\n");
            return 1;
        }
        return 0;
    }
    else {
        printf("error_plaintext input\n");
        return 1;
    }

}
