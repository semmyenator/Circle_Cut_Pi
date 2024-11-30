#include <stdio.h>
#include <math.h>
#include <time.h>

#define NUM_ITERATIONS 32

// 動態生成 CORDIC 相位表
void initialize_cordic_phase(double *cordic_phase, int iterations) {
    for (int i = 0; i < iterations; i++) {
        cordic_phase[i] = atan(pow(2, -i)); // 計算 arctan(2^(-i))
    }
}

// 計算 CORDIC 增益值 K
double calculate_K(int iterations) {
    double K = 1.0;
    for (int i = 0; i < iterations; i++) {
        K *= 1 / sqrt(1 + pow(2, -2 * i)); // K = K * 1/sqrt(1 + 2^(-2i))
    }
    return K;
}

// 旋轉模式實現（計算 sin 和 cos）
void cordic_rotation(double theta, double *sin_val, double *cos_val, int iterations) {
    double cordic_phase[NUM_ITERATIONS];
    initialize_cordic_phase(cordic_phase, iterations); // 初始化相位表

    double K = calculate_K(iterations); // 計算 CORDIC 增益
    double current_cos = K;             // 初始向量 x = K
    double current_sin = 0.0;           // 初始向量 y = 0.0

    for (int j = 0; j < iterations; j++) {
        int sigma = (theta >= 0) ? 1 : -1; // 根據 theta 符號確定旋轉方向

        double cos_shift = current_cos / pow(2, j);
        double sin_shift = current_sin / pow(2, j);

        if (sigma == 1) {
            current_cos = current_cos - sin_shift; // 正旋轉
            current_sin = current_sin + cos_shift;
            theta = theta - cordic_phase[j];
        } else {
            current_cos = current_cos + sin_shift; // 反旋轉
            current_sin = current_sin - cos_shift;
            theta = theta + cordic_phase[j];
        }
    }

    // 輸出 sin 和 cos 的結果
    *sin_val = current_sin;
    *cos_val = current_cos;
}

int main() {
    // 設定所需精度和目標值
    const double target_precision = 1E-15; // 目標精度
    const double true_pi = M_PI;           // 標準圓周率值

    // 初始化變數
    double sin_val, cos_val;
    double theta = M_PI / 4; // 設定目標角度 θ = π/4

    // 計算開始時間
    clock_t start_time = clock();

    // 使用 CORDIC 演算法計算 sin(π/4) 和 cos(π/4)
    cordic_rotation(theta, &sin_val, &cos_val, NUM_ITERATIONS);

    // 反推圓周率 π
    double approx_pi = 0.0;
    if (cos_val != 0 && sin_val != 0) {
        approx_pi = 4 * atan(sin_val / cos_val); // 根據 tan(π/4) = 1，反推出 π
    }

    // 計算結束時間
    clock_t end_time = clock();
    double elapsed = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    // 輸出結果
    printf("Calculated sin(π/4): %.16f\n", sin_val);
    printf("Calculated cos(π/4): %.16f\n", cos_val);
    printf("Approximated π:      %.16f\n", approx_pi);
    printf("True π:             %.16f\n", true_pi);
    printf("Difference:         %.16f\n", fabs(approx_pi - true_pi));
    printf("Elapsed time:       %f seconds\n", elapsed);

    // 驗證精度
    if (fabs(approx_pi - true_pi) <= target_precision) {
        printf("The approximation meets the target precision of %.16f.\n", target_precision);
    } else {
        printf("The approximation does not meet the target precision of %.16f.\n", target_precision);
    }

    return 0;
}