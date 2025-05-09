#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Fungsi untuk membaca data dari file CSV
int read_csv(const char *file_path, double *x, double *y, int max_size) {
    FILE *file = fopen(file_path, "r");
    if (!file) {
        printf("Error: Tidak dapat membuka file %s\n", file_path);
        return -1;
    }

    int i = 0;
    while (fscanf(file, "%lf,%lf", &x[i], &y[i]) == 2 && i < max_size) {
        i++;
    }

    fclose(file);
    printf("Data berhasil dibaca. Total data: %d\n", i);
    return i;
}

// Fungsi untuk regresi linier sederhana
void linear_regression(double *x, double *y, int n, double *m, double *c) {
    double sum_x = 0, sum_y = 0, sum_xy = 0, sum_x2 = 0;

    for (int i = 0; i < n; i++) {
        sum_x += x[i];
        sum_y += y[i];
        sum_xy += x[i] * y[i];
        sum_x2 += x[i] * x[i];
    }

    *m = (n * sum_xy - sum_x * sum_y) / (n * sum_x2 - sum_x * sum_x);
    *c = (sum_y - (*m) * sum_x) / n;

    printf("Regresi linier selesai. m = %.2f, c = %.2f\n", *m, *c);
}

// Fungsi untuk interpolasi linier
double linear_interpolation(double x, double x1, double y1, double x2, double y2) {
    return y1 + (y2 - y1) * (x - x1) / (x2 - x1);
}

// Fungsi untuk menulis data hasil regresi/interpolasi ke file (untuk plotting)
void write_plot_data(const char *file_path, double *x, double *y, int n) {
    FILE *file = fopen(file_path, "w");
    if (!file) {
        printf("Error: Tidak dapat menulis ke file %s\n", file_path);
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(file, "%lf %lf\n", x[i], y[i]);
    }

    fclose(file);
    printf("Data berhasil ditulis ke file %s\n", file_path);
}

// Fungsi utama
int main() {
    const char *input_file = "data.csv"; // Ganti dengan path file CSV Anda
    const char *output_file = "output.dat"; // File untuk hasil plotting
    const int max_size = 100; // Maksimal jumlah data
    double x[max_size], y[max_size];
    double m, c;

    // Membaca data dari file CSV
    int n = read_csv(input_file, x, y, max_size);
    if (n <= 0) {
        return 1;
    }

    // Melakukan regresi linier
    linear_regression(x, y, n, &m, &c);

    // Menghitung nilai prediksi menggunakan regresi
    double y_fit[max_size];
    for (int i = 0; i < n; i++) {
        y_fit[i] = m * x[i] + c;
    }

    // Menulis data hasil regresi ke file
    write_plot_data(output_file, x, y_fit, n);

    // Contoh interpolasi linier
    double x_interp = (x[0] + x[1]) / 2; // Nilai x di antara dua titik pertama
    double y_interp = linear_interpolation(x_interp, x[0], y[0], x[1], y[1]);
    printf("Interpolasi pada x = %.2f: y = %.2f\n", x_interp, y_interp);

    printf("Program selesai. Gunakan file %s untuk visualisasi.\n", output_file);
    return 0;
}